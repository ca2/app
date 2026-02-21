//
//  window.h
//  acme
// Created by camilo on 2026-02-39 15:09 <3ThomasBorregaardSørensen!!
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 20/02/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#pragma once


namespace operating_system
{

   struct window_t
   {
      union
      {
         unsigned char m_opaque[32];
         unsigned long long m_la[4];
      };

      window_t(nullptr_t) { Null(); }

      window_t() : window_t(nullptr) { }

      window_t(const window_t & window)
      {
         
         this->operator = (window);
         
      }

      
      void Null()
      {
         
         m_la[0] = 0;
         m_la[1] = 0;
         m_la[2] = 0;
         m_la[3] = 0;
         
      }
      
      bool operator == (const window_t & window) const
      {
         
         return
         this->m_la[0] == window.m_la[0]
         && this->m_la[1] == window.m_la[1]
         && this->m_la[2] == window.m_la[2]
         && this->m_la[3] == window.m_la[3];
         
      }
      
      
      window_t & operator = (const window_t & window)
      {
         
         this->m_la[0] = window.m_la[0];
         this->m_la[1] = window.m_la[1];
         this->m_la[2] = window.m_la[2];
         this->m_la[3] = window.m_la[3];
         
         return *this;
         
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
      
   };

   class window
   {
   public:
      
      enum_operating_system      m_eoperatingsystem;
      window_t                   m_window;


      window(nullptr_t):
         m_eoperatingsystem(e_operating_system_none),
         m_window(nullptr)
      {
         
      }


      window() :
         window(nullptr)
      {
         
      }
      
      
      window(const window & window) :
      m_eoperatingsystem(window.m_eoperatingsystem),
      m_window(window.m_window)
      {
         
      }
      
      
      window(const enum_operating_system & eoperatingsystem, const window_t & window) :
      m_eoperatingsystem(eoperatingsystem),
      m_window(window)
      {
         
      }
      
      
      bool is_null() const
      {
         return m_eoperatingsystem == e_operating_system_none
         || m_window.is_null();
         
      }
      
      
      bool is_set() const
      {
         
         return !this->is_null();
         
      }
      
      bool operator == (const ::operating_system::window & operatingsystemwindow) const
      {
         
         return this->m_eoperatingsystem == operatingsystemwindow.m_eoperatingsystem
         && this->m_window == operatingsystemwindow.m_window;
         
      }
      
   };


   template < typename BASE, enum_operating_system t_eoperatingsystem, typename STRUCT_T >
   class a_window
   {
   public:
      
      
      enum_operating_system m_eoperatingsystem;
      
      union
      {
         operating_system::window_t    m_window;
         STRUCT_T                      m_struct;
      };
      
      a_window()
      {
         
         m_window.Null();
         m_eoperatingsystem = t_eoperatingsystem;
         
      }
      
      a_window(const a_window & awindow) :
      m_eoperatingsystem(awindow.m_eoperatingsystem),
      m_window(awindow.m_window)
      {
         
      }

      
      ::operating_system::window & as_operating_system_window()
      {
         
         auto pthis = (BASE*)this;
         
         return *((::operating_system::window *)pthis);
         
      }
      
      
      const ::operating_system::window & as_operating_system_window() const
      {
         
         auto pthis = (BASE*)this;
         
         return *((::operating_system::window *)pthis);
         
      }
      
      
   };


} // namespace operating_system



