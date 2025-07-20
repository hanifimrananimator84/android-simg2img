#include <sparse/sparse.h>
#include <sys/stat.h>

bool sparse_file_exists(const char* path) {
    struct stat st;
    return stat(path, &st) == 0;
}

uint64_t sparse_file_size(const char* path) {
    struct stat st;
    if (stat(path, &st) != 0) {
        return 0;
    }
    return st.st_size;
}

void* sparse_aligned_alloc(size_t alignment, size_t size) {
#ifdef _WIN32
    return _aligned_malloc(size, alignment);
#else
    void* ptr = nullptr;
    posix_memalign(&ptr, alignment, size);
    return ptr;
#endif
}