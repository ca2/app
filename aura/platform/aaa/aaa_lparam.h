#pragma once




class CLASS_DECL_AURA lparam

{
public:


   LPARAM m_lparam;

   lparam(std::nullptr_t = nullptr) { m_lparam = 0; }

   lparam(i32 i) { m_lparam = (LPARAM) i; }

   lparam(i64 i) { m_lparam = (LPARAM) i; }


   /// catching/receiving object
   inline lparam(void * p) { m_lparam = (LPARAM)p;  }


   /// posting/sending object
   inline lparam(const ::particle * pparticle);


   /// posting/sending object
   template < typename T >
   inline lparam(const pointer < T > & p) : lparam((const ::object *) p.m_p) { }



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

      return i32_x(m_lparam);

   }


   inline int y() const
   {

      return i32_y(m_lparam);

   }


};



