#include "framework.h"


namespace turboc
{


   pane_impact::pane_impact(::particle * pparticle) :
      ::object(pparticle),
      ::user::tab(pparticle),

      ::user::tab_impact(pparticle),
      ::userex::pane_tab_impact(pparticle),
      place_holder_container(pparticle)
   {

   }


   pane_impact::~pane_impact()
   {

   }


   void pane_impact::assert_ok() const
   {

	   ::aura::impact::assert_ok();

   }


   void pane_impact::dump(dump_context & dumpcontext) const
   {

	   ::aura::impact::dump(dumpcontext);

   }


   void pane_impact::install_message_handling(::message::dispatch * pchannel)
   {

      ::userex::pane_tab_impact::install_message_handling(pchannel);

	   IGUI_WIN_MSG_LINK(e_message_create, pchannel, this, &pane_impact::on_message_create);

   }


   void pane_impact::on_message_create(signal_details * pmessage)
   {
      if(pmessage->previous())
         return;

      set_tab("turboc", MAIN_IMPACT);
      set_tab("switcher",MAIN_SWITCHER_IMPACT);
      set_tab("Open", FILEMANAGER_IMPACT);

      //set_current_tab_by_id(MAIN_SWITCHER_IMPACT);
      set_current_tab_by_id(MAIN_IMPACT);

   }


   void pane_impact::on_create_impact(::user::impact_data * pcreatordata)
   {

      switch(pcreatordata->id())
      {
      case MAIN_IMPACT:
         {
         papp->m_ptemplateHelloMultiverseImpact->open_document_file(get_app(), NULL,true,pcreatordata->m_pholder);


         }

         break;

      case PaneImpactHelloMultiverseSwitcher:
      {

         papp->m_ptemplateHelloMultiverseSwitcher->open_document_file(get_app(), NULL,true,pcreatordata->m_pholder);



      }

         break;

      default:

         break;

      }

      ::userex::pane_tab_impact::on_create_impact(pcreatordata);

   }




} // namespace turboc





