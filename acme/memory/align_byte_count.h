#ifdef __APPLE__


#define ALIGN_BYTE_COUNT (sizeof(size_t) * 2)


#else

//#define ALIGN_BYTE_COUNT (sizeof(size_t))


#define ALIGN_BYTE_COUNT 32 // AVX


#endif
