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


   /// catching/receiving particle
   inline lparam(void * p) { m_lparam = (iptr)p;  }


   /// posting/sending particle
   lparam(const ::particle * pelement);


   /// posting/sending particle
   template < typename T >
   inline lparam(const pointer < T > & p) : lparam((const ::particle *) p.m_p) { }
   template < typename T >
   inline lparam(const ptr < T > & p) : lparam((const ::particle *) p.m_p) { }

   template < typename T >
   inline lparam(pointer < T > && p) : m_lparam((iptr)(::particle *) p.m_p) { p.m_p = nullptr; p.m_pparticle = nullptr; }
   template < typename T >
   inline lparam(ptr < T > && p) : m_lparam((iptr)(::particle *) p.m_p) { p.m_p = nullptr; }


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
   inline bool operator ==(lparam l, const pointer < T > & pointer) { return ((::particle *) l.m_lparam) == pointer.m_pparticle; }


template < class T >
   inline bool operator !=(lparam l, const pointer < T > & pointer) { return ((::particle *) l.m_lparam) != pointer.m_pparticle; }



