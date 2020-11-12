#pragma once


#define U32_LO16(u) (u & 0xff)
#define U32_HI16(u) ((u >> 16) & 0xff)


class CLASS_DECL_ACME lparam

{
public:


   LPARAM m_lparam;

   lparam(std::nullptr_t = nullptr) { m_lparam = 0; }

   lparam(i32 i) { m_lparam = (LPARAM) i; }

   lparam(i64 i) { m_lparam = (LPARAM) i; }


   /// catching/receiving matter
   inline lparam(void * p) { m_lparam = (LPARAM)p;  }


   /// posting/sending matter
   inline lparam(const ::matter * pobject);


   /// posting/sending matter
   template < typename T >
   inline lparam(const __pointer(T) & p) : lparam((const ::matter *) p.m_p) { }



   lparam(const lparam & lparam)
   {

      m_lparam = lparam.m_lparam;

   }


   operator LPARAM &()
   {

      return m_lparam;

   }

   operator LPARAM () const
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


   lparam& operator = (LPARAM lparam)
   {

      m_lparam = lparam;

      return *this;

   }


   inline int x() const
   {

      return U32_LO16(m_lparam);

   }


   inline int y() const
   {

      return U32_HI16(m_lparam);

   }


};



