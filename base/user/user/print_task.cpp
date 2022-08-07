#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_component.h"
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


   void print_task::initialize(::object * pobject)
   {

      //auto estatus =
      
      ::task::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   print_task::~print_task()
   {

   }


   void     print_task::run()
   {

      throw ::interface_only();

   }


} // namespace user




