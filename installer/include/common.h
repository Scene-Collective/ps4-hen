#ifndef COMMON_H_
#define COMMON_H_

#include <types.h>

void write_blob(const char *path, const void *blob, const size_t blobsz);
const unsigned char *decompress_zlib(const unsigned char *zlib_data, size_t zlib_len, size_t *out_size);
const unsigned char *decompress_chunked_zlib(const unsigned char **chunk_ptrs, const size_t *chunk_lens, const size_t num_chunks, const size_t expected_decompressed_len);
int unchunk_decompress_and_write(const unsigned char **chunk_ptrs, const size_t *chunk_lens, const size_t num_chunks, const size_t expected_decompressed_len, const char *out_path);
void kill_proc(const char *proc);
void block_updates(void);

#endif
