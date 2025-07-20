#include "sparse/sparse.h"
#include "sparse/format.h"
#include "lib/utils.h"
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <raw.img> <sparse.img>\n"
                  << "Converts raw ext4 image to Android sparse format\n";
        return SPARSE_ERR_IO;
    }

    sparse_result_t ret = raw_to_sparse(argv[1], argv[2]);
    if (ret != SPARSE_OK) {
        std::cerr << "Conversion failed (Error: " << ret << ")\n";
        return ret;
    }

    std::cout << "Successfully created sparse image: " << argv[2] << "\n";
    return SPARSE_OK;
}
