//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"


namespace apex
{

   node::node()
   {

      m_papexnode = this;

   }


   node::~node()
   {


   }


   void node::set_application_menu(::apex::application_menu * pmenu, ::apex::application * papplication)
   {

   }


   ::e_status node::register_dll(const ::file::path & pathDll)
   {

      __throw(interface_only_exception());

      return error_interface_only;

   }


} // namespace apex



