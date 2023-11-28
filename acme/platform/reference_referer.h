// Created by camilo on 2023-11-25 21:15 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/_c.h"
#include "acme/primitive/string/c_string.h"


class CLASS_DECL_ACME reference_referer
{
public:


   ::particle *   m_pparticle;
   void *         m_p;
   ::c::string    m_cstringType;
   ::c::string    m_cstringDebug;

   reference_referer(const char * pszType = nullptr, const char * pszDebug = nullptr) :
      m_pparticle(nullptr),
      m_cstringType(::is_set(pszType) ? pszType : "(null)"),
      m_cstringDebug(::is_set(pszDebug) ? pszDebug : "(null)"),
      m_p(nullptr)
   {
      
   }
   reference_referer(const reference_referer & referer) :
      m_pparticle(referer.m_pparticle),
      m_cstringType(referer.m_cstringType),
      m_cstringDebug(referer.m_cstringDebug),
      m_p(referer.m_p)
   {
   }
   reference_referer(reference_referer && referer) :
      m_pparticle(referer.m_pparticle),
      m_cstringType(::transfer(referer.m_cstringType)),
      m_cstringDebug(::transfer(referer.m_cstringDebug)),
      m_p(referer.m_p)
   {
   }
   template < a_particle A_PARTICLE >
   reference_referer(A_PARTICLE * pparticle, const char * pszDebug = nullptr) :
      m_pparticle(pparticle),
      m_cstringType(typeid(*pparticle).name()),
      m_cstringDebug(::is_set(pszDebug) ? pszDebug : "(null)"),
      m_p(nullptr)
   {
   }
   template < non_particle NON_PARTICLE >
   reference_referer(NON_PARTICLE * p, const char * pszDebug = nullptr) :
      m_pparticle(nullptr),
      m_cstringType(typeid(*p).name()),
      m_cstringDebug(::is_set(pszDebug) ? pszDebug : "(null)"),
      m_p(p)
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
      m_pparticle = nullptr;

   }
   bool operator ==(const reference_referer & referer) const
   {
      return m_p == referer.m_p && m_pparticle == referer.m_pparticle;
   }
   void reset(const char * pszType = nullptr, const char * pszDebug = nullptr)
   {
      destroy();
      m_cstringType = ::is_set(pszType) ? pszType : "(null)";
      m_cstringDebug = ::is_set(pszDebug) ? pszDebug : "(null)";
   }
   reference_referer & operator=(const reference_referer & referer)
   {
      if (this != &referer)
      {
         destroy();
         m_pparticle = referer.m_pparticle;
         m_cstringType = referer.m_cstringType;
         m_cstringDebug = referer.m_cstringDebug;
         m_p = referer.m_p;
      }
      return *this;
   }
   reference_referer & operator =(reference_referer && referer) noexcept
   {
      if (this != &referer)
      {
         destroy();
         m_pparticle = referer.m_pparticle;
         m_cstringType = ::transfer(referer.m_cstringType);
         m_cstringDebug = ::transfer(referer.m_cstringDebug);
         m_p = referer.m_p;
      }
      return *this;
   }
   bool operator!() const
   {
      return m_p == nullptr && m_pparticle == nullptr;

   }
   explicit operator bool() const
   {
      return !this->operator!();
   }

};



