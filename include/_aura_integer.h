#pragma once


using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;


using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;


using f32 = float;
using f64 = double;


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



