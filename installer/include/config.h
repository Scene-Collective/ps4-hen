#ifndef CONFIG_H_
#define CONFIG_H_

#define TARGET_ID_SIZE 4 // eg. 0x84

struct configuration {
  int exploit_fixes;
  int mmap_patches;
  int block_updates;
  int disable_aslr;
  int nobd_patches;
  int upload_prx;
  char target_id[TARGET_ID_SIZE + 1]; // Add null term
};

int init_config(struct configuration *config);

#endif
