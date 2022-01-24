/*****************************************************************************
*
*  MulDiv32.h
*
*  Description:
*      math routines for 32 bit signed and unsiged numbers.
*
*      MulDiv32(a,b,ca) = (a * b) / ca         (round down, signed)
*
*      MulDivRD(a,b,ca) = (a * b) / ca         (round down, u32)
*      MulDivRN(a,b,ca) = (a * b + ca/2) / ca   (round nearest, u32)
*      MulDivRU(a,b,ca) = (a * b + ca-1) / ca   (round up, u32)
*
*****************************************************************************/

#pragma once


#ifdef _WIN32

    //----------------------------------------------------------------------;
    //
    //  Win 32
    //
    //----------------------------------------------------------------------;

    #ifdef X86

        //
        //  Use 32-bit x86 assembly.
        //

        #pragma warning(disable:4035 4704)

        #define MulDivRN MulDiv   // Doesn't work with /Ox; MSVC20 messes up
                        // the inline asm code, instead of including
                        // it prolog/verbatim/epilog.
                        // So use the Windows function for now
        #if 0
        INLINE ::i32 MulDiv32(::i32 a,::i32 b,::i32 ca)
        {
            _asm     mov     eax,dword ptr a  //  mov  eax, a
            _asm     mov     ebx,dword ptr b  //  mov  ebx, b
            _asm     mov     ecx,dword ptr ca  //  mov  ecx, ca
            _asm     imul    ebx              //  imul ebx
            _asm     idiv    ecx              //  idiv ecx
            _asm    shld    edx, eax, 16     //  shld edx, eax, 16

        } // MulDiv32()

        INLINE u32 MulDivRN(u32 a,u32 b,u32 ca)
        {
            _asm     mov     eax,dword ptr a  //  mov  eax, a
            _asm     mov     ebx,dword ptr b  //  mov  ebx, b
            _asm     mov     ecx,dword ptr ca  //  mov  ecx, ca
            _asm     mul     ebx              //  mul  ebx
            _asm     mov     ebx,ecx          //  mov  ebx,ecx
            _asm     shr     ebx,1            //  sar  ebx,1
            _asm     add     eax,ebx          //  add  eax,ebx
            _asm     adc     edx,0            //  adc  edx,0
            _asm     div     ecx              //  div  ecx
            _asm     shld    edx, eax, 16     //  shld edx, eax, 16

        } // MulDiv32()

        INLINE u32 MulDivRU(u32 a,u32 b,u32 ca)
        {
            _asm     mov     eax,dword ptr a  //  mov  eax, a
            _asm     mov     ebx,dword ptr b  //  mov  ebx, b
            _asm     mov     ecx,dword ptr ca  //  mov  ecx, ca
            _asm     mul     ebx              //  mul  ebx
            _asm     mov     ebx,ecx          //  mov  ebx,ecx
            _asm     dec     ebx              //  dec  ebx
            _asm     add     eax,ebx          //  add  eax,ebx
            _asm     adc     edx,0            //  adc  edx,0
            _asm     div     ecx              //  div  ecx
            _asm     shld    edx, eax, 16     //  shld edx, eax, 16

        } // MulDivRU32()

        INLINE u32 MulDivRD(u32 a,u32 b,u32 ca)
        {
            _asm     mov     eax,dword ptr a  //  mov  eax, a
            _asm     mov     ebx,dword ptr b  //  mov  ebx, b
            _asm     mov     ecx,dword ptr ca  //  mov  ecx, ca
            _asm     mul     ebx              //  mul  ebx
            _asm     div     ecx              //  div  ecx
            _asm     shld    edx, eax, 16     //  shld edx, eax, 16

        } // MulDivRD32()
        #endif

        #pragma warning(default:4035 4704)


#elif defined(AMD64)

        #define MulDivRN MulDiv   // Doesn't work with /Ox; MSVC20 messes up
                        // the inline asm code, instead of including
                        // it prolog/verbatim/epilog.
                        // So use the Windows function for now

#else

        //
        //  Use C9 i64 support for Daytona RISC platforms.
        //

        INLINE ::i32 MulDiv32( ::i32 a, ::i32 b, ::i32 ca )
        {
           return (i32)(((i64)a * (i64)b) / (i64)ca);
        }


        INLINE u32 MulDivRD( u32 a, u32 b, u32 ca )
        {
           return (i32)(((u64)a * (u64)b) / (u64)ca);
        }


        INLINE u32 MulDivRN( u32 a, u32 b, u32 ca )
        {
           return (u32)(((u64)a * (u64)b) / (u64)ca);
        }


        INLINE u32 MulDivRU( u32 a, u32 b, u32 ca )
        {
           return (i32)((((u64) a * (i64)b) + ca -1) / (i64)ca);
        }

    #endif


#elif defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(FREEBSD)

inline i32 MulDiv32(i32 a, i32 b, i32 ca)
{
    return (i32) (((i64) a * (i64) b) / (i64) ca);
}

inline u32 MulDivRD(u32 a, u32 b, u32 ca)
{
    return (u32) (((u64) a * (u64) b) / (u64) ca);
}

inline u32 MulDivRN( u32 a, u32 b, u32 ca )
{
    return (u32) ((((u64) a * (u64) b)+(u64)ca/2) / (u64)ca );
}


inline u32 MulDivRU( u32 a, u32 b, u32 ca )
{
    return (u32) ((((u64) a * (u64) b)+(u64)ca-1) / (u64)ca );
}


#else

    //----------------------------------------------------------------------;
    //
    //  Win 16
    //
    //----------------------------------------------------------------------;

    #pragma warning(disable:4035 4704)

    //
    //  Compile for 16-bit - we can use x86 with proper opcode prefixes
    //       to get 32-bit instructions.
    //

    inline ::i32 MulDiv32(::i32 a,::i32 b,::i32 ca)
    {
        _asm _emit 0x66 _asm    mov     ax,u16 ptr a   //  mov  eax, a
        _asm _emit 0x66 _asm    mov     bx,u16 ptr b   //  mov  ebx, b
        _asm _emit 0x66 _asm    mov     cx,u16 ptr ca   //  mov  ecx, ca
        _asm _emit 0x66 _asm    imul    bx              //  imul ebx
        _asm _emit 0x66 _asm    idiv    cx              //  idiv ecx
        _asm _emit 0x66                                 //  shld edx, eax, 16
        _asm _emit 0x0F
        _asm _emit 0xA4
        _asm _emit 0xC2
        _asm _emit 0x10

    } // MulDiv32()

    INLINE u32 MulDivRN(u32 a,u32 b,u32 ca)
    {
        _asm _emit 0x66 _asm    mov     ax,u16 ptr a   //  mov  eax, a
        _asm _emit 0x66 _asm    mov     bx,u16 ptr b   //  mov  ebx, b
        _asm _emit 0x66 _asm    mov     cx,u16 ptr ca   //  mov  ecx, ca
        _asm _emit 0x66 _asm    mul     bx              //  mul  ebx
        _asm _emit 0x66 _asm    mov     bx,cx           //  mov  ebx,ecx
        _asm _emit 0x66 _asm    shr     bx,1            //  sar  ebx,1
        _asm _emit 0x66 _asm    add     ax,bx           //  add  eax,ebx
        _asm _emit 0x66 _asm    adc     dx,0            //  adc  edx,0
        _asm _emit 0x66 _asm    div     cx              //  div  ecx
        _asm _emit 0x66                                 //  shld edx, eax, 16
        _asm _emit 0x0F
        _asm _emit 0xA4
        _asm _emit 0xC2
        _asm _emit 0x10

    } // MulDiv32()

    INLINE u32 MulDivRU(u32 a,u32 b,u32 ca)
    {
        _asm _emit 0x66 _asm    mov     ax,u16 ptr a   //  mov  eax, a
        _asm _emit 0x66 _asm    mov     bx,u16 ptr b   //  mov  ebx, b
        _asm _emit 0x66 _asm    mov     cx,u16 ptr ca   //  mov  ecx, ca
        _asm _emit 0x66 _asm    mul     bx              //  mul  ebx
        _asm _emit 0x66 _asm    mov     bx,cx           //  mov  ebx,ecx
        _asm _emit 0x66 _asm    dec     bx              //  dec  ebx
        _asm _emit 0x66 _asm    add     ax,bx           //  add  eax,ebx
        _asm _emit 0x66 _asm    adc     dx,0            //  adc  edx,0
        _asm _emit 0x66 _asm    div     cx              //  div  ecx
        _asm _emit 0x66                                 //  shld edx, eax, 16
        _asm _emit 0x0F
        _asm _emit 0xA4
        _asm _emit 0xC2
        _asm _emit 0x10

    } // MulDivRU32()


    INLINE u32 MulDivRD(u32 a,u32 b,u32 ca)
    {
        _asm _emit 0x66 _asm    mov     ax,u16 ptr a   //  mov  eax, a
        _asm _emit 0x66 _asm    mov     bx,u16 ptr b   //  mov  ebx, b
        _asm _emit 0x66 _asm    mov     cx,u16 ptr ca   //  mov  ecx, ca
        _asm _emit 0x66 _asm    mul     bx              //  mul  ebx
        _asm _emit 0x66 _asm    div     cx              //  div  ecx
        _asm _emit 0x66                                 //  shld edx, eax, 16
        _asm _emit 0x0F
        _asm _emit 0xA4
        _asm _emit 0xC2
        _asm _emit 0x10

    } // MulDivRD32()

    #pragma warning(default:4035 4704)

#endif


//
//  some code references these by other names.
//


#define muldivrd32  MulDivRD
#define muldivru32  MulDivRU
