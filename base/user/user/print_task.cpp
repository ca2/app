#include "framework.h" 
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


   ::estatus print_task::initialize(::object * pobjectContext)
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




