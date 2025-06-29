#ifndef CONFIG_H_
#define CONFIG_H_

#define DEFAULT_EXPLOIT_FIXES 0
#define DEFAULT_MMAP_PATCHES 1
#define DEFAULT_BLOCK_UPDATES 1
#define DEFAULT_DISABLE_ASLR 1
#define DEFAULT_NOBD_PATCHES 0
#define DEFAULT_UPLOAD_PRX 1
#define TARGET_ID_SIZE 4 // eg. 0x84

typedef struct {
  int exploit_fixes;
  int mmap_patches;
  int block_updates;
  int disable_aslr;
  int nobd_patches;
  int upload_prx;
  char target_id[TARGET_ID_SIZE + 1]; // Add null term
} configuration;

int init_config(configuration *config);

#endif
