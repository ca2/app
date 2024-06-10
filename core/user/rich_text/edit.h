#pragma once


#include "selection.h"
#include "aura/user/user/text_composition_composite.h"
#include "base/user/user/picture_interaction.h"


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_CORE edit :
         virtual public ::user::interaction,
         virtual public ::user::picture_interaction,
         virtual public text_composition_composite,
         virtual public ::user::rich_text::selection
//#ifdef WINDOWS_DESKTOP
  //       , virtual public ::imm_client
//#endif
      {
      public:
         bool                             m_bPendingSelectionChange;

         /// runtime span, ephemeral, derived
/// should be easily rebuildable from "storage" data and a client rectangle_i32
         pointer< pointer_array < line > >            m_plinea;
         strsize                                      m_iSelBeg;
         strsize                                      m_iSelEnd;
         ::collection::index                                        m_iSelLine;
         class ::time                                 m_timeCaretPeriod;
         //index                                      m_iFormatDefault;
         bool                                         m_bCaretRight;
         ::pointer < ::user::rich_text::data >        m_prichtextdataOwned;
         bool                                         m_bShouldDrawOverride;
         


         edit();
         ~edit() override;


         virtual void on_after_change(const ::atom & atom);
         double get_rotate() override;


         //::pointer<span>add_span(::e_align ealignNewLine = e_align_none);

         ::item_pointer on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder) override;

         virtual bool get_item_rect(::rectangle_i32 * prectangle, ::collection::index i);

         virtual bool get_element_rectangle(::rectangle_i32 * prectangle, ::collection::index i, enum_element eelement);


         ::user::drawable * get_drawable() override;

         bool should_draw() override;

         bool is_this_visible(enum_layout elayout = e_layout_design) override;


         virtual ::size_f64 get_size() override;

         virtual void do_layout();

         // void assert_ok() const override;
         // void dump(dump_context & dumpcontext) const override;

         virtual bool _001GetItemText(string & str, ::collection::index iItem);
         virtual bool _001IsPointInside(const ::point_i32 & point) override;
         virtual void update_data(bool bSaveAndValidate) override;
         virtual void update_placement() override;


         virtual void on_selection_change(format * pformat);
         virtual void get_selection_intersection_format(format * pformat, ::collection::index iSelBeg, ::collection::index iSelEnd);

         virtual void _001SetSelFontFormat(const format * pformat, const e_attribute & eattribute);
         virtual void _001InsertText(const ::string & psz, format * pformatParam = nullptr);
         virtual void _001GetLayoutText(string & str) const;


         //virtual i64 increment_reference_count() override
         //{
         //   return ::object::increment_reference_count();
         //}
         //virtual i64 decrement_reference_count() override
         //{
         //   return ::object::decrement_reference_count();
         //}

         ::data::data * _get_data(const ::atom & atom) override;

         virtual ::user::rich_text::data * get_rich_text_data();

         virtual bool set_text_editable(bool bEditable = true) override;

         bool is_text_editable() override;

         bool is_text_editor() override;

         virtual void _001OnDeleteText();

         virtual ::rectangle_f64 get_drawing_rect();

         virtual void internal_update_sel_char();

         virtual void do_layout(::draw2d::graphics_pointer & pgraphics);

         virtual void on_selection_change();

         void install_message_routing(::channel * psender) override;

         void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

         void draw_impl(::draw2d::graphics_pointer & pgraphics) override;

         virtual ::pointer<format_tool>get_format_tool(bool bCreate);

         virtual ::user::rich_text::format_host * get_format_host();

         ::pointer<::user::rich_text::format> get_selection_common_format() override;

         using ::user::interaction::get_text;
         //void get_text(string & str) override;
         virtual void _001GetLayoutText(string & str);


         void on_layout(::draw2d::graphics_pointer & pgraphics) override;

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


         void _001OnTimer(::timer * ptimer) override;


         virtual void key_to_char(::message::key * pkey);

         void on_set_keyboard_focus() override;

         void on_kill_keyboard_focus() override;

         bool keyboard_focus_is_focusable() override;


         void keyboard_focus_OnChar(::message::message * pmessage) override;


         void handle(::topic * ptopic, ::context * pcontext) override;

         virtual void draw_text(::draw2d::graphics_pointer & pgraphics, const ::rectangle_f64 & rectangle);

         virtual strsize _001GetLayoutTextLength() const;

         //strsize get_text_length() override;

         //void write(::binary_stream & stream) const override;
         //void read(::binary_stream & stream) override;

         void _001GetSel(strsize & iBeg, strsize & iEnd) override;
         virtual void _001GetSelLineText(string & str);


         void get_text_composition_area(::rectangle_i32 & r) override;
         void on_text_composition(string str) override;
         void on_text_composition_done() override;
         bool edit_undo() override;


         virtual strsize get_sel_beg();
         virtual strsize get_sel_end();

         virtual ::collection::index SelToLine(strsize i);
         virtual strsize LineColumnToSel(::collection::index iLine, strsize iColumn);


         bool has_text_input() override;

         virtual strsize _hit_test(point_f64 point);
         virtual strsize _hit_test_line_x(::collection::index iLine, double x);


      };


   } // namespace rich_text


} // namespace user






