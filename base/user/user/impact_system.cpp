#include "framework.h"
#include "base/user/user/_user.h"
#include "aura/user/wait_cursor.h"


// 0000 -> 7FFF IDR range
// 0000 -> 6FFF : ::account::user resources
// 7000 -> 7FFF : AFX (and standard windows) resources
// IDR ranges (NOTE: IDR_ values must be <32768)
#define ASSERT_VALID_IDR(nIDR) ASSERT((nIDR) != 0 && (nIDR) < 0x8000)

namespace user
{


   impact_system::impact_system(const char * pszMatter, ::type pDocClass, ::type pFrameClass, ::type pViewClass)
   {

      m_bHiddenOnNotifyIcon = false;

      m_puserinteractionOwner = nullptr;

      m_strMatter = pszMatter;
      m_typeDocument = pDocClass;
      m_typeFrame = pFrameClass;
      m_typeView = pViewClass;
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


   void impact_system::remove_document(::user::document * pdocument)
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
         string strExtension = pszPathName.ext();

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

         TRACE(trace_category_appmsg, e_trace_level_error, "Error: you must override impact_system::create_new_document.\n");

         ASSERT(false);

         return nullptr;

      }

      ::apex::application * papp = pcreate->create_get_application(get_context_application());

      __pointer(::user::document) pdocument;

      auto estatus = papp->__id_construct(pdocument, m_typeDocument);

      if (!estatus || !pdocument)
      {

         TRACE(trace_category_appmsg, e_trace_level_warning, "Warning: Dynamic create of ::user::document type %hs failed.\n", m_typeDocument.name().c_str());

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

      ASSERT(m_strMatter.has_char());

      if (pcreate->m_pusersystem.is_null())
      {

         pcreate->m_pusersystem = __new(::user::system);

         __user_system(pcreate->m_pusersystem)->m_pcreate = pcreate;

      }

      __pointer(::user::system) pusersystem = __user_system(pcreate->m_pusersystem);

      pusersystem->m_puiCurrentFrame = pOther;

      pusersystem->m_pdocumentCurrent = pdocument;

      if (pcreate->m_puiAlloc != nullptr)
      {

         pusersystem->m_puiNew = pcreate->m_puiAlloc;

      }
      else
      {

         pusersystem->m_typeNewView = m_typeView;

      }

      pusersystem->m_ptemplateNewDocument = this;

      if (!m_typeFrame)
      {

         TRACE(trace_category_appmsg, e_trace_level_error, "Error: you must override impact_system::create_new_frame.\n");

         ASSERT(false);

         return nullptr;

      }

      ::apex::application * papp = pcreate->create_get_application(get_context_application());

      __pointer(::user::frame_window) pframe;

      auto estatus = papp->__id_construct(pframe, m_typeFrame);

      if (!estatus || !pframe)
      {

         TRACE(trace_category_appmsg, e_trace_level_warning, "Warning: Dynamic create of frame %hs failed.\n", m_typeFrame.name().c_str());

         string strMessage;

         strMessage.Format("Warning: Dynamic create of frame %hs failed.\n\n(Does allocation was implemented)?", m_typeFrame.name().c_str());

         Application.message_box(strMessage);

         return nullptr;

      }

      ASSERT_KINDOF(frame_window, pframe);

      pframe->m_pdocumenttemplate = this;

      if (!pusersystem->m_typeNewView)
      {

         TRACE(trace_category_appmsg, e_trace_level_warning, "Warning: creating frame with no default ::user::impact.\n");

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

         if (!::is_screen_visible(pframe->layout().sketch().display()))
         {

            pframe->display(e_display_default);

         }

      }

      // create new from resource
      if (!pframe->LoadFrame(m_strMatter,
                             //WS_OVERLAPPEDWINDOW |
                             (bAddToTitle ? FWS_ADDTOTITLE : 0),   // default frame styles
                             __user_interaction(pcreate->m_puserinteractionParent), 
                              pusersystem))
      {

         TRACE(trace_category_appmsg, e_trace_level_warning, "Warning: impact_system couldn't create a frame.\n");

         // frame will be deleted in PostNcDestroy cleanup

         return nullptr;

      }

      return pframe;

   }


   void impact_system::InitialUpdateFrame(__pointer(::user::frame_window) pFrame, ::user::document * pdocument, bool bMakeVisible)
   {

      pFrame->InitialUpdateFrame(pdocument, bMakeVisible);

      pFrame->set_reposition();

      pFrame->set_need_layout();

      pFrame->set_need_redraw();

      pFrame->post_redraw();

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


   void impact_system::route_command_message(::message::command * pcommand)
   {

      channel::route_command_message(pcommand);

   }


   void impact_system::dump(dump_context & dumpcontext) const
   {
      channel::dump(dumpcontext);

      dumpcontext << "m_strMatter = " << m_strMatter.c_str();
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

   void impact_system::assert_valid() const
   {
      channel::assert_valid();

      ::count count = get_document_count();
      for (index index = 0; index < count; index++)
      {
         __pointer(::user::document) pdocument = get_document(index);
         pdocument->assert_valid();
      }
   }


   void impact_system::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      update_all_views(psubject);

   }


   void impact_system::update_all_views(::subject::subject * psubject)
   {

      ::count count = get_document_count();

      for (index index = 0; index < count; index++)
      {

         ::user::document * pdocument = get_document(index);

         pdocument->update_all_views(psubject);

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


   void impact_system::update_all_views(::user::impact * pimpact, const ::id & id)
   {

      ::count count = get_document_count();

      for (index index = 0; index < count; index++)
      {

         ::user::document * pdocument = get_document(index);

         pdocument->update_all_views(pimpact, id);

      }

   }


} // namespace user







