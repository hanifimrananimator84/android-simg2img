#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define SPARSE_HEADER_MAGIC 0xed26ff3a

typedef struct sparse_header {
  unsigned int magic;
  unsigned short major_version;
  unsigned short minor_version;
  unsigned short file_hdr_sz;
  unsigned short chunk_hdr_sz;
  unsigned int block_sz;
  unsigned int total_blks;
  unsigned int total_chunks;
  unsigned int image_checksum;
} sparse_header_t;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <sparse_image> <raw_image>\n", argv[0]);
    exit(1);
  }

  // [Rest of original code...]
  printf("Conversion complete!\n");
  return 0;
}
