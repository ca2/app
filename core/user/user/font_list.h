#pragma once


#include "axis/user/user/list_box.h"


namespace user
{


   class font_list;


   class CLASS_DECL_CORE font_list :
      virtual public list_box
   {
   public:



      enum timer
      {

         e_timer_update_font = USER_TIMER,

      };


      ::pointer<::write_text::font_list>     m_pfontlist;
      ::int_rectangle                        m_rectangleMargin;
      bool                                   m_bEnsureVisible;
      bool                                   m_bFirstShown;
      int                                  m_iLayoutSerial;
      ::string                               m_strFontBranch;


      font_list();
      ~font_list() override;


      void user_font_list_common_construct();


      //virtual void on_font_change();


      virtual void on_change_combo_sel(::collection::index iSel) override;

      //void attach_visual_font_list(::write_text::font_list * pdata);
      //virtual void on_update_data(::write_text::font_list * pdata, int iHint);

      //virtual void font_list_update();

      //// void assert_ok() const override;
      //// void dump(dump_context & dumpcontext) const override;

      //virtual bool get_color(::color::color & color32, e_color ecolor, ::user::interaction * pinteraction) override;

      void install_message_routing(::channel * pchannel) override;

      void _001OnNcClip(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;




      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


      virtual ::item_pointer current_item() override;

      virtual ::item_pointer hover_item() override;




      virtual string get_cur_sel_face_name();

      virtual string get_cur_hover_face_name();


      string get_sel_by_name() override;

      string get_hover_by_name() override;



      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_close);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);

      virtual void ensure_item_visible_by_index(::collection::index iItem) override;


      virtual void on_timer(::timer * ptimer) override;

      status < int_rectangle > item_rectangle(::item * pitem, ::user::enum_layout elayout) override;

      virtual ::item_pointer on_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;

      void on_update_hover(::item * pitem) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      bool set_sel_by_name(const ::scoped_string & scopedstrName) override;

      void ensure_sel_visible() override;

      virtual void __on_draw_ensure_sel_visible();

      virtual void query_full_size(::draw2d::graphics_pointer& pgraphics, ::int_size * psize) override;


      virtual void update_data(bool bSaveAndValidate) override;

      virtual void set_font_list_type(::write_text::enum_font_list efoldertype);
      virtual void set_font_branch(const ::scoped_string & scopedstrFontBranch);


   };


} // namespace user



