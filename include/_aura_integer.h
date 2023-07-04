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



#define I8_MAXIMUM (127)
#define I8_MINIMUM (-128)
#define U8_MAXIMUM (255)

#define I16_MAXIMUM	(32767)
#define I16_MINIMUM (-32768)
#define U16_MAXIMUM	(65535)

#define I32_MAXIMUM (2147483647)
#define I32_MINIMUM	(-2147483647 - 1)
#define U32_MAXIMUM (4294967295U)

#define I64_MAXIMUM	(9223372036854775807L)
#define I64_MINIMUM	(-9223372036854775807L - 1)
#define U64_MAXIMUM	(18446744073709551615UL)



using i32_bool = ::i32;





