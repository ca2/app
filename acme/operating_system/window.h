//
//  window.h
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


   //struct window_opaque_union_type
   //{

   //   union
   //   {

   //      unsigned char m_opaque[32];
   //      unsigned long long m_la[4];

   //   };

   //};


   struct window_opaque_t 
      //: public window_opaque_union_type
   {


      union
      {

         unsigned char m_opaque[32];
         unsigned long long m_la[4];

      };


      window_opaque_t(nullptr_t)
      {

         this->Null();

      }


      window_opaque_t() :
         window_opaque_t(nullptr)
      {

      }


      window_opaque_t(const window_opaque_t& window)
      {

         this->operator = (window);

      }


      void Null()
      {

         this->m_la[0] = 0;
         this->m_la[1] = 0;
         this->m_la[2] = 0;
         this->m_la[3] = 0;

      }


      bool is_null() const
      {

         return
            this->m_la[0] == 0
            && this->m_la[1] == 0
            && this->m_la[2] == 0
            && this->m_la[3] == 0;

      }


      bool is_set() const
      {

         return !this->is_null();

      }


      bool operator == (const window_opaque_t& windowopaque) const
      {

         return
            this->m_la[0] == windowopaque.m_la[0]
            && this->m_la[1] == windowopaque.m_la[1]
            && this->m_la[2] == windowopaque.m_la[2]
            && this->m_la[3] == windowopaque.m_la[3];

      }


      window_opaque_t& operator = (const window_opaque_t& windowopaque)
      {

         this->m_la[0] = windowopaque.m_la[0];
         this->m_la[1] = windowopaque.m_la[1];
         this->m_la[2] = windowopaque.m_la[2];
         this->m_la[3] = windowopaque.m_la[3];

         return *this;

      }


      operator ::hash32() const
      {
         return ::as_hash32(this->m_la[0])
            + ::as_hash32(this->m_la[1])
            + ::as_hash32(this->m_la[2])
            + ::as_hash32(this->m_la[3]);
      }



   };


   template < typename WINDOW_T >
   struct a_window_t
   {


      using WINDOW_TYPE = WINDOW_T;

      
      union
      {

         window_opaque_t   m_opaque;
         WINDOW_T          m_window;

      };

      
      a_window_t(nullptr_t) { this->Null(); }

      
      a_window_t() : a_window_t(nullptr) {}


      template < typename WINDOW_OPAQUE_T >
      requires (!::is_same < WINDOW_T, window_opaque_t >
      && ::is_same < WINDOW_OPAQUE_T, window_opaque_t >)
      a_window_t(const WINDOW_OPAQUE_T& windowopaque)
      {

         this->operator = (windowopaque);

      }


      a_window_t(const WINDOW_T & window)
      {

         this->operator = (window);

      }


      void Null() { this->m_window.Null(); }


      bool operator == (const a_window_t & awindowt) const
      {

         return this->m_window == awindowt.m_window;

      }
         
         
      template < typename WINDOW_OPAQUE_T >
         requires (!::is_same < WINDOW_T, window_opaque_t >
      && ::is_same < WINDOW_OPAQUE_T, window_opaque_t >)
      bool operator ==(const WINDOW_OPAQUE_T & windowopaque) const
      {

         return this->m_opaque == windowopaque;

      }


      typename
      bool operator == (const WINDOW_T & window) const
      {

         return this->m_window == window;

      }


      a_window_t& operator = (const a_window_t & awindowt)
      {

         this->m_window = awindowt.m_window;

         return *this;

      }


      template < typename WINDOW_OPAQUE_T >
         requires (!::is_same < WINDOW_T, window_opaque_t >
      && ::is_same < WINDOW_OPAQUE_T, window_opaque_t >)
      a_window_t& operator = (const WINDOW_OPAQUE_T & windowopaque)
      {

         this->m_opaque = windowopaque;

         return *this;

      }


      a_window_t& operator = (const WINDOW_T & window)
      {

         this->m_window = window;

         return *this;

      }


      bool is_null() const
      {
         
         return m_window.is_null();

      }


      bool is_set() const
      {

         return !this->is_null();

      }


      operator ::hash32() const { return m_opaque; }


   };


   template < enum_operating_system t_eoperatingsystem, typename WINDOW_T >
   class a_window;


   using window = a_window < e_operating_system_none, window_opaque_t >;


   template < enum_operating_system t_eoperatingsystem, typename WINDOW_T >
   class a_window :
      public a_window_t < WINDOW_T >
   {
   public:

      
      using BASE_TYPE = a_window_t < WINDOW_T >;

      
      using WINDOW_TYPE = typename BASE_TYPE::WINDOW_TYPE;
      
      
      enum_operating_system   m_eoperatingsystem;


      a_window(nullptr_t)
      {

         this->Null();

      }


      a_window() :
         a_window(nullptr)
      {
         
      }
      

      a_window(const a_window & awindow) :
      m_eoperatingsystem(awindow.m_eoperatingsystem),
         BASE_TYPE(awindow.m_window)
      {
         
      }


      template < typename WINDOW >
         requires (!::is_same < WINDOW_TYPE, window_opaque_t >
      && ::is_same < WINDOW, window >)
      a_window(const WINDOW & window) :
         m_eoperatingsystem(window.m_eoperatingsystem),
         BASE_TYPE(window.m_opaque)
      {

      }


      a_window(const WINDOW_TYPE & window) :
         m_eoperatingsystem(t_eoperatingsystem),
         BASE_TYPE(window)
      {

      }

      
      template < typename WINDOW_OPAQUE_T >
         requires (!::is_same < WINDOW_T, window_t >
      && ::is_same < WINDOW_OPAQUE_T, window_opaque_t >)
      a_window(const enum_operating_system& eoperatingsystem, const WINDOW_OPAQUE_T & windowopaque) :
         m_eoperatingsystem(eoperatingsystem),
         BASE_TYPE(windowopaque)
      {

      }


      void Null()
      {
         this->m_window.Null();
         m_eoperatingsystem = e_operating_system_none;
      }  


      ::operating_system::window & as_operating_system_window()
      {
         
         auto pthis = (::operating_system::window*)this;
         
         return *pthis;
         
      }
      
      
      const ::operating_system::window & as_operating_system_window() const
      {
         
         auto pthis = (::operating_system::window*)this;

         return *pthis;

      }

         
      bool is_null() const
      {
      
         return m_eoperatingsystem == e_operating_system_none
         || BASE_TYPE::is_null();

      }


      bool is_set() const
      {

         return !this->is_null();

      }


      bool operator == (const ::operating_system::window& operatingsystemwindow) const
      {

         return this->m_eoperatingsystem == operatingsystemwindow.m_eoperatingsystem
            && BASE_TYPE::operator == (operatingsystemwindow.m_window);

      }
      
      
      ::operating_system::window & operator = (const ::operating_system::window& operatingsystemwindow)
      {

         this->m_eoperatingsystem = operatingsystemwindow.m_eoperatingsystem;
         BASE_TYPE::operator = (operatingsystemwindow.m_window);

         return *this;

      }


   };

   //class window
   //{
   //public:

   //   enum_operating_system      m_eoperatingsystem;
   //   window_t                   m_window;


   //   window(nullptr_t) :
   //      m_eoperatingsystem(e_operating_system_none),
   //      m_window(nullptr)
   //   {

   //   }


   //   window() :
   //      window(nullptr)
   //   {

   //   }


   //   window(const window& window) :
   //      m_eoperatingsystem(window.m_eoperatingsystem),
   //      m_window(window.m_window)
   //   {

   //   }


   //   window(const enum_operating_system& eoperatingsystem, const window_t& window) :
   //      m_eoperatingsystem(eoperatingsystem),
   //      m_window(window)
   //   {

   //   }


   //   bool is_null() const
   //   {
   //      return m_eoperatingsystem == e_operating_system_none
   //         || m_window.is_null();

   //   }


   //   bool is_set() const
   //   {

   //      return !this->is_null();

   //   }

   //   bool operator == (const ::operating_system::window& operatingsystemwindow) const
   //   {

   //      return this->m_eoperatingsystem == operatingsystemwindow.m_eoperatingsystem
   //         && this->m_window == operatingsystemwindow.m_window;

   //   }

   //};



} // namespace operating_system



