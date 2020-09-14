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



      virtual ::estatus set_notify_user_interaction(::user::interaction* puserinteractionNotify);



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
      virtual bool OnScroll(UINT nScrollCode, UINT nPos, bool bDoScroll = TRUE);
      //virtual bool OnScrollBy(::size sizeScroll, bool bDoScroll = TRUE);

      // OLE drag/drop support
      /*   virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject,
      u32 dwKeyState, const ::point & point);
      virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject,
      u32 dwKeyState, const ::point & point);
      virtual void OnDragLeave();
      virtual bool OnDrop(COleDataObject* pDataObject,
      DROPEFFECT dropEffect, const ::point & point);
      virtual DROPEFFECT OnDropEx(COleDataObject* pDataObject,
      DROPEFFECT dropDefault, DROPEFFECT dropList, const ::point & point);
      virtual DROPEFFECT OnDragScroll(u32 dwKeyState, const ::point & point);*/

      //virtual void OnPrepareDC(::draw2d::graphics_pointer & pgraphics, CPrintInfo* pInfo = nullptr);

      virtual void OnActivateView(bool bActivate, __pointer(impact) pActivateView, __pointer(impact) pDeactiveView);
      virtual void OnActivateFrame(UINT nState, __pointer(::user::frame_window) pFrameWnd);


      virtual void set_impact_title(const string & strImpactTitle);
      virtual string get_impact_title() const;

      __pointer(::user::interaction) create_view(const ::type & type, ::user::document * pdocument = nullptr, ::user::interaction * pwndParent = nullptr, ::id id = ::id(), ::user::interaction * pviewLast = nullptr, ::user::impact_data * pdata = nullptr);

      virtual ::estatus initialize_view(::user::document * pdocument);

      template < class VIEW >
      __pointer(VIEW) create_view(::user::document * pdocument = nullptr, ::user::interaction * pwndParent = nullptr,::id id = ::id(),::user::interaction * pviewLast = nullptr, ::user::impact_data * pimpactdata = nullptr);

      template < class VIEW >
      __pointer(VIEW) create_view(::user::interaction * pwndParent,::id id = ::id(),::user::interaction * pviewLast = nullptr, ::user::impact_data * pimpactdata = nullptr);

      template < class VIEW >
      __pointer(VIEW) create_view(::user::impact_data * pimpactdata, ::user::interaction * pviewLast = nullptr);

      __pointer(::user::interaction) create_view(::user::interaction * pimpactAlloc, ::user::impact_data * pimpactdata, ::user::interaction * pviewLast = nullptr);





      virtual void CalcWindowRect(RECT * pClientRect, UINT nAdjustType = adjustBorder) override;



      virtual void route_command_message(::user::command * pcommand) override;

      virtual bool pre_create_window(::user::create_struct& cs) override;
      virtual void PostNcDestroy() override;


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      //DECL_GEN_SIGNAL(_001OnView);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);

      DECL_GEN_SIGNAL(_001OnMouseActivate);
      DECL_GEN_SIGNAL(_001OnUpdateSplitCmd);
      DECL_GEN_SIGNAL(_001OnSplitCmd);
      DECL_GEN_SIGNAL(_001OnUpdateNextPaneMenu);
      DECL_GEN_SIGNAL(_001OnNextPaneCmd);

      DECL_GEN_SIGNAL(_001OnFilePrint);
      DECL_GEN_SIGNAL(_001OnFilePrintPreview);


      DECL_GEN_SIGNAL(_001OnRButtonDown);
      DECL_GEN_SIGNAL(_001OnMButtonDown);


      void OnUpdateSplitCmd(::user::command* pCmdUI);
      bool OnSplitCmd(UINT nID);
      void OnUpdateNextPaneMenu(::user::command* pCmdUI);
      bool OnNextPaneCmd(UINT nID);

      // not mapped commands - must be mapped in derived class
      void OnFilePrint();
      void OnFilePrintPreview();

      // TODO: could return a kind of - also TODO - JOB object in case of assynchronous call
      //virtual void collaborate(::job * pjob);
      virtual i32  get_total_page_count(::task* ptask) override;


      virtual ::user::interaction::e_type get_window_type() override;

      //virtual void on_simple_view_update_hint(__pointer(::user::impact) pviewSender, e_hint ehint, object * pupdate);

      virtual void _001CallOnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_select() override;

      // each view can display one or more documents but has only one document interface
      //::user::document * get_document() const;

      //      virtual bool IsSelected(const object* pDocItem) const; // support for OLE

      // OLE scrolling support (used for drag/drop as well)
      //      virtual bool OnScroll(UINT nScrollCode, UINT nPos, bool bDoScroll = TRUE);
      //    virtual bool OnScrollBy(const ::size & sizeScroll, bool bDoScroll = TRUE);

      // OLE drag/drop support
#ifndef ANDROID
      //virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject,
      //   u32 dwKeyState, const ::point & point);
      //virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject,
      //   u32 dwKeyState, const ::point & point);
      //virtual void OnDragLeave();
      //virtual bool OnDrop(COleDataObject* pDataObject,
      //   DROPEFFECT dropEffect, const ::point & point);
      //virtual DROPEFFECT OnDropEx(COleDataObject* pDataObject,
      //   DROPEFFECT dropDefault, DROPEFFECT dropList, const ::point & point);
      //virtual DROPEFFECT OnDragScroll(u32 dwKeyState, const ::point & point);
#endif


      //virtual void OnActivateView(bool bActivate, __pointer(::user::impact) pActivateView, __pointer(::user::impact) pDeactiveView);
      //virtual void OnActivateFrame(UINT nState, __pointer(::user::frame_window) pFrameWnd);

      //virtual void update(::update * pupdate) override;

      //      virtual void dump(dump_context &) const;
      //    virtual void assert_valid() const;



      //      virtual void route_command_message(::user::command * pcommand);

      //      virtual bool pre_create_window(::user::create_struct& cs);


      //         virtual void install_message_routing(::channel * pchannel);

      virtual bool has_command_handler(::user::command * pcommand) override;

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


      virtual ::estatus initialize(::layered * pobjectContext) override
      {

         auto estatus = ::user::impact::initialize(pobjectContext);

         if (!estatus)
         {

            return estatus;

         }

         estatus = VIEW::initialize(pobjectContext);

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


      virtual void route_command_message(::user::command * pcommand) override
      {

         ::user::impact::route_command_message(pcommand);

      }


      virtual void on_command(::user::command* pcommand) override
      {

         VIEW::on_command(pcommand);

         if (pcommand->m_bRet)
         {

            return;

         }

         ::user::impact::on_command(pcommand);

      }

      using ::user::impact::update;
      void update(::update * pupdate) override
      {

         ::user::impact::update(pupdate);

         VIEW::update(pupdate);

      }


      virtual bool pre_create_window(::user::create_struct& cs) override
      {

         if (!::user::impact::pre_create_window(cs))
         {

            return false;

         }

         if (!VIEW::pre_create_window(cs))
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

         ::user::interaction * puiParent = GetParent();

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


   CLASS_DECL_BASE __pointer(::user::interaction) create_view(const ::type & type, ::user::document * pdocument, ::user::interaction * pwndParent, id id, ::user::interaction * pviewLast = nullptr);
   CLASS_DECL_BASE __pointer(::user::interaction) create_view(::create * pContext, ::user::interaction * pwndParent, id id);
   CLASS_DECL_BASE ::user::document * get_document(::user::interaction * pinteraction);


} // namespace user






