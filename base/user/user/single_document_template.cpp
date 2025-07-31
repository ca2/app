#include "framework.h"
#include "single_document_template.h"
#include "document.h"
#include "impact.h"
#include "frame_window.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/platform/scoped_restore.h"
#include "acme/handler/request.h"
#include "apex/platform/application.h"
#include "aura/user/user/wait_cursor.h"


namespace user
{


   single_document_template::single_document_template(const ::scoped_string & scopedstrMatter, const ::type_atom & typeatomDocument, const ::type_atom & typeatomFrame, const ::type_atom & typeatomImpact, const ::type_atom & typeatomData) :
      ::user::impact_system(scopedstrMatter, typeatomDocument, typeatomFrame, typeatomImpact, typeatomData)
   {

      defer_create_synchronization();

      m_pdocument = nullptr;

   }


   single_document_template::~single_document_template()
   {
#ifdef _DEBUG
      if (m_pdocument != nullptr)
         warning()(e_trace_category_appmsg) << "Warning: destroying single_document_template with live ::user::document.";
#endif
   }


   void single_document_template::destroy()
   {

      m_pdocument.release();

      ::user::impact_system::destroy();

   }





   ::collection::count single_document_template::get_document_count() const
   {
      return (m_pdocument == nullptr) ? 0 : 1;
   }

   ::user::document * single_document_template::get_document(::collection::index index) const
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

   // if lpszPathName == nullptr => create ___new file of this type
   void single_document_template::on_request(::request * prequestParameter)
   {

      auto prequest = ::as_pointer(prequestParameter);

      if (prequest.is_null())
      {

         throw ::exception(error_wrong_state);

      }

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

         }

      };

      if (prequest->id().is_null())
      {

         prequest->id() = m_typeatomImpact;

      }

      if (prequest->m_payloadOptions.has_property("visible"))
      {

         if(prequest->m_payloadOptions["visible"].is_true())
         {

            prequest->m_egraphicsoutputpurpose |= ::graphics::e_output_purpose_screen;

         }

      }

      prequest->m_estatus = error_failed;

      if (prequest)
      {

         prequest->payload("document").payload_release();

      }
      
      //bool bMakeVisible = prequest->payload("make_visible_boolean") || prequest->m_bMakeVisible;
      //   ::pointer<::user::interaction>puserinteractionParent = prequest->payload("parent_user_interaction").cast < ::user::interaction > ();
      //   ::pointer<::user::impact>pviewAlloc = prequest->payload("allocation_impact").cast < ::user::impact > ();

      ::pointer<::user::document>pdocument;

      ::pointer<::user::frame_window>pframe;

//      bool bCreated = false;      // => doc and frame created
//
//      bool bWasModified = false;

      prequest->m_bDocumentAndFrameCreated = false;

      prequest->m_bDocumentWasModified = false;

      if (m_pdocument.is_set())
      {
         // already have a ::user::document - reinit it

         pdocument = m_pdocument;

         if (!pdocument->save_modified())
         {

            return;        // leave the original one

         }

         ::user::impact * pimpact = pdocument->get_impact();

         pframe = pimpact->parent_frame();

         ASSERT(pframe != nullptr);

         ASSERT_KINDOF(frame_window, pframe);

         ASSERT_VALID(pframe);

      }
      else
      {
         
         // create a ___new ::user::document
         pdocument = create_new_document(prequest);
         
         ASSERT(pframe == nullptr);     // will be created below
         
         prequest->m_bDocumentAndFrameCreated = true;
         
      }

      if (pdocument == nullptr)
      {
         // linux message_box(__IDP_FAILED_TO_CREATE_DOC);

         output_error_message("Failed to create document");

         return;

      }

      prequest->payload("document") = pdocument;

      ASSERT(pdocument == m_pdocument);

      if (pframe == nullptr)
      {

         ASSERT(prequest->m_bDocumentAndFrameCreated);

         // create frame - set as main ::user::document frame
         bool bAutoDelete = pdocument->m_bAutoDelete;

         pdocument->m_bAutoDelete = false;

         // don't destroy if something goes wrong
         pframe = create_new_frame(pdocument, nullptr, prequest);

         pdocument->m_bAutoDelete = bAutoDelete;

         //auto psystem = system();

         if (!pframe)
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
      //else
      //{

      ASSERT_VALID(pframe);

      //if (! || !pusersystem->m_prequest)   // send initial update
      //{

      //pframe->send_message_to_descendants(e_message_system_update, id_initial_update, (lparam)0, true, true);

      //}


      //information() << "single_document_template::on_request_continuation";

      //      bool bMakeVisible = true;
      //
      //      if (prequest)
      //      {
      //
      //         if(prequest->payload("make_visible_boolean").is_true())
      //         {
      //
      //            prequest->m_egraphicsoutputpurpose |= ::graphics::e_output_purpose_screen;
      //
      //         }
      //
      //      }

      application()->post([this, pdocument, pframe, prequest]()
         {

            ::payload payloadFile = prequest->get_file();

            if (payloadFile.is_empty() || payloadFile.is_numeric())
            {

               // create a ___new ::user::document
               set_default_title(pdocument);

               // avoid creating temporary compound file when starting up invisible
               if (!(prequest->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_screen))
               {

                  pdocument->m_bEmbedded = true;

               }

               if (!pdocument->on_new_document())
               {
                  // user has been alerted to what failed in on_new_document
                  warning()(e_trace_category_appmsg) << "::user::document::on_new_document returned false.\n";

                  if (prequest->m_bDocumentAndFrameCreated)
                  {

                     pframe->destroy_window();    // will destroy ::user::document

                  }

                  return;

               }

               pdocument->m_bOpened = true;

               pdocument->id_update_all_impacts(id_initial_update);

            }
            else
            {

               wait_cursor wait(prequest);

               // open an existing ::user::document
               prequest->m_bDocumentWasModified = pdocument->is_modified();
               pdocument->set_modified_flag(false);  // not dirty for open

               if (!on_open_document(pdocument, prequest))
               {
                  // user has been alerted to what failed in on_open_document
                  warning()(e_trace_category_appmsg) << "::user::document::on_open_document returned false.\n";

                  if (prequest->m_bDocumentAndFrameCreated)
                  {

                     pframe->destroy_window();    // will destroy ::user::document

                  }
                  else if (!pdocument->is_modified())
                  {
                     // original ::user::document is untouched
                     pdocument->set_modified_flag(prequest->m_bDocumentWasModified);
                  }
                  else
                  {
                     // we corrupted the original ::user::document
                     set_default_title(pdocument);

                     if (!pdocument->on_new_document())
                     {
                        warning()(e_trace_category_appmsg) << "Error: on_new_document failed after trying "
                           "to open a ::user::document - trying to continue.\n";
                        // assume we can continue
                     }
                  }
                  return;        // open failed
               }
               pdocument->m_bOpened = true;
               pdocument->set_path_name(payloadFile);
               pdocument->update_title();
               pdocument->id_update_all_impacts(id_initial_update);


            }

            //      thread* pThread = ::get_task();

            if (!prequest->m_bHold)
            {

               pframe->payload("should_not_be_automatically_holded_on_initial_update_frame") = true;

            }

            prepare_frame(pframe, pdocument, prequest->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_screen);
            //      if(bCreated)
            //      {
            //
            //         prepare_frame(pFrame,pdocument,bMakeVisible);
            //
            //      }

                  /*     auto papp = get_app();

                       if (papp)
                       {

                          papp->defer_process_activation_message();

                       }*/

      });

      if (prequest)
      {

         prequest->payload("document") = pdocument;

      }
      else
      {

         //prequest->payload("document") = pdocument;

      }

      prequest->m_estatus = ::success;

//      }


   }


//   void single_document_template::on_request_continuation(::user::document * pdocument, ::user::frame_window * pframewindow, ::request * prequest)
//   {
//
//      ASSERT_VALID(pframewindow);
//
//      //if (! || !pusersystem->m_prequest)   // send initial update
//      //{
//
//        pframewindow->send_message_to_descendants(e_message_system_update, id_initial_update, (lparam) 0, true, true);
//
//      //}
//
//
//      information() << "single_document_template::on_request_continuation";
//
////      bool bMakeVisible = true;
////
////      if (prequest)
////      {
////
////         if(prequest->payload("make_visible_boolean").is_true())
////         {
////
////            prequest->m_egraphicsoutputpurpose |= ::graphics::e_output_purpose_screen;
////
////         }
////
////      }
//
//      ::payload payloadFile = prequest->get_file();
//
//      if (payloadFile.is_empty() || payloadFile.is_numeric())
//      {
//
//         // create a ___new ::user::document
//         set_default_title(pdocument);
//
//         // avoid creating temporary compound file when starting up invisible
//         if (!(prequest->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_screen))
//         {
//
//            pdocument->m_bEmbedded = true;
//
//         }
//
//         if (!pdocument->on_new_document())
//         {
//            // user has been alerted to what failed in on_new_document
//            warning()(e_trace_category_appmsg) << "::user::document::on_new_document returned false.\n";
//
//            if (prequest->m_bDocumentAndFrameCreated)
//            {
//
//               pframewindow->destroy_window();    // will destroy ::user::document
//
//            }
//
//            return;
//
//         }
//
//         pdocument->m_bOpened = true;
//
//         pdocument->id_update_all_impacts(id_incoming_document);
//
//      }
//      else
//      {
//
//         wait_cursor wait(prequest);
//
//         // open an existing ::user::document
//         prequest->m_bDocumentWasModified = pdocument->is_modified();
//         pdocument->set_modified_flag(false);  // not dirty for open
//
//         if (!on_open_document(pdocument, prequest))
//         {
//            // user has been alerted to what failed in on_open_document
//            warning()(e_trace_category_appmsg) << "::user::document::on_open_document returned false.\n";
//
//            if (prequest->m_bDocumentAndFrameCreated)
//            {
//
//               pframewindow->destroy_window();    // will destroy ::user::document
//
//            }
//            else if (!pdocument->is_modified())
//            {
//               // original ::user::document is untouched
//               pdocument->set_modified_flag(prequest->m_bDocumentWasModified);
//            }
//            else
//            {
//               // we corrupted the original ::user::document
//               set_default_title(pdocument);
//
//               if (!pdocument->on_new_document())
//               {
//                  warning()(e_trace_category_appmsg)<< "Error: on_new_document failed after trying "
//                                                       "to open a ::user::document - trying to continue.\n";
//                  // assume we can continue
//               }
//            }
//            return;        // open failed
//         }
//         pdocument->m_bOpened = true;
//         pdocument->set_path_name(payloadFile);
//         pdocument->update_title();
//         pdocument->id_update_all_impacts(id_incoming_document);
//
//
//      }
//
////      thread* pThread = ::get_task();
//
//      if(!prequest->m_bHold)
//      {
//
//         pframewindow->payload("should_not_be_automatically_holded_on_initial_update_frame") = true;
//
//      }
//
////      if(bCreated)
////      {
////
////         prepare_frame(pFrame,pdocument,bMakeVisible);
////
////      }
//
//      /*     auto papp = get_app();
//
//           if (papp)
//           {
//
//              papp->defer_process_activation_message();
//
//           }*/
//
//      if (prequest)
//      {
//
//         prequest->payload("document") = pdocument;
//
//      }
//      else
//      {
//
//         //prequest->payload("document") = pdocument;
//
//      }
//
//      prequest->m_estatus = ::success;
//
//   }


   void single_document_template::set_default_title(::user::document * pdocument)
   {
      
      string strDocName;

      if (!GetDocString(strDocName, impact_system::docName) || strDocName.is_empty())
      {

         //auto papp = get_app();

         //strDocName = papp->load_string("untitled");

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



