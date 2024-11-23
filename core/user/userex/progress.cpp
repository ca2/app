#include "framework.h"
#include "progress.h"
//#include "user.h"
#include "acme/constant/message.h"
#include "acme/constant/timer.h"
#include "acme/platform/timer.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/message/user.h"
#include "aura/platform/session.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/user/user/progress.h"
#include "aura/windowing/display.h"
#include "aura/windowing/windowing.h"
#include "base/user/user/multiple_document_template.h"
#include "base/user/user/document.h"
#include "core/user/user/user.h"


namespace userex
{


   progress_control::progress_control()
   {



      m_iStepCount = 0;
      m_pdocument = nullptr;
      m_pimpact = nullptr;



   }


   progress_control::~progress_control()
   {

   }


   void progress_control::set_progress_title(const ::string & pszTitle)
   {

      m_pimpact->parent_frame()->set_window_text(pszTitle);

   }


#ifdef _DEBUG
   huge_integer progress_control::decrement_reference_count()
   {

      huge_integer i = ::progress::real::decrement_reference_count();

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

         //auto pcontext = m_papplication;

         //auto psession = pcontext->m_psession;

         //auto puser = psession->m_puser;

         m_pdocument = user()->impact_system("progress_impact")->open_document_file(get_app(), ::e_type_null, __visible(false).is_true());

         m_pimpact = m_pdocument->get_typed_impact<::userex::progress_impact>();

      }

      m_pimpact->m_pprogress->m_scalar = scalar(this, e_scalar_progress);

      m_pimpact->m_pprogressreal = this;

   }


   void progress_control::close_progress()
   {

      ::user::document * pdocument = nullptr;

      {

         synchronous_lock synchronouslock(this->synchronization());

         pdocument = m_pdocument;

         m_pdocument = nullptr;

      }

      pdocument->close_document();

   }


   void progress_control::redraw()
   {

      if (m_pimpact == nullptr)
      {

         return;

      }

      m_pimpact->set_need_redraw();

      m_pimpact->post_redraw();


   }


   void progress_control::defer_show(::user::interaction * puiParent, const ::string & pszTitle, ::collection::count iStepCount)
   {

      m_strTitle = pszTitle;
      m_iStep = 0;
      m_iStepCount = iStepCount;


      m_strTitle = pszTitle;
      m_iStep = 0;

      ::pointer<progress_control>pprogressCopy = this;

      pprogressCopy->create_progress();

   //   application()->defer_branch("show_progress", [this, pprogressCopy, puiParent]()
   //   {

   //::pointer<progress_control>pprogress = pprogressCopy;


   ////try
   ////{

   ////   

   ////   release();

   ////}
   ////catch (...)
   ////{
   ////         
   ////   }

   //sleep(150_ms);

   //if (m_pdocument != nullptr)
   //{

   //   try
   //   {

   //   }
   //   catch (...)
   //   {


   //   }

   //   //::get_task()->m_bSimpleMessageLoop = false;

   //   //::get_task()->::thread::run();

   //}

   ////children_erase(::get_task());

   //close_progress();

   ////            release();

   //informationf("finished");

   //   });

   }


   progress_impact::progress_impact()
   {

   }


   progress_impact::~progress_impact()
   {

   }


   //void progress_impact::assert_ok() const
   //{

   //   ::user::impact::assert_ok();

   //}


   //void  progress_impact::dump(dump_context & dumpcontext) const
   //{

   //   ::user::impact::dump(dumpcontext);

   //}


   void  progress_impact::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &progress_impact::on_message_create);


   }


   void progress_impact::handle(::topic * ptopic, ::context * pcontext)
   {

   }


   void progress_impact::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pmessage->previous();

      __øconstruct(m_pprogress);

      m_pprogress->create_control(this, "progress_control");

      //if (!m_pprogress->create_control(this, "progress_control"))
      //{


      //   pcreate->m_lresult = -1;

      //   pcreate->m_bRet = true;

      //   return;

      //}

      SetTimer(e_timer_update_current_area, 300_ms);

   }


   void progress_impact::on_timer(::timer * ptimer)
   {

            if (ptimer->m_uEvent == e_timer_update_current_area)
            {
      
               KillTimer(ptimer->m_uEvent);
      
               ::int_rectangle rectangle;
      
               auto pwindowing = windowing();
      
               auto pdisplay = pwindowing->display();
      
               pdisplay->get_main_monitor(rectangle);
      
               rectangle.deflate(rectangle.width() / 6, rectangle.height() / 3, rectangle.width() / 6, rectangle.height() / 2);
      
               auto pframe = parent_frame();
      
               if (::is_set(pframe))
               {
      
                  pframe->m_sizeMinimum.cx() = 300;
                  pframe->m_sizeMinimum.cy() = 50;
      
                  pframe->good_restore(nullptr, rectangle, true);
      
                  pframe->set_need_redraw();
      
                  pframe->post_redraw();
      
               }
      
            }

   }


   void progress_impact::on_message_destroy(::message::message * pmessage)
   {

      pmessage->previous();

   }


   void progress_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_pprogress == nullptr)
      {

         return;

      }

      pgraphics->set_text_color(argb(255, 80, 80, 80));

      pgraphics->set_font(this);

      pgraphics->draw_text(m_pprogressreal->m_strStatus, m_rectangleStatus, e_align_center);

   }


   void progress_impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleX = this->rectangle();

      if (rectangleX.is_empty())
      {

         return;

      }

      int cxBorder = rectangleX.width() / 16;
      int h = rectangleX.height() / 4;

      ::int_rectangle rectangleIndicator(rectangleX);

      rectangleIndicator.deflate(cxBorder, h, cxBorder, h * 2);

      m_rectangleStatus = rectangleX;

      m_rectangleStatus.deflate(cxBorder, h * 2, cxBorder, h);

      m_pprogress->display_child(rectangleIndicator);

   }


} // namespace userex


