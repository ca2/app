#pragma once


namespace user
{


   class CLASS_DECL_CORE font_combo_box :
      virtual public ::user::combo_box
   {
   public:


      font_combo_box();
      ~font_combo_box() override;

      
      void font_combo_box_common_construct();
      

      void install_message_routing(::channel * psender) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      void handle(::topic * ptopic, ::context * pcontext) override;


   };


} //  namespace user



