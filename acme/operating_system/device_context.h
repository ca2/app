//
//  device_context.h
//  acme
// Created by camilo on 2026-02-39 15:09 <3ThomasBorregaardSørensen!!
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 20/02/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#pragma once


struct opaque_t {};


namespace operating_system
{


   //struct device_context_opaque_union_type
   //{

   //   union
   //   {

   //      unsigned char m_opaque[32];
   //      unsigned long long m_la[4];

   //   };

   //};


   struct device_context_opaque_t 
      //: public device_context_opaque_union_type
   {


      union
      {

         unsigned char              m_opaque[24];
         unsigned long long         m_ulla[3];

      };


      device_context_opaque_t(nullptr_t)
      {

         this->Null();

      }


      device_context_opaque_t() :
         device_context_opaque_t(nullptr)
      {

      }


      device_context_opaque_t(const device_context_opaque_t& device_context)
      {

         this->operator = (device_context);

      }


      void Null()
      {

         this->m_ulla[0] = 0;
         this->m_ulla[1] = 0;
         this->m_ulla[2] = 0;
         this->m_ulla[3] = 0;

      }


      bool is_null() const
      {

         return
            this->m_ulla[0] == 0
            && this->m_ulla[1] == 0
            && this->m_ulla[2] == 0
            && this->m_ulla[3] == 0;

      }


      bool is_set() const
      {

         return !this->is_null();

      }


      bool operator == (const device_context_opaque_t& device_contextopaque) const
      {

         return
            this->m_ulla[0] == device_contextopaque.m_ulla[0]
            && this->m_ulla[1] == device_contextopaque.m_ulla[1]
            && this->m_ulla[2] == device_contextopaque.m_ulla[2];

      }


      device_context_opaque_t& operator = (const device_context_opaque_t& device_contextopaque)
      {

         this->m_ulla[0] = device_contextopaque.m_ulla[0];
         this->m_ulla[1] = device_contextopaque.m_ulla[1];
         this->m_ulla[2] = device_contextopaque.m_ulla[2];

         return *this;

      }


      operator ::hash32() const
      {
         return ::as_hash32(this->m_ulla[0])
            + ::as_hash32(this->m_ulla[1])
            + ::as_hash32(this->m_ulla[2])
            + ::as_hash32(this->m_ulla[3]);
      }



   };


   template < typename WINDOW_T >
   struct a_device_context_t
   {


      using WINDOW_TYPE = WINDOW_T;

      
      union
      {

         device_context_opaque_t   m_opaque;
         WINDOW_T          m_device_context;

      };


      a_device_context_t(nullptr_t) { this->Null(); }

      
      a_device_context_t() : a_device_context_t(nullptr) {}


      template < typename WINDOW_OPAQUE_T >
      requires (!::is_same < WINDOW_T, device_context_opaque_t >
      && ::is_same < WINDOW_OPAQUE_T, device_context_opaque_t >)
      a_device_context_t(const WINDOW_OPAQUE_T& device_contextopaque)
      {

         this->operator = (device_contextopaque);

      }


      a_device_context_t(const WINDOW_T & device_context)
      {

         this->operator = (device_context);

      }


      void Null() { this->m_device_context.Null(); }


      bool operator == (const a_device_context_t & adevice_contextt) const
      {

         return this->m_device_context == adevice_contextt.m_device_context;

      }
         
         
      template < typename WINDOW_OPAQUE_T >
         requires (!::is_same < WINDOW_T, device_context_opaque_t >
      && ::is_same < WINDOW_OPAQUE_T, device_context_opaque_t >)
      bool operator ==(const WINDOW_OPAQUE_T & device_contextopaque) const
      {

         return this->m_opaque == device_contextopaque;

      }


      bool operator == (const WINDOW_TYPE & device_context) const
      {

         return this->m_device_context == device_context;

      }


      a_device_context_t& operator = (const a_device_context_t & adevice_contextt)
      {

         this->m_device_context = adevice_contextt.m_device_context;

         return *this;

      }


      template < typename WINDOW_OPAQUE_T >
         requires (!::is_same < WINDOW_T, device_context_opaque_t >
      && ::is_same < WINDOW_OPAQUE_T, device_context_opaque_t >)
      a_device_context_t& operator = (const WINDOW_OPAQUE_T & device_contextopaque)
      {

         this->m_opaque = device_contextopaque;

         return *this;

      }


      a_device_context_t& operator = (const WINDOW_T & device_context)
      {

         this->m_device_context = device_context;

         return *this;

      }


      bool is_null() const
      {
         
         return m_device_context.is_null();

      }


      bool is_set() const
      {

         return !this->is_null();

      }


      operator ::hash32() const { return m_opaque; }


   };


   template < enum_operating_system t_eoperatingsystem, typename WINDOW_T >
   class a_device_context;


   using device_context = a_device_context < e_operating_system_none, device_context_opaque_t >;


   template < enum_operating_system t_eoperatingsystem, typename WINDOW_T >
   class a_device_context :
      public a_device_context_t < WINDOW_T >
   {
   protected:
      ::acme::device_contexting::device_context *   m_pacmedevice_contextingdevice_context;
   public:

      
      using BASE_TYPE = a_device_context_t < WINDOW_T >;

      
      using WINDOW_TYPE = typename BASE_TYPE::WINDOW_TYPE;
      
      enum_operating_system         m_eoperatingsystem;


      a_device_context(nullptr_t)
      {

         this->Null();

      }


      a_device_context() :
         a_device_context(nullptr)
      {
         
      }
      

      a_device_context(const a_device_context & adevice_context) :
         m_pacmedevice_contextingdevice_context(adevice_context.m_pacmedevice_contextingdevice_context),
         m_eoperatingsystem(adevice_context.m_eoperatingsystem),
         BASE_TYPE(adevice_context.m_device_context)
      {
         
      }


      template < typename WINDOW >
         requires (!::is_same < WINDOW_TYPE, device_context_opaque_t >
      && ::is_same < WINDOW, device_context >)
      a_device_context(const WINDOW & device_context) :
         m_pacmedevice_contextingdevice_context(device_context._get_acme_device_contexting_device_context()),
         m_eoperatingsystem(device_context.m_eoperatingsystem),
         BASE_TYPE(device_context.m_opaque)
      {

      }


      a_device_context(const WINDOW_TYPE & device_context, ::acme::device_contexting::device_context * pacmedevice_contextingdevice_context = nullptr) :
         m_pacmedevice_contextingdevice_context(pacmedevice_contextingdevice_context),
         m_eoperatingsystem(t_eoperatingsystem),
         BASE_TYPE(device_context)
      {

      }

      
      template < typename WINDOW_OPAQUE_T >
         requires (!::is_same < WINDOW_T, device_context_opaque_t >
      && ::is_same < WINDOW_OPAQUE_T, device_context_opaque_t >)
      a_device_context(const enum_operating_system& eoperatingsystem, const WINDOW_OPAQUE_T & device_contextopaque, ::acme::device_contexting::device_context* pacmedevice_contextingdevice_context = nullptr) :
         m_pacmedevice_contextingdevice_context(pacmedevice_contextingdevice_context),
         m_eoperatingsystem(eoperatingsystem),
         BASE_TYPE(device_contextopaque)
      {

      }



      void _set_acme_device_contexting_device_context(::acme::device_contexting::device_context * pdevice_context)
      {

         m_pacmedevice_contextingdevice_context = pdevice_context;

      }


      ::acme::device_contexting::device_context * _get_acme_device_contexting_device_context() const
      {

         return m_pacmedevice_contextingdevice_context;

      }



      void Null()
      {
         this->m_device_context.Null();
         m_pacmedevice_contextingdevice_context = nullptr;
         m_eoperatingsystem = e_operating_system_none;
      }  


      ::operating_system::device_context & as_operating_system_device_context()
      {
         
         auto pthis = (::operating_system::device_context*)this;
         
         return *pthis;
         
      }
      
      
      const ::operating_system::device_context & as_operating_system_device_context() const
      {
         
         auto pthis = (::operating_system::device_context*)this;

         return *pthis;

      }

         
      bool is_null() const
      {
      
         return (m_eoperatingsystem == e_operating_system_none
         || BASE_TYPE::is_null()) && m_pacmedevice_contextingdevice_context == nullptr;

      }


      bool is_set() const
      {

         return !this->is_null();

      }


      bool operator == (const ::operating_system::device_context& operatingsystemdevice_context) const
      {

         if (operatingsystemdevice_context.m_eoperatingsystem != e_operating_system_none)
         {

            return (this->m_eoperatingsystem == operatingsystemdevice_context.m_eoperatingsystem
               && BASE_TYPE::operator == (operatingsystemdevice_context.m_device_context));

         }

         return m_pacmedevice_contextingdevice_context == operatingsystemdevice_context.m_pacmedevice_contextingdevice_context;

      }
      
      
     
      template < typename WINDOW >
         requires (!::is_same < WINDOW_TYPE, device_context_opaque_t >
      && ::is_same < WINDOW, device_context >)
      ::operating_system::device_context & operator = (const WINDOW & device_context)
      {

         this->m_pacmedevice_contextingdevice_context = device_context.m_pacmedevice_contextingdevice_context;
         this->m_eoperatingsystem = device_context.m_eoperatingsystem;
         BASE_TYPE::operator = (device_context.m_device_context);

         return *this;

      }
      

      a_device_context & operator = (const a_device_context & adevice_context)
      {

         this->m_pacmedevice_contextingdevice_context = adevice_context.m_pacmedevice_contextingdevice_context;
         this->m_eoperatingsystem = adevice_context.m_eoperatingsystem;
         BASE_TYPE::operator = (adevice_context.m_device_context);

         return *this;

      }


   };


   //class device_context
   //{
   //public:

   //   enum_operating_system      m_eoperatingsystem;
   //   device_context_t                   m_device_context;


   //   device_context(nullptr_t) :
   //      m_eoperatingsystem(e_operating_system_none),
   //      m_device_context(nullptr)
   //   {

   //   }


   //   device_context() :
   //      device_context(nullptr)
   //   {

   //   }


   //   device_context(const device_context& device_context) :
   //      m_eoperatingsystem(device_context.m_eoperatingsystem),
   //      m_device_context(device_context.m_device_context)
   //   {

   //   }


   //   device_context(const enum_operating_system& eoperatingsystem, const device_context_t& device_context) :
   //      m_eoperatingsystem(eoperatingsystem),
   //      m_device_context(device_context)
   //   {

   //   }


   //   bool is_null() const
   //   {
   //      return m_eoperatingsystem == e_operating_system_none
   //         || m_device_context.is_null();

   //   }


   //   bool is_set() const
   //   {

   //      return !this->is_null();

   //   }

   //   bool operator == (const ::operating_system::device_context& operatingsystemdevice_context) const
   //   {

   //      return this->m_eoperatingsystem == operatingsystemdevice_context.m_eoperatingsystem
   //         && this->m_device_context == operatingsystemdevice_context.m_device_context;

   //   }

   //};



} // namespace operating_system



