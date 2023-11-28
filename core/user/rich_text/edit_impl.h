#pragma once


#include "edit.h"
#include "base/user/user/show.h"


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_CORE edit_impl :
         virtual public ::user::rich_text::edit
      {
      public:


         bool                             m_bComposing;
         //::pointer<data>                  m_pdata;
         bool                             m_bSelDrag;
         ::pointer<::message::key>        m_pkeymessageLast;
         bool                             m_bKeyPressed;
         bool                             m_bEditable2;
         /// If true, mouse events over empty
         /// areas of text continue through message routing.
         bool                             m_bClickThrough;



         edit_impl();
         ~edit_impl() override;


         //virtual void initialize_impact(::user::document * pdocument) override;


         virtual void on_after_change(const ::atom & atom) override;
         virtual double get_rotate() override;


         void draw_control_background(::draw2d::graphics_pointer & pgraphics) override;

         void _001OnNcPostDraw(::draw2d::graphics_pointer & pgraphics) override;

         //virtual void do_layout() override;

         //virtual ::pointer<span> add_start_of_line_span(::e_align ealignEndOfLine);

         virtual ::pointer<span> add_span(::e_align ealignEndOfLine, bool bEndOfLine);

         //virtual ::pointer<span> add_end_of_line_span();

         virtual ::item_pointer on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder) override;

         virtual bool get_item_rect(::rectangle_i32 * prectangle, index i) override;

         virtual bool get_element_rectangle(::rectangle_i32 * prectangle, index i, enum_element eelement) override;

         virtual ::size_f64 get_size() override;

         // void assert_ok() const override;
         // void dump(dump_context & dumpcontext) const override;

         bool _001GetItemText(string & str, index iItem) override;
         bool _001IsPointInside(const ::point_i32 & point) override;
         void update_data(bool bSaveAndValidate) override;
         virtual void update_placement() override;

         //document * get_document();
         /*virtual i64 increment_reference_count(REFERENCING_DEBUGGING_PARAMETERS) override
         {
            return ::object::increment_reference_count(REFERENCING_DEBUGGING_ARGS);
         }
         virtual i64 decrement_reference_count(REFERENCING_DEBUGGING_PARAMETERS) override
         {
            return ::object::decrement_reference_count(REFERENCING_DEBUGGING_ARGS);
         }*/

         bool set_text_editable(bool bEditable = true) override;

         bool is_text_editable() override;

         bool is_text_editor() override;

         void _001OnDeleteText() override;

         using rich_text::edit::on_selection_change;
         void on_selection_change() override;

         void insert_text(string str, bool bForceNewStep, const ::action_context & context) override;

         void install_message_routing(::channel * psender) override;

         void _001CallOnDraw(::draw2d::graphics_pointer & pgraphics) override;

         void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

         void draw_impl(::draw2d::graphics_pointer & pgraphics) override;

         void _000DrawImpl(::draw2d::graphics_pointer & pgraphics) override;

         ::pointer<format_tool>get_format_tool(bool bCreate) override;

         ::user::rich_text::format_host * get_format_host() override;

         ::pointer<::user::rich_text::format> get_selection_common_format() override;


         //::user::tool_window * tool_window(enum_tool etool, bool bCreate) override;

         using ::user::interaction::_001GetText;
         void _001GetText(string & str) override;
         void _001GetLayoutText(string & str) override;

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
         // DECLARE_MESSAGE_HANDLER(on_message_set_focus);
         //DECLARE_MESSAGE_HANDLER(on_message_kill_focus);


         void _001OnTimer(::timer * ptimer) override;


         void key_to_char(::message::key * pkey) override;


         bool keyboard_focus_is_focusable() override;


         void keyboard_focus_OnChar(::message::message * pmessage) override;




         void on_set_keyboard_focus() override;


         void on_kill_keyboard_focus() override;


         void handle(::topic * ptopic, ::context * pcontext) override;


         strsize _001GetTextLength() override;

         //void write(::binary_stream & stream) const override;
         //void read(::binary_stream & stream) override;

         void _001GetSel(strsize & iBeg, strsize & iEnd) override;
         void _001GetSelLineText(string & str) override;


         void get_text_composition_area(::rectangle_i32 & r) override;
         void on_text_composition(string str) override;
         void on_text_composition_done() override;
         bool edit_undo() override;


         void read_from_stream(::binary_stream & binarystream) override;
         void write_to_stream(::binary_stream & binarystream) override;


      };

      using edit_impact_impl = ::user::show < ::user::rich_text::edit_impl >;

   } // namespace rich_text


} // namespace user



