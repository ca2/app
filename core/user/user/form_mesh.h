#pragma once


#include "axis/user/form/window.h"
#include "mesh.h"


namespace user
{


   class CLASS_DECL_CORE form_mesh:
      virtual public ::user::form_window,
      virtual public ::user::mesh
   {
   public:


      class CLASS_DECL_CORE control_keep
      {
      public:
         inline control_keep(form_mesh * pformmesh, ::item * pitem)
         {
            m_pformmesh                      = pformmesh;
            m_pitem                          = pformmesh->m_pitemControl;
            pformmesh->m_pitemControl        = pitem;
         }
         inline control_keep(form_mesh * pformmesh,const ::int_point & point)
         {
            m_pformmesh                      = pformmesh;
            m_pitem                          = pformmesh->m_pitemControl;
            pformmesh->control_001DisplayHitTest(point);
         }
         inline ~control_keep()
         {
            m_pformmesh->m_pitemControl      = m_pitem;
         }
         form_mesh *             m_pformmesh;
         ::item_pointer          m_pitem;
      };


      ::pointer<::user::interaction>     m_pcontrolEdit;

      ::collection::count                             m_iClickCount;
      ::item_pointer                      m_pitemClick;

      ::item_pointer                      m_pitemControl;


      form_mesh();
      ~form_mesh() override;


      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void _001DrawSubItem(draw_mesh_subitem * pdrawitem) override;

      //void _000OnMouse(::message::mouse * pmouse) override;


      virtual bool _001HitTest_(const ::int_point & point, ::collection::index&iItem, ::collection::index&iSubItem) override;

      void control_get_client_rect(::user::interaction * pinteraction, ::int_rectangle & rectangle) override;

      void control_get_window_rect(::user::interaction * pinteraction, ::int_rectangle & rectangle) override;

      bool control_001DisplayHitTest(const ::int_point & point);

      bool _001IsEditing() override;

      bool _001IsPointInside(::user::interaction * pinteraction, const long_long_point & point) override;

      void _001HideEditingControls();
      void _001HideControl(::user::interaction * pinteraction);
      //virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
      //virtual LRESULT _001BaseWndGetProperty(EProperty eprop,lparam lparam) override;

      // void _001UpdateColumns();
      ::user::interaction * _001GetEditControl();
      void _001SetEditControl(::user::interaction * pinteraction);
      virtual void _001PlaceControl(::user::interaction * pinteraction, ::collection::index iEditItem, bool bClick = false, bool bOnlySizeAndPosition = false);
      virtual ::user::interaction * _001GetControl(::collection::index iItem, ::collection::index iSubItem);
      bool on_click(::item * pitem, ::user::mouse * pmouse) override;
      void on_timer(::timer * ptimer) override;

      
      virtual void get_selection(const ::scoped_string & scopedstrDataKey, ::string_array &stra) override;


      DECLARE_MESSAGE_HANDLER(_001OnNotify);
      DECLARE_MESSAGE_HANDLER(_001OnMessageNotify);

      DECLARE_MESSAGE_HANDLER(on_message_scroll_y);
      DECLARE_MESSAGE_HANDLER(on_message_scroll_x);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);

      virtual bool _001OnMouseActivate(::windowing::window * pDesktopWnd,unsigned int nHitTest,const ::atom & atom,lresult & iResult);


      void install_message_routing(::channel * pchannel) override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      virtual bool _001OnControlSetFocus(::user::interaction * pinteraction) override;

      virtual bool _001OnControlKillFocus(::user::interaction * pinteraction) override;

      virtual bool _001OnSetItemText(::user::interaction * pinteraction, ::collection::index iItem, ::collection::index iSubItem);


   };


} // namespace user








