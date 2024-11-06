#include "framework.h"
#include "info_impact.h"
#include "document.h"
#include "thread.h"
#include "operation.h"
#include "acme/constant/message.h"
#include "acme/platform/timer.h"
#include "aura/graphics/draw2d/graphics.h"


namespace filemanager
{


   void DoBar(::draw2d::graphics_pointer & pgraphics,int ileft,int iTop,int cx,int cy,double dAnimation);


   void DoBar(::draw2d::graphics_pointer & pgraphics,int ileft,int iTop,int cx,int cy,double dAnimation)
   {
      int iDeltaDark = 23;
      int iDeltaVermelho = 77;
      int iDeltaAzul = 84;
      int iDeltaV1 = 23;
      int iDeltaV2 = 23;
      int iW = 49;
      int x = ileft;
      double dSoft = 184.6;
      int iRight = ileft + cx;
      int iMaxW = iRight - iW;
      ::color32_t color32;
      for(x = ileft; x < iMaxW; x+=iW)
      {
         color32 = rgb(
              255 - iDeltaVermelho - iDeltaDark,
              (unsigned char)(255 - (iDeltaV2 / 2.0) + (int)(sin((double)x / dSoft + dAnimation)  *(iDeltaV2 / 2.0))) - iDeltaV1 - iDeltaDark,
              255 - iDeltaAzul - 23 - iDeltaDark);
         pgraphics->fill_rectangle(::double_rectangle_dimension(x,iTop,iW,cy), color32);
      }
      if(x < iRight)
      {
         color32 = rgb(
              255 - iDeltaVermelho - iDeltaDark,
              (unsigned char)(255 - (iDeltaV2 / 2.0) + (int)(sin((double)x / dSoft + dAnimation)  *(iDeltaV2 / 2.0))) - iDeltaV1 - iDeltaDark,
              255 - iDeltaAzul - 23 - iDeltaDark);
         pgraphics->fill_rectangle(::double_rectangle_dimension(x,iTop,iRight - x,cy), color32);
      }
   }


   operation_info_impact::operation_info_impact()
   {

      m_dAnimation = 0.0;

   }


   void operation_info_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {



      /*::fill_rectangle(hdc, &rectangleProgress, g_hbrushProgress3);
      rectangleProgress.left()++;
      rectangleProgress.right()--;
      rectangleProgress.top()++;
      rectangleProgress.bottom()--;*/
      auto rectangleX = this->rectangle();
      int iLineCount = 23;
      double dBarHeight = (double)rectangleX.height() / (double)iLineCount;
      double dTop = 0.0;
      ::int_rectangle rectangleProgress;
      rectangleProgress = rectangleX;
      //rectangleProgress.left() += 23;
      //rectangleProgress.right() -= 23;
      rectangleProgress.top() += (int)dTop;
      rectangleProgress.bottom() = (int)(dTop + dBarHeight);
      double dProgressL = 0.0;
      double dProgressU;
      double dProgressD = 1.0 / (double)iLineCount;
      ::int_rectangle rectangleBar;
      double dProgress;
      dProgress = get_document()->m_poperationthread->get_progress_rate();
      for(int iLine = 0; iLine < iLineCount; iLine++)
      {

         rectangleBar = rectangleProgress;
         dProgressU = dProgressL + dProgressD;
         if(dProgress < dProgressU)
         {
            pgraphics->fill_rectangle(rectangleProgress,rgb(255,240,200));
         }
         if(dProgress > dProgressL)
         {
            if(dProgress < dProgressU)
            {
               rectangleBar.right() = ((int)((rectangleProgress.right() - rectangleProgress.left()) * (dProgress - dProgressL) * ((double)iLineCount))) + rectangleProgress.left();
            }
            DoBar(pgraphics,rectangleBar.left(),rectangleBar.top(),
                  rectangleBar.right() - rectangleBar.left(),rectangleBar.bottom() - rectangleBar.top(),m_dAnimation);
         }
         dTop += dBarHeight;
         rectangleProgress.top() = (int)dTop;
         rectangleProgress.bottom() = (int)(dTop + dBarHeight);
         dProgressL = dProgressU;
      }
      //::fill_rectangle(hdc, &rectangleProgress, g_hbrushProgress1);

   }

   void operation_info_impact::OnFileOperationStep(int iOperation,bool bFinal)
   {
      __UNREFERENCED_PARAMETER(iOperation);
      __UNREFERENCED_PARAMETER(bFinal);
   }

   ::pointer<operation_document>operation_info_impact::get_document()
   {
      return  (::user::impact::get_document());
   }

   void operation_info_impact::_001OnTimer(::timer * ptimer)
   {
      ::user::impact::_001OnTimer(ptimer);
      if(ptimer->m_uEvent == 123)
      {
      }
   }

   void operation_info_impact::on_message_create(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      //SetTimer(123, 184, nullptr);
   }

   void operation_info_impact::install_message_routing(::channel * pchannel)
   {
      ::user::impact::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_create,pchannel,this,&operation_info_impact::on_message_create);
//      //MESSAGE_LINK(e_message_timer,pchannel,this,&operation_info_impact::_001OnTimer);
   }

//   void operation_info_impact::assert_ok() const
//   {
//      ::user::impact::assert_ok();
//   }
//   void operation_info_impact::dump(dump_context & context) const
//   {
//      ::user::impact::dump(context);
//   }


} // namespace filemanager

























