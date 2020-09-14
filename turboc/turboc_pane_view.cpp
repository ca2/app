#include "framework.h"


namespace turboc
{


   pane_view::pane_view(::layered * pobjectContext) :
      ::object(pobject),
      ::user::tab(pobject),

      ::user::tab_view(pobject),
      ::userex::pane_tab_view(pobject),
      place_holder_container(pobject)
   {

   }


   pane_view::~pane_view()
   {

   }


   void pane_view::assert_valid() const
   {

	   ::aura::impact::assert_valid();

   }


   void pane_view::dump(dump_context & dumpcontext) const
   {

	   ::aura::impact::dump(dumpcontext);

   }


   void pane_view::install_message_handling(::message::dispatch * pchannel)
   {

      ::userex::pane_tab_view::install_message_handling(pchannel);

	   IGUI_WIN_MSG_LINK(WM_CREATE, pchannel, this, &pane_view::_001OnCreate);

   }


   void pane_view::_001OnCreate(signal_details * pmessage)
   {
      if(pmessage->previous())
         return;

      set_tab("turboc", MAIN_IMPACT);
      set_tab("switcher",MAIN_SWITCHER_IMPACT);
      set_tab("Open", FILEMANAGER_IMPACT);

      //set_cur_tab_by_id(MAIN_SWITCHER_IMPACT);
      set_cur_tab_by_id(MAIN_IMPACT);

   }


   void pane_view::on_create_impact(::user::impact_data * pcreatordata)
   {

      switch(pcreatordata->m_id)
      {
      case MAIN_IMPACT:
         {
         Application.m_ptemplateHelloMultiverseView->open_document_file(get_context_application(), NULL,true,pcreatordata->m_pholder);


         }

         break;

      case PaneViewHelloMultiverseSwitcher:
      {

         Application.m_ptemplateHelloMultiverseSwitcher->open_document_file(get_context_application(), NULL,true,pcreatordata->m_pholder);



      }

         break;

      default:

         break;

      }

      ::userex::pane_tab_view::on_create_impact(pcreatordata);

   }




} // namespace turboc





