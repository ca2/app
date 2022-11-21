// Created by camilo on 2022-10-09 20:55 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/parallelization/mutex.h"
#include "acme/platform/library.h"
#include "acme/primitive/collection/atom_map.h"
#include "acme/primitive/collection/string_map.h"
//#include "acme/primitive/primitive/pointer.h"


namespace acme
{


   using library_map = string_map < ::pointer < ::acme::library > >;

   class acme;

} // namespace acme


class CLASS_DECL_ACME sub_system :
   virtual public ::particle
{
public:

   //   int g_argc = 0;


   //platform_char ** g_argv = nullptr;


   ::e_display                      m_edisplay;
   ::e_activation                   m_eactivation;

   ::acme::acme * m_pacme;

   int               m_argc = 0;

   char ** m_argv = nullptr;
   char ** m_envp = nullptr;

   wchar_t ** m_wargv = nullptr;
   wchar_t ** m_wenvp = nullptr;

#ifdef WINDOWS

   hinstance         m_hinstanceThis = nullptr;
   hinstance         m_hinstancePrev = nullptr;
   int               m_nCmdShow = -1000;

#endif

   ::block                          m_blockMatter;

   ::critical_section               m_criticalsection;
   ::acme::library_map              m_mapLibrary;
   ::pointer<::factory::factory>                               m_pfactory;
   ::pointer<atom_map < ::pointer<::factory::factory > > >     m_pmapFactory;
   //::pointer < ::mutex >                                            m_pmutexComponentFactory;
   ::pointer < string_map < string_map < ::pointer<::factory::factory >>>>       m_pmapComponentFactory;


   int m_iProcessStatus = 0;


   sub_system(::acme::acme * pacme);
   ~sub_system();


   //static sub_system * get();


   void set_args(int argc, char ** argv, wchar_t ** wargv);

   string _get_argv(int iArg) const;
   int get_argc();
   int * get_pargc();
   char *** get_pargv();
   char ** get_argv();
   wchar_t *** get_pwargv();
   wchar_t ** get_wargv();

   inline ::count _get_argc() const { return m_argc; }

   string get_executable() const;

   string get_argument1(int iArgument) const;

   inline ::count get_argument_count1() const { return _get_argc() - 1; }

   string_array get_arguments();

   string get_arg(int i) const;
   string get_env(const char * pszVariableName) const;


   int get_status();
   void set_status(int iStatus);


   virtual void set_resource_block(const char * pstart, const char * pend);



   void factory_initialize();
   void factory_terminate();

   // void factory_close();

};
