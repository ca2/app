#include "framework.h"
#include "base/user/user/_user.h"
#include "aura/user/wait_cursor.h"


namespace user
{


   single_document_template::single_document_template(const ::string & pszMatter, ::type pDocClass, ::type pFrameClass, ::type pImpactClass) :
      ::user::impact_system(pszMatter, pDocClass, pFrameClass, pImpactClass)
   {

      defer_create_mutex();

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

   // if lpszPathName == nullptr => create new file of this type
   void single_document_template::on_request(::create * pcreate)
   {

      if (pcreate->m_atom.is_null())
      {

         pcreate->m_atom = m_typeImpact.m_strName;

      }

      if (pcreate->m_varOptions.has_property("visible"))
      {

         pcreate->m_bMakeVisible = pcreate->m_varOptions.is_true("visible");

      }

      pcreate->m_estatus = error_failed;

      if (pcreate->m_pcommandline)
      {

         pcreate->m_pcommandline->m_varQuery["document"].release();

      }

      //bool bMakeVisible = pcreate->m_pcommandline->m_varQuery["make_visible_boolean"] || pcreate->m_bMakeVisible;
      //   __pointer(::user::interaction) puserinteractionParent = pcreate->m_pcommandline->m_varQuery["parent_user_interaction"].cast < ::user::interaction > ();
      //   __pointer(::user::impact) pviewAlloc = pcreate->m_pcommandline->m_varQuery["allocation_view"].cast < ::user::impact > ();

      __pointer(::user::document) pdocument;

      __pointer(::user::frame_window) pFrame;

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

         ::user::impact * pimpact = pdocument->get_view();

         pFrame = pimpact->get_parent_frame();

         ASSERT(pFrame != nullptr);

         ASSERT_KINDOF(frame_window, pFrame);

         ASSERT_VALID(pFrame);

      }
      else
      {
         
         // create a new ::user::document
         pdocument = create_new_document(pcreate);
         
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
         pFrame = create_new_frame(pdocument, nullptr, pcreate);

         pdocument->m_bAutoDelete = bAutoDelete;

         auto psystem = m_psystem->m_pbasesystem;

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
      
      if (pcreate->m_pcommandline)
      {

         bMakeVisible = pcreate->m_pcommandline->m_varQuery["make_visible_boolean"].get_bool() || pcreate->m_bMakeVisible;

      }

      ::payload payloadFile = pcreate->get_file();

      if (payloadFile.is_empty() || payloadFile.is_numeric())
      {

         // create a new ::user::document
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

         pdocument->id_update_all_views(id_new_document);

      }
      else
      {

         wait_cursor wait(pcreate);

         // open an existing ::user::document
         bWasModified = pdocument->is_modified();
         pdocument->set_modified_flag(false);  // not dirty for open

         if (!on_open_document(pdocument, pcreate))
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
         pdocument->id_update_all_views(OPEN_DOCUMENT_UPDATE);


      }

//      thread* pThread = ::get_task();

      if(!pcreate->m_bHold)
      {

         pFrame->payload("should_not_be_automatically_holded_on_initial_update_frame") = true;

      }

      if(bCreated)
      {

         InitialUpdateFrame(pFrame,pdocument,bMakeVisible);

      }

 /*     auto papp = get_app();

      if (papp)
      {

         papp->defer_process_activation_message();

      }*/

      if (pcreate->m_pcommandline)
      {

         pcreate->m_pcommandline->m_varQuery["document"] = pdocument;

      }
      else
      {

         //pcreate->m_varQuery["document"] = pdocument;

      }

      pcreate->m_estatus = ::success;

   }


   void single_document_template::set_default_title(::user::document * pdocument)
   {
      
      string strDocName;

      if (!GetDocString(strDocName, impact_system::docName) || strDocName.is_empty())
      {

         auto papp = get_app();

         strDocName = papp->m_papplication->load_string("untitled");

      }

      pdocument->set_title(strDocName);

   }


   void single_document_template::dump(dump_context & dumpcontext) const
   {

      impact_system::dump(dumpcontext);

      if (m_pdocument)
      {

         dumpcontext << "with ::user::document: " << (void*)m_pdocument;

      }
      else
      {

         dumpcontext << "with no ::user::document";

      }

      dumpcontext << "\n";

   }


   void single_document_template::assert_ok() const
   {

      impact_system::assert_ok();

   }


} // namespace user



