#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>
#include <stdlib.h>

#include "util.h"

#define SIMPLE_VERT_PATH "./simple.vert"
#define SIMPLE_FRAG_PATH "./simple.frag"

char *read_file(char *);
long file_size(char *);

#endif // FILE_H_
