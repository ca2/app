#include "framework.h"
#include "print_task.h"
#include "acme/exception/interface_only.h"
#include "aura/graphics/draw2d/printer.h"


namespace user
{


   print_task::print_task()
   {

      m_iPageStart = -1;
      m_iPageCount = -1;
      m_iPrintingPage = 0;

   }


   void print_task::initialize(::particle * pparticle)
   {

      //auto estatus =
      
      ::task::initialize(pparticle);

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




