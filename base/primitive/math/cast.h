#pragma once



//#define __STR(xxx) #xxx
//#define __CONCAT(xxx, yyy) xxx ## yyy


template < typename TYPE >
class number_cast
{
public:


   TYPE      m_number;


   inline number_cast(__int64 i);
   inline number_cast(int i);

   operator TYPE() { return m_number; }

};


// using iptr_cast = number_cast <iptr>;
// below optimized specialization

class iptr_cast
{
public:


   iptr      m_number;


   inline iptr_cast(::i64 i);
   inline iptr_cast(::u64 u) :iptr_cast((::i64)(u)) {}
   inline iptr_cast(::i32 i) { m_number = (iptr)i;  }
   inline iptr_cast(::u32 u) { m_number = (iptr)u; }
#if defined(__APPLE__)
   inline iptr_cast(unsigned long u) { m_number = (iptr)u; }
#elif !defined(ANDROID) && !defined(_UWP) && !defined(WINDOWS) && !defined(RASPBIAN)
   inline iptr_cast(long long ll) { m_number = (iptr)ll; }
#endif

   operator iptr() { return  m_number; }

};

class i32_cast
{
public:


   i32      m_number;


   inline i32_cast(::i64 i);
   inline i32_cast(::u64 u) :i32_cast((::i64)(u)) {}
   inline i32_cast(::i32 i) { m_number = i; }
   inline i32_cast(::u32 u);

   operator i32() { return  m_number; }

};

class u32_cast
{
public:


   u32      m_number;


   inline u32_cast(::i64 i);
   inline u32_cast(::u64 u) :u32_cast((::i64)(u)) {}
   inline u32_cast(::i32 i);
   inline u32_cast(::u32 u) { m_number = u; }

   operator u32() { return  m_number; }

};

using index_cast = iptr_cast;
using count_cast = iptr_cast;


using memsize_cast = iptr_cast;
using strsize_cast = iptr_cast;


using LONG_cast = i32_cast;

using ULONG_cast = u32_cast;
using DWORD_cast = u32_cast;


#define __iptr(x) ((::iptr)(::iptr_cast)(x))

#define __index(x) ((::index)(::index_cast)(x))
#define __count(x) ((::count)(::count_cast)(x))

#define __memsize(x) ((::memsize)(::memsize_cast)(x))
#define __strsize(x) ((::strsize)(::strsize_cast)(x))

#define __LONG(x) ((LONG)(::i32_cast)(x))


