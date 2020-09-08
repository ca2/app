//
//  aura_app.h
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 18/08/19.
//
#pragma once


class node_data_exchange;


void aura_set_get_new_application(PFN_NEW_AURA_APPLICATION pnewapplication);


class CLASS_DECL_APEX static_setup 
{
public:


   enum e_flag
   {

      flag_none,
      flag_system = 1,
      flag_session = 2,
      flag_application = 4,
      flag_library = 8,
      flag_object_user = 16,
      flag_do_not_install = 4096,

   };


   const char *                  m_pszName;
   e_flag                        m_eflag;
   static_setup*                 m_psetupNext;


   static static_setup *         s_psetupList;


   static_setup(::static_setup::e_flag eflag, const char * pszName);


   void construct();


   inline bool should_install() { return !has_flag(flag_do_not_install); }
   bool has_flag(::static_setup::e_flag eflag) { return ((int)m_eflag & (int)eflag) == (int)eflag; }


   static static_setup* get_first(::static_setup::e_flag eflag, const char* pszName = nullptr);

   virtual ::generic_object * create_new_object();
   virtual ::apex::application* create_new_application();
   virtual ::apex::library* create_new_library();

   virtual ::generic_object* new_object();
   virtual ::apex::application* new_application();
   virtual ::apex::library* new_library();


};


template < typename LIBRARY >
class static_library_factory :
   public static_setup
{
public:


   virtual ::apex::library* new_library() override { return new LIBRARY; }


   static_library_factory(const char * pszName = "") :
      static_setup(flag_library, pszName)
   {


   }


};


template < typename OBJECT >
class static_object_factory :
   public static_setup
{
public:


   virtual ::generic_object * new_object() override { return new OBJECT; }


   static_object_factory(::static_setup::e_flag eflag, const char* pszName = "") :
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




