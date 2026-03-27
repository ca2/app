// Created by camilo on 2024-02-24 03:44 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "group.h"
#include "acme/exception/interface_only.h"


namespace coding
{


   group::group()
   {

      m_pintegration = nullptr;
      m_pitem = nullptr;

   }


   group::~group()
   {

   }


   ::collection::count group::get_size()
   {

      return 0;

   }


   enum_integrate group::get_eintegrate(::collection::index i)
   {

      return e_integrate_none;

   }


   ::string group::get_name(::collection::index i)
   {

      return {};

   }


   ::string group::get_short_name(::collection::index i)
   {

      return get_name(i);

   }


   void group::call_integrate(item* pitem)
   {
      
      m_pitem = pitem;

      integrate();
      

   }


   void group::integrate()
   {

      throw interface_only();

   }


} // namespace coding



