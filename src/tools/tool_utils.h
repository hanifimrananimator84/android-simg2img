#ifndef TOOL_UTILS_H
#define TOOL_UTILS_H

#include "sparse/sparse.h"
#include <string>

class ProgressBar {
public:
    ProgressBar(size_t max) : max_(max) {}
    void update(size_t current);

private:
    size_t max_;
    const int bar_width_ = 50;
};

void print_chunk_stats(const sparse_header_t* header);
std::string humanize_size(size_t bytes);

#endif // TOOL_UTILS_H
