#include "framework.h"
#include "multiple_document_template.h"
#include "document.h"
#include "frame_window.h"
#include "impact.h"
#include "acme/constant/id.h"
#include "acme/constant/user_message.h"
#include "acme/handler/request.h"
#include "acme/platform/scoped_restore.h"
#include "berg/platform/application.h"


namespace user
{


   multiple_document_template::multiple_document_template(const ::scoped_string & scopedstrMatter, const ::type_atom & typeatomDocument, const ::type_atom & typeatomFrame, const ::type_atom & typeatomImpact, const ::type_atom & typeatomData) :
      ::user::impact_system(scopedstrMatter, typeatomDocument, typeatomFrame, typeatomImpact, typeatomData)
   {

      defer_create_synchronization();

      ASSERT(m_docptra.is_empty());

      m_nUntitledCount = 0;   // start at 1

   }


   multiple_document_template::~multiple_document_template()
   {

#ifdef _DEBUG

      if (!m_docptra.is_empty())
      {

         warning()(e_trace_category_appmsg) << "Warning: destroying multiple_document_template with " << m_docptra.get_count() << " documents alive.";

      }

#endif

   }



   void multiple_document_template::destroy()
   {

      for (auto & pdocument : m_docptra)
      {
         
         try
         {

            pdocument.defer_destroy();

         }
         catch (...)
         {


         }

      }

      ::user::impact_system::destroy();

   }


   void multiple_document_template::load_impact_system()
   {

      impact_system::load_impact_system();

   }


   

   ::collection::count multiple_document_template::get_document_count() const
   {

      return m_docptra.get_count();

   }


   ::user::document * multiple_document_template::get_document(::collection::index index) const
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


   void multiple_document_template::erase_document(::user::document * pdocument)
   {

      impact_system::erase_document(pdocument);

      m_docptra.erase(pdocument);

   }


   void multiple_document_template::on_request(::request * prequest)
   {

      prequest->m_countStack++;

      at_end_of_scope
      {

         prequest->m_countStack--;

      if (prequest->m_countStack <= 0)
      {

         for (auto & procedure : prequest->m_procedureaOnFinishRequest)
         {

            try
            {

               procedure();

            }
            catch (...)
            {


            }

         }

         prequest->m_procedureaOnFinishRequest.clear();
      };

      };

      prequest->m_estatus = error_failed;

      prequest->payload("document") = (::object *) nullptr;

      //bool bMakeVisible = prequest->m_bMakeVisible;

      ::pointer<::user::document>pdocument = create_new_document(prequest);

      if (pdocument == nullptr)
      {

         warning()(e_trace_category_appmsg) << "impact_system::create_new_document returned nullptr.";

         // TODO Translate
         output_error_message("failed to create ::user::document");

         return;

      }

      bool bAutoDelete = pdocument->m_bAutoDelete;

      pdocument->m_bAutoDelete = false;   // don't destroy if something goes wrong

      ::pointer<::user::frame_window>pFrame = create_new_frame(pdocument, nullptr, prequest);

      pdocument->m_bAutoDelete = bAutoDelete;

      if (pFrame == nullptr)
      {

         string strId;

         if (prequest->m_puserelementAlloc)
         {

            strId = ::type(prequest->m_puserelementAlloc).name();

         }

         if (!strId.case_insensitive_contains("userex::message_box"))
         {

            output_error_message("Failed to create ::user::document");

         }

         erase_document(pdocument);

         return;

      }

      ASSERT_OK(pFrame);

      if(prequest->m_pdata)
      {

         pdocument->m_bNew = true;

         if (!pdocument->open_data(prequest->m_pdata))
         {
            // ::account::user has be alerted to what failed in on_new_document
            warning()(e_trace_category_appmsg) << "::user::document::on_new_document returned false.\n";
            pFrame->destroy_window();
            return;

         }
         pdocument->m_bOpened = true;
         // it worked, now bump untitled count
         //m_nUntitledCount++;
         pdocument->id_update_all_impacts(id_initial_update);


      }


      else if(!prequest->has_file())
      {
         // create a ___new ::user::document - with default ::user::document name
         set_default_title(pdocument);

         // avoid creating temporary compound file when starting up invisible
         if (!(prequest->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_screen))
         {

            pdocument->m_bEmbedded = true;

         }

         pdocument->m_bNew = true;

         if (!pdocument->on_new_document())
         {
            // ::account::user has be alerted to what failed in on_new_document
            warning()(e_trace_category_appmsg) << "::user::document::on_new_document returned false.\n";
            pFrame->destroy_window();
            return;

         }
         pdocument->m_bOpened = true;
         // it worked, now bump untitled count
         m_nUntitledCount++;
         pdocument->id_update_all_impacts(id_initial_update);

      }
      else
      {

         pdocument->m_bNew = false;

         // open an existing ::user::document
         if(!on_open_document(pdocument, prequest))
         {
            // failed to open or just failed to queue to open
            // if m_bQueueDocumentOpening flag is set, document opening is queued, and failure would be reported in a unknown way
            // prepare aura for async operations and also async failures
            // ::account::user has be alerted to what failed in on_open_document
            warning()(e_trace_category_appmsg) << "::user::document::on_open_document returned false.\n";
            pFrame->post_message(::user::e_message_destroy_window);
            return;

         }
         pdocument->m_bOpened = true;
         //pdocument->set_path_name(pcreate->m_payloadFile);

         pdocument->id_update_all_impacts(id_initial_update);

      }

      if(!prequest->m_bHold)
      {

         pFrame->payload("should_not_be_automatically_holded_on_initial_update_frame") = true;

      }

      prepare_frame(pFrame, pdocument, prequest->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_screen);

      prequest->payload("document") = pdocument;

      prequest->m_estatus = ::success;

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

         strNum.formatf("%d", m_nUntitledCount+1);

         strDocName += strNum;

      }
      else
      {

         auto papp = pdocument->get_app();

         strDocName = papp->load_string("untitled");

      }

      pdocument->set_title(strDocName);

   }


   /////////////////////////////////////////////////////////////////////////////
   // multiple_document_template diagnostics


//   void multiple_document_template::dump(dump_context & dumpcontext) const
//   {
//      impact_system::dump(dumpcontext);
//
//      //dumpcontext << "\nm_nUntitledCount = " << m_nUntitledCount;
//      //dumpcontext << "\nwith " << m_docptra.get_count() << " open documents";
//      //::collection::count count = get_document_count();
//      //for(::collection::index index = 0; index < count; index++)
//      //{
//      //   ::pointer<::user::document>pdocument = get_document(index);
//      //   dumpcontext << "\nwith ::user::document " << (void *)pdocument;
//      //}
//
//      //dumpcontext << "\n";
//   }
//
//   void multiple_document_template::assert_ok() const
//   {
//      impact_system::assert_ok();
//
//      ::collection::count count = get_document_count();
//      for(::collection::index index = 0; index < count; index++)
//      {
//         ::pointer<::user::document>pdocument = get_document(index);
//         pdocument->assert_ok();
//      }
//
//   }


} // namespace user















