#pragma once


//#include "acme/prototype/geometry2d/point.h"
#include "acme/prototype/prototype/pointer.h"


class CLASS_DECL_ACME lparam
{
public:


   iptr             m_lparam;


   constexpr lparam(nullptr_t = nullptr) { m_lparam = 0; }

   template < prototype_integral INTEGRAL >
   constexpr lparam(INTEGRAL i) { m_lparam = (iptr)i; }
   template < prototype_size SIZE >
   constexpr lparam(const SIZE & size):lparam((int)size.cx, (int) size.cy) {}
   template < prototype_point POINT >
   constexpr lparam(const POINT & point);
   lparam(int x, int y) { m_lparam = make_unsigned_int(x, y); }


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


   constexpr lparam(const lparam & lparam)
   {

      m_lparam = lparam.m_lparam;

   }


   operator iptr &()
   {

      return m_lparam;

   }

   constexpr operator iptr () const
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
   constexpr T raw_cast() const
   {

      return (T) m_lparam;

   }


   constexpr lparam& operator = (const lparam & lparam)
   {

      m_lparam = lparam.m_lparam;

      return *this;

   }


   constexpr lparam& operator = (iptr lparam)
   {

      m_lparam = lparam;

      return *this;

   }


   constexpr short x() const
   {

      return ::lparam_int_x(m_lparam);

   }


   constexpr short y() const
   {

      return ::lparam_int_y(m_lparam);

   }

   constexpr ::int_point point() const;

};


//template < class T >
//   inline bool operator ==(lparam l, const pointer < T > & pointer) { return ((::subparticle *) l.m_lparam) == pointer.m_psubparticle; }
//
//
//template < class T >
//   inline bool operator !=(lparam l, const pointer < T > & pointer) { return ((::subparticle *) l.m_lparam) != pointer.m_psubparticle; }
//


