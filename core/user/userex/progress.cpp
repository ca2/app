#include "framework.h"
#include "core/user/userex/_userex.h"
#include "acme/const/timer.h"
#include "core/user/userex/progress.h"

namespace userex
{


   progress_control::progress_control()
   {

      
      
      m_iStepCount = 0;
      m_pdocument = nullptr;
      m_pview = nullptr;



   }


   progress_control::~progress_control()
   {

   }


   void progress_control::set_progress_title(const char * pszTitle)
   {

      m_pview->get_parent_frame()->set_window_text(pszTitle);

   }

#ifdef DEBUG
   i64 progress_control::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      i64 i = ::progress_control::dec_ref(OBJ_REF_DBG_ARGS);

      //if (i == 1 && m_pthread.is_set())
      //{

      //   m_pthread->finish();

      //}

      return i;

   }

#endif

   void progress_control::create_progress()
   {

      if (m_pdocument == nullptr)
      {

         auto pcontext = m_pcontext;
         
         auto psession = pcontext->m_paurasession;
         
         auto puser = psession->m_puser->m_pcoreuser;

         m_pdocument = puser->m_ptemplateProgress2->open_document_file(get_application(), ::e_type_null, __visible(false));

         m_pview = m_pdocument->get_typed_view<::userex::progress_view>();

      }

      m_pview->m_pprogress->m_pscalar = new double_scalar(this, scalar_progress);

      m_pview->m_pprogresscontrol = this;

   }


   void progress_control::close_progress()
   {

      ::user::document * pdocument = nullptr;

      {

         synchronous_lock synchronouslock(mutex());

         pdocument = m_pdocument;

         m_pdocument = nullptr;

      }

      pdocument->close_document();

   }


   void progress_control::redraw()
   {

      if (m_pview == nullptr)
      {

         return;

      }

      m_pview->set_need_redraw();

      m_pview->post_redraw();


   }


   void progress_control::defer_show(::user::interaction * puiParent, const char* pszTitle, ::count iStepCount)
   {

      m_strTitle = pszTitle;
      m_iStep = 0;
      m_iStepCount = iStepCount;


      m_strTitle = pszTitle;
      m_iStep = 0;

      __pointer(progress_control) pprogressCopy = this;

      pprogressCopy->create_progress();

//      defer_fork("show_progress", [this, pprogressCopy, puiParent]()
//      {
//
//         __pointer(progress_control) pprogress = pprogressCopy;
//
//
//         try
//         {
//
//            
//
//            release();
//
//         }
//         catch (...)
//         {
//                  
//            }
//
//            sleep(150_ms);
//
//            if (m_pdocument != nullptr)
//            {
//
//               try
//               {
//
//            }
//            catch (...)
//            {
//
//
//            }
//
//            ::get_task()->m_bSimpleMessageLoop = false;
//
//            ::get_task()->::thread::run();
//
//         }
//
//         children_erase(::get_task());
//
//         close_progress();
//
////            release();
//
//         output_debug_string("finished");
//
//      });

   }


   progress_view::progress_view()
   {

   }


   progress_view::~progress_view()
   {

   }


   void progress_view::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void  progress_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void  progress_view::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &progress_view::on_message_create);


   }


   void progress_view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

   }


   void progress_view::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);
      
      pmessage->previous();

      if (!m_pprogress->create_control(this, "progress_control"))
      {


         pcreate->m_lresult = -1;

         pcreate->m_bRet = true;

         return;

      }

      SetTimer(e_timer_update_current_area, 300);


   }


   void progress_view::_001OnTimer(::timer* ptimer)
   {

      if (ptimer->m_uEvent == e_timer_update_current_area)
      {

         KillTimer(ptimer->m_uEvent);

         ::rectangle_i32 rectangle;

         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         auto pdisplay = pwindowing->display();

         pdisplay->get_main_monitor(rectangle);

         rectangle.deflate(rectangle.width() / 6, rectangle.height() / 3, rectangle.width() / 6, rectangle.height() / 2);

         auto pframe = get_parent_frame();

         if (::is_set(pframe))
         {

            pframe->m_sizeMinimum.cx = 300;
            pframe->m_sizeMinimum.cy = 50;

            pframe->good_restore(nullptr, rectangle, true);

            pframe->set_need_redraw();

            pframe->post_redraw();

         }

      }

   }


   void progress_view::on_message_destroy(::message::message * pmessage)
   {

      pmessage->previous();

   }


   void progress_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_pprogress == nullptr)
      {

         return;

      }

      pgraphics->set_text_color(argb(255, 80, 80, 80));

      pgraphics->draw_text(m_pprogresscontrol->m_strStatus, m_rectStatus, e_align_center);

   }


   void progress_view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = get_client_rect();

      if(rectangleClient.is_empty())
      {

         return;

      }

      int cxBorder = rectangleClient.width() / 16;
      int h = rectangleClient.height() / 4;

      ::rectangle_i32 rectIndicator(rectangleClient);

      rectIndicator.deflate(cxBorder, h, cxBorder, h * 2);

      m_rectStatus = rectangleClient;

      m_rectStatus.deflate(cxBorder, h * 2, cxBorder, h);

      m_pprogress->display_child(rectIndicator);

   }


} // namespace userex


