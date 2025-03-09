// Created by camilo on 2025-03-09 01:22 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/handler/source.h"


class CLASS_DECL_ACME component :
   virtual public ::source
{
public:


   ::string                                     m_strComponent;
   ::string                                     m_strComponentPath;
   ::string_array                               m_straImplementationAll;
   ::string_array                               m_straImplementationOnShelf;
   ::string_array                               m_straImplementationInstalled;
   ::string_array                               m_straImplementationEnabled;


   ::string_map < ::pointer < ::component_implementation > > m_mapImplementation;


   component();
   ~component() override;


   void on_initialize_particle() override;



   virtual void update();

   virtual void _update_implementations_on_shelf();

   virtual void _update_installed_implementations();

   virtual void _update_enabled_implementations();

   virtual void _001CreateForm(::user::interaction * puserinteractionParent);

   virtual bool is_implementation(const ::scoped_string & scopedstrImplementation);
   virtual bool is_implementation_installed(const ::scoped_string & scopedstrImplementation);
   virtual bool is_implementation_on_shelf(const ::scoped_string & scopedstrImplementation);
   virtual bool is_implementation_enabled(const ::scoped_string & scopedstrImplementation);


   virtual ::component_implementation * implementation(const ::scoped_string & scopedstrImplementation);


};



