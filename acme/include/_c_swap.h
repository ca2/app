#pragma once


#define lower_u8(x) ((x) & 0x00ff)

#define upper_u8(x) (((x) >> 8) & 0x00ff)

#define lower_u16(x) ((x) & 0x0000ffff)

#define upper_u16(x) (((x) >> 16) & 0x0000ffff)

#define make_u16(lower, upper) (((lower) & 0xff) | (((upper) << 8) & 0xff00))
#define make_u32(lower, upper) (((lower) & 0xffff) | (((upper) << 16) & 0xffff0000))

#define swap_u16(x)		make_u16(upper_u8(x), lower_u8(x))
#define swap_u32(x)		make_u32(swap_u16(upper_u16(x)), swap_u16(lower_u16(x)))



#define first_u16(u) ((u) & 0xffff)
#define second_u16(u) (((u) >> 16) & 0xffff)
#define first_i16(u) ((::i16)(((::i32)(u)) & 0xffff)) // signed first_u16 or at least should be designed to be signed
#define second_i16(u) ((::i16)((((::i32)(u)) >> 16) & 0xffff)) // signed second_u16 or at least should be designed to be signed
#define x_i16(u) first_i16(u)
#define y_i16(u) second_i16(u)
#define lower32_from64(u) ((u) & 0xffffffff)
#define upper32_from64(u) ((u >> 32) & 0xffffffff)



