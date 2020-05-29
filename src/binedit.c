#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  if (4 != argc) {
    printf("Usage: %s input_file offset patch_file\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char *input_file = argv[1];
  size_t offset = atoi(argv[2]);
  char *patch_file = argv[3];
  size_t patch_len;

  FILE *fp;
  struct stat fpstat;

  assert(-1 != stat(patch_file, &fpstat));
  char *patch_data = (char *) malloc(sizeof(char) * fpstat.st_size);
  assert(NULL != patch_data);
  patch_len = fpstat.st_size;
  fp = fopen(patch_file, "rb");
  assert(0 < fread(patch_data, fpstat.st_size, sizeof(char), fp));
  fclose(fp);

  assert(-1 != stat(input_file, &fpstat));
  char *buffer = (char *) malloc(sizeof(char) * fpstat.st_size);
  assert(NULL != buffer);
  fp = fopen(input_file, "rb");
  assert(0 < fread(buffer, fpstat.st_size, sizeof(char), fp));

  fwrite(buffer, offset, sizeof(char), stdout);
  fwrite(patch_data, patch_len, sizeof(char), stdout);
  fwrite(buffer + offset + patch_len, fpstat.st_size - offset - patch_len, sizeof(char), stdout);

  exit(EXIT_SUCCESS);
}
