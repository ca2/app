#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif
#include "aura/message.h"


namespace user
{


   multiple_document_template::multiple_document_template(const char * pszMatter, ::type pDocClass, ::type pFrameClass, ::type pViewClass) :
      ::user::impact_system(pszMatter, pDocClass, pFrameClass, pViewClass)
   {

      ASSERT(m_docptra.is_empty());

      m_nUntitledCount = 0;   // start at 1

   }


   void multiple_document_template::load_template()
   {

      impact_system::load_template();

   }


   multiple_document_template::~multiple_document_template()
   {

#ifdef _DEBUG

      if (!m_docptra.is_empty())
      {

         TRACE(trace_category_appmsg, trace_level_warning, "Warning: destroying multiple_document_template with %d documents alive.\n", m_docptra.get_count());

      }

#endif

   }


   ::count multiple_document_template::get_document_count() const
   {

      return m_docptra.get_count();

   }


   ::user::document * multiple_document_template::get_document(index index) const
   {
      if(index < 0 || index >= m_docptra.get_count())
         return nullptr;
      return m_docptra.element_at(index);
   }


   void multiple_document_template::add_document(::user::document * pdocument)
   {

      if (m_docptra.add_unique(pdocument))
      {

         impact_system::add_document(pdocument);

      }

   }


   void multiple_document_template::remove_document(::user::document * pdocument)
   {

      impact_system::remove_document(pdocument);

      m_docptra.remove(pdocument);

   }


   void multiple_document_template::on_request(::create * pcreate)
   {

      pcreate->m_estatus = error_failed;

      pcreate->m_pcommandline->m_varQuery["document"] = (::object *)nullptr;

      bool bMakeVisible = pcreate->m_bMakeVisible;

      __pointer(::user::document) pdocument = create_new_document(pcreate);

      if (pdocument == nullptr)
      {

         TRACE(trace_category_appmsg, trace_level_warning, "impact_system::create_new_document returned nullptr.\n");

         // TODO Translate
         message_box("failed to create ::user::document");

         return;

      }

      bool bAutoDelete = pdocument->m_bAutoDelete;

      pdocument->m_bAutoDelete = FALSE;   // don't destroy if something goes wrong

      __pointer(::user::frame_window) pFrame = create_new_frame(pdocument, nullptr, pcreate);

      pdocument->m_bAutoDelete = bAutoDelete;

      if (pFrame == nullptr)
      {

         string strId;

         if (pcreate->m_puiAlloc != nullptr)
         {

            strId = ::type(pcreate->m_puiAlloc).name();

         }

         if (strId.find_ci("userex::message_box") < 0)
         {

            message_box("Failed to create ::user::document");

         }

         remove_document(pdocument);

         return;

      }

      ASSERT_VALID(pFrame);

      if(pcreate->m_pcommandline->m_varFile.is_empty())
      {
         // create a new ::user::document - with default ::user::document name
         set_default_title(pdocument);

         // avoid creating temporary compound file when starting up invisible
         if (!bMakeVisible)
            pdocument->m_bEmbedded = TRUE;

         if (!pdocument->on_new_document())
         {
            // ::account::user has be alerted to what failed in on_new_document
            TRACE(trace_category_appmsg, trace_level_warning, "::user::document::on_new_document returned FALSE.\n");
            pFrame->DestroyWindow();
            return;

         }

         // it worked, now bump untitled count
         m_nUntitledCount++;
         pdocument->id_update_all_views(NEW_DOCUMENT_UPDATE);
      }
      else
      {
         // open an existing ::user::document
         if(!on_open_document(pdocument, pcreate))
         {
            // failed to open or just failed to queue to open
            // if m_bQueueDocumentOpening flag is set, document opening is queued, and failure would be reported in a unknown way
            // prepare aura for async operations and also async failures
            // ::account::user has be alerted to what failed in on_open_document
            TRACE(trace_category_appmsg, trace_level_warning, "::user::document::on_open_document returned FALSE.\n");
            pFrame->post_message(e_message_destroy_window);
            return;

         }
         //pdocument->set_path_name(pcreate->m_pcommandline->m_varFile);

         pdocument->id_update_all_views(OPEN_DOCUMENT_UPDATE);
      }

      if(!pcreate->m_bHold)
      {

         pFrame->value("should_not_be_automatically_holded_on_initial_update_frame") = true;

      }

      InitialUpdateFrame(pFrame, pdocument, bMakeVisible);

      pcreate->m_pcommandline->m_varQuery["document"] = pdocument;

      pcreate->m_estatus = ::success;

   }


   void multiple_document_template::set_default_title(::user::document * pdocument)
   {

      //weeds-2019March

//      if(true)
//      {
//
//         return;
//
//      }

      string strDocName;

      if (GetDocString(strDocName, impact_system::docName) &&
            !strDocName.is_empty())
      {

         string strNum;

         strNum.Format("%d", m_nUntitledCount+1);

         strDocName += strNum;

      }
      else
      {

         strDocName = App(pdocument).load_string("untitled");

      }

      pdocument->set_title(strDocName);

   }


   /////////////////////////////////////////////////////////////////////////////
   // multiple_document_template diagnostics


   void multiple_document_template::dump(dump_context & dumpcontext) const
   {
      impact_system::dump(dumpcontext);

      dumpcontext << "\nm_nUntitledCount = " << m_nUntitledCount;
      dumpcontext << "\nwith " << m_docptra.get_count() << " open documents";
      ::count count = get_document_count();
      for(index index = 0; index < count; index++)
      {
         __pointer(::user::document) pdocument = get_document(index);
         dumpcontext << "\nwith ::user::document " << (void *)pdocument;
      }

      dumpcontext << "\n";
   }

   void multiple_document_template::assert_valid() const
   {
      impact_system::assert_valid();

      ::count count = get_document_count();
      for(index index = 0; index < count; index++)
      {
         __pointer(::user::document) pdocument = get_document(index);
         pdocument->assert_valid();
      }

   }


} // namespace user















