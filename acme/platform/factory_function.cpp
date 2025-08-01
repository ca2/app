// Created by camilo on 2022-12-03 16:04 <3ThomasBorregaardSorensen!!
#include "framework.h"


//#ifdef CUBE


#include "factory_function.h"


factory_function* factory_function::g_pfactoryfunctionNext = nullptr;


factory_function::factory_function(const_char_pointer pszName, FACTORY_FUNCTION* pfnFactory) :
   m_pszName(pszName),
   m_pfnFactory(pfnFactory)
{

   m_pfactoryfunctionNext = g_pfactoryfunctionNext;

   g_pfactoryfunctionNext = this;

}


FACTORY_FUNCTION* factory_function::get(const ::scoped_string & scopedstrName)
{

   if (scopedstrName.is_empty())
   {

      return nullptr;

   }

   auto pfactoryfunction = g_pfactoryfunctionNext;

   while (pfactoryfunction)
   {

      if (scopedstrName == pfactoryfunction->m_pszName)
      {

         return pfactoryfunction->m_pfnFactory;

      }

      pfactoryfunction = pfactoryfunction->m_pfactoryfunctionNext;

   }

   return nullptr;

}


//#endif


