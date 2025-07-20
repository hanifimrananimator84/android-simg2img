#include "test_helpers.h"
#include "lib/utils.h"
#include <gtest/gtest.h>

TEST(UtilsTest, CRC32Validation) {
    const char* test_file = "crc_test.bin";
    FILE* f = sparse_fopen(test_file, "wb");
    const char* data = "test crc32";
    fwrite(data, strlen(data), 1, f);
    fclose(f);

    uint32_t crc = sparse_crc32_file(test_file);
    EXPECT_EQ(crc, 0x178A48DF); // Precomputed CRC32
}

TEST(UtilsTest, EndianConversion) {
    uint32_t val = 0x12345678;
    uint32_t swapped = sparse_htole32(val);
    EXPECT_EQ(sparse_le32toh(swapped), val);
}
