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
         class ::time                     m_timeStartDrag;
         ::pointer<::message::key>        m_pkeymessageLast;
         bool                             m_bKeyPressed;
         bool                             m_bEditable2;
         /// If true, mouse happenings over empty
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

         virtual ::item_pointer on_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;

         virtual bool get_item_rect(::int_rectangle * prectangle, ::collection::index i) override;

         virtual bool get_element_rectangle(::int_rectangle * prectangle, ::collection::index i, enum_element eelement) override;

         virtual ::double_size get_size() override;

         // void assert_ok() const override;
         // void dump(dump_context & dumpcontext) const override;

         bool _001GetItemText(string & str, ::collection::index iItem) override;
         bool _001IsPointInside(const ::int_point & point) override;
         void update_data(bool bSaveAndValidate) override;
         virtual void update_placement() override;

         //document * get_document();
         /*virtual long long increment_reference_count() override
         {
            return ::object::increment_reference_count();
         }
         virtual long long decrement_reference_count() override
         {
            return ::object::decrement_reference_count();
         }*/

         bool set_text_editable(bool bEditable = true) override;

         bool is_text_editable() override;

         bool is_text_editor() override;

         void _001OnDeleteText() override;

         using rich_text::edit::on_selection_change;
         void on_selection_change() override;

         void insert_text(const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context & context) override;

         void install_message_routing(::channel * psender) override;

         void _001CallOnDraw(::draw2d::graphics_pointer & pgraphics) override;

         ::double_point get_point_transform() override;

         void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

         void draw_impl(::draw2d::graphics_pointer & pgraphics) override;

         void _000DrawImpl(::draw2d::graphics_pointer & pgraphics) override;

         ::pointer<format_tool>get_format_tool(bool bCreate) override;

         ::user::rich_text::format_host * get_format_host() override;

         ::pointer<::user::rich_text::format> get_selection_common_format() override;


         //::user::tool_window * tool_window(enum_tool etool, bool bCreate) override;

         //using ::user::interaction::get_text;
         //void get_text(string & str) override;
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
         // DECLARE_MESSAGE_HANDLER(on_message_set_focus);
         //DECLARE_MESSAGE_HANDLER(on_message_kill_focus);


         void on_timer(::timer * ptimer) override;


         void key_to_char(::message::key * pkey) override;


         bool keyboard_focus_is_focusable() override;


         void keyboard_focus_OnChar(::message::message * pmessage) override;




         void on_set_keyboard_focus() override;


         void on_kill_keyboard_focus() override;


         void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


         //character_count get_text_length() override;

         //void write(::binary_stream & stream) const override;
         //void read(::binary_stream & stream) override;

         void get_text_selection(character_count & iBeg, character_count & iEnd) const override;
         void _001GetSelLineText(string & str) override;


         void get_text_composition_area(::int_rectangle & r) override;
         void on_text_composition(const ::scoped_string & scopedstr) override;
         void on_text_composition_done() override;
         bool edit_undo() override;


         void read_from_stream(::binary_stream & binarystream) override;
         void write_to_stream(::binary_stream & binarystream) override;


      };

      using edit_impact_impl = ::user::show < ::user::rich_text::edit_impl >;

   } // namespace rich_text


} // namespace user



