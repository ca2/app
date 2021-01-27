//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


#include "acme/platform/node.h"

namespace linux
{

   class CLASS_DECL_ACME node :
      virtual public ::acme::node
   {
   public:


      node();
      virtual ~node();


      virtual void os_calc_user_dark_mode();

      virtual string os_get_user_theme();

      virtual void os_process_user_theme(string strTheme);


};


} // namespace linux