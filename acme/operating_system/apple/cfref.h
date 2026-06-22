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
inline void cfref_default_release(CFREF cfref)
{
   
   ::CFRelease(cfref);
   
}

class ref_base
{
public:
   
   bool m_bOwnReference = false;

   virtual~ref_base(){}
   
   virtual void release_base() = 0;
   
};
class ref_array;

template < typename REF_BASE >
class ref :
virtual public ref_base
{
public:
   
   
   using REF_BASE_TYPE = typename REF_BASE::REF_BASE_TYPE;
   
protected:
   REF_BASE *m_prefbase;
public:
   
   ref()
   {
      
      m_prefbase=nullptr;
      
   }
   
   
   ref(ref_array & refa, REF_BASE_TYPE refbasetype);
   
protected:
   ref(ref * pref):
      m_prefbase(new REF_BASE(pref->m_prefbase->operator REF_BASE_TYPE()))
   {
      
      m_bOwnReference = pref->m_bOwnReference;
      
      pref->m_bOwnReference= false;
      
   }
public:
   
   ~ref()
   {
      
      full_release();
      
   }
   
   
   ref & operator = (const ref & r)
   {
      
      if(&r != this && m_prefbase != r.m_prefbase && (!m_prefbase || !r.m_prefbase ||
                                                      m_prefbase->operator REF_BASE_TYPE()
         != r.m_prefbase->operator REF_BASE_TYPE()))
      {
         this->full_release();
         m_prefbase = new REF_BASE(r.m_prefbase->operator REF_BASE_TYPE());
         m_bOwnReference = false;
      }
      return *this;
   }
   ref & operator = (REF_BASE_TYPE refbasetype)
   {
      this->full_release();
      m_prefbase = new REF_BASE(refbasetype);
      m_bOwnReference = true;
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
   bool operator!() const {return m_prefbase == nullptr;}
   
   ref * clone()
   {
      
      return new ref(this);
   }
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

   void release_base()
   {
      
      if(m_prefbase)
      {
         
         if(m_bOwnReference)
         {
            
            m_bOwnReference = false;
            
            m_prefbase->release();
            
         }
         
      }
      
   }

   void full_release()
   {
      
      if(m_prefbase)
      {
         
         if(m_bOwnReference)
         {
            
            m_bOwnReference = false;
            
            m_prefbase->release();
            
         }
         
         delete m_prefbase;
         
         m_prefbase = nullptr;
         
      }
      
   }

   void set(ref_array & refa, REF_BASE_TYPE refbasetype);
   operator REF_BASE_TYPE()
   {
      if(::is_null(m_prefbase))
      {
         
         return nullptr;
         
      }
      return m_prefbase->operator REF_BASE_TYPE();
      
   }
   
};

class ref_array
{
protected:
   ::array_base<ref_base * > m_refbaseptra;
public:
   bool m_bAutoRelease;
   ref_array(bool bAutoRelease = true):
   m_bAutoRelease(bAutoRelease)
   {
      
   }
   ~ref_array()
   {
      if(m_bAutoRelease)
      {
         release();
      }
   }
   void release()
   {
      for(auto prefbase :  m_refbaseptra)
      {
         
         if(::is_set(prefbase))
         {
            
            try
            {
            
               prefbase->release_base();
               
            }
            catch (...)
            {
                  
            }
            
            delete prefbase;
            
         }
         
      }
      m_refbaseptra.clear();
   }

   template < typename REF >
   void add(REF * pref)
   {
      m_refbaseptra.add(pref->clone());
   }

};
template < typename REF_BASE >
ref<REF_BASE>::ref(ref_array & refa, REF_BASE_TYPE refbasetype)
{
   m_prefbase =new REF_BASE(refbasetype);
   m_bOwnReference = true;
   refa.add(this);
   
   
}
template < typename REF_BASE >
void ref<REF_BASE>::set(ref_array & refa, REF_BASE_TYPE refbasetype)
{
   full_release();
   m_prefbase =new REF_BASE(refbasetype);
   m_bOwnReference = true;
   refa.add(this);
   
   
}
template < typename CFREF = CFTypeRef, void (* t_functionRelease)(CFREF) = ::cfref_default_release < CFREF > >
class cfref_base
{
public:
   
   using REF_BASE_TYPE = CFREF;
   
   CFREF      m_cfref;
   
   
   cfref_base()
   {
      
      m_cfref = nullptr;
      
   }
   
   cfref_base(CFREF cfref):
      m_cfref(cfref)
   {
      
      
   }
   
   void release()
   {
      
      if(m_cfref)
      {
         
         auto cfref = m_cfref;
         
         m_cfref=nullptr;
         
         t_functionRelease(cfref);
      }
      
   }
   
   
   operator REF_BASE_TYPE() {return m_cfref;}
   
};


template < typename CFREF = CFTypeRef, void (* t_functionRelease)(CFREF) = ::cfref_default_release < CFREF > >
class cfref :
public ::ref < cfref_base < CFREF, t_functionRelease > >
{
public:
   
   using REF = ::ref < cfref_base < CFREF, t_functionRelease > >;
   
   using REF::REF;
   
   using REF::operator=;
   
};


using cftyperef = cfref < CFTypeRef, ::CFRelease >;


