#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif
#include "aura/graphics/draw2d/printer.h"
#include "print_task.h"



namespace user
{


   print_task::print_task()
   {

      m_iPageStart = -1;
      m_iPageCount = -1;
      m_iPrintingPage = 0;

   }


   ::estatus print_task::initialize(::layered * pobjectContext)
   {

      auto estatus = ::task::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   print_task::~print_task()
   {

   }


   ::estatus     print_task::run()
   {

      return error_interface_only;

   }


} // namespace user




