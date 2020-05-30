#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>

void usage(char *progname) {
    printf("Usage: %s input_file offset [-f] patch_file\n", progname);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  if (4 > argc) {
    usage(argv[0]);
  }

  FILE *fp;
  struct stat fpstat;

  char *input_file = argv[1];
  size_t offset = atoi(argv[2]);
  char *patch_file = argv[3];
  char *patch_data;
  size_t patch_len;

  if (0 == strcmp(patch_file, "-f")) {
    if(5 != argc) {
      usage(argv[0]);
    }
    patch_file = argv[4];
    assert(-1 != stat(patch_file, &fpstat));
    patch_data = (char *) malloc(sizeof(char) * fpstat.st_size);
    assert(NULL != patch_data);
    patch_len = fpstat.st_size;
    fp = fopen(patch_file, "rb");
    assert(0 < fread(patch_data, fpstat.st_size, sizeof(char), fp));
    fclose(fp);
  } else {
    patch_data = patch_file;
    patch_len = strlen(patch_data);
  }


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
