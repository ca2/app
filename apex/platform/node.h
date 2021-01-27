//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


namespace apex
{


   class CLASS_DECL_APEX node :
      virtual public ::acme::node
   {
   public:


      node();
      virtual ~node();




      virtual void set_application_menu(::apex::application_menu * pmenu, ::apex::application * papplication);


   };


} // namespace apex



