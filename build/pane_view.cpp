#include "framework.h"
#include "acme/constant/id.h"
#include "base/user/user/tab_pane.h"


#ifdef _DEBUG
//#define DEBUG_GCOM 1
#define DEBUG_GCOM 0
#else
#define DEBUG_GCOM 0
#endif

namespace app_core_build
{


   pane_view::pane_view()
   {

   }


   pane_view::~pane_view()
   {

   }


   void pane_view::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void pane_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void pane_view::install_message_routing(::channel * pchannel)
   {

      ::userex::pane_tab_view::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &pane_view::on_message_create);

   }


   void pane_view::on_message_create(::message::message * pmessage)
   {

      if (pmessage->previous())
      {

         return;

      }

      m_papplication->m_ppaneview = this;

      set_tab("Options", OPTIONS_IMPACT);
      set_tab("Build", MAIN_IMPACT);
#if 1
      set_tab("Open", FILEMANAGER_IMPACT);
#endif



      set_current_tab_by_id(MAIN_IMPACT);

   }


   void pane_view::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::userex::pane_tab_view::_001OnNcDraw(pgraphics);

   }


   void pane_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::userex::pane_tab_view::_001OnDraw(pgraphics);

   }


   void pane_view::on_change_cur_sel()
   {

      ::userex::pane_tab_view::on_change_cur_sel();

   }


   void pane_view::on_create_impact(::user::impact_data * pimpactdata)
   {

      switch(pimpactdata->m_id)
      {
      break;
      case MAIN_IMPACT:
      {

         auto pcreate = m_pusersystem->m_pcreate;

         auto pcommandline = pcreate->m_pcommandline;

         auto& payloadFile = pcommandline->m_varFile;

         auto papplication = get_application();

         m_papplication->m_ptemplateHelloMultiverseView->open_document_file(papplication, payloadFile, true, pimpactdata->m_pplaceholder);

      }
      break;
      }

      ::userex::pane_tab_view::on_create_impact(pimpactdata);

   }


   void pane_view::handle(::topic * psubject, ::context * pcontext)
   {


      ::userex::pane_tab_view::handle(psubject, pcontext);

   }




} // namespace app_core_build



