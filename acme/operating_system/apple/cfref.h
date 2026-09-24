//
//  cfref.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-06-18 07:45.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//  <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#pragma once

template < typename CFREF >
inline CFREF cfref_retain(CFREF cfref)
{
   
   ::CFRetain(cfref);
   
}


template < typename CFREF >
inline void cfref_release(CFREF cfref)
{
   
   ::CFRelease(cfref);
   
}

class ref_particle
{
public:
   
   virtual ~ref_particle()
   {
      
      release();
      
   }
   
   
   virtual CFTypeRef get_cf_type_ref()
   {
      
      return nullptr;
      
   }
   
   
   virtual CFTypeRef detach_cf_type_ref()
   {
      
      return nullptr;
      
   }

   
   virtual void retain()
   {
      
      
   }
   
   virtual void release()
   {
      
   }
   
};


//class ref_array;
//
//template < typename REF_BASE >
//class ref :
//virtual public ref_base
//{
//public:
//   
//   
//   using REF_BASE_TYPE = typename REF_BASE::REF_BASE_TYPE;
//   
//protected:
//   REF_BASE *m_prefbase;
//public:
//   
//   ref()
//   {
//      
//      m_prefbase=nullptr;
//      
//   }
//   
//   
//   ref(ref_array & refa, REF_BASE_TYPE refbasetype);
//   ref(const ref & rRef) :
//   ref((ref *) &rRef)
//   {
//      
//      
//   }
//protected:
//   ref(ref * pref):
//      m_prefbase(new REF_BASE(pref->m_prefbase->operator REF_BASE_TYPE()))
//   {
//      
//      m_bOwnReference = pref->m_bOwnReference;
//      
//      pref->m_bOwnReference= false;
//      
//   }
//public:
//   
//   ~ref()
//   {
//      
//      full_release();
//      
//   }
//   
//   
//   ref & operator = (const ref & r)
//   {
//      
//      if(&r != this && m_prefbase != r.m_prefbase && (!m_prefbase || !r.m_prefbase ||
//                                                      m_prefbase->operator REF_BASE_TYPE()
//         != r.m_prefbase->operator REF_BASE_TYPE()))
//      {
//         this->full_release();
//         m_prefbase = new REF_BASE(r.m_prefbase->operator REF_BASE_TYPE());
//         m_bOwnReference = false;
//      }
//      return *this;
//   }
//   ref & operator = (REF_BASE_TYPE refbasetype)
//   {
//      this->full_release();
//      m_prefbase = new REF_BASE(refbasetype);
//      m_bOwnReference = true;
//      return *this;
//   }
//
////   cfref(CFREF cfref)
////   {
////      
////      m_cfref = cfref;
////      
////   }
////   cfref(ref_array & refa, CFREF cfref)
////   {
////      
////      m_cfref = cfref;
////      
////      refa << *this;
////      
////   }
////
////
////   ~cfref()
////   {
////    
////   }
////   
//   bool operator!() const {return m_prefbase == nullptr;}
//   
//   ref * clone()
//   {
//      
//      return new ref(this);
//   }
////   void release() override
////   {
////      
////      if(!m_cfref)
////      {
////         
////         return;
////         
////      }
////      
////      auto cfref = m_cfref;
////      
////      m_cfref = nullptr;
////      
////      t_functionRelease(cfref);
////      
////   }
//   
////   
////   operator CFREF()
////   {
////    
////      return m_cfref;
////      
////   }
////      
////   
//
//   void release_base()
//   {
//      
//      if(m_prefbase)
//      {
//         
//         if(m_bOwnReference)
//         {
//            
//            m_bOwnReference = false;
//            
//            m_prefbase->release();
//            
//         }
//         
//      }
//      
//   }
//
//   void full_release()
//   {
//      
//      if(m_prefbase)
//      {
//         
//         if(m_bOwnReference)
//         {
//            
//            m_bOwnReference = false;
//            
//            m_prefbase->release();
//            
//         }
//         
//         delete m_prefbase;
//         
//         m_prefbase = nullptr;
//         
//      }
//      
//   }
//
//   void set(ref_array & refa, REF_BASE_TYPE refbasetype);
//   operator REF_BASE_TYPE()
//   {
//      if(::is_null(m_prefbase))
//      {
//         
//         return nullptr;
//         
//      }
//      return m_prefbase->operator REF_BASE_TYPE();
//      
//   }
//   
//};
//
//class ref_array
//{
//protected:
//   ::array_base<ref_base * > m_refbaseptra;
//public:
//   bool m_bAutoRelease;
//   ref_array(bool bAutoRelease = true):
//   m_bAutoRelease(bAutoRelease)
//   {
//      
//   }
//   ~ref_array()
//   {
//      if(m_bAutoRelease)
//      {
//         release();
//      }
//   }
//   void release()
//   {
//      for(auto prefbase :  m_refbaseptra)
//      {
//         
//         if(::is_set(prefbase))
//         {
//            
//            try
//            {
//            
//               prefbase->release_base();
//               
//            }
//            catch (...)
//            {
//                  
//            }
//            
//            delete prefbase;
//            
//         }
//         
//      }
//      m_refbaseptra.clear();
//   }
//
//   template < typename REF >
//   void add(REF * pref)
//   {
//      m_refbaseptra.add(pref->clone());
//   }
//
//};
//template < typename REF_BASE >
//ref<REF_BASE>::ref(ref_array & refa, REF_BASE_TYPE refbasetype)
//{
//   m_prefbase =new REF_BASE(refbasetype);
//   m_bOwnReference = true;
//   refa.add(this);
//   
//   
//}
//template < typename REF_BASE >
//void ref<REF_BASE>::set(ref_array & refa, REF_BASE_TYPE refbasetype)
//{
//   full_release();
//   m_prefbase =new REF_BASE(refbasetype);
//   m_bOwnReference = true;
//   refa.add(this);
//   
//   
//}
template < typename CFREF = CFTypeRef >
class cfref_particle :
   virtual public ref_particle
{
public:
   

   using REF_BASE_TYPE = CFREF;
   

   CFREF      m_cfref;
   
   
   inline static CFREF (* g_functionRetain)(CFREF) = ::cfref_retain < CFREF >;
   inline static void (* g_functionRelease)(CFREF) = ::cfref_release < CFREF >;
   

   cfref_particle()
   {
      
      m_cfref = nullptr;
      
   }

   
   cfref_particle(transfer_t, CFREF cfref):
      m_cfref(cfref)
   {
   
      
   }
   

   cfref_particle(CFREF cfref):
      m_cfref(cfref)
   {
      
      g_functionRetain(cfref);
      
   }
   
   
   cfref_particle(const cfref_particle & r):
      m_cfref(r.m_cfref)
   {
      
      g_functionRetain(m_cfref);
      
   }

   
   cfref_particle(cfref_particle && r):
      m_cfref(r.m_cfref)
   {
      
      r.m_cfref = nullptr;
      
   }
   
   ~cfref_particle()
   {
      
      release();
      
   }
   
   
   void retain() override
   {
      
      if(m_cfref)
      {
         
         g_functionRetain(m_cfref);
         
      }

   }

   
   void release() override
   {
      
      if(m_cfref)
      {
         
         auto cfref = m_cfref;
         
         m_cfref=nullptr;
         
         g_functionRelease(cfref);
         
      }
      
   }
   
   CFTypeRef get_cf_type_ref() override
   {
      
      return m_cfref;
      
   }

   
   CFTypeRef detach_cf_type_ref() override
   {
      
      auto r = m_cfref;
      
      m_cfref = nullptr;
      
      return r;
      
   }

   operator REF_BASE_TYPE() {return m_cfref;}
   
};


//template < typename CFREF = CFTypeRef, void (* t_functionRetain)(CFREF) = ::cfref_default_retain < CFREF >,
//void (* t_functionRelease)(CFREF) = ::cfref_default_release < CFREF > >
//class cfref :
//public ::ref < cfref_base < CFREF, t_functionRelease > >
//{
//public:
//   
//   using REF = ::ref < cfref_base < CFREF, t_functionRelease > >;
//   
//   using REF::REF;
//   
//   using REF::operator=;
//   
//};
//

class ref_base
{
public:
   
   
   ref_particle * m_p;
   
   ref_base()
   {
      
      m_p = nullptr;
      
   }
   
   ref_base(ref_particle * p)
   {
      
      m_p = p;
      
   }

   ref_base(transfer_t, ref_particle * p)
   {
      
      m_p = p;
      
   }

   ref_base(const ref_base & refbase) :
      m_p(((ref_base &) refbase).retained())
   {

   }

   
   ref_base(ref_base && refbase) :
      m_p(refbase.m_p)
   {
      
      refbase.m_p = nullptr;
      
   }
   
   template < typename CFREF >
   ref_base(const ::cfref_particle < CFREF > & r)
   {
      
      m_p = new ::cfref_particle<CFREF>(r.m_p);
      
   }

   
   ~ref_base()
   {
      
      release();
      
   }
   
  
   virtual void release()
   {
      
        if(m_p)
        {
         
           auto p = m_p;
           
           m_p = nullptr;
           
           delete p;
           
        }
        
      
   }
   
   virtual ref_particle * retained()
   {
      
      throw ::interface_only();
      
   }
   
   bool operator!() const {return m_p == nullptr;}

};


//class ref_array;
//
template < typename CFREF >
class ref :
virtual public ref_base
{
public:


   using REF_BASE_TYPE = typename CFREF::REF_BASE_TYPE;

//protected:
   //REF_BASE *m_prefbase;
//public:

   ref()
   {

   }

   ref(CFREF * p) :
   ref_base(p)
   {
   
   }

   ref(transfer_t, CFREF * p) :
   ref_base(transfer_t{}, p)
   {
      
   }

   ref(REF_BASE_TYPE r) :
   ref_base(transfer_t{}, new CFREF(r))
   {
      
   }

   
   ref(const ref & r) :
      ref_base(new CFREF(r))
   {
      
   }

   ref(ref && r) :
      ref_base(transfer_t{}, r.m_p)
   {
      
      r.m_p = nullptr;
      
   }
   
   ~ref()
   {
    
   }


   ref & operator = (const ref & r)
   {
      
      if(r.m_p != m_p)
      {
         
         release();
         
         m_p = new CFREF(r);
        
      }

      return *this;
      
   }

   
   ref & operator = (CFREF * pcfref)
   {
      
      release();

      m_p = new CFREF(pcfref);
   
      return *this;
      
   }
   

   ref & operator = (REF_BASE_TYPE refbasetype)
   {
      
      release();
      
      m_p = new CFREF(transfer_t{}, refbasetype);

      return *this;
      
   }

//   cfref(CFREF cfref)
//   {
//
//      m_cfref = cfref;
//
//   }
//   cfref(ref_array & refa, CFREF cfref)
//   {
//
//      m_cfref = cfref;
//
//      refa << *this;
//
//   }
//
//
//   ~cfref()
//   {
//
//   }
//

//   ref * clone()
//   {
//
//      return new ref(this);
//   }
//   void release() override
//   {
//
//      if(!m_cfref)
//      {
//
//         return;
//
//      }
//
//      auto cfref = m_cfref;
//
//      m_cfref = nullptr;
//
//      t_functionRelease(cfref);
//
//   }

//
//   operator CFREF()
//   {
//
//      return m_cfref;
//
//   }
//
//

//   void release_base()
//   {
//
//      if(m_prefbase)
//      {
//
//         if(m_bOwnReference)
//         {
//
//            m_bOwnReference = false;
//
//            m_prefbase->release();
//
//         }
//
//      }
//
//   }
//
//   void full_release()
//   {
//
//      if(m_prefbase)
//      {
//
//         if(m_bOwnReference)
//         {
//
//            m_bOwnReference = false;
//
//            m_prefbase->release();
//
//         }
//
//         delete m_prefbase;
//
//         m_prefbase = nullptr;
//
//      }
//
//   }

   //void set(ref_array & refa, REF_BASE_TYPE refbasetype);
   operator REF_BASE_TYPE()
   {
      if(::is_null(m_p))
      {

         return nullptr;

      }
      return (REF_BASE_TYPE) m_p->get_cf_type_ref();

   }
   operator REF_BASE_TYPE() const
   {
      if(::is_null(m_p))
      {

         return nullptr;

      }
      return (REF_BASE_TYPE) ((ref_particle *) m_p)->get_cf_type_ref();

   }
   
   virtual ref_particle * retained()
   {
      
      if(::is_null(m_p))
      {
         
         return nullptr;
         
      }
      
      auto p = new CFREF((REF_BASE_TYPE)m_p->get_cf_type_ref());
      
      p->retain();
      
      return p;
      
   }
   
   
   virtual REF_BASE_TYPE detach()
   {
      
      if(::is_null(m_p))
      {
         
         return nullptr;
         
      }
      
      auto r = (REF_BASE_TYPE)m_p->detach_cf_type_ref();
    
      auto p = m_p;
      
      m_p = nullptr;
      
      delete p;
      
      return r;
      
   }
   
   
};


template <typename T>
class ref;

template <typename T>
struct is_ref : std::false_type
{
};

template <typename T>
struct is_ref<ref<T>> : std::true_type
{
};

template <typename T>
inline constexpr bool is_ref_v =
   is_ref<std::remove_cvref_t<T>>::value;

template <typename T>
concept not_ref = !is_ref_v<T>;


//
//class ref_array
//{
//protected:
//   ::array_base<ref_base * > m_refbaseptra;
//public:
//   bool m_bAutoRelease;
//   ref_array(bool bAutoRelease = true):
//   m_bAutoRelease(bAutoRelease)
//   {
//
//   }
//   ~ref_array()
//   {
//      if(m_bAutoRelease)
//      {
//         release();
//      }
//   }
//   void release()
//   {
//      for(auto prefbase :  m_refbaseptra)
//      {
//
//         if(::is_set(prefbase))
//         {
//
//            try
//            {
//
//               prefbase->release_base();
//
//            }
//            catch (...)
//            {
//
//            }
//
//            delete prefbase;
//
//         }
//
//      }
//      m_refbaseptra.clear();
//   }
//
//   template < typename REF >
//   void add(REF * pref)
//   {
//      m_refbaseptra.add(pref->clone());
//   }
//
//};
//template < typename REF_BASE >
//ref<REF_BASE>::ref(ref_array & refa, REF_BASE_TYPE refbasetype)
//{
//   m_prefbase =new REF_BASE(refbasetype);
//   m_bOwnReference = true;
//   refa.add(this);
//
//
//}
//template < typename REF_BASE >
//void ref<REF_BASE>::set(ref_array & refa, REF_BASE_TYPE refbasetype)
//{
//   full_release();
//   m_prefbase =new REF_BASE(refbasetype);
//   m_bOwnReference = true;
//   refa.add(this);
//
//
//}




//template < >
//inline auto cftransfer<CFNumberRef>(CFNumberRef cfnumberref)
//{
//   
//   return ::ref <::cftyperef> {transfer_t{}, new ::cftyperef(cfnumberref)};
//   
//}
//
//template < >
//inline auto cftransfer<CFDictionaryRef>(CFDictionaryRef cfdictionaryref)
//{
//   
//   return ::ref <::cftyperef> {transfer_t{}, new ::cftyperef(cfdictionaryref)};
//   
//}
//
//template < >
//inline auto cftransfer<CFAttributedStringRef>(CFAttributedStringRef cfattributedstringref)
//{
//   
//   return ::ref <::cftyperef> {transfer_t{}, new ::cftyperef(cfattributedstringref)};
//   
//}


template < typename CFREF >
using cfref = ::ref<::cfref_particle<CFREF>>;

using cftyperef = cfref < CFTypeRef >;


template < typename CFREF >
auto as_cfref(CFREF cfref)
{
   
   return ::cfref < CFREF > {transfer_t{}, new ::cfref_particle<CFREF>(cfref)};
   
}

using ref_array = ::array < ::ref_base >;


class cf_array :
   virtual public ref_array
{
public:
   
   ::array < const void * > m_voidptra;
   
   cf_array(){}
   ~cf_array(){}
   
   
   template < typename CFREF >
   void add(const ::ref<::cfref_particle<CFREF>> & r)
   {
      
      ::ref_array::add(r);
      
      m_voidptra.add(r.m_p->get_cf_type_ref());
      
   }


   template < typename CFREF >
   requires (not_ref<CFREF>)
   void add(CFREF r)
   {
      
      ::ref_array::add(::ref<::cfref_particle<CFREF>>(r));
      
      m_voidptra.add(this->last().m_p->get_cf_type_ref());
      
   }

   
   const void * * data() {return m_voidptra.data();}
};
//inline ::array<const void * > cfpayloads(const ref_array & refa)
//{
//   ::array<const void * > a;
//   
//   for(auto & ref : refa)
//   {
//      a.add((const void *) ref.m_p->get_cf_type_ref());
//      
//   }
//   
//   return a;
//}

