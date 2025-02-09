// Created by camilo on 2023-11-25 21:15 <3ThomasBorregaardSorensen!!
#pragma once


#if REFERENCING_DEBUGGING


CLASS_DECL_ACME bool refdbg_add_top_track(::subparticle* pparticle);
CLASS_DECL_ACME void refdbg_erase_top_track(::subparticle* pparticle);


CLASS_DECL_ACME::subparticle* refdbg_get_track_allocation();
CLASS_DECL_ACME::reference_referer* refdbg_get_top_referer();
CLASS_DECL_ACME::reference_referer* refdbg_get_top_releaser();

CLASS_DECL_ACME void __check_refdbg


//#include "acme/platform/_c.h"
#include "acme/prototype/prototype/interlocked_count.h"
#include "acme/prototype/string/c_string.h"


CLASS_DECL_ACME long long new_reference_referer_serial();


class CLASS_DECL_ACME reference_referer
{
public:

   //bool                    m_bConstructor;
   //::subparticle *         m_psubparticleExisting;
   ::subparticle *         m_psubparticle;
   void *                  m_p;
   long long                   m_iSerial;
   ::c::string             m_cstringType;
   ::c::string             m_cstringFunctionName;
   ::c::string             m_cstringDebug;
   //::reference_referer *   m_preferencerefererNext = nullptr;

   static long long new_serial() { return new_reference_referer_serial(); }
   reference_referer(const char * pszType = nullptr, const char * pszFunctionName = nullptr, const char * pszDebug = nullptr) :
      //m_bConstructor(true),
      //m_psubparticleExisting(nullptr),
      m_psubparticle(nullptr),
      m_p(nullptr),
      m_cstringType(pszType),
      m_cstringFunctionName(pszFunctionName),
      m_cstringDebug(pszDebug),
      m_iSerial(new_serial())
   {
      common_construct();
   }
   reference_referer(const reference_referer & referer) :
      //m_bConstructor(referer.m_bConstructor),
      //m_psubparticleExisting(referer.m_psubparticleExisting),
      m_psubparticle(referer.m_psubparticle),
      m_cstringType(referer.m_cstringType),
      m_cstringFunctionName(referer.m_cstringFunctionName),
      m_cstringDebug(referer.m_cstringDebug),
      m_p(referer.m_p),
      m_iSerial(referer.m_iSerial)
   {
      common_construct();
   }
   reference_referer(reference_referer && referer) :
      //m_bConstructor(referer.m_bConstructor),
      //m_psubparticleExisting(referer.m_psubparticleExisting),
      m_psubparticle(referer.m_psubparticle),
      m_cstringType(::transfer(referer.m_cstringType)),
      m_cstringFunctionName(::transfer(referer.m_cstringFunctionName)),
      m_cstringDebug(::transfer(referer.m_cstringDebug)),
      m_p(referer.m_p),
      m_iSerial(referer.m_iSerial)
   {
      //referer.m_psubparticleExisting = nullptr;
      referer.m_psubparticle = nullptr;
      referer.m_p = nullptr;
      referer.m_iSerial = -1;
      //referer.m_preferencerefererNext = nullptr;
      common_construct();
   }
   template < primitive_subparticle A_SUBPARTICLE >
   //reference_referer(::subparticle * psubparticleExisting, A_SUBPARTICLE * pparticle, const char * pszFunctionName = nullptr, const char * pszDebug = nullptr) :
   reference_referer(A_SUBPARTICLE * pparticle, const char * pszFunctionName = nullptr, const char * pszDebug = nullptr) :
      //m_bConstructor(!psubparticleExisting),
      //m_psubparticleExisting(psubparticleExisting),
      m_psubparticle(pparticle),
      m_cstringType(typeid(*pparticle).name()),
      m_cstringFunctionName(pszFunctionName),
      m_cstringDebug(pszDebug),
      m_p(nullptr),
      m_iSerial(new_serial())
   {
      common_construct();
   }
   template < non_primitive_subparticle NON_SUBPARTICLE >
   //reference_referer(::subparticle * psubparticleExisting, NON_SUBPARTICLE * p, const char * pszFunctionName, const char * pszDebug = nullptr) :
   reference_referer(NON_SUBPARTICLE * p, const char * pszFunctionName, const char * pszDebug = nullptr) :
      //m_bConstructor(!psubparticleExisting),
      //m_psubparticleExisting(psubparticleExisting),
      m_psubparticle(nullptr),
      m_cstringType(typeid(*p).name()),
      m_cstringFunctionName(pszFunctionName),
      m_cstringDebug(pszDebug),
      m_p(p),
      m_iSerial(new_serial())
   {
      common_construct();
   }
   ~reference_referer()
   {
      destroy();
   }
   void destroy()
   {
      //m_bConstructor = false;
      m_p = nullptr;
      m_cstringType.destroy();
      m_cstringFunctionName.destroy();
      m_cstringDebug.destroy();
      m_psubparticle = nullptr;
      m_iSerial = -1;
   }
   bool operator ==(const reference_referer & referer) const
   {
      return m_iSerial == referer.m_iSerial;
   }
   void reset(const char * pszType = nullptr, const char * pszFunctionName = nullptr, const char * pszDebug = nullptr)
   {
      destroy();
      m_cstringType = pszType;
      m_cstringFunctionName = pszFunctionName;
      m_cstringDebug = pszDebug;
   }
   reference_referer & operator=(const reference_referer & referer)
   {
      if (this != &referer)
      {
         destroy();
         //m_bConstructor = referer.m_bConstructor;
         //m_psubparticleExisting = referer.m_psubparticleExisting;
         m_psubparticle = referer.m_psubparticle;
         m_cstringType = referer.m_cstringType;
         m_cstringFunctionName = referer.m_cstringFunctionName;
         m_cstringDebug = referer.m_cstringDebug;
         m_p = referer.m_p;
         m_iSerial = referer.m_iSerial;
         //m_preferencerefererNext = referer.m_preferencerefererNext;
      }
      return *this;
   }
   reference_referer & operator =(reference_referer && referer) noexcept
   {
      if (this != &referer)
      {
         destroy();
         //m_bConstructor = referer.m_bConstructor;
         //m_psubparticleExisting = referer.m_psubparticleExisting;
         m_psubparticle = referer.m_psubparticle;
         m_cstringType = ::transfer(referer.m_cstringType);
         m_cstringFunctionName = ::transfer(referer.m_cstringFunctionName);
         m_cstringDebug = ::transfer(referer.m_cstringDebug);
         //m_preferencerefererNext = referer.m_preferencerefererNext;
         m_p = referer.m_p;
         m_iSerial = referer.m_iSerial;
         //referer.m_bConstructor = false;
         //referer.m_psubparticleExisting = nullptr;
         referer.m_psubparticle = nullptr;
         referer.m_p = nullptr;
         referer.m_iSerial = -1;
         //referer.m_preferencerefererNext = nullptr;
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

   void common_construct();

};


#endif // REFERENCING_DEBUGGING



class __new_site
{
public:


#if REFERENCING_DEBUGGING


   ::reference_referer* m_preferer;


   __new_site(const ::reference_referer& referer, ::reference_referer** pprefererGet = nullptr)
   {

      ASSERT(!::allocator::is_suppressing_referencing_debugging());

      if (!::allocator::is_suppressing_referencing_debugging())
      {

         m_preferer = ::allocator::push_referer(referer);

         if (pprefererGet)
         {

            *pprefererGet = m_preferer;

         }

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
      
      
      p->on_after_construct(m_preferer);


#endif


      return p;


   }


   template < non_primitive_subparticle T >
   T * operator << (T * p)
   {


#if REFERENCING_DEBUGGING


//      p->on_after_construct(m_preferer);
      ::allocator::__on_after_construct_non_subparticle();


#endif


      return p;


   }

};



class __raw_new_site
{
public:


   bool        m_bOldSuppressingReferencingDebugging;


   __raw_new_site()
   {

#if REFERENCING_DEBUGGING

      m_bOldSuppressingReferencingDebugging = ::allocator::is_suppressing_referencing_debugging();

      if (!m_bOldSuppressingReferencingDebugging)
      {

         ::allocator::start_suppressing_referencing_debugging();

      }

#endif

   }


   template < primitive_subparticle T >
   T* operator << (T* p)
   {

#if REFERENCING_DEBUGGING

      if (!m_bOldSuppressingReferencingDebugging)
      {

         ::allocator::cease_referencing_debugging_suppression();

      }
      
      p->on_after_construct(nullptr);

#endif

      return p;

   }


   template < non_primitive_subparticle T >
   T* operator << (T* p)
   {

#if REFERENCING_DEBUGGING

      if (!m_bOldSuppressingReferencingDebugging)
      {

         ::allocator::cease_referencing_debugging_suppression();

      }

      ::allocator::__on_after_construct_non_subparticle();

#endif

      return p;

   }


};


class __new_refdbg_continuation_site
{
public:


#if REFERENCING_DEBUGGING

   ::reference_referer * m_preferencerefererTransferStack;

#endif


   __new_refdbg_continuation_site()
   {

#if REFERENCING_DEBUGGING

      if(::allocator::get_top_referer())
      {

         m_preferencerefererTransferStack = ::allocator::get_top_referer();

      }

#endif

   }


   template < primitive_subparticle T >
   T* operator << (T* p)
   {

#if REFERENCING_DEBUGGING

      p->on_after_construct(nullptr);

      p->m_prefererTransfer2 = m_preferencerefererTransferStack;

#endif

      return p;

   }


   template < non_primitive_subparticle T >
   T* operator << (T* p)
   {

#if REFERENCING_DEBUGGING

      ::allocator::__on_after_construct_non_subparticle();

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

