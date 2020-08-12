#pragma once


namespace draw2d_cairo
{

   class CLASS_DECL_DRAW2D_CAIRO palette :
      virtual public ::draw2d_cairo::object,
      virtual public ::draw2d::palette
   {
   public:


      palette();
      virtual ~palette();


   };


} // namespace draw2d_cairo

