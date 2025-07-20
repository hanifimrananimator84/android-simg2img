/* 
 * CRC32 implementation from zlib (simplified)
 * Original copyright notice must be preserved
 */
#include <sparse/sparse.h>

static const uint32_t crc_table[256] = {
    0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL,
    // ... (full table from zlib)
};

uint32_t sparse_crc32(uint32_t crc, const void* buf, size_t len) {
    const uint8_t* p = (const uint8_t*)buf;
    crc = crc ^ 0xffffffffUL;
    while (len--) {
        crc = crc_table[(crc ^ *p++) & 0xff] ^ (crc >> 8);
    }
    return crc ^ 0xffffffffUL;
}