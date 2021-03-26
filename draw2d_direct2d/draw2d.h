#pragma once


namespace draw2d_direct2d
{


   class CLASS_DECL_DRAW2D_DIRECT2D draw2d :
      virtual public ::draw2d::draw2d
   {
   public:


      draw2d();
      virtual ~draw2d();


      virtual ::e_status initialize(::object * pobject) override;

      virtual string write_text_get_default_library_name() override;

   };


} // namespace draw2d_direct2d



