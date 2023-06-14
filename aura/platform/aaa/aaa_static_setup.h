//
//  aura_app.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 18/08/19.
//
#pragma once


class node_data_exchange;


void aura_set_get_new_application(PFN_NEW_AURA_APPLICATION pnewapplication);


class CLASS_DECL_AURA system_setup
{
public:


   enum enum_flag
   {

      e_flag_none,
      flag_system = 1,
      flag_session = 2,
      flag_application = 4,
      flag_library = 8,
      flag_object_user = 16,
      flag_do_not_install = 4096,

   };


   const char *                  m_pszName;
   enum_flag                        m_eflag;
   system_setup*                 m_ppropertysetupNext;


   static system_setup *         s_psetupList;


   system_setup(::system_setup::enum_flag eflag, const ::string & pszName);


   void construct();


   inline bool should_install() { return !has_flag(flag_do_not_install); }
   bool has_flag(::system_setup::enum_flag eflag) { return ((int)m_eflag & (int)eflag) == (int)eflag; }


   static system_setup* get_first(::system_setup::enum_flag eflag, const ::string & pszName = nullptr);

   virtual ::matter * create_new_object();
   virtual ::aura::application* create_new_application();
   virtual ::acme::library* create_new_library();

   virtual ::matter* new_object();
   virtual ::aura::application* new_application();
   virtual ::acme::library* new_library();


};


template < typename LIBRARY >
class static_library_factory :
   public system_setup
{
public:


   virtual ::acme::library* new_library() override { return memory_new LIBRARY; }


   static_library_factory(const ::string & pszName = "") :
      system_setup(flag_library, pszName)
   {


   }


};


template < typename OBJECT >
class static_object_factory :
   public system_setup
{
public:


   virtual ::matter * new_object() override { return memory_new OBJECT; }


   static_object_factory(::system_setup::enum_flag eflag, const ::string & pszName = "") :
      system_setup(eflag, pszName)
   {

   }


};


#define __namespace_library_factory(LIBRARY) \
::static_library_factory < library > COUNTER_TOKEN(g_library_factory)(LIBRARY);
 

#define __namespace_object_factory(OBJECT, EOBJECT) \
::static_object_factory < OBJECT > COUNTER_TOKEN(g_library_factory)(EOBJECT);


#define __namespace_system_factory(SYSTEM) \
__namespace_object_factory(SYSTEM,:: system_setup::flag_system)


#define __namespace_session_factory(SESSION) \
__namespace_object_factory(SESSION,:: system_setup::flag_session)




