//
//  apex_app.h
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 18/08/19.
//  Moved from Apex to Acme on 2021-03-20 18:39 <3ThomasBS_
//
#pragma once


#include "acme/primitive/primitive/particle.h"
//#include "acme/primitive/primitive/pointer.h"


//#define DECLARE_FACTORY(library) \
//__FACTORY_EXPORT void IDENTIFIER_CONCATENATE(library, _factory)(::factory::factory* pfactory);

//#define STRINGFY(a) #a
#define SETUP_FACTORY(library) \
::system_setup IDENTIFIER_CONCATENATE(m_setup_, library){ &IDENTIFIER_CONCATENATE(library, _factory), STRINGFY(library)}


//class node_data_exchange;


//void apex_set_get_new_application(PFN_NEW_APEX_APPLICATION pnewapplication);


class CLASS_DECL_ACME system_setup
{
public:


   enum enum_flag
   {

      e_flag_none,
      flag_system = 1,
      flag_session = 2,
      flag_application = 4,
      flag_multimedia = 8,
      flag_library = 16,
      flag_object_user = 32,
      flag_factory = 64,
      flag_do_not_install = 4096,

   };


   const char *                  m_pszName;
   enum_flag                     m_eflag;
   system_setup*                 m_ppropertysetupNext;
   PFN_factory                   m_pfnFactory;


   static system_setup *         s_psetupList;


   system_setup(::system_setup::enum_flag eflag, const char * pszName);
   system_setup(PFN_factory pfnFactory, const char * pszName);


   void construct();


   inline bool should_install() { return !has_flag(flag_do_not_install); }
   [[nodiscard]] bool has_flag(::system_setup::enum_flag eflag) { return ((int)m_eflag & (int)eflag) == (int)eflag; }


   static system_setup* get_last(::system_setup::enum_flag eflag, const ::scoped_string & scopedstrName = nullptr);
   static system_setup* get_first(::system_setup::enum_flag eflag, const ::scoped_string & scopedstrName = nullptr);
   static PFN_factory get_factory_function(const ::scoped_string & scopedstrName = nullptr);


   virtual ::pointer<::acme::library>create_library();
   virtual ::pointer < ::particle > create_particle();
   virtual ::pointer < ::particle > create_application_as_particle();


   virtual ::pointer<::acme::library>_create_library();
   virtual ::pointer < ::particle > _create_particle();
   virtual ::pointer < ::particle > _create_application_as_particle();


};


template < typename LIBRARY >
class static_library_factory :
   public system_setup
{
public:


   ::pointer<::acme::library>_create_library() override { return __new(LIBRARY); }


   explicit static_library_factory(const ::scoped_string & scopedstrName = "") :
      system_setup(flag_library, scopedstrName)
   {


   }


};


template < typename OBJECT >
class static_object_factory :
   public system_setup
{
public:


   ::pointer < ::particle > _create_particle() override { return __new(OBJECT); }


   explicit static_object_factory(::system_setup::enum_flag eflag, const ::scoped_string & scopedstrName = "") :
      system_setup(eflag, scopedstrName)
   {

   }


};


#define __namespace_library_factory(LIBRARY) \
::static_library_factory < library > COUNTER_TOKEN(g_library_factory)(LIBRARY);
 

#define __namespace_object_factory(OBJECT, EOBJECT) \
::static_object_factory < OBJECT > COUNTER_TOKEN(g_library_factory)(EOBJECT);


// #define __namespace_system_factory(SYSTEM) \
// __namespace_object_factory(SYSTEM,:: system_setup::flag_system)


// #define __namespace_session_factory(SESSION) \
// __namespace_object_factory(SESSION,:: system_setup::flag_session)






template < typename APPLICATION_TYPE >
class static_application_factory :
   public system_setup
{
public:


   ::pointer < ::particle >  _create_application_as_particle() override
   {

      auto papp = __new(APPLICATION_TYPE);

      return papp;

   }


   static_application_factory(const ::scoped_string & scopedstrName = "") :
      system_setup(flag_application, scopedstrName)
   {


   }


};


#define __namespace_application_factory(APPID) \
::static_application_factory < application > g_applicationfactory(APPID);



class CLASS_DECL_ACME app_factory
{
public:

    
   app_factory(PFN_factory pfnFactory);


   static ::pointer<::acme::application>new_app();
    

};



