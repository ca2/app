// Created by camilo on 2023-11-25 21:15 <3ThomasBorregaardSorensen!!
#pragma once


#if REFERENCING_DEBUGGING



//#include "acme/platform/_c.h"
#include "acme/prototype/prototype/interlocked_count.h"
#include "acme/prototype/string/c_string.h"


CLASS_DECL_ACME::i64 new_reference_referer_serial();


class CLASS_DECL_ACME reference_referer
{
public:

   ::subparticle *      m_psubparticle;
   void *               m_p;
   ::i64                m_iSerial;
   ::c::string          m_cstringType;
   ::c::string          m_cstringDebug;

   static ::i64 new_serial() { return new_reference_referer_serial(); }
   reference_referer(const char * pszType = nullptr, const char * pszDebug = nullptr) :
      m_psubparticle(nullptr),
      m_p(nullptr),
      m_cstringType(pszType),
      m_cstringDebug(pszDebug),
      m_iSerial(new_serial())
   {
   }
   reference_referer(const reference_referer & referer) :
      m_psubparticle(referer.m_psubparticle),
      m_cstringType(referer.m_cstringType),
      m_cstringDebug(referer.m_cstringDebug),
      m_p(referer.m_p),
      m_iSerial(referer.m_iSerial)
   {
   }
   reference_referer(reference_referer && referer) :
      m_psubparticle(referer.m_psubparticle),
      m_cstringType(::transfer(referer.m_cstringType)),
      m_cstringDebug(::transfer(referer.m_cstringDebug)),
      m_p(referer.m_p),
      m_iSerial(referer.m_iSerial)
   {
      referer.m_psubparticle = nullptr;
      referer.m_p = nullptr;
      referer.m_iSerial = -1;
   }
   template < a_particle A_PARTICLE >
   reference_referer(A_PARTICLE * pparticle, const char * pszDebug = nullptr) :
      m_psubparticle(pparticle),
      m_cstringType(typeid(*pparticle).name()),
      m_cstringDebug(pszDebug),
      m_p(nullptr),
      m_iSerial(new_serial())
   {
   }
   template < non_particle NON_PARTICLE >
   reference_referer(NON_PARTICLE * p, const char * pszDebug = nullptr) :
      m_psubparticle(nullptr),
      m_cstringType(typeid(*p).name()),
      m_cstringDebug(pszDebug),
      m_p(p),
      m_iSerial(new_serial())
   {
   }
   ~reference_referer()
   {
      destroy();
   }
   void destroy()
   {
      m_p = nullptr;
      m_cstringType.destroy();
      m_cstringDebug.destroy();
      m_psubparticle = nullptr;
      m_iSerial = -1;
   }
   bool operator ==(const reference_referer & referer) const
   {
      return m_iSerial == referer.m_iSerial;
   }
   void reset(const char * pszType = nullptr, const char * pszDebug = nullptr)
   {
      destroy();
      m_cstringType = pszType;
      m_cstringDebug = pszDebug;
   }
   reference_referer & operator=(const reference_referer & referer)
   {
      if (this != &referer)
      {
         destroy();
         m_psubparticle = referer.m_psubparticle;
         m_cstringType = referer.m_cstringType;
         m_cstringDebug = referer.m_cstringDebug;
         m_p = referer.m_p;
         m_iSerial = referer.m_iSerial;
      }
      return *this;
   }
   reference_referer & operator =(reference_referer && referer) noexcept
   {
      if (this != &referer)
      {
         destroy();
         m_psubparticle = referer.m_psubparticle;
         m_cstringType = ::transfer(referer.m_cstringType);
         m_cstringDebug = ::transfer(referer.m_cstringDebug);
         m_p = referer.m_p;
         m_iSerial = referer.m_iSerial;
         referer.m_psubparticle = nullptr;
         referer.m_p = nullptr;
         referer.m_iSerial = -1;
      }
      return *this;
   }
   bool operator!() const
   {
      return m_p == nullptr && m_psubparticle == nullptr;

   }
   explicit operator bool() const
   {
      return !this->operator!();
   }

};


#endif // REFERENCING_DEBUGGING



class __new_site
{
public:


#if REFERENCING_DEBUGGING


   ::reference_referer* m_preferer;


   __new_site(const ::reference_referer& referer, ::reference_referer** pprefererGet = nullptr)
   {

      m_preferer = __raw_new reference_referer(referer);

      if (pprefererGet)
      {

         *pprefererGet = m_preferer;

      }

   }


#else


   __new_site()
   {


   }


#endif

   template < primitive_subparticle T >
   T* operator << (T* p)
   {
#if REFERENCING_DEBUGGING
      p->add_referer(m_preferer);
#endif
      return p;

   }

};


class __delete_site
{
public:

#if REFERENCING_DEBUGGING
   ::reference_referer* m_preferer;
   __delete_site(::reference_referer * preferer)
   {
      m_preferer = preferer;
   }
#else
   __delete_site()
   {
   }
#endif

   template < typename T >
   T* operator << (T* p)
   {
#if REFERENCING_DEBUGGING
      p->add_referer(m_preferer);
#endif
      return p;

   }

};

