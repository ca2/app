// Created by camilo on 2022-12-03 16:02 <3ThomasBorregaardSorensen!!
#pragma once


typedef void FACTORY_FUNCTION(::factory::factory*);


class CLASS_DECL_ACME factory_function
{
public:


   const char* m_pszName;
   FACTORY_FUNCTION* m_pfnFactory;
   factory_function* m_pfactoryfunctionNext;


   static factory_function* g_pfactoryfunctionNext;


   factory_function(const char * pszName, FACTORY_FUNCTION* pfnFactory);

   static FACTORY_FUNCTION* get(const ::scoped_string & scopedstrName);

};


#define REFERENCE_FACTORY(name) \
__FACTORY_IMPORT void TOKEN_CONCATENATE(name, _factory)(::factory::factory * pfactory); \
::factory_function TOKEN_CONCATENATE(g_set_factory_function_, name) = {STRINGFY(name), &::TOKEN_CONCATENATE(name, _factory) };



