//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#ifdef LINUX
#include "aura/os/linux/x11.h"
#endif


namespace aura
{


   node::node()
   {

      m_pauranode = this;

   }


   node::~node()
   {


   }


//#ifdef LINUX
//
//   ::linux::appindicator * node::appindicator_allocate()
//   {
//
//      return nullptr;
//
//   }
//
//
//   void node::appindicator_destroy(::linux::appindicator * pappindicator)
//   {
//
//      //return nullptr;
//
//   }
//
//
//#endif


   void node::set_application_menu(::apex::application_menu * pmenu, ::apex::application * papplication)
   {

   }


//   void * node::node_wrap_window(void * pdisplay, i64 window)
//   {
//
//      return nullptr;
//
//   }


//   void node::user_fork(const ::promise::routine & routine)
//   {
//
//#ifdef LINUX
//
//      x11_fork([routine]()
//               {
//
//                  routine();
//
//               });
//
//#endif
//
//   }



} // namespace aura



