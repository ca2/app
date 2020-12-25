#pragma once


namespace sphere
{


   class CLASS_DECL_SPHERE main_frame :
      virtual public simple_main_frame
   {
   public:


      

      main_frame(::layered * pobjectContext);
      virtual ~main_frame();


      //virtual bool get_translucency(::user::enum_translucency & etranslucency, ::user::enum_element eelement, ::user::interaction * pinteraction) override;

      //virtual bool get_color(color32_t & cr, ::user::e_color ecolor, ::user::interaction * pinteraction) override;

      virtual bool has_pending_graphical_update() override;

   };


} // namespace sphere



















