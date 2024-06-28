#pragma once


#include "acme/user/user/property.h"


namespace user
{


   class CLASS_DECL_AXIS multiple_option :
      virtual public ::user::interaction
   {
   public:


      ::user::property              m_propertyOption;


      ::atom_array                  m_atomaOptions;
      ::pointer_array < ::image >   m_imagea;
      ::string_array                m_straName;


      multiple_option();
      ~multiple_option() override;


      void user_multiple_option_common_construct();


      void install_message_routing(::channel * pchannel) override;


      ::pointer < ::particle > clone() override;


      ::write_text::font_pointer get_font(style* pstyle, enum_element eelement = e_element_none, ::user::enum_state estate = e_state_none) override;


      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      virtual enum_input_type preferred_input_type() override;

      virtual bool has_action_hover();



      virtual ::collection::count get_option_count() const;

      //virtual bool create_interaction(::user::interaction * pinteractionParent, const ::atom & atom) override;

      bool get_element_rectangle(::rectangle_i32 & prectangle, enum_element eelement) override;

      ::item_pointer on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder) override;

      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_key_up);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(on_message_move);


      void on_reposition() override;

      virtual void _on_reposition();

      

      void on_set_keyboard_focus() override;
      void on_kill_keyboard_focus() override;




      bool should_show_keyboard_focus() override;


      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      void handle(::topic * ptopic, ::context * pcontext) override;



      void set_current_item(::item * pitem, const ::action_context & actioncontext) override;


      virtual void set_current_item_by_atom(const ::atom & atom, const ::action_context & action_context);
      virtual void set_current_item_by_text(const ::scoped_string & scopedstr, const ::action_context & action_context);
      virtual void set_current_item_by_index(::collection::index iIndex, const ::action_context & action_context);
      virtual string get_current_item_text();
      virtual ::atom get_current_item_atom();


      virtual ::collection::index add_item(const ::scoped_string & scopedstr, const ::atom & atom);
      virtual ::collection::index erase_item_at(::collection::index nIndex);
      virtual ::collection::index insert_item_at(::collection::index nIndex, const ::string & pszString);

      virtual void reset_content();
      

      bool keyboard_focus_is_focusable() override;


   };


} //  namespace user



