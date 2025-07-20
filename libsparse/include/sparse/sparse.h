#pragma once

typedef struct sparse_header {
    unsigned int magic;
    unsigned int total_blks;
    // Add other sparse format fields
} sparse_header_t;

int sparse_to_raw(const char* sparse_path, const char* raw_path);
int raw_to_sparse(const char* raw_path, const char* sparse_path);
