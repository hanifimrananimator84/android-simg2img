#include "../sparse/sparse.h"
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <sparse.img> <raw.img>\n";
        return 1;
    }
    return sparse_to_raw(argv[1], argv[2]);
}
