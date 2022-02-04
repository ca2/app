#pragma once


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


         virtual void on_after_change(::enum_topic etopic);
         double get_rotate() override;


         //__pointer(span) add_span(::e_align ealignNewLine = e_align_none);

         void on_hit_test(::item & item) override;

         virtual bool get_item_rect(RECTANGLE_I32 * prectangle, index i);

         virtual bool get_element_rect(RECTANGLE_I32 * prectangle, index i, enum_element eelement);


         virtual ::size_f64 get_size() override;

         virtual void do_layout();

         void assert_valid() const override;
         void dump(dump_context & dumpcontext) const override;

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

         virtual bool is_text_editable() const override;

         virtual bool is_text_editor() const override;

         virtual void _001OnDeleteText();

         virtual void on_selection_change();

         virtual void install_message_routing(::channel * psender) override;

         virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

         virtual void draw_impl(::draw2d::graphics_pointer & pgraphics) override;

         __pointer(format_tool) get_format_tool(bool bCreate);

         using ::user::interaction::_001GetText;
         virtual void _001GetText(string & str) const override;
         virtual void _001GetLayoutText(string & str) const;

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
         //DECLARE_MESSAGE_HANDLER(_001OnSetFocus);
         //DECLARE_MESSAGE_HANDLER(_001OnKillFocus);


         virtual void _001OnTimer(::timer * ptimer) override;


         virtual void key_to_char(::message::key * pkey);

         virtual void on_set_keyboard_focus() override;

         virtual void on_kill_keyboard_focus() override;

         virtual bool keyboard_focus_is_focusable() const override;


         virtual void keyboard_focus_OnChar(::message::message * pmessage) override;


         virtual void handle(::topic * psubject, ::context * pcontext) override;


         virtual strsize _001GetTextLength() const override;

         virtual ::stream & write(::stream & stream) const override;
virtual ::stream & read(::stream & stream) override;

         virtual void _001GetSel(strsize & iBeg, strsize & iEnd) const override;
         virtual void _001GetSelLineText(string & str) const;


         virtual void get_text_composition_area(::rectangle_i32 & r) override;
         virtual void on_text_composition(string str) override;
         virtual void on_text_composition_done() override;
         virtual bool edit_undo() override;


         virtual bool has_text_input() override;


      };


   } // namespace rich_text


} // namespace user






