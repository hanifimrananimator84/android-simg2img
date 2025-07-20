#ifndef ANDROID_SIMG2IMG_VERSION_H
#define ANDROID_SIMG2IMG_VERSION_H

#define SPARSEUTILS_VERSION_MAJOR 4
#define SPARSEUTILS_VERSION_MINOR 0
#define SPARSEUTILS_VERSION_PATCH 2

// Version string in "x.y.z" format
#define SPARSEUTILS_VERSION_STRING \
    STRINGIFY(SPARSEUTILS_VERSION_MAJOR) "." \
    STRINGIFY(SPARSEUTILS_VERSION_MINOR) "." \
    STRINGIFY(SPARSEUTILS_VERSION_PATCH)

// Helper macro for string conversion
#define STRINGIFY(x) #x

// API versioning for binary compatibility
#define SPARSEUTILS_API_VERSION 202400UL  // YYYYMM format
#define SPARSEUTILS_ABI_VERSION 1

// Feature flags
#define SPARSEUTILS_FEATURE_IMG_DISPLAY  0x01
#define SPARSEUTILS_FEATURE_FAST_CONVERT 0x02

// Version check macros
#define SPARSEUTILS_CHECK_VERSION(major, minor, patch) \
    (SPARSEUTILS_VERSION_MAJOR > (major) || \
    (SPARSEUTILS_VERSION_MAJOR == (major) && SPARSEUTILS_VERSION_MINOR >= (minor)) || \
    (SPARSEUTILS_VERSION_MAJOR == (major) && SPARSEUTILS_VERSION_MINOR == (minor) && \
     SPARSEUTILS_VERSION_PATCH >= (patch)))

#ifdef __cplusplus
namespace sparseutils {
constexpr int VERSION_MAJOR = SPARSEUTILS_VERSION_MAJOR;
constexpr int VERSION_MINOR = SPARSEUTILS_VERSION_MINOR;
constexpr int VERSION_PATCH = SPARSEUTILS_VERSION_PATCH;
constexpr const char* VERSION = SPARSEUTILS_VERSION_STRING;
} // namespace sparseutils
#endif

#endif // ANDROID_SIMG2IMG_VERSION_H
