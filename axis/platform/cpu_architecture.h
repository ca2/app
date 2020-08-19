/* CpuArch.h -- CPU specific code
2010-10-26: Igor Pavlov : Public domain */
// from 7-zip on 2012-12-23, dawn
#pragma once

#ifndef AURA_CPU_ARCHITECTURE_H
#define AURA_CPU_ARCHITECTURE_H

/*
MY_CPU_LE means that CPU is LITTLE ENDIAN.
If MY_CPU_LE is not defined, we don't know about that property of platform (it can be LITTLE ENDIAN).

MY_CPU_LE_UNALIGN means that CPU is LITTLE ENDIAN and CPU supports unaligned memory accesses.
If MY_CPU_LE_UNALIGN is not defined, we don't know about these properties of platform.
*/

#if defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)
#define MY_CPU_AMD64
#endif

#if defined(MY_CPU_AMD64) || defined(_M_IA64)
#define MY_CPU_64BIT
#endif

#if defined(_M_IX86) || defined(__i386__)
#define MY_CPU_X86
#endif

#if defined(MY_CPU_X86) || defined(MY_CPU_AMD64)
#define MY_CPU_X86_OR_AMD64
#endif

#if defined(MY_CPU_X86) || defined(_M_ARM)
#define MY_CPU_32BIT
#endif

#if defined(_WIN32) && defined(_M_ARM)
#define MY_CPU_ARM_LE
#endif

#if defined(_WIN32) && defined(_M_IA64)
#define MY_CPU_IA64_LE
#endif

#if defined(MY_CPU_X86_OR_AMD64)
#define MY_CPU_LE_UNALIGN
#endif

#if defined(MY_CPU_X86_OR_AMD64) || defined(MY_CPU_ARM_LE)  || defined(MY_CPU_IA64_LE) || defined(__ARMEL__) || defined(__MIPSEL__) || defined(__LITTLE_ENDIAN__)
#define MY_CPU_LE
#endif

#if defined(__BIG_ENDIAN__)
#define MY_CPU_BE
#endif

#if defined(MY_CPU_LE) && defined(MY_CPU_BE)
Stop_Compiling_Bad_Endian
#endif

#ifdef MY_CPU_LE_UNALIGN

#define GetUi16(point) (*(const u16 *)(point))
#define GetUi32(point) (*(const u32 *)(point))
#define GetUi64(point) (*(const u64 *)(point))
#define SetUi16(point, d) *(u16 *)(point) = (d);
#define SetUi32(point, d) *(u32 *)(point) = (d);
#define SetUi64(point, d) *(u64 *)(point) = (d);

#else

#define GetUi16(point) (((const u8 *)(point))[0] | ((u16)((const u8 *)(point))[1] << 8))

#define GetUi32(point) ( \
   ((const u8 *)(point))[0]        | \
   ((u32)((const u8 *)(point))[1] <<  8) | \
   ((u32)((const u8 *)(point))[2] << 16) | \
   ((u32)((const u8 *)(point))[3] << 24))

#define GetUi64(point) (GetUi32(point) | ((u64)GetUi32(((const u8 *)(point)) + 4) << 32))

#define SetUi16(point, d) { u32 _x_ = (d); \
   ((u8 *)(point))[0] = (byte)_x_; \
   ((u8 *)(point))[1] = (byte)(_x_ >> 8); }

#define SetUi32(point, d) { u32 _x_ = (d); \
   ((u8 *)(point))[0] = (byte)_x_; \
   ((u8 *)(point))[1] = (byte)(_x_ >> 8); \
   ((u8 *)(point))[2] = (byte)(_x_ >> 16); \
   ((u8 *)(point))[3] = (byte)(_x_ >> 24); }

#define SetUi64(point, d) { u64 _x64_ = (d); \
   SetUi32(point, (u32)_x64_); \
   SetUi32(((u8 *)(point)) + 4, (u32)(_x64_ >> 32)); }

#endif

#if defined(MY_CPU_LE_UNALIGN) && defined(_WIN64) && (_MSC_VER >= 1300)

//#pragma intrinsic(_byteswap_ulong)
//#pragma intrinsic(_byteswap_uint64)
#define GetBe32(point) _byteswap_ulong(*(const u32 *)(const u8 *)(point))
#define GetBe64(point) _byteswap_uint64(*(const u64 *)(const u8 *)(point))

#else

#define GetBe32(point) ( \
   ((u32)((const u8 *)(point))[0] << 24) | \
   ((u32)((const u8 *)(point))[1] << 16) | \
   ((u32)((const u8 *)(point))[2] <<  8) | \
   ((const u8 *)(point))[3] )

#define GetBe64(point) (((u64)GetBe32(point) << 32) | GetBe32(((const u8 *)(point)) + 4))

#endif

#define GetBe16(point) (((u16)((const u8 *)(point))[0] << 8) | ((const u8 *)(point))[1])


#ifdef MY_CPU_X86_OR_AMD64

struct Cx86cpuid
{
   u32 maxFunc;
   u32 vendor[3];
   u32 ver;
   u32 b;
   u32 c;
   u32 d;
};

enum
{
   CPU_FIRM_INTEL,
   CPU_FIRM_AMD,
   CPU_FIRM_VIA
};

CLASS_DECL_AURA i32 x86cpuid_CheckAndRead(struct Cx86cpuid *point);
CLASS_DECL_AURA i32 x86cpuid_GetFirm(const struct Cx86cpuid *point);

#define x86cpuid_GetFamily(point) (((point)->ver >> 8) & 0xFF00F)
#define x86cpuid_GetModel(point) (((point)->ver >> 4) & 0xF00F)
#define x86cpuid_GetStepping(point) ((point)->ver & 0xF)

CLASS_DECL_AURA i32 CPU_Is_InOrder(void);
CLASS_DECL_AURA i32 CPU_Is_Aes_Supported(void);


CLASS_DECL_AURA i32 cpu_has_avx(void);


#ifndef ANDROID

inline u16 __swap16gen(u16 x)
{
   return (((x) & 0xff) << 8) |(((x) & 0xff00) >> 8);
}

inline u32 __swap32gen(u32 x)
{
   return (((x) & 0xff) << 24 |
           ((x) & 0xff00) << 8 | ((x) & 0xff0000) >> 8 |
           ((x) & 0xff000000) >> 24);
}

#endif


/*
 * Define MD_SWAP if you provide __swap{16,32}md functions/macros that are
 * optimized for your architecture,  These will be used for __swap{16,32}
 * unless the argument is a constant and we are using GCC, where we can
 * take advantage of the CSE phase much better by using the generic version.
 */
#ifdef MD_SWAP
#if __GNUC__

#define swap16(x) ({							\
	u_int16_t __swap16_x = (x);					\
									\
	__builtin_constant_p(x) ? __swap16gen(__swap16_x) :		\
	    __swap16md(__swap16_x);					\
})

#define swap32(x) ({							\
	u_int32_t __swap32_x = (x);					\
									\
	__builtin_constant_p(x) ? __swap32gen(__swap32_x) :		\
	    __swap32md(__swap32_x);					\
})

#endif /* __GNUC__  */

#else /* MD_SWAP */
#define swap16 __swap16gen
#define swap32 __swap32gen
#endif /* MD_SWAP */





#ifndef BYTE_ORDER

#define LITTLE_ENDIAN	1234
#define BIG_ENDIAN	4321
#define PDP_ENDIAN	3412

#ifdef MY_CPU_LE
#define BYTE_ORDER LITTLE_ENDIAN
#endif // MY_CPU_LE

#ifdef MY_CPU_BE
#define BYTE_ORDER BIG_ENDIAN
#endif // MY_CPU_LE



#if BYTE_ORDER == LITTLE_ENDIAN

/* Can be overridden by machine/endian.h before inclusion of this file.  */
#ifndef _QUAD_HIGHWORD
#define _QUAD_HIGHWORD 1
#endif
#ifndef _QUAD_LOWWORD
#define _QUAD_LOWWORD 0
#endif

#ifndef ANDROID
#define htobe16 swap16
#define htobe32 swap32
#define betoh16 swap16
#define betoh32 swap32

#define htole16(x) (x)
#define htole32(x) (x)
#define letoh16(x) (x)
#define letoh32(x) (x)
#endif

#endif /* BYTE_ORDER */

#if BYTE_ORDER == BIG_ENDIAN

/* Can be overridden by machine/endian.h before inclusion of this file.  */
#ifndef _QUAD_HIGHWORD
#define _QUAD_HIGHWORD 0
#endif
#ifndef _QUAD_LOWWORD
#define _QUAD_LOWWORD 1
#endif

#define htole16 swap16
#define htole32 swap32
#define letoh16 swap16
#define letoh32 swap32

#define htobe16(x) (x)
#define htobe32(x) (x)
#define betoh16(x) (x)
#define betoh32(x) (x)

#endif /* BYTE_ORDER */


#endif




#endif


#endif // AURA_CPU_ARCHITECTURE_H
