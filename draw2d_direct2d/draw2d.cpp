#include "framework.h"


namespace draw2d_direct2d
{


   draw2d::draw2d()
   {
      
      ::direct2d::component::initialize();

   }


   draw2d::~draw2d()
   {

      ::direct2d::component::terminate();

   }


   ::e_status draw2d::initialize(::layered * pobjectContext)
   {

      auto estatus = ::draw2d::draw2d::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }
   
      //estatus = initialize_gdiplus();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      return estatus;
   
   }


   string draw2d::write_text_get_default_library_name()
   {

      return "direct2d";

   }

} // namespace draw2d_direct2d



