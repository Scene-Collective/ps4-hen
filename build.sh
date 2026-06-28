#!/bin/bash
set -e

# Only update/install if running as root AND on Ubuntu
# This is for the CI
# On your system you shouldn't be running as root and should already have these installed
if [ "$(id -u)" -eq 0 ] && grep -qi ubuntu /etc/os-release; then
  apt-get update
  apt-get install -y --no-install-recommends ca-certificates curl pigz unzip xxd
fi

pushd kpayload > /dev/null
make
popd > /dev/null

mkdir -p tmp
pushd tmp > /dev/null

# known bundled plugins
PRX_FILES="plugin_bootloader.prx plugin_loader.prx plugin_mono.prx plugin_server.prx plugin_shellcore.prx"

SKIP_DOWNLOAD=false
if [ -f plugins.zip ]; then
  SKIP_DOWNLOAD=true
else
  for prx in "${PRX_FILES[@]}"; do
    if [ -f "$prx" ]; then
      SKIP_DOWNLOAD=true
      break
    fi
  done
fi

if [ "$SKIP_DOWNLOAD" = false ]; then
  f="plugins.zip"
  rm -f $f
  curl -fLJO https://github.com/Scene-Collective/ps4-hen-plugins/releases/latest/download/$f
  unzip $f
fi

# need to use translation units to force rebuilds
# including as headers doesn't do it
for file in *.prx; do
  echo "$file"
  var_prefix="${file//./_}"

  # Check if file needs chunking (> 64KB uncompressed)
  uncompressed_size=$(stat -c%s "${file}")
  # 64 KiB chunk size (64 * 1024)
  chunk_size=$((64 * 1024))

  if [ "$uncompressed_size" -gt $chunk_size ]; then
    echo "File ${file} (${uncompressed_size} bytes) exceeds 64KB, chunking..."

    # Split uncompressed file into 64KB chunks with numeric suffixes
    split -b $chunk_size -d "${file}" "${file}.chunk_"

    {
      echo "#include <types.h>"
      echo ""

      echo "// Chunked file: ${file} (${uncompressed_size} bytes)"

      # Don't have clang-format try and mess with any of this
      echo ""
      echo "// clang-format off"
      echo ""

      echo "static const size_t ${var_prefix}_total_size = ${uncompressed_size};"

      # Count chunks (robust to special characters)
      chunk_count=$(find . -maxdepth 1 -name "${file}.chunk_*" -print | wc -l)
      echo "static const unsigned int ${var_prefix}_chunk_count = ${chunk_count};"
      echo ""
    } > "../installer/source/${file}.inc.c"

    # Process each chunk (robust to special characters, sorted)
    chunk_num=0
    find . -maxdepth 1 -name "${file}.chunk_*" -print0 | sort -z | while IFS= read -r -d '' chunk; do
      echo "Processing chunk ${chunk_num}..."

      # Compress this chunk
      pigz -9 -m -k -z "$chunk"

      # Add compressed chunk data to include file (strip leading ./ to avoid double underscores)
      # shellcheck disable=SC2094
      xxd -i "$(basename -- "${chunk}.zz")" < "${chunk}.zz" | sed 's/^unsigned /static const unsigned /' | sed 's/^ unsigned int / size_t /' | sed 's/_zz//g' >> "../installer/source/${file}.inc.c"
      echo "" >> "../installer/source/${file}.inc.c"

      # Clean up
      rm -f "${chunk}.zz"
      chunk_num=$((chunk_num + 1))
    done

    {
      # Create array of chunk pointers and sizes for easy access
      echo "static const unsigned char *${var_prefix}_chunks[] = {"
      for ((i=0; i<chunk_count; i++)); do
        if [ $i -eq $((chunk_count - 1)) ]; then
          echo "  ${var_prefix}_chunk_$(printf "%02d" $i)"
        else
          echo "  ${var_prefix}_chunk_$(printf "%02d" $i),"
        fi
      done
      echo "};"
      echo ""
      echo "static const size_t ${var_prefix}_chunk_lens[] = {"
      for ((i=0; i<chunk_count; i++)); do
        if [ $i -eq $((chunk_count - 1)) ]; then
          echo "  ${var_prefix}_chunk_$(printf "%02d" $i)_len"
        else
          echo "  ${var_prefix}_chunk_$(printf "%02d" $i)_len,"
        fi
      done
      echo "};"

      # Turn clang-format back on
      echo ""
      echo "// clang-format on"
    } >> "../installer/source/${file}.inc.c"

    # Clean up chunk files
    rm -f "${file}.chunk_"*

  else
    echo "File ${file} (${uncompressed_size} bytes) is small enough, no chunking needed"

    {
      echo "#include <types.h>"
      echo ""

      echo "// Non-chunked file: ${file} (${uncompressed_size} bytes)"

      # Don't have clang-format try and mess with any of this
      echo ""
      echo "// clang-format off"
      echo ""

      echo "static const size_t ${var_prefix}_total_size = ${uncompressed_size};"
      echo "static const unsigned int ${var_prefix}_chunk_count = 1;"
      echo ""
    } > "../installer/source/${file}.inc.c"

    pigz -9 -m -k -z "${file}"
    xxd -i "${file}.zz" | sed 's/^unsigned /static const unsigned /' | sed 's/^ unsigned int / size_t /' | sed 's/_zz//g' >> "../installer/source/${file}.inc.c"

    {
      # Add chunk pointer and length arrays for uniform access
      echo ""
      echo "static const unsigned char *${var_prefix}_chunks[] = {"
      echo "  ${var_prefix}"
      echo "};"
      echo ""
      echo "static const size_t ${var_prefix}_chunk_lens[] = {"
      echo "  ${var_prefix}_len"
      echo "};"

      # Turn clang-format back on
      echo ""
      echo "// clang-format on"
    } >> "../installer/source/${file}.inc.c"

    rm "${file}.zz"
  fi
done

popd > /dev/null

{
  # Don't have clang-format try and mess with any of this
  echo "// clang-format off"
  echo ""
} > "installer/source/hen.ini.inc.c"

xxd -i "hen.ini" | sed 's/^unsigned /static const unsigned /' | sed 's/^ unsigned int / size_t /' >> "installer/source/hen.ini.inc.c"

{
  # Turn clang-format back on
  echo ""
  echo "// clang-format on"
} >> "installer/source/hen.ini.inc.c"

pushd installer > /dev/null
make
popd > /dev/null

rm -f hen.bin
cp installer/installer.bin hen.bin
