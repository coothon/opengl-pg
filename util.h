#ifndef UTIL_H_
#define UTIL_H_

#include <stdio.h>
#define GLFW_INCLUDE_NONE
#include "include/khrplatform.h"
#include "include/glad.h"
#include <GLFW/glfw3.h>

void glfw_error_cb(int, const char *);
void glfw_key_cb(GLFWwindow *, int, int, int, int);

#endif // UTIL_H_
