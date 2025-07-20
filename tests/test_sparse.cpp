#include "test_helpers.h"
#include "sparse/sparse.h"
#include <gtest/gtest.h>

TEST(SparseTest, HeaderValidation) {
    const char* test_img = "test.sparse.img";
    create_test_image(test_img, 10); // 10MB test image
    
    FILE* f = sparse_fopen(test_img, "rb");
    sparse_header_t header;
    fread(&header, sizeof(header), 1, f);
    fclose(f);

    EXPECT_EQ(header.magic, SPARSE_HEADER_MAGIC);
    EXPECT_EQ(header.major_version, 1);
}

TEST(SparseTest, RoundtripConversion) {
    const char* raw_img = "test.raw.img";
    const char* sparse_img = "test.sparse.img";
    create_test_raw_image(raw_img, 5); // 5MB raw image

    ASSERT_EQ(raw_to_sparse(raw_img, sparse_img), SPARSE_OK);
    ASSERT_EQ(sparse_to_raw(sparse_img, "roundtrip.raw.img"), SPARSE_OK);
    
    EXPECT_TRUE(compare_files(raw_img, "roundtrip.raw.img"));
}
