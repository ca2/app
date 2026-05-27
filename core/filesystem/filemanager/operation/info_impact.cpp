#include "framework.h"
#include "info_impact.h"
#include "document.h"
#include "thread.h"
#include "operation.h"
#include "acme/constant/user_message.h"
#include "acme/platform/timer.h"
#include "aura/graphics/draw2d/graphics.h"


namespace filemanager
{


   void DoBar(::draw2d::graphics_pointer & pgraphics,::i32 ileft,::i32 iTop,::i32 cx,::i32 cy,::f64 dAnimation);


   void DoBar(::draw2d::graphics_pointer & pgraphics,::i32 ileft,::i32 iTop,::i32 cx,::i32 cy,::f64 dAnimation)
   {
      ::i32 iDeltaDark = 23;
      ::i32 iDeltaVermelho = 77;
      ::i32 iDeltaAzul = 84;
      ::i32 iDeltaV1 = 23;
      ::i32 iDeltaV2 = 23;
      ::i32 iW = 49;
      ::i32 x = ileft;
      ::f64 dSoft = 184.6;
      ::i32 iRight = ileft + cx;
      ::i32 iMaxW = iRight - iW;
      ::color32_t color32;
      for(x = ileft; x < iMaxW; x+=iW)
      {
         color32 = rgb(
              255 - iDeltaVermelho - iDeltaDark,
              (::u8)(255 - (iDeltaV2 / 2.0) + (::i32)(sin((::f64)x / dSoft + dAnimation)  *(iDeltaV2 / 2.0))) - iDeltaV1 - iDeltaDark,
              255 - iDeltaAzul - 23 - iDeltaDark);
         pgraphics->fill_rectangle(::f64_rectangle_dimension(x,iTop,iW,cy), color32);
      }
      if(x < iRight)
      {
         color32 = rgb(
              255 - iDeltaVermelho - iDeltaDark,
              (::u8)(255 - (iDeltaV2 / 2.0) + (::i32)(sin((::f64)x / dSoft + dAnimation)  *(iDeltaV2 / 2.0))) - iDeltaV1 - iDeltaDark,
              255 - iDeltaAzul - 23 - iDeltaDark);
         pgraphics->fill_rectangle(::f64_rectangle_dimension(x,iTop,iRight - x,cy), color32);
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
      auto rectangleX = this->rectangle();
      ::i32 iLineCount = 23;
      ::f64 dBarHeight = (::f64)rectangleX.height() / (::f64)iLineCount;
      ::f64 dTop = 0.0;
      ::i32_rectangle rectangleProgress;
      rectangleProgress = rectangleX;
      //rectangleProgress.left += 23;
      //rectangleProgress.right -= 23;
      rectangleProgress.top += (::i32)dTop;
      rectangleProgress.bottom = (::i32)(dTop + dBarHeight);
      ::f64 dProgressL = 0.0;
      ::f64 dProgressU;
      ::f64 dProgressD = 1.0 / (::f64)iLineCount;
      ::i32_rectangle rectangleBar;
      ::f64 dProgress;
      dProgress = get_document()->m_poperationthread->get_progress_rate();
      for(::i32 iLine = 0; iLine < iLineCount; iLine++)
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
               rectangleBar.right = ((::i32)((rectangleProgress.right - rectangleProgress.left) * (dProgress - dProgressL) * ((::f64)iLineCount))) + rectangleProgress.left;
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

   void operation_info_impact::OnFileOperationStep(::i32 iOperation,bool bFinal)
   {
      __UNREFERENCED_PARAMETER(iOperation);
      __UNREFERENCED_PARAMETER(bFinal);
   }

   ::pointer<operation_document>operation_info_impact::get_document()
   {
      return  (::user::impact::get_document());
   }

   void operation_info_impact::on_timer(::timer * ptimer)
   {
      ::user::impact::on_timer(ptimer);
      if(ptimer->m_uTimer == 123)
      {
      }
   }

   void operation_info_impact::on_message_create(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      //set_timer(123, 184, nullptr);
   }

   void operation_info_impact::install_message_routing(::channel * pchannel)
   {
      ::user::impact::install_message_routing(pchannel);
      USER_MESSAGE_LINK(::user::e_message_create,pchannel,this,&operation_info_impact::on_message_create);
//      //USER_MESSAGE_LINK(::user::e_message_timer,pchannel,this,&operation_info_impact::on_timer);
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

























