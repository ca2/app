#pragma once


#define MAKELONG(a, b)          ((::i32)(((::u16)(((::uptr)(a)) & 0xffff)) | ((::u32)((::u16)(((::uptr)(b)) & 0xffff))) << 16))
#define MAKELPARAM(l, h)        ((::lparam)(::uptr)(::u32)MAKELONG(l, h))


class CLASS_DECL_ACME lparam

{
public:


   iptr             m_lparam;


   lparam(std::nullptr_t = nullptr) { m_lparam = 0; }

   template < primitive_integral INTEGRAL >
   lparam(INTEGRAL i) { m_lparam = (iptr) i; }

   lparam(::i32 x, ::i32 y) { m_lparam = MAKELPARAM(x, y); }


   /// catching/receiving matter
   inline lparam(void * p) { m_lparam = (iptr)p;  }


   /// posting/sending matter
   lparam(const ::matter * pobject);


   /// posting/sending matter
   template < typename T >
   inline lparam(const __pointer(T) & p) : lparam((const ::matter *) p.m_p) { }



   lparam(const lparam & lparam)
   {

      m_lparam = lparam.m_lparam;

   }


   operator iptr &()
   {

      return m_lparam;

   }

   operator iptr () const
   {

      return m_lparam;

   }

   operator void * &()
   {

      return (void * &) m_lparam;

   }

   operator void * () const
   {

      return (void *) m_lparam;

   }



   template < typename T >
   T * cast() const
   {

      return (T *) m_lparam;

   }

   template < typename T >
   T scast() const
   {

      return (T) m_lparam;

   }


   lparam& operator = (const lparam & lparam)
   {

      m_lparam = lparam.m_lparam;

      return *this;

   }


   lparam& operator = (iptr lparam)
   {

      m_lparam = lparam;

      return *this;

   }


   inline short x() const
   {

      return (short) (m_lparam & 0xffff);

   }


   inline short y() const
   {

      return (short) ((m_lparam >> 16) & 0xffff);

   }


};



