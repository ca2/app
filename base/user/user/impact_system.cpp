#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif
#include "aura/user/user/wait_cursor.h"


// 0000 -> 7FFF IDR range
// 0000 -> 6FFF : ::account::user resources
// 7000 -> 7FFF : AFX (and standard windows) resources
// IDR ranges (NOTE: IDR_ values must be <32768)
#define ASSERT_VALID_IDR(nIDR) ASSERT((nIDR) != 0 && (nIDR) < 0x8000)

namespace user
{


   impact_system::impact_system(const ::atom & atom, const ::type & typeDocument, const ::type & typeFrame, const ::type & typeImpact)
   {

      m_bHiddenOnNotifyIcon = false;

      m_puserinteractionOwner = nullptr;

      m_atom = atom;
      m_typeDocument = typeDocument;
      m_typeFrame = typeFrame;
      m_typeImpact = typeImpact;
      m_pAttachedFactory = nullptr;

      load_template();

   }


   void impact_system::load_template()
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

      add_composite(pdocument);

   }


   void impact_system::erase_document(::user::document * pdocument)
   {

      ASSERT(pdocument->m_pimpactsystem == this);   // must be attached to us

      pdocument->m_pimpactsystem.release();

   }


   impact_system::Confidence impact_system::MatchDocType(const ::file::path & pszPathName,::user::document *& rpDocMatch)

   {

      ASSERT(pszPathName.has_char());


      rpDocMatch = nullptr;

      // go through all documents
      ::count count = get_document_count();
      for (index index = 0; index < count; index++)
      {
         __pointer(::user::document) pdocument = get_document(index);
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

         if (strExtension.has_char())
         {
            if (strExtension.compare_ci(strFilterExt) == 0)
            {
               return yesAttemptNative; // extension matches, looks like ours
            }
         }
      }

      // otherwise we will guess it may work
      return yesAttemptForeign;

   }


   __pointer(::user::document) impact_system::create_new_document(::create * pcreate)
   {

      // default implementation constructs one from ::type
      if (!m_typeDocument)
      {

         CATEGORY_ERROR(appmsg, "Error: you must override impact_system::create_new_document.");

         ASSERT(false);

         return nullptr;

      }

      ::app * papp = pcreate->create_get_app(get_app());

      __pointer(::user::document) pdocument;

      //auto estatus = 
      
      papp->__id_construct(pdocument, m_typeDocument);

      if (!pdocument)
      {

         CATEGORY_WARNING(appmsg, "Warning: Dynamic create of ::user::document type %hs failed.\n" << m_typeDocument.name());

         return nullptr;

      }

      pdocument->on_create(pcreate);

      ASSERT_KINDOF(::user::document, pdocument);

      add_document(pdocument);

      return pdocument;

   }


   __pointer(::user::frame_window) impact_system::create_new_frame(::user::document * pdocument, __pointer(::user::frame_window) pOther, ::create * pcreate)
   {

      bool bAddToTitle = is_true("add_to_title");

      ASSERT(m_atom.has_char());

      __pointer(::user::system) pusersystem = pcreate->m_pmatterUserPayload;

      if (!pusersystem)
      {

         pusersystem = __new(::user::system);

         pusersystem->m_pcreate = pcreate;

         pcreate->m_pmatterUserPayload = pusersystem;

      }

      pusersystem->m_puserprimitiveCurrentFrame = pOther;

      pusersystem->m_pdocumentCurrent = pdocument;

      if (pcreate->m_puserprimitiveAlloc != nullptr)
      {

         pusersystem->m_puserprimitiveNew = pcreate->m_puserprimitiveAlloc;

      }
      else
      {

         pusersystem->m_typeNewImpact = m_typeImpact;

      }

      pusersystem->m_ptemplateNewDocument = this;

      if (!m_typeFrame)
      {

         CATEGORY_ERROR(appmsg, "Error: you must override impact_system::create_new_frame.\n");

         ASSERT(false);

         return nullptr;

      }

      ::app * papp = pcreate->create_get_app(get_app());

      __pointer(::user::frame_window) pframe;

      //auto estatus =
      
      papp->__id_construct(pframe, m_typeFrame);

      if (!pframe)
      {

         CATEGORY_WARNING(appmsg,"Warning: Dynamic create of frame %hs failed.\n", m_typeFrame.name().c_str());

         string strMessage;

         strMessage.format("Warning: Dynamic create of frame %hs failed.\n\n(Does allocation was implemented)?", m_typeFrame.name().c_str());

         //message_box(strMessage);

         output_error_message(strMessage);

         return nullptr;

      }

      ASSERT_KINDOF(frame_window, pframe);

      pframe->m_pdocumenttemplate = this;

      if (!pusersystem->m_typeNewImpact)
      {

         CATEGORY_WARNING(appmsg,"Warning: creating frame with no default ::user::impact.\n");

      }

      if (pcreate->m_ewindowflag & e_window_flag_updown)
      {

         pframe->m_ewindowflag += e_window_flag_updown;

      }

      if (m_puserinteractionOwner != nullptr)
      {

         pframe->m_puserinteractionOwner = m_puserinteractionOwner;

      }

      if (pcreate->m_bMakeVisible)
      {

         if (!::is_screen_visible(pframe->const_layout().sketch().display()))
         {

            pframe->display(e_display_default);

         }

      }

      __pointer(::user::interaction) puserinteractionParent = pcreate->m_puserprimitiveParent;

      // create new from resource
      if (!pframe->LoadFrame(m_atom,
                             //WS_OVERLAPPEDWINDOW |
                             (bAddToTitle ? FWS_ADDTOTITLE : 0),   // default frame styles
         puserinteractionParent,
                              pusersystem))
      {

         CATEGORY_WARNING(appmsg,"Warning: impact_system couldn't create a frame.\n");

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
      ::count count = get_document_count();
      for (index index = 0; index < count; index++)
      {
         __pointer(::user::document) pdocument = get_document(index);
         if (!pdocument->save_modified())
            return false;
      }
      return true;
   }

   void impact_system::pre_close_all_documents()
   {

      for (index index = 0; index < get_document_count(); index++)
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

      for (index index = 0; index < get_document_count(); index++)
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



   void impact_system::on_idle()
   {
      ::count count = get_document_count();
      for (index index = 0; index < count; index++)
      {
         __pointer(::user::document) pdocument = get_document(index);
         ASSERT_KINDOF(::user::document, pdocument);
         pdocument->on_idle();
      }
   }


   void impact_system::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      channel::route_command(pcommand);

   }


   void impact_system::dump(dump_context & dumpcontext) const
   {
      channel::dump(dumpcontext);

      dumpcontext << "m_strMatter = " << m_atom.to_string();
      dumpcontext << "\nm_strDocStrings: " << m_strDocStrings;

      if (m_typeDocument)
         dumpcontext << "\nm_pDocClass = " << m_typeDocument.name();
      else
         dumpcontext << "\nm_pDocClass = nullptr";

      if (dumpcontext.GetDepth() > 0)
      {
         dumpcontext << "\ndocument list = {";
         ::count count = get_document_count();
         for (index index = 0; index < count; index++)
         {
            __pointer(::user::document) pdocument = get_document(index);
            dumpcontext << (void *)pdocument.m_p;
         }
         dumpcontext << "\n}";
      }

      dumpcontext << "\n";
   }

   void impact_system::assert_ok() const
   {
      channel::assert_ok();

      ::count count = get_document_count();
      for (index index = 0; index < count; index++)
      {
         __pointer(::user::document) pdocument = get_document(index);
         pdocument->assert_ok();
      }
   }


   void impact_system::handle(::topic * ptopic, ::context * pcontext)
   {

      update_all_views(ptopic);

   }


   void impact_system::update_all_views(::topic * ptopic)
   {

      ::count count = get_document_count();

      for (index index = 0; index < count; index++)
      {

         ::user::document * pdocument = get_document(index);

         pdocument->update_all_views(ptopic);

      }

   }


   bool impact_system::on_open_document(::user::document * pdocument, ::create * pcreate)
   {

      wait_cursor wait(pdocument);

      return do_open_document(pdocument, pcreate);

   }


   bool impact_system::do_open_document(::user::document * pdocument, ::create * pcreate)
   {

      if (!pdocument->open_document(pcreate))
      {

         return false;

      }

      return true;

   }


   void impact_system::reload_template()
   {
   }


   void impact_system::update_all_views(::user::impact * pimpact, const ::atom & atom)
   {

      ::count count = get_document_count();

      for (index index = 0; index < count; index++)
      {

         ::user::document * pdocument = get_document(index);

         pdocument->update_all_views(pimpact, atom);

      }

   }


} // namespace user







