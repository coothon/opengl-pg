#include "file.h"

// Error: NULL.
char *read_file(char *path) {
	char *file_contents = NULL;
	FILE *fp;

	long path_file_size = file_size(path);
	if (path_file_size == -1L) return NULL;

	fp = fopen(path, "r");
	if (!fp) return NULL;

	file_contents = (char *)calloc(path_file_size, sizeof(char));
	if (!file_contents) {
		fclose(fp);
		return NULL;
	}

	fseek(fp, 0, SEEK_SET);
	for (long i = 0L; i < path_file_size; ++i) {
		int c = getc(fp);
		if (c == EOF) {
			file_contents[i] = 0;
			break;
		}

		file_contents[i] = (char)c;
	}

	fclose(fp);
	return file_contents;
}

// Error: -1L.
long file_size(char *path) {
	long total_size = 0L;
	long orig_seek = 0L;
	FILE *fp;

	fp = fopen(path, "r");
	if (!fp) return -1L;
	
	// Preserve original seek location to minimize undefined behaviour.
	orig_seek = ftell(fp);
	if (orig_seek == -1L) {
		fclose(fp);
		return -1L;
	}
	fseek(fp, 0, SEEK_END);
	total_size = ftell(fp);
	fseek(fp, orig_seek, SEEK_SET);

	fclose(fp);
	return total_size;
}
