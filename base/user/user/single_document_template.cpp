#include "framework.h"
#include "single_document_template.h"
#include "document.h"
#include "impact.h"
#include "frame_window.h"
#include "acme/constant/id.h"
#include "acme/handler/request.h"
#include "apex/platform/application.h"
#include "aura/user/user/wait_cursor.h"


namespace user
{


   single_document_template::single_document_template(const ::string & pszMatter, ::type pDocClass, ::type pFrameClass, ::type pImpactClass) :
      ::user::impact_system(pszMatter, pDocClass, pFrameClass, pImpactClass)
   {

      defer_create_synchronization();

      m_pdocument = nullptr;

   }


   single_document_template::~single_document_template()
   {
#ifdef _DEBUG
      if (m_pdocument != nullptr)
         CATEGORY_WARNING(appmsg, "Warning: destroying single_document_template with live ::user::document.");
#endif
   }

   ::count single_document_template::get_document_count() const
   {
      return (m_pdocument == nullptr) ? 0 : 1;
   }

   ::user::document * single_document_template::get_document(index index) const
   {
      if(index == 0)
         return m_pdocument;
      else
         return nullptr;
   }


   void single_document_template::add_document(::user::document * pdocument)
   {

      if(m_pdocument == nullptr)
      {

         m_pdocument = pdocument;

         impact_system::add_document(pdocument);

      }

   }


   void single_document_template::erase_document(::user::document * pdocument)
   {

      if(m_pdocument == pdocument)
      {

         impact_system::erase_document(pdocument);

         m_pdocument.release();

      }

   }


   /////////////////////////////////////////////////////////////////////////////
   // single_document_template commands

   // if lpszPathName == nullptr => create memory_new file of this type
   void single_document_template::on_request(::request * prequest)
   {

      if (prequest->m_atom.is_null())
      {

         prequest->m_atom = m_typeImpact;

      }

      if (prequest->m_payloadOptions.has_property("visible"))
      {

         prequest->m_bMakeVisible = prequest->m_payloadOptions.is_true("visible");

      }

      prequest->m_estatus = error_failed;

      if (prequest)
      {

         prequest->payload("document").release();

      }

      //bool bMakeVisible = prequest->payload("make_visible_boolean") || prequest->m_bMakeVisible;
      //   ::pointer<::user::interaction>puserinteractionParent = prequest->payload("parent_user_interaction").cast < ::user::interaction > ();
      //   ::pointer<::user::impact>pviewAlloc = prequest->payload("allocation_impact").cast < ::user::impact > ();

      ::pointer<::user::document>pdocument;

      ::pointer<::user::frame_window>pFrame;

      bool bCreated = false;      // => doc and frame created

      bool bWasModified = false;

      if (m_pdocument.is_set())
      {
         // already have a ::user::document - reinit it

         pdocument = m_pdocument;

         if (!pdocument->save_modified())
         {

            return;        // leave the original one

         }

         ::user::impact * pimpact = pdocument->get_impact();

         pFrame = pimpact->parent_frame();

         ASSERT(pFrame != nullptr);

         ASSERT_KINDOF(frame_window, pFrame);

         ASSERT_VALID(pFrame);

      }
      else
      {
         
         // create a memory_new ::user::document
         pdocument = create_new_document(prequest);
         
         ASSERT(pFrame == nullptr);     // will be created below
         
         bCreated = true;
         
      }

      if (pdocument == nullptr)
      {
         // linux message_box(__IDP_FAILED_TO_CREATE_DOC);

         output_error_message("Failed to create document");

         return;

      }

      ASSERT(pdocument == m_pdocument);

      if (pFrame == nullptr)
      {

         ASSERT(bCreated);

         // create frame - set as main ::user::document frame
         bool bAutoDelete = pdocument->m_bAutoDelete;

         pdocument->m_bAutoDelete = false;

         // don't destroy if something goes wrong
         pFrame = create_new_frame(pdocument, nullptr, prequest);

         pdocument->m_bAutoDelete = bAutoDelete;

         //auto psystem = acmesystem()->m_pbasesystem;

         if (!pFrame)
         {

            //auto& result = psystem->m_estatus;

            //::e_status estatus;

            //if(!result.get_exit_status(estatus))
            //{

            //   output_error_message("Failed to create Document");

            //}

            return;

         }

      }

      ASSERT_VALID(pFrame);

      bool bMakeVisible = true;
      
      if (prequest)
      {

         bMakeVisible = prequest->payload("make_visible_boolean").get_bool() || prequest->m_bMakeVisible;

      }

      ::payload payloadFile = prequest->get_file();

      if (payloadFile.is_empty() || payloadFile.is_numeric())
      {

         // create a memory_new ::user::document
         set_default_title(pdocument);

         // avoid creating temporary compound file when starting up invisible
         if (!bMakeVisible)
         {

            pdocument->m_bEmbedded = true;

         }

         if (!pdocument->on_new_document())
         {
            // user has been alerted to what failed in on_new_document
            CATEGORY_WARNING(appmsg, "::user::document::on_new_document returned false.\n");

            if (bCreated)
            {

               pFrame->destroy_window();    // will destroy ::user::document

            }

            return;

         }

         pdocument->id_update_all_impacts(id_new_document);

      }
      else
      {

         wait_cursor wait(prequest);

         // open an existing ::user::document
         bWasModified = pdocument->is_modified();
         pdocument->set_modified_flag(false);  // not dirty for open

         if (!on_open_document(pdocument, prequest))
         {
            // user has been alerted to what failed in on_open_document
            CATEGORY_WARNING(appmsg, "::user::document::on_open_document returned false.\n");

            if (bCreated)
            {

               pFrame->destroy_window();    // will destroy ::user::document

            }
            else if (!pdocument->is_modified())
            {
               // original ::user::document is untouched
               pdocument->set_modified_flag(bWasModified);
            }
            else
            {
               // we corrupted the original ::user::document
               set_default_title(pdocument);

               if (!pdocument->on_new_document())
               {
                  CATEGORY_WARNING(appmsg, "Error: on_new_document failed after trying "
                        "to open a ::user::document - trying to continue.\n");
                  // assume we can continue
               }
            }
            return;        // open failed
         }
         pdocument->set_path_name(payloadFile);
         pdocument->update_title();
         pdocument->id_update_all_impacts(ID_OPEN_DOCUMENT);


      }

//      thread* pThread = ::get_task();

      if(!prequest->m_bHold)
      {

         pFrame->payload("should_not_be_automatically_holded_on_initial_update_frame") = true;

      }

      if(bCreated)
      {

         prepare_frame(pFrame,pdocument,bMakeVisible);

      }

 /*     auto papp = get_app();

      if (papp)
      {

         papp->defer_process_activation_message();

      }*/

      if (prequest)
      {

         prequest->payload("document") = pdocument;

      }
      else
      {

         //prequest->payload("document") = pdocument;

      }

      prequest->m_estatus = ::success;

   }


   void single_document_template::set_default_title(::user::document * pdocument)
   {
      
      string strDocName;

      if (!GetDocString(strDocName, impact_system::docName) || strDocName.is_empty())
      {

         //auto papp = get_app();

         //strDocName = papp->m_papexapplication->load_string("untitled");

      }

      pdocument->set_title(strDocName);

   }


//   void single_document_template::dump(dump_context & dumpcontext) const
//   {
//
//      impact_system::dump(dumpcontext);
//
//      //if (m_pdocument)
//      //{
//
//      //   dumpcontext << "with ::user::document: " << (void*)m_pdocument;
//
//      //}
//      //else
//      //{
//
//      //   dumpcontext << "with no ::user::document";
//
//      //}
//
//      //dumpcontext << "\n";
//
//   }
//
//
//   void single_document_template::assert_ok() const
//   {
//
//      impact_system::assert_ok();
//
//   }


} // namespace user



