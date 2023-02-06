#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>
#include <stdlib.h>

#include "util.h"

#define CS_VERT_PATH "./clip_space.vert"
#define SS_VERT_PATH "./screen_space.vert"
#define SIMPLE_FRAG_PATH "./simple.frag"
#define BACKGROUND_FRAG_PATH "./background.frag"

char *read_file(char *);
long file_size(char *);

#endif // FILE_H_
