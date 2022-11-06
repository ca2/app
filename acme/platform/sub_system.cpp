// Created by camilo on 2022-10-09 21:01 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "sub_system.h"
#include "acme/platform/library.h"
#include "acme/exception/exception.h"
#include "acme/parallelization/task.h"


sub_system::sub_system()
{

}


sub_system::~sub_system()
{

   task_release();

   {

      array<void *> librarya;

      for (auto & plibrary : m_mapLibrary.values())
      {

         if (plibrary)
         {

            librarya.add(plibrary->m_plibrary);

            plibrary->m_plibrary = nullptr;

            plibrary->destroy();

         }

      }

      m_mapLibrary.clear();

      for (auto & p : librarya)
      {


         __node_library_close(p);

      }

   }

}


//::sub_system * sub_system::get()
//{
//
//   return g_psub_system;
//
//}


void sub_system::set_args(int argc, char ** argv, wchar_t ** wargv)
{

   m_argc = argc;

   m_argv = argv;

   m_wargv = wargv;

}





int sub_system::get_argc()
{

   return m_argc;

}


string sub_system::_get_argv(int iArgument) const
{

   if (iArgument < 0 || iArgument >= _get_argc())
   {

      return "";

   }

   if (m_wargv && m_wargv[iArgument])
   {

      return m_wargv[iArgument];

   }
   else if (m_argv && m_argv[iArgument])
   {

      return m_argv[iArgument];

   }

   return "";

}


string sub_system::get_executable() const
{

   return _get_argv(0);

}


string_array sub_system::get_arguments()
{

   string_array stra;

   for (::index i = 0; i < m_argc; i++)
   {

      string strArgument;

      if (m_wargv && m_wargv[i])
      {

         strArgument = m_wargv[i];

      }
      else if (m_argv && m_argv[i])
      {

         strArgument = m_argv[i];

      }
      else
      {

         break;

      }

      stra.add(strArgument);

   }

   return ::move(stra);

}


string sub_system::get_argument1(int iArgument) const
{

   return _get_argv(iArgument + 1);

}



int * sub_system::get_pargc()
{

   return &m_argc;

}


char *** sub_system::get_pargv()
{

   return &m_argv;

}


char ** sub_system::get_argv()
{

   return *get_pargv();

}


wchar_t *** sub_system::get_pwargv()
{

   return &m_wargv;

}


wchar_t ** sub_system::get_wargv()
{

   return *get_pwargv();

}


string sub_system::get_arg(int i) const
{

   if (m_wargv)
   {

      return string(m_wargv[i]);

   }
   else if (m_argv)
   {

      return string(m_argv[i]);

   }

   return "";


}


string sub_system::get_env(const char * pszVariableName) const
{

   if (m_wenvp)
   {

      wstring wstrPrefix(pszVariableName);

      wstrPrefix += "=";

      for (auto p = m_wenvp; p != nullptr; p++)
      {

         wstring wstr(*p);

         if (wstr.begins_eat_ci(wstrPrefix))
         {

            return wstr;

         }

      }

      return "";

   }
   else if (m_envp)
   {

      string strPrefix(pszVariableName);

      strPrefix += "=";

      for (auto p = m_envp; p != nullptr; p++)
      {

         string str(*p);

         if (str.begins_eat_ci(strPrefix))
         {

            return str;

         }

      }

      return "";

   }

   return "";

}


int sub_system::get_status()
{

   return m_iProcessStatus;

}


void sub_system::set_status(int iStatus)
{

   m_iProcessStatus = iStatus;

}


void sub_system::set_resource_block(const char * pstart, const char * pend)
{

   m_blockMatter = ::block(pstart, pend - pstart);

}



