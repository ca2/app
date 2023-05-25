#pragma once


#include "base/user/user/picture_interaction.h"
#include "aura/user/user/text_composition_composite.h"


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_CORE edit :
         virtual public ::user::interaction,
         virtual public ::user::picture_interaction,
         virtual public text_composition_composite
//#ifdef WINDOWS_DESKTOP
  //       , virtual public ::imm_client
//#endif
      {
      public:


         edit();
         ~edit() override;


         virtual void on_after_change(const ::atom & atom);
         double get_rotate() override;


         //::pointer<span>add_span(::e_align ealignNewLine = e_align_none);

         ::item_pointer on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder) override;

         virtual bool get_item_rect(::rectangle_i32 * prectangle, index i);

         virtual bool get_element_rect(::rectangle_i32 * prectangle, index i, enum_element eelement);


         virtual ::size_f64 get_size() override;

         virtual void do_layout();

         // void assert_ok() const override;
         // void dump(dump_context & dumpcontext) const override;

         virtual bool _001GetItemText(string & str, index iItem);
         virtual bool _001IsPointInside(const ::point_i32 & point) override;
         virtual void update_data(bool bSaveAndValidate) override;
         virtual void update_placement() override;


         //virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
         //{
         //   return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
         //}
         //virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
         //{
         //   return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
         //}

         virtual ::user::rich_text::data * get_rich_text_data();

         virtual bool set_text_editable(bool bEditable = true) override;

         bool is_text_editable() override;

         bool is_text_editor() override;

         virtual void _001OnDeleteText();

         virtual void on_selection_change();

         virtual void install_message_routing(::channel * psender) override;

         virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

         virtual void draw_impl(::draw2d::graphics_pointer & pgraphics) override;

         ::pointer<format_tool>get_format_tool(bool bCreate);

         using ::user::interaction::_001GetText;
         void _001GetText(string & str) override;
         virtual void _001GetLayoutText(string & str);

         virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

         DECLARE_MESSAGE_HANDLER(on_message_create);
         DECLARE_MESSAGE_HANDLER(on_message_destroy);
         DECLARE_MESSAGE_HANDLER(on_message_show_window);
         DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
         DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
         DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
         DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
         DECLARE_MESSAGE_HANDLER(on_message_character);
         DECLARE_MESSAGE_HANDLER(on_message_key_down);
         DECLARE_MESSAGE_HANDLER(on_message_key_up);
         //DECLARE_MESSAGE_HANDLER(on_message_set_focus);
         //DECLARE_MESSAGE_HANDLER(on_message_kill_focus);


         virtual void _001OnTimer(::timer * ptimer) override;


         virtual void key_to_char(::message::key * pkey);

         virtual void on_set_keyboard_focus() override;

         virtual void on_kill_keyboard_focus() override;

         bool keyboard_focus_is_focusable() override;


         void keyboard_focus_OnChar(::message::message * pmessage) override;


         void handle(::topic * ptopic, ::context * pcontext) override;


         strsize _001GetTextLength() override;

         //void write(::binary_stream < FILE > & stream) const override;
         //void read(::binary_stream < FILE > & stream) override;

         void _001GetSel(strsize & iBeg, strsize & iEnd) override;
         virtual void _001GetSelLineText(string & str);


         void get_text_composition_area(::rectangle_i32 & r) override;
         void on_text_composition(string str) override;
         void on_text_composition_done() override;
         bool edit_undo() override;


         bool has_text_input() override;


      };


   } // namespace rich_text


} // namespace user






