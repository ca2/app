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


      inline ::core::application* get_app() const { return m_pcontext ? m_pcontext->m_pcoreapplication : nullptr; }
      inline ::core::session* get_session() const { return m_pcontext ? m_pcontext->m_pcoresession : nullptr; }
      inline ::core::system* get_system() const { return acmesystem() ? acmesystem()->m_pcoresystem : nullptr; }


      void _001DrawSubItem(::draw2d::graphics_pointer & pgraphics, draw_list_subitem * psubitem) override;

      using ::user::list::_001HitTest_;
      bool _001HitTest_(const ::point_i32 & point, index&iItem, index&iSubItem) override;


      virtual ::user::interaction* get_control(::user::list_column * pcolumn, ::index iItem);

      virtual void on_check_save(::user::interaction* puserinteraction);
      virtual void on_check_load(::user::interaction* puserinteraction);

      void control_get_client_rect(::user::interaction * pinteraction, RECTANGLE_I32 & prectangle) override;

      void control_get_window_rect(::user::interaction * pinteraction, RECTANGLE_I32 & rectangle) override;

      bool control_001DisplayHitTest(const ::point_i32 & point);

      virtual bool _001IsEditing() override;

      bool _001IsPointInside(::user::interaction * pinteraction, const point_i64 & point) override;

      void _001OnAddColumn(list_column * pcolumn) override;

      virtual void _001HideEditingControls();
      virtual void _001HideControl(::user::interaction * pinteraction);
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void _001UpdateColumns() override;
      ::user::interaction * _001GetEditControl();
      void _001SetEditControl(::user::interaction * pinteraction);
      bool _001AddControl(::user::interaction * pinteraction) override;
      void _001PlaceControl(::user::interaction * pinteraction, index iEditItem, bool bClick = false, bool bOnlySizeAndPosition = false) override;
      virtual void _001OnShowControl(::user::interaction * pinteraction);
      ::user::interaction * _001GetControl(index iItem, index iSubItem) override;
      virtual ::user::interaction * _001GetControl(draw_list_subitem * psubitem);
      virtual bool on_click(::item * pitem) override;
      bool on_right_click(::item * pitem) override;
      void _001OnTimer(::timer * ptimer) override;

      using list::_001GetSelection;
      void _001GetSelection(::database::key & key,::database::selection & selection) override;

      DECLARE_MESSAGE_HANDLER(_001OnNotify);
      DECLARE_MESSAGE_HANDLER(_001OnMessageNotify);

      DECLARE_MESSAGE_HANDLER(_001OnVScroll);
      DECLARE_MESSAGE_HANDLER(_001OnHScroll);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);

      bool _001OnUpdateItemCount(u32 dwFlags = 0) override;

      void _001UpdateComboBox(::user::interaction * pinteraction) override;

      void _001UpdateEdit(::user::interaction * pinteraction) override;
      bool _001SaveEdit(::user::interaction * pinteraction) override;

      bool _001OnMouseActivate(::user::interaction_impl * pDesktopWnd,::u32 nHitTest,const ::atom & atom,lresult & iResult) override;


      void install_message_routing(::channel * pchannel) override;

      void handle(::topic * ptopic, ::context * pcontext) override;

      void _001OnColumnChange() override;


      void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;


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



