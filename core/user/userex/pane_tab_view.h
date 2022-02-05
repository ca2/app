#pragma once


namespace userex
{


   class pane_view;


   class CLASS_DECL_CORE pane_tab_view :
      virtual public ::user::tab_view,
      virtual public ::user::form_callback
   {
   public:


      
      id_map < __pointer(::form_document) >  m_mapForm;
      __pointer(pane_view)                   m_ppaneview;
      ::object *                             m_pfilemanager;
      ::object *                             m_pfilemanagerTabbed;
      __pointer(::user::document)            m_pdocAppOptions;
      font_view *                            m_pfontview;
      color_view *                           m_pcolorview;
      ::form_document *                      m_pdocumentMenu;



      pane_tab_view();
      ~pane_tab_view() override;


      void install_message_routing(::channel * pchannel) override;


      inline ::core::application* get_application() const { return m_pcontext ? m_pcontext->m_pcoreapplication : nullptr; }
      inline ::core::session* get_session() const { return m_pcontext ? m_pcontext->m_pcoresession : nullptr; }
      inline ::core::system* get_system() const { return m_psystem ? m_psystem->m_pcoresystem : nullptr; }

      
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnFileSaveAs);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateFileSaveAs);


      void _001OnRemoveTab(::user::tab_pane * ptab) override;


      ::user::interaction * get_view_uie() override;

      id get_view_id() override;

      void on_change_cur_sel() override;

      bool on_prepare_impact_data(::user::impact_data * pimpactdata) override;

      bool on_after_create_impact_data(::user::impact_data * pimpactdata) override;

      void GetTabClientRect(RECTANGLE_I32 * prectangle) override;

      bool on_place_hold(::user::interaction * pinteraction, ::user::place_holder * pholder) override;

      ::user::tab_pane * create_tab_by_id(const ::id & id) override;

      void on_create_impact(::user::impact_data * pimpactdata) override;

      virtual ::filemanager::document * filemanager_document();

      virtual ::filemanager::document * tabbed_filemanager_manager();

      virtual void FileManagerSaveAs(::user::document * pdocument);

      virtual void TabbedFileManagerSaveAs(::user::document * pdocument);

      void _001OnTabClose(index iTab) override;

      virtual void interactive_credentials(::account::credentials * pcredentials);

      //virtual bool create_app_options(::user::impact_data * pimpactdata);

      void handle(::topic * ptopic, ::context * pcontext) override;

      //void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void prepare_form(id id, ::form_document * pdocument);


   };


} // namespace userex


template <  typename APPLICATION, typename BASE1 = optional_interaction1, typename BASE2 = optional_interaction2, typename BASE3 = optional_interaction3, typename BASE4 = optional_interaction4 >
class application_pane_tab_view :
   virtual public ::object,
   virtual public BASE1,
   virtual public BASE2,
   virtual public BASE3,
   virtual public BASE4
{
public:


   __pointer(APPLICATION) m_papplication;


   application_pane_tab_view()
   {

   }


   void initialize(::object* pobject) override
   {

      //auto estatus =
      
      BASE1::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus =
      
      BASE2::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus =
      
      BASE3::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      BASE4::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }

   APPLICATION_CONSUMER_BODY


   virtual void install_message_routing(::channel* pchannel) override
   {

      BASE1::install_message_routing(pchannel);

      BASE2::install_message_routing(pchannel);

      BASE3::install_message_routing(pchannel);

      BASE4::install_message_routing(pchannel);

   }


   void on_layout(::draw2d::graphics_pointer& pgraphics) override
   {

      BASE1::on_layout(pgraphics);

      BASE2::on_layout(pgraphics);

      BASE3::on_layout(pgraphics);

      BASE4::on_layout(pgraphics);

   }


   inline APPLICATION* get_application() { return m_papplication.get(); }
   inline APPLICATION* get_application() const { return (APPLICATION *) m_papplication.get(); }

   void on_change_cur_sel() override = 0;
   void on_create_impact(::user::impact_data * pimpactdata) override = 0;


};



