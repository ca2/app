// Created by Camilo on 2021-10-04 12:06 BRT <3ThomasBorregaardS�rensen!!
#pragma once


#include "acme/primitive/primitive/particle.h"


class trace;


// Declare a global instance of this class to automatically register a custom trace category at startup
class CLASS_DECL_ACME trace_category
{
public:


   enum_trace_category        m_etracecategory;
   const char *               m_pszName;
   enum_trace_level           m_etracelevelMinimum;
   bool                       m_bEnabled;


   trace_category();
   ~trace_category();


   enum_trace_level get_trace_level() const { return m_etracelevelMinimum; }
   void set_trace_level(enum_trace_level etracelevel) { m_etracelevelMinimum = etracelevel;  }
   bool is_enabled() const { return m_bEnabled; }
   void enable(bool bEnable = true) { m_bEnabled = bEnable; }

   operator enum_trace_category () const { return m_etracecategory; }


};


class CLASS_DECL_ACME trace :
   virtual public ::particle
{
public:


   ::trace_category       m_tracecategorya[e_trace_category_count];


   trace();
   ~trace() override;


   ::trace_category * operator[](enum_trace_category etracecategory)
   {

      if (etracecategory < e_trace_category_general || etracecategory >= e_trace_category_count)
      {

         return nullptr;

      }

      return &m_tracecategorya[etracecategory];

   }


   ::trace_category * enabled_get(enum_trace_category etracecategory, enum_trace_level etracelevel)
   {

      auto ptracecategory = operator[](etracecategory);

      if (ptracecategory == nullptr)
      {

         return nullptr;

      }

      if (!ptracecategory->is_enabled() || etracelevel < ptracecategory->m_etracelevelMinimum)
      {

         return nullptr;

      }

      return ptracecategory;

   }


   //void print(enum_trace_level etracelevel, enum_trace_category etracecategory, const scoped_string & strFunction, const scoped_string & strFileName, i32 nLine, const scoped_string & str) override;


};



CLASS_DECL_ACME const char * get_windows_message_name(::u32 nMsg);



