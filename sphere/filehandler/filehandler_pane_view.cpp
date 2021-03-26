#include "framework.h"
#include "base/update.h" 


namespace filehandler
{


   pane_view::pane_view(::object * pobject) :
      ::object(pobject),
      ::user::tab_view(pobject),
      ::userex::pane_tab_view(pobject),
      place_holder_container(pobject)
   {

      m_pimpactdataOld = nullptr;




      m_pimpactdata              = nullptr;
      m_pimpactdataOld              = nullptr;

      /*   ::user::single_document_template* pdoctemplate;
      pdoctemplate = new ::user::single_document_template(
      IDR_ALBUM,
      __type(MediaLibraryDoc),
      __type(MediaLibraryChildFrame),
      __type(::mplite::library::view));
      m_pdocumenttemplateAlbum = pdoctemplate;

      pdoctemplate = new ::user::single_document_template(
      IDR_ALBUM,
      __type(OptionsDoc),
      __type(OptionsChildFrame),
      __type(OptionsView));


      m_pdocumenttemplateOptions = pdoctemplate;

      pdoctemplate = new ::user::single_document_template(
      IDR_ALBUM,
      __type(GoodMixerDoc),
      __type(simple_child_frame),
      __type(MixerMainView));

      m_pdocumenttemplateAudioControl = pdoctemplate;*/

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


   /////////////////////////////////////////////////////////////////////////////
   // pane_view message handlers

   void pane_view::on_message_create(::message::message * pmessage)
   {

      if (pmessage->previous())
      {

         return;

      }

      papplication->filehandler()->m_ppaneview = this;

      add_tab("New", impact_new);

   }


   void pane_view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      UNREFERENCED_PARAMETER(psubject);

   }



   bool pane_view::pre_create_window(::user::system * pusersystem)
   {


      return ::user::impact::pre_create_window(pusersystem);
   }

   void pane_view::on_create_impact(::user::impact_data * pimpactdata)
   {

      //         __pointer(application) papp =  (( (get_parent_frame()))->get_application());

      string strFile = pimpactdata->m_id;

      if(::str::begins_eat_ci(strFile, "default_file_handler://"))
      {

         __pointer(::filehandler::view) pview = create_view < ::filehandler::view > (pimpactdata);

         pimpactdata->m_puserinteraction = pview;

         pimpactdata->m_pdocument = get_document();

         pview->m_strName = strFile;
         //pview->on_layout(::draw2d::graphics_pointer & pgraphics);

      }

      switch(pimpactdata->m_id)
      {
      case impact_new:
      {
         /*               __pointer(::create) pcreate(this);
         pcreate->m_bMakeVisible = true;
         pcreate->m_puserinteractionParent = this;
         rtprxsp(::document) pdocument = dynamic_cast < rtprxsp(::document) > (papp->m_ptemplateVideo->do_request(pcreate));
         if(pdocument != nullptr)
         {
         __pointer(::user::impact) pview = pdocument->get_view();
         pview->call_update(INITIAL_UPDATE);
         if(pview != nullptr)
         {
         __pointer(::user::frame_window) pframe =  (pview->get_parent_frame());
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
         cc.m_typeNewView =  __type(rtprx::view);

         __pointer(::user::impact) pview = (CreateView(&cc, 101, this));
         if(pview != nullptr)
         {
         pimpactdata = new ViewData();
         pimpactdata->m_eview = eview;
         pimpactdata->m_pdocument = get_document();
         pimpactdata->m_puserinteraction = pview;
         }*/
      }
      break;
      default:
         //ASSERT(false);
         break;
      }
   }

   void pane_view::rotate()
   {
   }

   void pane_view::_001OnMenuMessage(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      set_cur_tab_by_id(m_pimpactdataOld->m_id);
   }

   void pane_view::install_message_routing(::channel * pchannel)
   {
      ::userex::pane_tab_view::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &pane_view::on_message_create);
      MESSAGE_LINK(WM_USER + 1122, pchannel, this, &pane_view::_001OnMenuMessage);
   }


} // namespace filehandler




