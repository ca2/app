//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


#ifdef LINUX

namespace linux
{

   class appindicator;

}

#endif

namespace aura
{


   class CLASS_DECL_AURA node :
      virtual public ::apex::node
   {
   public:


      node();
      virtual ~node();



#ifdef LINUX

      virtual ::linux::appindicator * appindicator_allocate();
      virtual void appindicator_destroy(::linux::appindicator * pappindicator);

#endif

      virtual void set_application_menu(::apex::application_menu * pmenu, ::apex::application * papplication);

//      virtual void * node_wrap_window(void * pdisplay, i64 window);

      //using apex::node::user_fork;

      //virtual void user_fork(const ::promise::routine & routine) override;


   };


} // namespace aura



