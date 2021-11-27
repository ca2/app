//
//  apex_app.h
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 18/08/19.
//  Moved from Apex to Acme on 2021-03-20 18:39 <3ThomasBS_
//
#pragma once


#define DECLARE_FACTORY(library) \
__FACTORY_EXPORT void library ## _factory(::factory::factory* pfactory);


#define SETUP_FACTORY(library) \
::static_setup m_setup_ ## library{ &library ## _factory, #library}


//class node_data_exchange;


//void apex_set_get_new_application(PFN_NEW_APEX_APPLICATION pnewapplication);


class CLASS_DECL_ACME static_setup 
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
   static_setup*                 m_ppropertysetupNext;
   PFN_factory                   m_pfnFactory;


   static static_setup *         s_psetupList;


   static_setup(::static_setup::enum_flag eflag, const char * pszName);
   static_setup(PFN_factory pfnFactory, const char* pszName);


   void construct();


   inline bool should_install() { return !has_flag(flag_do_not_install); }
   [[nodiscard]] bool has_flag(::static_setup::enum_flag eflag) { return ((int)m_eflag & (int)eflag) == (int)eflag; }


   static static_setup* get_last(::static_setup::enum_flag eflag, const char* pszName = nullptr);
   static static_setup* get_first(::static_setup::enum_flag eflag, const char* pszName = nullptr);
   static PFN_factory get_factory_function(const char* pszName = nullptr);


   virtual __pointer(::acme::library) create_library();
   virtual __pointer(::element) create_element();
   virtual __pointer(::element) create_application_as_element();


   virtual __pointer(::acme::library) _create_library();
   virtual __pointer(::element) _create_element();
   virtual __pointer(::element) _create_application_as_element();


};


template < typename LIBRARY >
class static_library_factory :
   public static_setup
{
public:


   __pointer(::acme::library) _create_library() override { return __new(LIBRARY); }


   explicit static_library_factory(const char * pszName = "") :
      static_setup(flag_library, pszName)
   {


   }


};


template < typename OBJECT >
class static_object_factory :
   public static_setup
{
public:


   __pointer(::element) _create_element() override { return __new(OBJECT); }


   explicit static_object_factory(::static_setup::enum_flag eflag, const char* pszName = "") :
      static_setup(eflag, pszName)
   {

   }


};


#define __namespace_library_factory(LIBRARY) \
::static_library_factory < library > TOKEN_AT_LINE(g_library_factory)(LIBRARY);
 

#define __namespace_object_factory(OBJECT, EOBJECT) \
::static_object_factory < OBJECT > TOKEN_AT_LINE(g_library_factory)(EOBJECT);


#define __namespace_system_factory(SYSTEM) \
__namespace_object_factory(SYSTEM,:: static_setup::flag_system)


#define __namespace_session_factory(SESSION) \
__namespace_object_factory(SESSION,:: static_setup::flag_session)






template < typename APPLICATION >
class static_application_factory :
   public static_setup
{
public:


   virtual __pointer(::element) _create_application_as_element() override
   {

      auto papplication = __new(APPLICATION);

      return papplication;

   }


   static_application_factory(const char* pszName = "") :
      static_setup(flag_application, pszName)
   {


   }


};


#define __namespace_application_factory(APPID) \
::static_application_factory < application > g_applicationfactory(APPID);



