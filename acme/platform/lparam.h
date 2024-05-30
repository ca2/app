#pragma once


#include "acme/primitive/geometry2d/point.h"
#include "acme/primitive/primitive/pointer.h"


class CLASS_DECL_ACME lparam
{
public:


   iptr             m_lparam;


   lparam(std::nullptr_t = nullptr) { m_lparam = 0; }

   template < primitive_integral INTEGRAL >
   lparam(INTEGRAL i) { m_lparam = (iptr)i; }
   template < primitive_size SIZE >
   lparam(const SIZE & size):lparam((::i32)size.cx(), (::i32) size.cy()) {}
   template < primitive_point POINT >
   lparam(const POINT & point) : lparam((::i32)point.x(), (::i32)point.y()) {}
   lparam(::i32 x, ::i32 y) { m_lparam = make_u32(x, y); }


   /// catching/receiving subparticle
   inline lparam(void * p) { m_lparam = (iptr)p;  }


   /// posting/sending subparticle with referencing forking
   lparam(const ::subparticle * psubparticle);

#if REFERENCING_DEBUGGING

   /// posting/sending subparticle with referencing transfer
   lparam(::subparticle * psubparticle, ::reference_referer * preferer);

#endif

   /// posting/sending subparticle
   template < typename T >
   inline lparam(const pointer < T > & p) : lparam((const ::subparticle *) p.m_p) { }
   //template < typename T >
   //inline lparam(const ptr < T > & p) : lparam((const ::subparticle *) p.m_p) { }

   template < typename T >
   inline lparam(pointer < T > && p) : lparam(p.m_p REFDBG(, p.m_preferer)) { p.m_p = nullptr; p.m_psubparticle = nullptr; REFDBG(p.m_preferer = nullptr); }
   //template < typename T >
   //inline lparam(ptr < T > && p) : lparam(p.m_p REFDBG(, p.m_preferer)) { p.m_p = nullptr; REFDBG(p.m_preferer = nullptr); }


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

      return ::i32_x(m_lparam);

   }


   inline short y() const
   {

      return ::i32_y(m_lparam);

   }

   ::point_i32 point() const
   {
      
      return {(::i32) this->x(), (::i32) this->y()};
      
   }

};


//template < class T >
//   inline bool operator ==(lparam l, const pointer < T > & pointer) { return ((::subparticle *) l.m_lparam) == pointer.m_psubparticle; }
//
//
//template < class T >
//   inline bool operator !=(lparam l, const pointer < T > & pointer) { return ((::subparticle *) l.m_lparam) != pointer.m_psubparticle; }
//


