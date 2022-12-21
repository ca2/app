// Created by camilo on 2022-10-09 20:55 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/parallelization/mutex.h"
#include "acme/platform/library.h"
#include "acme/primitive/collection/atom_map.h"
#include "acme/primitive/collection/string_map.h"
//#include "acme/primitive/primitive/pointer.h"


#ifdef LINUX


#endif


class main;


namespace acme
{


   using library_map = string_map < ::pointer < ::acme::library > >;

   class acme;

} // namespace acme


namespace factory
{

   using factory_pointer = ::pointer < ::factory::factory >;
   using factory_map = ::string_map < factory_pointer >;
   using component_factory_map = ::string_map < factory_map >;

} // namespace factory


class CLASS_DECL_ACME sub_system :
   virtual public ::particle
{
public:


   critical_section                                m_criticalsection;
   
   ::e_display                                     m_edisplay;
   ::e_activation                                  m_eactivativation;
   int                                             m_argc = 0;
   char **                                         m_argv = nullptr;
   char **                                         m_envp = nullptr;
   
#ifdef WINDOWS_DESKTOP
   
   wchar_t **                                      m_wargv = nullptr;
   wchar_t **                                      m_wenvp = nullptr;
   hinstance                                       m_hinstanceThis = nullptr;
   hinstance                                       m_hinstancePrev = nullptr;
   int                                             m_nCmdShow = -1;
   
#endif
   
#ifdef LINUX

   ::locale_t                                      m_localeC;

#endif

   ::block                                         m_blockMatter;
   ::acme::library_map                             m_mapLibrary;
   ::factory::factory_pointer                      m_pfactory;
   ::factory::factory_map                          m_factorymap;
   ::factory::component_factory_map                m_componentfactorymap;


   int                                             m_iProcessStatus = 0;


   sub_system();
   ~sub_system();
   
   


   void set_args(int argc, char ** argv, wchar_t ** wargv);

   string _get_argv(int iArg) const;
   int get_argc();
   int * get_pargc();
   char *** get_pargv();
   char ** get_argv();
   
#ifdef WINDOWS
   
   wchar_t *** get_pwargv();
   wchar_t ** get_wargv();
   
#endif

   inline ::count _get_argc() const { return m_argc; }

   string get_executable() const;

   string get_argument1(int iArgument) const;

   inline ::count get_argument_count1() const { return _get_argc() - 1; }

   string_array get_arguments();

   string get_arg(int i) const;
   string get_env(const ::scoped_string & scopedstrVariableName) const;


   int get_status();
   void set_status(int iStatus);


   virtual void set_resource_block(const char * pstart, const char * pend);



   void factory_initialize();
   void factory_terminate();


   ::factory::factory_pointer & factory();
   ::factory::factory_pointer & factory(const ::string & strLibrary);
   ::factory::factory_pointer & factory(const ::string & strComponent, const ::string & strImplementation);


   ::pointer<::factory::factory_item_interface> & get_factory_item(const ::atom& atom, const ::atom& atomSource);


   bool has_factory_item(const ::atom& atom);


   void set_factory(const ::atom& atom, const ::pointer<::factory::factory_item_interface>& pfactory);


   void set_factory_from(const ::atom& atom, const ::atom& atomSource, const ::pointer<::factory::factory_item_interface>& pfactory);


   template < typename TYPE, typename BASE >
   void add_factory_item(const ::atom& atom)
   {

      set_factory(atom, __new(::factory::factory_item < TYPE, BASE >()));

   }

   
   ::factory::factory * get_factory(const ::atom & atomSource);



   //virtual void set_factory_global(const ::string &pszComponent, const ::string &pszImplementation);

   //virtual ::pointer<::acme::library> open_component_library(const ::string &pszComponent, const ::string &pszImplementation);

   virtual ::pointer<::acme::library> create_library(const ::string& strLibrary);

   virtual ::pointer<::acme::library>& library(const ::string& str);

   //virtual ::pointer<::acme::library>& library(const ::string& strComponent, const ::string& strImplementation);

   virtual ::pointer<::factory::factory>& impact_factory(const ::string& strComponent, const ::string& strImplementation);



};
