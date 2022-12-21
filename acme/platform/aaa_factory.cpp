#include "framework.h"
#include "factory.h"
#include "acme/primitive/primitive/factory.h"
#include "acme/primitive/string/string.h"
#ifndef WINDOWS


#include <cxxabi.h>


thread_local char * t_pszDemangle;
thread_local size_t t_sizeDemangle;
//extern critical_section * g_pcsDemangle;


bool demangle (string & str, const ::scoped_string & scopedstrType)
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



   ::pointer < ::particle > factory::create(const ::string & strType)
   {

      //auto psystem = acmesystem();

      //synchronous_lock synchronouslock(&psystem->m_pmutexLibrary);

      //::matter* p = nullptr;

      ////if (get_library() != nullptr)
      ////{

      ////   p = get_library()->new_object(pszClass);

      ////}
      ////else
      //{

      //   p = new_object(pszClass);

      //}

      //auto pparticle = ::move_transfer(p);

      //if (!pparticle)
      //{

      //   return nullptr;

      //}

      //return pparticle;

      auto pfactoryinterface = get_factory_item(strType);

      //if (!pfactoryinterface)
      //{

      //   return error_no_factory;

      //}

      return pfactoryinterface->create_particle();

   }


   bool factory::has_type(const ::string & strType) const
   {

      //auto psystem = acmesystem();

      //synchronous_lock synchronouslock(&psystem->m_pmutexLibrary);

      //if (get_library() == nullptr)
      //{

      //   return false;

      //}

      return get_factory_item(strType) != nullptr;

   }


} // namespace factory



