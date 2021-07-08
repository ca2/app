#pragma once


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


      __pointer(::write_text::font_list)   m_pfontlist;
      ::rectangle_i32                           m_rectMargin;
      bool                             m_bEnsureVisible;
      bool                             m_bFirstShown;
      ::i32                            m_iLayoutSerial;


      font_list();
      virtual ~font_list();


      void user_font_list_common_construct();


      //virtual void on_font_change();


      virtual void on_change_combo_sel(index iSel) override;

      //void attach_visual_font_list(::write_text::font_list * pdata);
      //virtual void on_update_data(::write_text::font_list * pdata, i32 iHint);

      //virtual void font_list_update();

      //virtual void assert_valid() const;
      //virtual void dump(dump_context & dumpcontext) const;

      //virtual bool get_color(::color::color & color32, e_color ecolor, ::user::interaction * pinteraction) override;


      virtual void install_message_routing(::channel * pchannel) override;

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;


      virtual ::user::item current_item() override;

      virtual ::user::item hover_item() override;

      string get_cur_sel_face_name();

      string get_cur_hover_face_name();

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_close);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);

      virtual void _001EnsureVisible(index iItem) override;


      virtual void _001OnTimer(::timer * ptimer) override;

      virtual void on_hit_test(::user::item & item) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool set_sel_by_name(string str);

      virtual void ensure_sel_visible();

      virtual void __on_draw_ensure_sel_visible();

      virtual void query_full_size(::draw2d::graphics_pointer& pgraphics, ::SIZE_I32 * psize) override;


      virtual bool update_data(bool bSaveAndValidate) override;

      virtual void set_font_list_type(::write_text::font_list::enum_type etype);


   };


   typedef ::user::show < ::user::font_list > font_list_view;


} // namespace user



