#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>

void usage(char *progname) {
  puts("binedit v0.2.0 Ali Raheem");
  puts("https://github.com/ali-raheem/binedit");
  printf("Usage: %s input_file offset [-f] patch\n", progname);
  exit(EXIT_FAILURE);
}

int parse(char *outBuffer, char *inBuffer) {
  int i, j;
  int len = strlen(inBuffer);
  i = 0;
  j = 0;
  while(i < len) {
    switch(inBuffer[i]) {
    case '\\':
      switch(inBuffer[++i]) {
      case '\\':
	outBuffer[j++] = inBuffer[i];
	break;
      case 'x':
	assert(1 == sscanf(inBuffer+i+1, "%2x", (uint *) &outBuffer[j++]));
	i += 2;
	break;
      default:
	printf("Error: Don't know what '\\%c' means.\n", inBuffer[i]);
	exit(EXIT_FAILURE);
      }
      break;
    default:
      outBuffer[j++] = inBuffer[i];
    }
    i++;
  }
  return j;
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
    patch_data = (char *) malloc(sizeof(char) * strlen(patch_file));
    assert(NULL != patch_data);
    patch_len = parse(patch_data, patch_file);
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
