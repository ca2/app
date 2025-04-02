#include "framework.h"
#include "impact_system.h"
#include "document.h"
#include "impact.h"
#include "frame_window.h"
#include "acme/platform/application.h"
#include "acme/handler/request.h"
#include "aura/user/user/system.h"
#include "aura/user/user/wait_cursor.h"


// 0000 -> 7FFF IDR range
// 0000 -> 6FFF : ::account::user resources
// 7000 -> 7FFF : standard windows resources
// IDR ranges (NOTE: IDR_ values must be <32768)
#define ASSERT_VALID_IDR(nIDR) ASSERT((nIDR) != 0 && (nIDR) < 0x8000)

namespace user
{


   impact_system::impact_system(const ::atom & atom, const ::type_atom & typeatomDocument, const ::type_atom & typeatomFrame, const ::type_atom & typeatomImpact, const ::type_atom & typeatomData)
   {

      m_bHiddenOnNotifyIcon = false;

      m_puserinteractionOwner = nullptr;

      id() = atom;
      m_typeatomDocument = typeatomDocument;
      m_typeatomFrame = typeatomFrame;
      m_typeatomImpact = typeatomImpact;
      m_typeatomData = typeatomData;
      m_pAttachedFactory = nullptr;

      //load_impact_system();

   }


   void impact_system::load_impact_system()
   {
   }


   impact_system::~impact_system()
   {

   }


   bool impact_system::GetDocString(string & rString, enum DocStringIndex i) const
   {

      return false;

   }


   void impact_system::add_document(::user::document * pdocument)
   {

      ASSERT(pdocument->m_pimpactsystem == nullptr);   // no template attached yet

      pdocument->m_pimpactsystem = this;

      pdocument->install_message_routing(pdocument);

//      add_composite(pdocument);

   }


   void impact_system::erase_document(::user::document * pdocument)
   {

      ASSERT(pdocument->m_pimpactsystem == this);   // must be attached to us

      pdocument->m_pimpactsystem.release();

   }


   impact_system::Confidence impact_system::MatchDocType(const ::file::path & pszPathName,::user::document *& rpDocMatch)

   {

      ASSERT(pszPathName.has_character());


      rpDocMatch = nullptr;

      // go through all documents
      ::collection::count count = get_document_count();
      for (::collection::index index = 0; index < count; index++)
      {
         ::pointer<::user::document>pdocument = get_document(index);
         if (pdocument->get_file_path() == pszPathName)

         {
            // already open
            rpDocMatch = pdocument;
            return yesAlreadyOpen;
         }
      }

      // see if it matches our default suffix
      string strFilterExt;
      if (GetDocString(strFilterExt, impact_system::filterExt) &&
            !strFilterExt.is_empty())
      {
         // see if extension matches
         ASSERT(strFilterExt[0] == '.');
         string strExtension = pszPathName.final_extension();

         if (strExtension.has_character())
         {
            if (strExtension.case_insensitive_order(strFilterExt) == 0)
            {
               return yesAttemptNative; // extension matches, looks like ours
            }
         }
      }

      // otherwise we will guess it may work
      return yesAttemptForeign;

   }


   ::pointer<::user::document>impact_system::create_new_document(::request * prequest)
   {

      // default implementation constructs one from ::type
      if (!m_typeatomDocument)
      {

         error()(e_trace_category_appmsg) << "Error: you must override impact_system::create_new_document.";

         ASSERT(false);

         return nullptr;

      }

      ::platform::application * papp = prequest->create_get_app(get_app());

      ::pointer<::user::document>pdocument;

      //auto estatus = 
      
      papp->__id_construct(pdocument, m_typeatomDocument);

      if (!pdocument)
      {

         warning()(e_trace_category_appmsg) << "Warning: Dynamic create of ::user::document type %hs failed.\n" << m_typeatomDocument.as_string();

         return nullptr;

      }

      pdocument->on_create(prequest);

      ASSERT_KINDOF(::user::document, pdocument);

      add_document(pdocument);

      return pdocument;

   }


   ::pointer<::user::frame_window>impact_system::create_new_frame(::user::document * pdocument, ::pointer<::user::frame_window>pOther, ::request * prequest)
   {

      bool bAddToTitle = is_true("add_to_title");

      ASSERT(id().has_character());

      ::pointer<::user::system>pusersystem = prequest->m_pmatterUserPayload;

      if (!pusersystem)
      {

         pusersystem = __allocate ::user::system();

         prequest->m_pmatterUserPayload = pusersystem;

      }
      
      if(!pusersystem->m_prequest)
      {
       
         pusersystem->m_prequest = prequest;

      }

      pusersystem->m_puserprimitiveCurrentFrame = pOther;

      pusersystem->m_pdocumentCurrent = pdocument;

      if (prequest->m_puserelementAlloc != nullptr)
      {

         pusersystem->m_puserprimitiveNew = prequest->m_puserelementAlloc;

      }
      else
      {

         pusersystem->m_typeatomNewImpact = m_typeatomImpact;

      }

      pusersystem->m_ptemplateNewDocument = this;

      if (!m_typeatomFrame)
      {

         error()(e_trace_category_appmsg) << "Error: you must override impact_system::create_new_frame.\n";

         ASSERT(false);

         return nullptr;

      }

      ::platform::application * papp = prequest->create_get_app(get_app());

      ::pointer<::user::frame_window>pframe;

      //auto estatus =
      
      papp->__id_construct(pframe, m_typeatomFrame);

      if (!pframe)
      {

         warning()(e_trace_category_appmsg) << "Warning: Dynamic create of frame %hs failed." << m_typeatomFrame.as_string().c_str();

         string strMessage;

         strMessage.formatf("Warning: Dynamic create of frame %hs failed.\n\n(Does allocation was implemented)?", m_typeatomFrame.as_string().c_str());

         //message_box(strMessage);

         output_error_message(strMessage);

         return nullptr;

      }

      ASSERT_KINDOF(frame_window, pframe);

      pframe->m_pimpactsystem = this;

      if (!pusersystem->m_typeatomNewImpact)
      {

         warning()(e_trace_category_appmsg) << "Warning: creating frame with no default ::user::impact.\n";

      }

      if (prequest->m_ewindowflag & e_window_flag_updown)
      {

         pframe->m_ewindowflag += e_window_flag_updown;

      }

      if (m_puserinteractionOwner != nullptr)
      {

         pframe->set_owner(m_puserinteractionOwner);

      }

      //if (prequest->m_bMakeVisible)
      //{

      //   if (!::is_screen_visible(pframe->const_layout().sketch().display()))
      //   {

      //      pframe->display(e_display_normal);

      //   }

      //}


      //pframe->m_procedureOnAfterCreate=[this, pdocument, pframe, prequest]()
      //{

      //   on_request_continuation(pdocument, pframe, prequest);

      //};

      ::pointer<::user::interaction>puserinteractionParent = prequest->m_puserelementParent;

      // create ___new from resource
      if (!pframe->LoadFrame(id(),
                             //WS_OVERLAPPEDWINDOW |
                             (bAddToTitle ? FWS_ADDTOTITLE : 0),   // default frame styles
         puserinteractionParent,
                              pusersystem))
      {

         warning()(e_trace_category_appmsg) << "Warning: impact_system couldn't create a frame.\n";

         // frame will be deleted in post_non_client_destroy cleanup

         return nullptr;

      }

      return pframe;

   }


   void impact_system::prepare_frame(::user::frame_window * pframe, ::user::document * pdocument, bool bMakeVisible)
   {

      pframe->prepare_frame(pdocument, bMakeVisible);

   }


   /////////////////////////////////////////////////////////////////////////////
   // impact_system commands and command helpers

   bool impact_system::save_all_modified()
   {
      ::collection::count count = get_document_count();
      for (::collection::index index = 0; index < count; index++)
      {
         ::pointer<::user::document>pdocument = get_document(index);
         if (!pdocument->save_modified())
            return false;
      }
      return true;
   }

   void impact_system::pre_close_all_documents()
   {

      for (::collection::index index = 0; index < get_document_count(); index++)
      {

         try
         {

            ::user::document * pdocument = get_document(index);

            pdocument->pre_close_document();

         }
         catch (...)
         {

         }

      }

   }

   void impact_system::close_all_documents(bool)
   {

      for (::collection::index index = 0; index < get_document_count(); index++)
      {

         try
         {

            ::user::document * pdocument = get_document(index);

            pdocument->close_document();

         }
         catch (...)
         {

         }

      }

   }


   void impact_system::on_request_continuation(::user::document * pdocument, ::user::frame_window * pframewindow, ::request * prequest)
   {


   }


   void impact_system::on_idle()
   {
      ::collection::count count = get_document_count();
      for (::collection::index index = 0; index < count; index++)
      {
         ::pointer<::user::document>pdocument = get_document(index);
         ASSERT_KINDOF(::user::document, pdocument);
         pdocument->on_idle();
      }
   }


   void impact_system::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      channel::route_command(pcommand);

   }


//   void impact_system::dump(dump_context & dumpcontext) const
//   {
//      channel::dump(dumpcontext);
//
//      //dumpcontext << "m_strMatter = " << id();
//      //dumpcontext << "\nm_strDocStrings: " << m_strDocStrings;
//
//      //if (m_typeatomDocument)
//      //   dumpcontext << "\nm_pDocClass = " << m_typeatomDocument.name();
//      //else
//      //   dumpcontext << "\nm_pDocClass = nullptr";
//
//      //if (dumpcontext.GetDepth() > 0)
//      //{
//      //   dumpcontext << "\ndocument list = {";
//      //   ::collection::count count = get_document_count();
//      //   for (::collection::index index = 0; index < count; index++)
//      //   {
//      //      ::pointer<::user::document>pdocument = get_document(index);
//      //      dumpcontext << (void *)pdocument.m_p;
//      //   }
//      //   dumpcontext << "\n}";
//      //}
//
//      //dumpcontext << "\n";
//   }
//
//   void impact_system::assert_ok() const
//   {
//      channel::assert_ok();
//
//      ::collection::count count = get_document_count();
//      for (::collection::index index = 0; index < count; index++)
//      {
//         ::pointer<::user::document>pdocument = get_document(index);
//         pdocument->assert_ok();
//      }
//   }


   void impact_system::handle(::topic * ptopic, ::handler_context * pcontext)
   {

      update_all_impacts(ptopic);

   }


   void impact_system::update_all_impacts(::topic * ptopic)
   {

      ::collection::count count = get_document_count();

      for (::collection::index index = 0; index < count; index++)
      {

         ::user::document * pdocument = get_document(index);

         pdocument->update_all_impacts(ptopic);

      }

   }


   bool impact_system::on_open_document(::user::document * pdocument, ::request * prequest)
   {

      wait_cursor wait(pdocument);

      return do_open_document(pdocument, prequest);

   }


   bool impact_system::do_open_document(::user::document * pdocument, ::request * prequest)
   {

      if (!pdocument->open_document(prequest))
      {

         return false;

      }

      return true;

   }


   void impact_system::reload_template()
   {
   }


   void impact_system::update_all_impacts(::user::impact * pimpact, const ::atom & atom)
   {

      ::collection::count count = get_document_count();

      for (::collection::index index = 0; index < count; index++)
      {

         ::user::document * pdocument = get_document(index);

         pdocument->update_all_impacts(pimpact, atom);

      }

   }


} // namespace user







