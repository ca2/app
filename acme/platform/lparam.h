#pragma once


class CLASS_DECL_ACME lparam
{
public:


   iptr             m_lparam;


   lparam(std::nullptr_t = nullptr) { m_lparam = 0; }

   template < primitive_integral INTEGRAL >
   lparam(INTEGRAL i) { m_lparam = (iptr)i; }
   template < primitive_size SIZE >
   lparam(const SIZE & size):lparam((::i32)size.cx, (::i32) size.cy) {}
   template < primitive_point POINT >
   lparam(const POINT & point) : lparam((::i32)point.x, (::i32)point.y) {}
   lparam(::i32 x, ::i32 y) { m_lparam = __MAKE_LPARAM(x, y); }


   /// catching/receiving element
   inline lparam(void * p) { m_lparam = (iptr)p;  }


   /// posting/sending element
   lparam(const ::element * pelement);


   /// posting/sending element
   template < typename T >
   inline lparam(const __pointer(T) & p) : lparam((const ::element *) p.m_p) { }



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
   __pointer(T) move()
   {

      auto p = ___pointer < T > ( e_move_transfer, (::element*)m_lparam );

      m_lparam = 0;

      return p;

   }


   template < typename T >
   T raw_cast() const
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



template < class T >
   inline bool operator ==(lparam l, const ___pointer < T > & pointer) { return ((T *) l) == pointer.m_p; }


template < class T >
   inline bool operator !=(lparam l, const ___pointer < T > & pointer) { return ((T *) l) != pointer.m_p; }



