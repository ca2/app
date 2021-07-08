#pragma once


//#define WM_VIEW (WM_USER + 1023)



namespace user
{



   class CLASS_DECL_BASE impact :
      virtual public ::user::box
   {
   public:



      string                              m_strImpactTitle;
      id                                  m_idCreator;
      __reference(::user::document)       m_pdocument;
      __reference(::user::interaction)    m_puserinteractionImpactNotify;


      impact();
      virtual ~impact();

      virtual void dump(dump_context&) const override;
      virtual void assert_valid() const override;



      inline ::base::application* get_application() const { return m_pcontext ? m_pcontext->m_pbaseapplication : nullptr; }
      inline ::base::session* get_session() const { return m_pcontext ? m_pcontext->m_pbasesession : nullptr; }
      inline ::base::system* get_system() const { return m_psystem ? m_psystem->m_pbasesystem : nullptr; }
      inline ::base::user* user() const { return get_session() ? get_session()->user() : nullptr; }


      virtual ::e_status set_notify_user_interaction(::user::interaction* puserinteractionNotify);



      ::user::document * get_document() const;

      template < class DATA >
      DATA * get_typed_data();

      template < class DOCUMENT >
      DOCUMENT * get_typed_document();

      template < class DOCUMENT >
      ::data::data * get_typed_document_data();

      virtual void install_message_routing(::channel * pchannel) override;

      virtual bool IsSelected(const object* pDocItem) const; // support for OLE

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

      virtual void OnActivateView(bool bActivate, __pointer(impact) pActivateView, __pointer(impact) pDeactiveView);
      virtual void OnActivateFrame(enum_activate eactivate,  __pointer(::user::frame_window) pFrameWnd);


      virtual void set_impact_title(const string & strImpactTitle);
      virtual string get_impact_title() const;

      __pointer(::user::interaction) create_view(const ::type & type, ::user::document * pdocument = nullptr, ::user::interaction * puserinteractionParent = nullptr, const ::id & id = ::id(), ::user::interaction * pviewLast = nullptr, ::user::impact_data * pdata = nullptr);

      virtual ::e_status initialize_view(::user::document * pdocument);

      template < class VIEW >
      __pointer(VIEW) create_view(::user::document * pdocument = nullptr, ::user::interaction * puserinteractionParent = nullptr, const ::id & id = ::id(),::user::interaction * pviewLast = nullptr, ::user::impact_data * pimpactdata = nullptr);

      template < class VIEW >
      __pointer(VIEW) create_view(::user::interaction * puserinteractionParent, const ::id & id = ::id(),::user::interaction * pviewLast = nullptr, ::user::impact_data * pimpactdata = nullptr);

      template < class VIEW >
      __pointer(VIEW) create_view(::user::impact_data * pimpactdata, ::user::interaction * pviewLast = nullptr);

      __pointer(::user::interaction) create_view(::user::interaction * pimpactAlloc, ::user::impact_data * pimpactdata, ::user::interaction * pviewLast = nullptr);





      //virtual void CalcWindowRect(RECTANGLE_I32 * pClientRect, ::u32 nAdjustType = adjustBorder) override;



      virtual void route_command_message(::message::command * pcommand) override;

      virtual bool pre_create_window(::user::system * pusersystem) override;
      virtual void PostNcDestroy() override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      //DECLARE_MESSAGE_HANDLER(_001OnView);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);

      DECLARE_MESSAGE_HANDLER(_001OnMouseActivate);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateSplitCmd);
      DECLARE_MESSAGE_HANDLER(_001OnSplitCmd);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateNextPaneMenu);
      DECLARE_MESSAGE_HANDLER(_001OnNextPaneCmd);

      DECLARE_MESSAGE_HANDLER(_001OnFilePrint);
      DECLARE_MESSAGE_HANDLER(_001OnFilePrintPreview);


      DECLARE_MESSAGE_HANDLER(on_message_right_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_middle_button_down);


      void OnUpdateSplitCmd(::message::command* pCmdUI);
      bool OnSplitCmd(::u32 nID);
      void OnUpdateNextPaneMenu(::message::command* pCmdUI);
      bool OnNextPaneCmd(::u32 nID);

      // not mapped commands - must be mapped in derived class
      void OnFilePrint();
      void OnFilePrintPreview();

      // TODO: could return a kind of - also TODO - JOB object in case of assynchronous call
      //virtual void collaborate(::job * pjob);
      virtual i32  get_total_page_count(::subject::context * psubject) override;


      virtual ::user::interaction::enum_type get_window_type() override;

      //virtual void on_simple_view_update_hint(__pointer(::user::impact) pviewSender, e_hint ehint, object * pupdate);

      virtual void _001CallOnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_select() override;

      // each view can display one or more documents but has only one document interface
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


      //virtual void OnActivateView(bool bActivate, __pointer(::user::impact) pActivateView, __pointer(::user::impact) pDeactiveView);
      //virtual void OnActivateFrame(::u32 nState, __pointer(::user::frame_window) pFrameWnd);

      //virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;

      //      virtual void dump(dump_context &) const;
      //    virtual void assert_valid() const;



      //      virtual void route_command_message(::message::command * pcommand);

      //      virtual bool pre_create_window(::user::system * pusersystem);


      //         virtual void install_message_routing(::channel * pchannel);

      virtual bool has_command_handler(::message::command * pcommand) override;

      virtual void walk_pre_translate_tree(::message::message * pmessage,__pointer(::user::interaction) puiStop);


      //virtual string calc_parent_data_key() override;

      //virtual bool is_local_data() override;


   };


   template < class VIEW >
   class show :
      virtual public impact,
      virtual public VIEW
   {
   public:



      



      show()
      {

      }




      virtual ~show()
      {

      }


      inline ::base::application* get_application() const { return m_pcontext ? m_pcontext->m_pbaseapplication : nullptr; }
      inline ::base::session* get_session() const { return m_pcontext ? m_pcontext->m_pbasesession : nullptr; }
      inline ::base::system* get_system() const { return m_psystem ? m_psystem->m_pbasesystem : nullptr; }
      inline ::base::user* user() const { return get_session() ? get_session()->user() : nullptr; }


      virtual ::e_status initialize(::object * pobject) override
      {

         auto estatus = ::user::impact::initialize(pobject);

         if (!estatus)
         {

            return estatus;

         }

         estatus = VIEW::initialize(pobject);

         if (!estatus)
         {

            return estatus;

         }

         return estatus;

      }


      virtual void assert_valid() const override
      {
         impact::assert_valid();
         VIEW::assert_valid();

      }
      virtual void dump(dump_context & dumpcontext) const override
      {
         impact::dump(dumpcontext);
         VIEW::dump(dumpcontext);
      }


      virtual void install_message_routing(::channel * pchannel) override
      {

         VIEW::install_message_routing(pchannel);
         ::user::impact::install_message_routing(pchannel);

      }


      virtual void route_command_message(::message::command * pcommand) override
      {

         ::user::impact::route_command_message(pcommand);

      }


      virtual void on_command(::message::command* pcommand) override
      {

         VIEW::on_command(pcommand);

         if (pcommand->m_bRet)
         {

            return;

         }

         ::user::impact::on_command(pcommand);

      }

      //using ::user::impact::update;
      void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override
      {

         ::user::impact::on_subject(psubject, pcontext);

         VIEW::on_subject(psubject, pcontext);

      }


      virtual bool pre_create_window(::user::system * pusersystem) override
      {

         if (!::user::impact::pre_create_window(pusersystem))
         {

            return false;

         }

         if (!VIEW::pre_create_window(pusersystem))
         {

            return false;

         }

         return true;

      }


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override
      {

         VIEW::_001OnDraw(pgraphics);

      }


      virtual void on_control_event(::user::control_event * pevent) override
      {

         VIEW::on_control_event(pevent);

         if(pevent->m_bRet)
         {

            return;

         }

         if(m_puserinteractionImpactNotify)
         {

            m_puserinteractionImpactNotify->on_control_event(pevent);

         }

         ::user::interaction * puiParent = get_parent();

         if (puiParent != nullptr)
         {

            puiParent->on_control_event(pevent);

            if (pevent->m_bRet)
            {

               return;

            }

         }



      }

   };


   CLASS_DECL_BASE __pointer(::user::interaction) create_view(const ::type & type, ::user::document * pdocument, ::user::interaction * puserinteractionParent, const ::id & id, ::user::interaction * pviewLast = nullptr);
   CLASS_DECL_BASE __pointer(::user::interaction) create_view(::user::system * pusersystem, ::user::interaction * puserinteractionParent, const ::id & id);
   CLASS_DECL_BASE ::user::document * get_document(::user::interaction * pinteraction);


} // namespace user






