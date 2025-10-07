#pragma once


#include "aura/user/user/interaction.h"


namespace user
{


   class split_layout;


   class CLASS_DECL_BERG split_bar :
      public ::user::interaction
   {
   public:

      


      ::collection::index                         m_iIndex;
      split_layout *                m_pparent;
      unsigned int                           m_dwPosition;
      double                        m_dRate;
      double                        m_dMinimumRate;
      double                        m_dMaximumRate;
      unsigned int                           m_dwMaxPosition;



      split_bar();
      ~split_bar() override;


      void install_message_routing(::channel * pchannel) override;


      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      //using ::user::interaction::create_interaction;
      //virtual bool create_child(split_layout * psplitlayoutParent);
      bool pre_create_window(::user::system * pusersystem) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;
      

   };


} // namespace user


