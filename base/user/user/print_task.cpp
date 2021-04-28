#include "framework.h"
#include "base/user/user/_user.h"
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


   ::e_status print_task::initialize(::object * pobject)
   {

      auto estatus = ::task::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   print_task::~print_task()
   {

   }


   ::e_status     print_task::run()
   {

      return error_interface_only;

   }


} // namespace user




