#pragma once


#include "base/user/user/tab_impact.h"
#include "aura/user/user/form_callback.h"
#include "apex/platform/app_consumer.h"


namespace userex
{


   class pane_impact;


   class CLASS_DECL_CORE pane_tab_impact :
      virtual public ::user::tab_impact,
      virtual public ::user::form_callback
   {
   public:


      class CLASS_DECL_CORE handler :
         virtual public ::object
      {
      public:


         virtual void handle(pane_tab_impact * ppanetabimpact, ::topic * ptopic, ::context * pcontext) = 0;


      };

      
      atom_map < ::pointer<::form_document >> m_mapForm;
      ::pointer<pane_impact>                  m_ppaneimpact;
      atom_map < ::pointer<::object >>        m_mapFileManager;
      ::pointer<::user::document>           m_pdocAppOptions;
      ::pointer<font_impact>                m_pfontimpact;
      ::pointer<color_impact>               m_pcolorimpact;
      ::pointer<::form_document>            m_pformdocumentMenu;
      pointer_array < handler >               m_handlera;



      pane_tab_impact();
      ~pane_tab_impact() override;


      void install_message_routing(::channel * pchannel) override;
      
      
      virtual ::user::interaction * get_font_interaction();
      virtual ::user::interaction * get_color_interaction();

      void add_pane_tab_impact_handler_library(const ::string & strLibrary);


      ::core::application* get_app();
      ::core::session* get_session();
      ::core::system* get_system();

      
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnFileSaveAs);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateFileSaveAs);


      void _001OnRemoveTab(::user::tab_pane * ptab) override;


      ::user::interaction * get_impact_uie() override;

      atom get_impact_id() override;

      void on_change_cur_sel() override;

      bool on_prepare_impact_data(::user::impact_data * pimpactdata) override;

      bool on_after_create_impact_data(::user::impact_data * pimpactdata) override;

      void GetTabClientRect(RECTANGLE_I32 & rectangle) override;

      bool on_place_hold(::user::interaction * pinteraction, ::user::place_holder * pholder) override;

      ::user::tab_pane * create_tab_by_id(const ::atom & atom) override;

      void on_create_impact(::user::impact_data * pimpactdata) override;

      virtual ::filemanager::document * filemanager_document(const ::atom & atom);

      void _001OnTabClose(index iTab) override;

      virtual void interactive_credentials(::account::credentials * pcredentials);

      void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void prepare_form(atom atom, ::form_document * pformdocument);


   };


} // namespace userex


template <  typename APPLICATION, typename BASE1 = optional_interaction1, typename BASE2 = optional_interaction2, typename BASE3 = optional_interaction3, typename BASE4 = optional_interaction4 >
class application_pane_tab_impact :
   virtual public ::object,
   virtual public BASE1,
   virtual public BASE2,
   virtual public BASE3,
   virtual public BASE4
{
public:


   ::pointer<APPLICATION>m_papp;


   application_pane_tab_impact()
   {

   }


   void initialize(::particle * pparticle) override
   {

      //auto estatus =
      
      BASE1::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus =
      
      BASE2::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus =
      
      BASE3::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      BASE4::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   APP_CONSUMER_BODY


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


   inline APPLICATION* get_app() { return m_papp.get(); }
   inline APPLICATION* get_app() const { return (APPLICATION *)m_papp.get(); }

   void on_change_cur_sel() override = 0;
   void on_create_impact(::user::impact_data * pimpactdata) override = 0;


};



