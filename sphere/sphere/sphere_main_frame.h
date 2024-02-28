#pragma once


namespace sphere
{


   class CLASS_DECL_SPHERE main_frame :
      virtual public simple_main_frame
   {
   public:


      

      main_frame(::particle * pparticle);
      virtual ~main_frame();


      //virtual bool get_translucency(::user::enum_translucency & etranslucency, ::enum_element eelement, ::user::interaction * pinteraction) override;

      //virtual bool get_color(color32_t & color32, ::user::e_color ecolor, ::user::interaction * pinteraction) override;

      bool has_pending_graphical_update() override;

   };


} // namespace sphere



















