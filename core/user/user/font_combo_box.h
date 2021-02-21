#pragma once


namespace user
{


   class CLASS_DECL_CORE font_combo_box :
      virtual public ::user::combo_box
   {
   public:


      font_combo_box();
      virtual ~font_combo_box();

      
      void font_combo_box_common_construct();
      

      virtual void install_message_routing(::channel * psender);


      DECL_GEN_SIGNAL(on_message_create);

      void on_layout(::draw2d::graphics_pointer & pgraphics);


   };


} //  namespace user



