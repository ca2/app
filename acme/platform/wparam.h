// From lparam.h by camilo on 2026-04-18 12:07 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/prototype/prototype/pointer.h"
#include "acme/platform/lparam.h"


class CLASS_DECL_ACME wparam
{
public:


   iptr             m_wparam;


   constexpr wparam(nullptr_t = nullptr) { m_wparam = 0; }

   template < prototype_integral_number INTEGRAL_NUMBER >
   constexpr wparam(INTEGRAL_NUMBER i) { m_wparam = (iptr)i; }
   template < prototype_size SIZE >
   constexpr wparam(const SIZE & size):wparam((int)size.cx, (int) size.cy) {}
   template < prototype_point POINT >
   constexpr wparam(const POINT & point);
   constexpr wparam(const lparam& lparam) { m_wparam = lparam.m_lparam; }
   wparam(int x, int y) { m_wparam = make_unsigned_int(x, y); }


   /// catching/receiving subparticle
   inline wparam(void * p) { m_wparam = (iptr)p;  }


   /// posting/sending subparticle with referencing forking
   wparam(const ::subparticle * psubparticle);

#if REFERENCING_DEBUGGING

   /// posting/sending subparticle with referencing transfer
   wparam(::subparticle * psubparticle, ::reference_referer * preferer);

#endif

   /// posting/sending subparticle
   template < typename T >
   inline wparam(const pointer < T > & p) : wparam((const ::subparticle *) p.m_p) { }
   //template < typename T >
   //inline wparam(const ptr < T > & p) : wparam((const ::subparticle *) p.m_p) { }

   template < typename T >
   inline wparam(pointer < T > && p) : wparam(p.m_p REFDBG(, p.m_preferer)) { p.m_p = nullptr; p.m_psubparticle = nullptr; REFDBG(p.m_preferer = nullptr); }
   //template < typename T >
   //inline wparam(ptr < T > && p) : wparam(p.m_p REFDBG(, p.m_preferer)) { p.m_p = nullptr; REFDBG(p.m_preferer = nullptr); }


   constexpr wparam(const wparam & wparam)
   {

      m_wparam = wparam.m_wparam;

   }


   operator iptr &()
   {

      return m_wparam;

   }

   constexpr operator iptr () const
   {

      return m_wparam;

   }

   operator void * &()
   {

      return (void * &) m_wparam;

   }

   operator void * () const
   {

      return (void *) m_wparam;

   }


   template < typename T >
   constexpr T raw_cast() const
   {

      return (T) m_wparam;

   }


   constexpr wparam& operator = (const wparam & wparam)
   {

      m_wparam = wparam.m_wparam;

      return *this;

   }


   constexpr wparam& operator = (iptr wparam)
   {

      m_wparam = wparam;

      return *this;

   }


   constexpr wparam &operator=(const lparam &lparam)
   {

      m_wparam = lparam.m_lparam;

      return *this;

   }


   constexpr short x() const
   {

      return ::iptr_int_x(m_wparam);

   }


   constexpr short y() const
   {

      return ::iptr_int_y(m_wparam);

   }

   constexpr short hiword() const { return __hiword(m_wparam); }
   constexpr short loword() const { return __loword(m_wparam); }

   constexpr ::int_point point() const;

};


//template < class T >
//   inline bool operator ==(wparam l, const pointer < T > & pointer) { return ((::subparticle *) l.m_wparam) == pointer.m_psubparticle; }
//
//
//template < class T >
//   inline bool operator !=(wparam l, const pointer < T > & pointer) { return ((::subparticle *) l.m_wparam) != pointer.m_psubparticle; }
//


constexpr lparam::lparam(const wparam& wparam)
{


   m_lparam = wparam.m_wparam;

}



