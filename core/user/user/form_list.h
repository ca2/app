#pragma once


#include "form_mesh.h"
#include "list.h"


namespace user
{


   class CLASS_DECL_CORE form_list:
      virtual public ::user::form_mesh,
      virtual public ::user::list
   {
   public:


      //index_map < pointer_array < ::user::interaction > > m_mapControl;


      form_list();
      ~form_list() override;


      // ::core::application* get_app();
      // ::core::session* get_session();
      // ::core::system* get_system();


      void _001DrawSubItem(::draw2d::graphics_pointer & pgraphics, draw_list_subitem * psubitem) override;

      using ::user::list::_001HitTest_;
      bool _001HitTest_(const ::point_i32 & point, ::collection::index&iItem, ::collection::index&iSubItem) override;


      virtual ::user::interaction* get_control(::user::list_column * pcolumn, ::collection::index iItem);

      virtual void on_check_save(::user::interaction* puserinteraction);
      virtual void on_check_load(::user::interaction* puserinteraction);

      void control_get_client_rect(::user::interaction * pinteraction, ::rectangle_i32 & prectangle) override;

      void control_get_window_rect(::user::interaction * pinteraction, ::rectangle_i32 & rectangle) override;

      bool control_001DisplayHitTest(const ::point_i32 & point);

      virtual bool _001IsEditing() override;

      bool _001IsPointInside(::user::interaction * pinteraction, const point_i64 & point) override;

      void _001OnAddColumn(list_column * pcolumn) override;

      virtual void _001HideEditingControls();
      virtual void _001HideControl(::user::interaction * pinteraction);
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      //void _001UpdateColumns() override;
      ::user::interaction * _001GetEditControl();
      void _001SetEditControl(::user::interaction * pinteraction);
      ::pointer<list_column>new_list_column_with_control(::user::interaction * puserinteraction) override;
      bool _001AddControl(::user::interaction * pinteraction) override;
      void _001PlaceControl(::user::interaction * pinteraction, ::collection::index iEditItem, bool bClick = false, bool bOnlySizeAndPosition = false) override;
      virtual void _001OnShowControl(::user::interaction * pinteraction);
      ::user::interaction * _001GetControl(::collection::index iItem, ::collection::index iSubItem) override;
      virtual ::user::interaction * _001GetControl(draw_list_subitem * psubitem);
      bool on_click(::item * pitem) override;
      bool on_right_click(::item * pitem) override;
      void _001OnTimer(::timer * ptimer) override;

      using list::get_selection;
      void get_selection(const ::scoped_string & scopedstrDataKey,::string_array & stra) override;
      DECLARE_MESSAGE_HANDLER(_001OnMessageNotify);

      DECLARE_MESSAGE_HANDLER(on_message_scroll_y);
      DECLARE_MESSAGE_HANDLER(on_message_scroll_x);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);

      void on_update_item_count() override;

      void _001UpdateComboBox(::user::interaction * pinteraction) override;

      void _001UpdateEdit(::user::interaction * pinteraction) override;
      bool _001SaveEdit(::user::interaction * pinteraction) override;

      bool _001OnMouseActivate(::windowing::window * pDesktopWnd,::u32 nHitTest,const ::atom & atom,lresult & iResult) override;


      void install_message_routing(::channel * pchannel) override;

      void handle(::topic * ptopic, ::context * pcontext) override;

      void on_column_update() override;


      void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;


      virtual bool _001UpperEditableControl(::collection::index & iItem, ::collection::index & iSubItem);
      virtual bool _001PreviousEditableControl(::collection::index & iItem, ::collection::index & iSubItem);
      virtual bool _001NextEditableControl(::collection::index & iItem, ::collection::index & iSubItem);
      virtual bool _001LowerEditableControl(::collection::index & iItem, ::collection::index & iSubItem);

      //virtual void _001DrawSubItem(draw_list_item * pdrawitem);

      virtual ::enum_check _001GetSubItemCheck(::collection::index iItem, ::collection::index iSubItem);
      virtual bool _001SetSubItemCheck(::collection::index iItem, ::collection::index iSubItem, ::enum_check echeck);
      virtual bool _001IsSubItemEnabled(::collection::index iItem, ::collection::index iSubItem);

   };


} // namespace user



