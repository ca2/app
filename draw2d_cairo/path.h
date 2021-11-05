#pragma once


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO path :
      virtual public ::draw2d_cairo::object,
      virtual public ::draw2d::path
   {
   public:


      path();
      ~path() override;


      bool create(::draw2d::graphics * pgraphics);
      ::e_status destroy() override;

      bool contains(::draw2d::graphics_pointer & pgraphics, const point_f64& point) override;


   };









} // namespace draw2d_cairo



