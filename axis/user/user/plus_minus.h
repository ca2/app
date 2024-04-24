// From design/text_format/user_object.h by camilo on
// 2022-09-04 00:15 <3ThomasBorregaardSorensen!! (ThomasLikesNumber5!!)
#pragma once


#include "aura/user/user/interaction.h"


namespace user
{


   class CLASS_DECL_AXIS plus_minus :
      virtual public ::user::interaction
   {
   public:


      bool                             m_bLabel;

      int                              m_i;
      int                              m_iMin;
      int                              m_iMax;
      int                              m_iStep;
      ::pointer<::user::still>      m_pstill;
      ::pointer<::user::button>     m_pbuttonMinus;
      ::pointer<::user::button>     m_pbuttonPlus;

      string                           m_strMin;
      string                           m_strMax;
      string                           m_strFormat;



      plus_minus();
      virtual ~plus_minus();


      void install_message_routing(::channel * pchannel) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);


      void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      //virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void handle(::topic * ptopic, ::context * pcontext) override;


      virtual string calc_still_label();

      virtual void set_value(int iValue, const ::action_context & action_context);

      virtual void on_update();

   };


} //  namespace user



