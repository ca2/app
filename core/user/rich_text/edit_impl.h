#pragma once


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_CORE edit_impl :
         virtual public ::user::show < ::user::rich_text::edit >
      {
      public:


         bool                          m_bComposing;
         __pointer(data)               m_pdata;
         bool                          m_bSelDrag;
         __pointer(::message::key)     m_pkeymessageLast;
         bool                          m_bKeyPressed;
         bool                          m_bEditable2;
         /// If true, mouse events over empty
         /// areas of text continue through message routing.
         bool                          m_bClickThrough;

         bool                          m_bPendingSelectionChange;


         edit_impl();
         ~edit_impl() override;


         virtual void initialize_edit_impl(document * pdocument);


         virtual void on_after_change(const ::atom & atom) override;
         virtual double get_rotate() override;


         virtual void draw_control_background(::draw2d::graphics_pointer & pgraphics) override;

         //virtual void do_layout() override;

         __pointer(span) add_span(::e_align ealignNewLine = e_align_none);

         virtual void on_hit_test(::item & item) override;

         virtual bool get_item_rect(RECTANGLE_I32 * prectangle, index i) override;

         virtual bool get_element_rect(RECTANGLE_I32 * prectangle, index i, enum_element eelement) override;

         virtual ::size_f64 get_size() override;

         void assert_ok() const override;
         void dump(dump_context & dumpcontext) const override;

         bool _001GetItemText(string & str, index iItem) override;
         bool _001IsPointInside(const ::point_i32 & point) override;
         void update_data(bool bSaveAndValidate) override;
         virtual void update_placement() override;

         document * get_document();
         /*virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
         {
            return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
         }
         virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
         {
            return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
         }*/

         bool set_text_editable(bool bEditable = true) override;

         bool is_text_editable() const override;

         bool is_text_editor() const override;

         void _001OnDeleteText() override;

         void on_selection_change() override;

         void insert_text(string str, bool bForceNewStep, const ::action_context & context) override;

         void install_message_routing(::channel * psender) override;

         void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

         void draw_impl(::draw2d::graphics_pointer & pgraphics) override;

         __pointer(format_tool) get_format_tool(bool bCreate);

         //::user::tool_window * tool_window(enum_tool etool, bool bCreate) override;

         using ::user::interaction::_001GetText;
         void _001GetText(string & str) const override;
         void _001GetLayoutText(string & str) const override;

         void on_layout(::draw2d::graphics_pointer & pgraphics) override;


         ::user::rich_text::data * get_rich_text_data() override;

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
         // DECLARE_MESSAGE_HANDLER(_001OnSetFocus);
         //DECLARE_MESSAGE_HANDLER(_001OnKillFocus);


         void _001OnTimer(::timer * ptimer) override;


         void key_to_char(::message::key * pkey) override;


         bool keyboard_focus_is_focusable() const override;


         void keyboard_focus_OnChar(::message::message * pmessage) override;


         void on_set_keyboard_focus() override;


         void on_kill_keyboard_focus() override;


         void handle(::topic * ptopic, ::context * pcontext) override;


         strsize _001GetTextLength() const override;

         ::stream & write(::stream & stream) const override;
         ::stream & read(::stream & stream) override;

         void _001GetSel(strsize & iBeg, strsize & iEnd) const override;
         void _001GetSelLineText(string & str) const override;


         void get_text_composition_area(::rectangle_i32 & r) override;
         void on_text_composition(string str) override;
         void on_text_composition_done() override;
         bool edit_undo() override;


      };

      //using edit_impact = ::user::show < ::user::rich_text::edit_impl >;

   } // namespace rich_text


} // namespace user



