#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include "../include/sparse/sparse.h"

void create_test_image(const char* path, int mb_size);
bool compare_files(const char* path1, const char* path2);

#endif
