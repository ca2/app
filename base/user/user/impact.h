#pragma once


//#define WM_VIEW (WM_USER + 1023)
#include "aura/user/user/box.h"
#include "impact_data.h"
#include "document.h"


namespace user
{


   class CLASS_DECL_BASE impact :
      virtual public ::user::box
   {
   public:



      string                              m_strImpactTitle;
      atom                                m_atomCreator;
      ::pointer<::user::document>        m_pdocument;
      ::pointer<::user::interaction>     m_puserinteractionImpactNotify;
      bool                                m_bToolbar;


      impact();
      ~impact() override;

      
      // void dump(dump_context&) const override;
      // void assert_ok() const override;



      ::base::application * get_app();
      ::base::session * get_session();
      ::base::system * get_system();
      ::base::user * user();


      virtual void set_notify_user_interaction(::user::interaction* puserinteractionNotify);



      ::user::document * get_document() const;


      template < class DATA >
      DATA * get_typed_data()
      {

         ASSERT(::is_set(this));

         return m_pdocument->get_typed_data < DATA >();

      }


      template < class DOCUMENT >
      ::data::data * get_typed_document_data()
      {

         ASSERT(::is_set(this));

         return m_pdocument->get_typed_document_data < DOCUMENT >();

      }


      template < class DOCUMENT >
      DOCUMENT * get_typed_document()
      {

         ASSERT(::is_set(this));

         return m_pdocument->get_typed_document < DOCUMENT >();

      }


      void install_message_routing(::channel * pchannel) override;

      virtual bool IsSelected(const ::object* pDocItem) const; // support for OLE

      // OLE scrolling support (used for drag/drop as well)
      virtual bool OnScroll(::u32 nScrollCode, ::u32 nPos, bool bDoScroll = true);
      //virtual bool OnScrollBy(::size_i32 sizeScroll, bool bDoScroll = true);

      // OLE drag/drop support
      /*   virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject,
      u32 dwKeyState, const ::point_i32 & point);
      virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject,
      u32 dwKeyState, const ::point_i32 & point);
      virtual void OnDragLeave();
      virtual bool OnDrop(COleDataObject* pDataObject,
      DROPEFFECT dropEffect, const ::point_i32 & point);
      virtual DROPEFFECT OnDropEx(COleDataObject* pDataObject,
      DROPEFFECT dropDefault, DROPEFFECT dropList, const ::point_i32 & point);
      virtual DROPEFFECT OnDragScroll(u32 dwKeyState, const ::point_i32 & point);*/

      //virtual void OnPrepareDC(::draw2d::graphics_pointer & pgraphics, CPrintInfo* pInfo = nullptr);

      virtual void OnActivateImpact(bool bActivate, ::pointer<impact>pActivateImpact, ::pointer<impact>DeactiveImpact);
      virtual void OnActivateFrame(enum_activate eactivate,  ::pointer<::user::frame_window>pFrameWnd);


      virtual void set_impact_title(const ::string & strImpactTitle);
      virtual string get_impact_title() const;

      enum_window_type get_window_type() override;


      ::pointer<::user::interaction>create_impact(const ::type & type, ::user::document * pdocument = nullptr, ::user::interaction * puserinteractionParent = nullptr, const ::atom & atom = ::atom(), ::user::interaction * pviewLast = nullptr, ::user::impact_data * pdata = nullptr);

      virtual void initialize_impact(::user::document * pdocument);

      template < class VIEW >
      ::pointer<VIEW>create_impact(::user::document * pdocument = nullptr, ::user::interaction * puserinteractionParent = nullptr, const ::atom & atom = ::atom(),::user::interaction * pviewLast = nullptr, ::user::impact_data * pimpactdata = nullptr);

      template < class VIEW >
      ::pointer<VIEW>create_impact(::user::interaction * puserinteractionParent, const ::atom & atom = ::atom(),::user::interaction * pviewLast = nullptr, ::user::impact_data * pimpactdata = nullptr);

      template < class VIEW >
      ::pointer<VIEW>create_impact(::user::impact_data * pimpactdata, ::user::interaction * pviewLast = nullptr);

      ::pointer<::user::interaction>create_impact(::user::interaction * pimpactAlloc, ::user::impact_data * pimpactdata, ::user::interaction * pviewLast = nullptr);





      //virtual void CalcWindowRect(RECTANGLE_I32 * pClientRect, ::u32 nAdjustType = adjustBorder) override;



      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;

      virtual bool pre_create_window(::user::system * pusersystem) override;
      virtual void post_non_client_destroy() override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      //DECLARE_MESSAGE_HANDLER(_001OnImpact);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);

      DECLARE_MESSAGE_HANDLER(_001OnMouseActivate);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateSplitCmd);
      DECLARE_MESSAGE_HANDLER(_001OnSplitCmd);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateNextPaneMenu);
      DECLARE_MESSAGE_HANDLER(_001OnNextPaneCmd);

      DECLARE_MESSAGE_HANDLER(_001OnFilePrint);
      DECLARE_MESSAGE_HANDLER(_001OnFilePrintThumbnail);


      DECLARE_MESSAGE_HANDLER(on_message_right_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_middle_button_down);


      void OnUpdateSplitCmd(::message::command* pCmdUI);
      bool OnSplitCmd(::u32 nID);
      void OnUpdateNextPaneMenu(::message::command* pCmdUI);
      bool OnNextPaneCmd(::u32 nID);

      // not mapped commands - must be mapped in derived class
      void OnFilePrint();
      void OnFilePrintThumbnail();

      // TODO: could return a kind of - also TODO - JOB object in case of assynchronous call
      //virtual void collaborate(::job * pjob);
      virtual i32  get_total_page_count(::context * ptopic) override;


      virtual ::user::interaction::enum_type get_window_type() override;

      //virtual void on_simple_impact_update_hint(::pointer<::user::impact>pviewSender, e_hint ehint, object * pupdate);

      virtual void _001CallOnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_select() override;

      // each impact can display one or more documents but has only one document interface
      //::user::document * get_document() const;

      //      virtual bool IsSelected(const object* pDocItem) const; // support for OLE

      // OLE scrolling support (used for drag/drop as well)
      //      virtual bool OnScroll(::u32 nScrollCode, ::u32 nPos, bool bDoScroll = true);
      //    virtual bool OnScrollBy(const ::size_i32 & sizeScroll, bool bDoScroll = true);

      // OLE drag/drop support
#ifndef ANDROID
      //virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject,
      //   u32 dwKeyState, const ::point_i32 & point);
      //virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject,
      //   u32 dwKeyState, const ::point_i32 & point);
      //virtual void OnDragLeave();
      //virtual bool OnDrop(COleDataObject* pDataObject,
      //   DROPEFFECT dropEffect, const ::point_i32 & point);
      //virtual DROPEFFECT OnDropEx(COleDataObject* pDataObject,
      //   DROPEFFECT dropDefault, DROPEFFECT dropList, const ::point_i32 & point);
      //virtual DROPEFFECT OnDragScroll(u32 dwKeyState, const ::point_i32 & point);
#endif


      //virtual void OnActivateImpact(bool bActivate, ::pointer<::user::impact>pActivateImpact, ::pointer<::user::impact>DeactiveImpact);
      //virtual void OnActivateFrame(::u32 nState, ::pointer<::user::frame_window>pFrameWnd);

      //void handle(::topic * ptopic, ::context * pcontext) override;

      //      virtual void dump(dump_context &) const;
      //    // void assert_ok() const override;



      //      virtual void route_command(::message::command * pcommand, bool bRouteToKeyDescendant);

      //      virtual bool pre_create_window(::user::system * pusersystem);


      //         void install_message_routing(::channel * pchannel) override;

      virtual bool has_command_handler(::message::command * pcommand) override;

      virtual void walk_pre_translate_tree(::message::message * pmessage,::pointer<::user::interaction>puiStop);

      virtual bool has_toolbar();

      virtual ::atom get_toolbar_id();

      virtual toolbar * get_toolbar(::user::frame * pframe, bool bCreate = true);


   };



   template < class VIEW >
   inline ::pointer<VIEW>impact::create_impact(::user::document * pdocument, ::user::interaction * puserinteractionParent, const ::atom & atom, ::user::interaction * pviewLast, ::user::impact_data * pimpactdata)
   {

      return create_impact(__type(VIEW), pdocument, puserinteractionParent, atom, pviewLast, pimpactdata);

   }


   template < class VIEW >
   inline ::pointer<VIEW>impact::create_impact(::user::interaction * puserinteractionParent, const ::atom & atom, ::user::interaction * pviewLast, ::user::impact_data * pimpactdata)
   {

      return create_impact < VIEW >(get_document(), puserinteractionParent, atom, pviewLast, pimpactdata);

   }


   template < class VIEW >
   inline ::pointer<VIEW>impact::create_impact(::user::impact_data * pimpactdata, ::user::interaction * pviewLast)
   {

      pimpactdata->m_puserinteraction.release();

      return create_impact < VIEW >(get_document(), pimpactdata->m_pplaceholder, pimpactdata->m_atom, pviewLast, pimpactdata);

   }


} // namespace user




