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


      virtual bool create(::draw2d::graphics * pgraphics);
      ::e_status destroy() override;



   };









} // namespace draw2d_cairo



