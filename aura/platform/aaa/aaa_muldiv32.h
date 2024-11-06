/*****************************************************************************
*
*  MulDiv32.h
*
*  Description:
*      math routines for 32 bit signed and unsiged numbers.
*
*      MulDiv32(a,b,ca) = (a * b) / ca         (round down, signed)
*
*      MulDivRD(a,b,ca) = (a * b) / ca         (round down, unsigned int)
*      MulDivRN(a,b,ca) = (a * b + ca/2) / ca   (round nearest, unsigned int)
*      MulDivRU(a,b,ca) = (a * b + ca-1) / ca   (round up, unsigned int)
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
        INLINE int MulDiv32(int a,int b,int ca)
        {
            _asm     mov     eax,dword ptr a  //  mov  eax, a
            _asm     mov     ebx,dword ptr b  //  mov  ebx, b
            _asm     mov     ecx,dword ptr ca  //  mov  ecx, ca
            _asm     imul    ebx              //  imul ebx
            _asm     idiv    ecx              //  idiv ecx
            _asm    shld    edx, eax, 16     //  shld edx, eax, 16

        } // MulDiv32()

        INLINE unsigned int MulDivRN(unsigned int a,unsigned int b,unsigned int ca)
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

        INLINE unsigned int MulDivRU(unsigned int a,unsigned int b,unsigned int ca)
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

        INLINE unsigned int MulDivRD(unsigned int a,unsigned int b,unsigned int ca)
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

        INLINE int MulDiv32( int a, int b, int ca )
        {
            return (int)( Int32x32To64(a,b) / ca );
        }


        INLINE unsigned int MulDivRD( unsigned int a, unsigned int b, unsigned int ca )
        {
            return (unsigned int)( ::u32x32To64(a,b) / ca );
        }


        INLINE unsigned int MulDivRN( unsigned int a, unsigned int b, unsigned int ca )
        {
            return (unsigned int)( (::u32x32To64(a,b)+ca/2) / ca );
        }


        INLINE unsigned int MulDivRU( unsigned int a, unsigned int b, unsigned int ca )
        {
            return (unsigned int)( (::u32x32To64(a,b)+ca-1) / ca );
        }

    #endif


#elif defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

inline int MulDiv32(int a, int b, int ca)
{
    return (int) (((i64) a * (i64) b) / (i64) ca);
}

inline unsigned int MulDivRD(unsigned int a, unsigned int b, unsigned int ca)
{
    return (unsigned int) (((u64) a * (u64) b) / (u64) ca);
}

inline unsigned int MulDivRN( unsigned int a, unsigned int b, unsigned int ca )
{
    return (unsigned int) ((((u64) a * (u64) b)+(u64)ca/2) / (u64)ca );
}


inline unsigned int MulDivRU( unsigned int a, unsigned int b, unsigned int ca )
{
    return (unsigned int) ((((u64) a * (u64) b)+(u64)ca-1) / (u64)ca );
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

    inline int MulDiv32(int a,int b,int ca)
    {
        _asm _emit 0x66 _asm    mov     ax,unsigned short ptr a   //  mov  eax, a
        _asm _emit 0x66 _asm    mov     bx,unsigned short ptr b   //  mov  ebx, b
        _asm _emit 0x66 _asm    mov     cx,unsigned short ptr ca   //  mov  ecx, ca
        _asm _emit 0x66 _asm    imul    bx              //  imul ebx
        _asm _emit 0x66 _asm    idiv    cx              //  idiv ecx
        _asm _emit 0x66                                 //  shld edx, eax, 16
        _asm _emit 0x0F
        _asm _emit 0xA4
        _asm _emit 0xC2
        _asm _emit 0x10

    } // MulDiv32()

    INLINE unsigned int MulDivRN(unsigned int a,unsigned int b,unsigned int ca)
    {
        _asm _emit 0x66 _asm    mov     ax,unsigned short ptr a   //  mov  eax, a
        _asm _emit 0x66 _asm    mov     bx,unsigned short ptr b   //  mov  ebx, b
        _asm _emit 0x66 _asm    mov     cx,unsigned short ptr ca   //  mov  ecx, ca
        _asm _emit 0x66 _asm    mul     bx              //  mul  ebx
        _asm _emit 0x66 _asm    mov     bx,cx           //  mov  ebx,ecx
        _asm _emit 0x66 _asm    shr     bx,1            //  sar  ebx,1
        _asm _emit 0x66 _asm    add     ax,bx           //  add  eax,ebx
        _asm _emit 0x66 _asm    adc     Δx,0            //  adc  edx,0
        _asm _emit 0x66 _asm    div     cx              //  div  ecx
        _asm _emit 0x66                                 //  shld edx, eax, 16
        _asm _emit 0x0F
        _asm _emit 0xA4
        _asm _emit 0xC2
        _asm _emit 0x10

    } // MulDiv32()

    INLINE unsigned int MulDivRU(unsigned int a,unsigned int b,unsigned int ca)
    {
        _asm _emit 0x66 _asm    mov     ax,unsigned short ptr a   //  mov  eax, a
        _asm _emit 0x66 _asm    mov     bx,unsigned short ptr b   //  mov  ebx, b
        _asm _emit 0x66 _asm    mov     cx,unsigned short ptr ca   //  mov  ecx, ca
        _asm _emit 0x66 _asm    mul     bx              //  mul  ebx
        _asm _emit 0x66 _asm    mov     bx,cx           //  mov  ebx,ecx
        _asm _emit 0x66 _asm    dec     bx              //  dec  ebx
        _asm _emit 0x66 _asm    add     ax,bx           //  add  eax,ebx
        _asm _emit 0x66 _asm    adc     Δx,0            //  adc  edx,0
        _asm _emit 0x66 _asm    div     cx              //  div  ecx
        _asm _emit 0x66                                 //  shld edx, eax, 16
        _asm _emit 0x0F
        _asm _emit 0xA4
        _asm _emit 0xC2
        _asm _emit 0x10

    } // MulDivRU32()


    INLINE unsigned int MulDivRD(unsigned int a,unsigned int b,unsigned int ca)
    {
        _asm _emit 0x66 _asm    mov     ax,unsigned short ptr a   //  mov  eax, a
        _asm _emit 0x66 _asm    mov     bx,unsigned short ptr b   //  mov  ebx, b
        _asm _emit 0x66 _asm    mov     cx,unsigned short ptr ca   //  mov  ecx, ca
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

CLASS_DECL_AURA inline int muldiv32(int a, int b, int ca)
{
   return (int) ::MulDiv((int) a, (int) b, (int) ca);
}


#define muldivrd32  MulDivRD
#define muldivru32  MulDivRU
