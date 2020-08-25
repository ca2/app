#pragma once


namespace user
{


   class CLASS_DECL_CORE form_list:
      virtual public ::user::form_mesh,
      virtual public ::user::list
   {
   public:


      form_list();
      virtual ~form_list();


      virtual void _001DrawSubItem(draw_list_item * pdrawitem) override;

      using ::user::list::_001HitTest_;
      virtual bool _001HitTest_(const ::point & point, index&iItem, index&iSubItem) override;

      void _000OnMouse(::message::mouse * pmouse) override;

      void control_get_client_rect(::user::interaction * pinteraction,RECT * prect) override;

      void control_get_window_rect(::user::interaction * pinteraction,RECT * prect) override;

      bool control_001DisplayHitTest(const ::point & point);

      virtual bool _001IsEditing() override;

      virtual bool _001IsPointInside(::user::interaction * pinteraction,point64 ptt) override;

      virtual void _001OnAddColumn(list_column * pcolumn) override;

      virtual void _001HideEditingControls();
      virtual void _001HideControl(::user::interaction * pinteraction);
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      //virtual LRESULT _001BaseWndGetProperty(EProperty eprop,LPARAM lparam) override;

      void _001UpdateColumns() override;
      ::user::interaction * _001GetEditControl();
      void _001SetEditControl(::user::interaction * pinteraction);
      virtual index _001AddControl(control_descriptor  * pdescriptor) override;
      virtual void _001PlaceControl(::user::interaction * pinteraction, index iEditItem, bool bClick = false, bool bOnlySizeAndPosition = false) override;
      virtual void _001OnShowControl(::user::interaction * pinteraction);
      ::user::interaction * _001GetControl(index iItem, index iSubItem) override;
      virtual bool on_click(const ::user::item & item) override;
      virtual bool on_right_click(const ::user::item & item) override;
      void _001OnTimer(::timer * ptimer) override;

      using list::_001GetSelection;
      virtual void _001GetSelection(::database::key & key,::database::selection & selection) override;

      DECL_GEN_SIGNAL(_001OnNotify);
      DECL_GEN_SIGNAL(_001OnMessageNotify);

      DECL_GEN_SIGNAL(_001OnVScroll);
      DECL_GEN_SIGNAL(_001OnHScroll);
      DECL_GEN_SIGNAL(_001OnKeyDown);

      virtual bool _001OnUpdateItemCount(u32 dwFlags = 0) override;

      virtual void _001UpdateComboBox(::user::interaction * pinteraction) override;

      virtual void _001UpdateEdit(::user::interaction * pinteraction) override;
      virtual bool _001SaveEdit(::user::interaction * pinteraction) override;

      virtual bool _001OnMouseActivate(::user::interaction_impl * pDesktopWnd,UINT nHitTest,UINT message,LRESULT & iResult) override;


      virtual void install_message_routing(::channel * pchannel) override;

      void on_control_event(::user::control_event * pevent) override;

      virtual void _001OnColumnChange() override;


      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;


      virtual bool _001UpperEditableControl(index & iItem, index & iSubItem);
      virtual bool _001PreviousEditableControl(index & iItem, index & iSubItem);
      virtual bool _001NextEditableControl(index & iItem, index & iSubItem);
      virtual bool _001LowerEditableControl(index & iItem, index & iSubItem);

      //virtual void _001DrawSubItem(draw_list_item * pdrawitem);

      virtual ::enum_check _001GetSubItemCheck(index iItem, index iSubItem);
      virtual bool _001SetSubItemCheck(index iItem, index iSubItem, ::enum_check echeck);
      virtual bool _001IsSubItemEnabled(index iItem, index iSubItem);

   };

} // namespace user





