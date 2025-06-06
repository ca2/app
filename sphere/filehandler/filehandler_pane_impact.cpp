#include "framework.h"
#include "base/update.h" 


namespace filehandler
{


   pane_impact::pane_impact(::particle * pparticle) :
      ::object(pparticle),
      ::user::tab_impact(pparticle),
      ::userex::pane_tab_impact(pparticle),
      place_holder_container(pparticle)
   {

      m_pimpactdataOld = nullptr;




      m_pimpactdata              = nullptr;
      m_pimpactdataOld              = nullptr;

      /*   ::user::single_document_template* pdoctemplate;
      pdoctemplate = ___new ::user::single_document_template(
      IDR_ALBUM,
      ::type < MediaLibraryDoc >(),
      ::type < MediaLibraryChildFrame >(),
      ::type < ::mplite::library::impact >());
      m_pimpactsystemAlbum = pdoctemplate;

      pdoctemplate = ___new ::user::single_document_template(
      IDR_ALBUM,
      ::type < OptionsDoc >(),
      ::type < OptionsChildFrame >(),
      ::type < OptionsImpact >());


      m_pimpactsystemOptions = pdoctemplate;

      pdoctemplate = ___new ::user::single_document_template(
      IDR_ALBUM,
      ::type < GoodMixerDoc >(),
      ::type < simple_child_frame >(),
      ::type < MixerMainImpact >());

      m_pimpactsystemAudioControl = pdoctemplate;*/

   }

   pane_impact::~pane_impact()
   {
   }





   void pane_impact::assert_ok() const
   {
      ::user::impact::assert_ok();
   }

   void pane_impact::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }


   /////////////////////////////////////////////////////////////////////////////
   // pane_impact message handlers

   void pane_impact::on_message_create(::message::message * pmessage)
   {

      if (pmessage->previous())
      {

         return;

      }

      papp->filehandler()->m_ppaneimpact = this;

      add_tab("New", impact_new);

   }


   void pane_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      __UNREFERENCED_PARAMETER(ptopic);

   }



   bool pane_impact::pre_create_window(::user::system * pusersystem)
   {


      return ::user::impact::pre_create_window(pusersystem);
   }

   void pane_impact::on_create_impact(::user::impact_data * pimpactdata)
   {

      //         ::pointer<application>papp =  (( (get_parent_frame()))->get_app());

      string strFile = pimpactdata->id();

      if(strFile.case_insensitive_begins_eat("default_file_handler://"))
      {

         ::pointer<::filehandler::impact>pimpact = create_impact < ::filehandler::impact > (pimpactdata);

         pimpactdata->m_puserinteraction = pimpact;

         pimpactdata->m_pdocument = get_document();

         pimpact->m_strName = strFile;
         //pimpact->on_layout(pgraphics);

      }

      switch(pimpactdata->id())
      {
      case impact_new:
      {
         /*               ::pointer<::create>pcreate(this);
         pcreate->m_bMakeVisible = true;
         pcreate->m_puserinteractionParent = this;
         rtprxsp(::document) pdocument = dynamic_cast < rtprxsp(::document) > (papp->m_ptemplateVideo->do_request(pcreate));
         if(pdocument != nullptr)
         {
         ::pointer<::user::impact>pimpact = pdocument->get_impact();
         pimpact->call_update(id_initial_update);
         if(pimpact != nullptr)
         {
         ::pointer<::user::frame_window>pframe =  (pimpact->get_parent_frame());
         if(pframe != nullptr)
         {
         pimpactdata->m_pdocument = pdocument;
         pimpactdata->m_puserinteraction = pframe;

         //                  pdocument->Initialize(true);
         }
         }
         }*/
         /*         create_context cc;
         cc.m_pCurrentDoc = get_document();
         cc.m_typeatomNewImpact =  ::type < rtprx::impact >();

         ::pointer<::user::impact>pimpact = (CreateImpact(&cc, 101, this));
         if(pimpact != nullptr)
         {
         pimpactdata = ___new ::user::impact_data ();
         pimpactdata->m_eview = eview;
         pimpactdata->m_pdocument = get_document();
         pimpactdata->m_puserinteraction = pimpact;
         }*/
      }
      break;
      default:
         //ASSERT(false);
         break;
      }
   }

   void pane_impact::rotate()
   {
   }

   void pane_impact::_001OnMenuMessage(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      set_current_tab_by_id(m_pimpactdataOld->id());
   }

   void pane_impact::install_message_routing(::channel * pchannel)
   {
      ::userex::pane_tab_impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &pane_impact::on_message_create);
      MESSAGE_LINK(WM_USER + 1122, pchannel, this, &pane_impact::_001OnMenuMessage);
   }


} // namespace filehandler




