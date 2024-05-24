//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


#include "acid/platform/node.h"

namespace linux
{

   class CLASS_DECL_ACID node :
      virtual public ::acid::node
   {
   public:


      node();
      virtual ~node();


      virtual void os_calc_user_dark_mode();

      virtual string os_get_user_theme();

      virtual void os_process_user_theme(string strTheme);


};


} // namespace linux
