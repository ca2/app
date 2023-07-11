#include "framework.h"
#include "operation_info_impact.h"
#include "operation_document.h"
#include "operation_thread.h"
#include "operation.h"
#include "acme/constant/message.h"
#include "acme/platform/timer.h"
#include "aura/graphics/draw2d/graphics.h"


namespace filemanager
{


   void DoBar(::draw2d::graphics_pointer & pgraphics,i32 ileft,i32 iTop,i32 cx,i32 cy,double dAnimation);


   void DoBar(::draw2d::graphics_pointer & pgraphics,i32 ileft,i32 iTop,i32 cx,i32 cy,double dAnimation)
   {
      i32 iDeltaDark = 23;
      i32 iDeltaVermelho = 77;
      i32 iDeltaAzul = 84;
      i32 iDeltaV1 = 23;
      i32 iDeltaV2 = 23;
      i32 iW = 49;
      i32 x = ileft;
      double dSoft = 184.6;
      i32 iRight = ileft + cx;
      i32 iMaxW = iRight - iW;
      ::color32_t color32;
      for(x = ileft; x < iMaxW; x+=iW)
      {
         color32 = rgb(
              255 - iDeltaVermelho - iDeltaDark,
              (::u8)(255 - (iDeltaV2 / 2.0) + (i32)(sin((double)x / dSoft + dAnimation)  *(iDeltaV2 / 2.0))) - iDeltaV1 - iDeltaDark,
              255 - iDeltaAzul - 23 - iDeltaDark);
         pgraphics->fill_rectangle(::rectangle_f64_dimension(x,iTop,iW,cy), color32);
      }
      if(x < iRight)
      {
         color32 = rgb(
              255 - iDeltaVermelho - iDeltaDark,
              (::u8)(255 - (iDeltaV2 / 2.0) + (i32)(sin((double)x / dSoft + dAnimation)  *(iDeltaV2 / 2.0))) - iDeltaV1 - iDeltaDark,
              255 - iDeltaAzul - 23 - iDeltaDark);
         pgraphics->fill_rectangle(::rectangle_f64_dimension(x,iTop,iRight - x,cy), color32);
      }
   }


   operation_info_impact::operation_info_impact()
   {

      m_dAnimation = 0.0;

   }


   void operation_info_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {



      /*::fill_rectangle(hdc, &rectangleProgress, g_hbrushProgress3);
      rectangleProgress.left++;
      rectangleProgress.right--;
      rectangleProgress.top++;
      rectangleProgress.bottom--;*/
      auto rectangleClient = client_rectangle();
      i32 iLineCount = 23;
      double dBarHeight = (double)rectangleClient.height() / (double)iLineCount;
      double dTop = 0.0;
      ::rectangle_i32 rectangleProgress;
      rectangleProgress = rectangleClient;
      //rectangleProgress.left += 23;
      //rectangleProgress.right -= 23;
      rectangleProgress.top += (::i32)dTop;
      rectangleProgress.bottom = (::i32)(dTop + dBarHeight);
      double dProgressL = 0.0;
      double dProgressU;
      double dProgressD = 1.0 / (double)iLineCount;
      ::rectangle_i32 rectangleBar;
      double dProgress;
      dProgress = get_document()->m_poperationthread->get_progress_rate();
      for(i32 iLine = 0; iLine < iLineCount; iLine++)
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
               rectangleBar.right = ((i32)((rectangleProgress.right - rectangleProgress.left) * (dProgress - dProgressL) * ((double)iLineCount))) + rectangleProgress.left;
            }
            DoBar(pgraphics,rectangleBar.left,rectangleBar.top,
                  rectangleBar.right - rectangleBar.left,rectangleBar.bottom - rectangleBar.top,m_dAnimation);
         }
         dTop += dBarHeight;
         rectangleProgress.top = (::i32)dTop;
         rectangleProgress.bottom = (::i32)(dTop + dBarHeight);
         dProgressL = dProgressU;
      }
      //::fill_rectangle(hdc, &rectangleProgress, g_hbrushProgress1);

   }

   void operation_info_impact::OnFileOperationStep(i32 iOperation,bool bFinal)
   {
      UNREFERENCED_PARAMETER(iOperation);
      UNREFERENCED_PARAMETER(bFinal);
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
      UNREFERENCED_PARAMETER(pmessage);
      //SetTimer(123, 184, nullptr);
   }

   void operation_info_impact::install_message_routing(::channel * pchannel)
   {
      ::user::impact::install_message_routing(pchannel);
      MESSAGE_LINK(MESSAGE_CREATE,pchannel,this,&operation_info_impact::on_message_create);
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

























