#include "framework.h"


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      thread::thread(__pointer(base_application) papp) :
         ::object(pobject),
         ::thread(pobject)
      {
         SetMainWnd(nullptr);
         m_bPendingShowCommand = false;
         //    m_pmfmh = new CMessageFilterMainHook();
      }


      thread::~thread()
      {
         //    if(m_pmfmh != nullptr)
         //      delete m_pmfmh;
      }


      bool thread::initialize_thread()
      {
         set_auto_delete(false);
         SetMainWnd(nullptr);
         ASSERT(GetMainWnd() == nullptr);
         // TODO:  perform and per-thread initialization here

         //    CVMSApp * pApp = (CVMSApp *) &System;
         //CVMSApp * pApp = (CVMSApp *) &System;
         //   MessageFilterHookManager * pmfmh;
         //  MessageFilterHookManager::AppGetMessageFilterHookManager(&pmfmh);
         //pmfmh->MessageFilterHook();
         //MessageFilterHook();

         //ViewToolsAlbum();
         return true;
      }

      i32 thread::exit_thread()
      {
         // TODO:  perform any per-thread cleanup here
         //    CVMSApp * pApp = (CVMSApp *) &System;
         //MessageFilterHookManager * pmfmh;
         //MessageFilterHookManager::AppGetMessageFilterHookManager(&pmfmh);
         //pmfmh->MessageFilterUnhook();

         CoUninitialize();
         return ::thread::exit_thread();
      }

      void thread::install_message_routing(::channel * pchannel)
      {
         MESSAGE_LINK(thread::MessageMixerThread, pchannel, this, &thread::OnMixerMessage);
         MESSAGE_LINK(WM_USER, pchannel, this, &thread::OnUserMessage);
      }

      // BEGIN_MESSAGE_MAP(thread, thread)
      //{{AFX_MSG_MAP(thread)
      // NOTE - the ClassWizard will add and remove mapping macros here.
      //}}AFX_MSG_MAP
      //    ON_THREAD_MESSAGE(thread::MessageMixerThread, OnMixerMessage)
      /* xxx   ON_THREAD_MESSAGE(VMSM_V001, OnVmsmV001)
      ON_THREAD_MESSAGE(VMSM_EXCEPTION, OnVmsmException) */
      //    ON_THREAD_MESSAGE(WM_USER, OnUserMessage)
      // END_MESSAGE_MAP()

      /////////////////////////////////////////////////////////////////////////////
      // thread message handlers


      void thread::OnMixerMessage(::message::message * pmessage)
      {
         __pointer(::message::base) pbase(pmessage);

         if(pbase->m_wparam ==  23)
         {
         }
         else if(pbase->m_wparam ==  21)
         {
         }
         else if(pbase->m_wparam == 19)
         {
            ASSERT(false);
            //        CDBCentral * pgraphics = (CDBCentral *) lParam;
            //      pgraphics->SongsCreateBuildAlbumThread(
            //        (CDataCentral::EBuildSongsAlbumOperation)
            //      (CDataCentral::eBuildSongsAlbumDeleteNotFound |
            //    CDataCentral::eBuildSongsAlbumAddNew |
            //  CDataCentral::eBuildSongsAlbumCreateSearchReferences),
            //false, this, this);
         }
         else if(pbase->m_wparam == 20)
         {
            ASSERT(false);
            //        CDBCentral * pgraphics = (CDBCentral *) lParam;
            //      pgraphics->SongsCreateBuildAlbumThread(
            //        (CDataCentral::EBuildSongsAlbumOperation)
            //      (CDataCentral::eBuildSongsAlbumAddNew |
            //    CDataCentral::eBuildSongsAlbumCreateSearchReferences),
            //  true, this, this);
         }
         else if(pbase->m_wparam == 810)
         {
            ASSERT(false);
            //        CDBCentral * pgraphics = (CDBCentral *) lParam;
            //      pgraphics->SongsCreateBuildAlbumThread(
            //        (CDataCentral::EBuildSongsAlbumOperation)
            //      CDataCentral::eBuildSongsAlbumDeleteNotFound,
            //    false, this, this);
         }
         else if(pbase->m_wparam == 20191817)
         {
            ASSERT(false);
         }
         else if(pbase->m_wparam == 67985)
         {
            ASSERT(false);
            //        m_pMixerDocTemplate->close_all_documents(lParam != 0);
         }


         //    if(m_pMixerDocTemplate != nullptr)
         //  {
         //    m_pMixerDocTemplate->open_new_document();
         //  if(GetMainWnd() != nullptr)
         //{
         //  GetMainWnd()->SetForegroundWindow();
         //}
         //}
      }




      bool thread::on_idle(::i32 lCount)
      {
         // TODO: add your specialized code here and/or call the base class
         return ::thread::on_idle(lCount);
      }

      void thread::OnVmsmException(::message::message * pmessage)
      {
         UNREFERENCED_PARAMETER(pmessage);
         //__pointer(base_application) pApp = (__pointer(base_application)) &System;
         //pApp->post_thread_message(VMSM_EXCEPTION, wParam, lParam);
      }


      void thread::OnUserMessage(::message::message * pmessage)
      {
         __pointer(::message::base) pbase(pmessage);

         switch(pbase->m_wparam)
         {

         case 21:
            //                    ASSERT(false);
            //                  //ReserveSong_(pMsg->lParam);
            //GetPlayerDocTemplate()->ReserveSong(lParam, false, true);
            break;
         case 22:
         {
            //  CDWArray * pdwa = (CDWArray *) lParam;
            //GetPlayerDocTemplate()->ReserveSong((LPINT) &pdwa->get_data()[1], pdwa->get_at(0), false, true);
            //delete pdwa;
         }
         break;
         case 23:
         {
            //CStrArray * pstra = (CStrArray *) lParam;
            //GetPlayerDocTemplate()->ReserveSong(pstra, false, true);
            //delete pstra;
         }
         break;
         case 543:
         {

            //            if(m_poptionsview == nullptr)
            {
               //                m_poptionsview = new COptionsDialog();
               //              m_poptionsview->create(nullptr);
            }

            //            if(m_poptionsview != nullptr)
            {
               //            m_poptionsview->ShowWindow(SW_SHOWNORMAL);
            }

         }
         break;

         }

         switch(pbase->m_wparam)
         {
         case 131415:
            // ViewToolsAlbum();
            break;
         case 565758:
         {
            /*CDBBuildAlbumThreadData * lpdata =
            (CDBBuildAlbumThreadData *)lParam;
            __pointer(single_document_template) pAlbumDocTemplate = nullptr;
            if(GetAlbumThread())
            {
            pAlbumDocTemplate = GetAlbumThread()->GetMixerDocTemplate();
            }
            bool bVisible = false;
            if(pAlbumDocTemplate != nullptr)
            {
            bVisible = pAlbumDocTemplate->get_document_count() != nullptr;

            // avoid thread quit on close all documents
            GetAlbumThread()->GetMainWnd() = nullptr;

            GetAlbumThread()->GetMixerDocTemplate()->close_all_documents(false);
            }
            //CMixerFrameWnd * pAlbum = GetMixerDocTemplate();
            //bool bVisible;
            //if(pAlbum != nullptr)
            //{
            //  bVisible = (pAlbum->GetStyle() & WS_VISIBLE) != 0;
            //if(bVisible)
            //  pAlbum->ShowWindow(SW_HIDE);
            //}
            lpdata->bVisible = bVisible;*/
         }
         break;
         case 676869:
         {
            //ASSERT(false);
            /*            CDBBuildAlbumThreadData * lpdata =
            (CDBBuildAlbumThreadData *)lParam;
            if(!lpdata->m_ptaskdlg->create(IDD_TASK))
            {
            System.message_box("Could not create task dialog");
            return;
            }

            GetAlbumThread()->GetMainWnd() = lpdata->m_ptaskdlg;
            */
         }
         case 787970:
         {
            /*CDBBuildAlbumThreadData * lpdata =
            (CDBBuildAlbumThreadData *)lParam;
            if(m_pMixerDocTemplate != nullptr)
            {
            if(lpdata->bVisible)
            {
            lpdata->lpDataCentral->m_csBuildAlbumThreadData.lock();
            lpdata->m_evStarted.lock();
            //lpdata->m_ptaskdlg->m_pCloseWindow = pAlbum;
            //            lpdata->m_ptaskdlg->m_lparamClose = 10;
            lpdata->lpDataCentral->m_csBuildAlbumThreadData.unlock();
            }
            }*/
         }
         break;
         case 345456:
         {

         }
         break;
         case 321432:
         {
            // On Task Dialog Stop
            //ASSERT(m_pdbcentral != nullptr);
            //m_pdbcentral->SetBuildAlbumThreadsCancelFlag();
         }
         break;
         case 3214:
         {
            //OnChangeEconoMode();

         }
         break;
         case 534231:
         {
            //GetKarWnd()->send_message_to_descendants(WM_USER, 534231);
         }
         break;

         default:;
            break;

         }

      }


      void thread::pre_translate_message(::message::message * pmessage)
      {

         return ::thread::pre_translate_message(pmessage);

      }


   } // namespace audio_mixer_mmsystem


} // namespace multimedia






