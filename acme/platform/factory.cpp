#include "framework.h"

#ifndef WINDOWS


#include <cxxabi.h>


thread_local char * t_pszDemangle;
thread_local size_t t_sizeDemangle;
//extern critical_section * g_pcsDemangle;


bool demangle (string & str, const char * pszType)
{

   //critical_section_lock cs(g_pcsDemangle);

   int status = -4;

   t_pszDemangle = abi::__cxa_demangle(pszType, t_pszDemangle, &t_sizeDemangle, &status);

   if (status == 0)
   {

      str = t_pszDemangle;

      return true;

   }

   return false;

}


//bool demangle (string & str)
//{
//
//   return str, str.c_str();
//
//}


#endif


namespace factory
{



   __pointer(::element) factory::create(const ::string & strType)
   {

      //auto psystem = get_system();

      //synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

      //::matter* p = nullptr;

      ////if (get_library() != nullptr)
      ////{

      ////   p = get_library()->new_object(pszClass);

      ////}
      ////else
      //{

      //   p = new_object(pszClass);

      //}

      //auto pobject = ::move_transfer(p);

      //if (!pobject)
      //{

      //   return nullptr;

      //}

      //return pobject;

      auto pfactoryinterface = get_factory_item(strType);

      //if (!pfactoryinterface)
      //{

      //   return error_no_factory;

      //}

      return pfactoryinterface->create_element();

   }


   bool factory::has_type(const ::string & strType) const
   {

      //auto psystem = get_system();

      //synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

      //if (get_library() == nullptr)
      //{

      //   return false;

      //}

      return get_factory_item(strType) != nullptr;

   }


} // namespace factory



