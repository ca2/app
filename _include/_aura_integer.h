#pragma once


typedef  int8_t   i8;
typedef int16_t   i16;
typedef int32_t   i32;
typedef int64_t   i64;


typedef  uint8_t  u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;

typedef float     f32;
typedef double    f64;


#ifdef __cplusplus

template < typename TARGET, typename SOURCE >
TARGET throw_cast(SOURCE src)
{

   return (TARGET) src;

}

#endif



#define MAXI8 (127)
#define MINI8 (-128)
#define MAXU8 (255)

#define MAXI16	(32767)
#define MINI16 (-32768)
#define MAXU16	(65535)

#define MAXI32 (2147483647)
#define MINI32	(-2147483647 - 1)
#define MAXU32 (4294967295U)

#define MAXI64	(9223372036854775807L)
#define MINI64	(-9223372036854775807L - 1)
#define MAXU64	(18446744073709551615UL)



