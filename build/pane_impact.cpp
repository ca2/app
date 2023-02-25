#include "framework.h"
#include "pane_impact.h"
#include "acme/constant/id.h"
#include "acme/handler/request.h"
#include "aura/user/user/system.h"
#include "base/user/user/single_document_template.h"
#include "base/user/user/tab_pane.h"
#include "core/user/userex/pane_impact.h"


#ifdef _DEBUG
//#define DEBUG_GCOM 1
#define DEBUG_GCOM 0
#else
#define DEBUG_GCOM 0
#endif


namespace app_build
{


   pane_impact::pane_impact()
   {

   }


   pane_impact::~pane_impact()
   {

   }


   //void pane_impact::assert_ok() const
   //{

   //   ::user::impact::assert_ok();

   //}


   //void pane_impact::dump(dump_context & dumpcontext) const
   //{

   //   ::user::impact::dump(dumpcontext);

   //}


   void pane_impact::install_message_routing(::channel * pchannel)
   {

      ::userex::pane_tab_impact::install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &pane_impact::on_message_create);

   }


   void pane_impact::on_message_create(::message::message * pmessage)
   {

      if (pmessage->previous())
      {

         return;

      }

      m_papplicationForConsumer->m_ppaneimpact = this;

      set_tab("Options", OPTIONS_IMPACT);
      set_tab("Build", MAIN_IMPACT);
#if 1
      set_tab("Open", FILEMANAGER_IMPACT);
#endif



      set_current_tab_by_id(MAIN_IMPACT);

   }


   void pane_impact::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::userex::pane_tab_impact::_001OnNcDraw(pgraphics);

   }


   void pane_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::userex::pane_tab_impact::_001OnDraw(pgraphics);

   }


   void pane_impact::on_change_cur_sel()
   {

      ::userex::pane_tab_impact::on_change_cur_sel();

   }


   void pane_impact::on_create_impact(::user::impact_data * pimpactdata)
   {

      switch(pimpactdata->m_atom.as_i64())
      {
      break;
      case MAIN_IMPACT:
      {

         auto prequest = m_pusersystem->m_prequest;

         auto payloadFile = prequest->m_payloadFile;

         auto papp = get_app();

         m_papplicationForConsumer->m_ptemplateHelloMultiverseImpact->open_document_file(papp, payloadFile, true, pimpactdata->m_pplaceholder);

      }
      break;
      }

      ::userex::pane_tab_impact::on_create_impact(pimpactdata);

   }


   void pane_impact::handle(::topic * ptopic, ::context * pcontext)
   {


      ::userex::pane_tab_impact::handle(ptopic, pcontext);

   }




} // namespace app_build



