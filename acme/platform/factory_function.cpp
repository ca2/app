// Created by camilo on 2022-12-03 16:04 <3ThomasBorregaardSorensen!!
#include "framework.h"


factory_function* factory_function::g_pfactoryfunctionNext = nullptr;


factory_function::factory_function(const scoped_string & strName, FACTORY_FUNCTION* pfnFactory) :
   m_pszName(pszName),
   m_pfnFactory(pfnFactory)
{

   m_pfactoryfunctionNext = g_pfactoryfunctionNext;

   g_pfactoryfunctionNext = this;

}


FACTORY_FUNCTION* factory_function::get(const scoped_string & strName)
{

   if (::is_empty(pszName))
   {

      return nullptr;

   }

   auto pfactoryfunction = g_pfactoryfunctionNext;

   while (pfactoryfunction)
   {

      if (strcmp(pfactoryfunction->m_pszName, pszName) == 0)
      {

         return pfactoryfunction->m_pfnFactory;

      }

      pfactoryfunction = pfactoryfunction->m_pfactoryfunctionNext;

   }

   return nullptr;

}