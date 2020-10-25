#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif


namespace filemanager
{


   void DoBar(::draw2d::graphics_pointer & pgraphics,i32 ileft,i32 iTop,i32 cx,i32 cy,double dAnime);


   void DoBar(::draw2d::graphics_pointer & pgraphics,i32 ileft,i32 iTop,i32 cx,i32 cy,double dAnime)
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
      COLORREF cr;
      for(x = ileft; x < iMaxW; x+=iW)
      {
         cr = RGB(
              255 - iDeltaVermelho - iDeltaDark,
              (255 - (iDeltaV2 / 2.0) + (i32)(sin((double)x / dSoft + dAnime)  *(iDeltaV2 / 2.0))) - iDeltaV1 - iDeltaDark,
              255 - iDeltaAzul - 23 - iDeltaDark);
         pgraphics->fill_solid_rect_dim(x,iTop,iW,cy,cr);
      }
      if(x < iRight)
      {
         cr = RGB(
              255 - iDeltaVermelho - iDeltaDark,
              (255 - (iDeltaV2 / 2.0) + (i32)(sin((double)x / dSoft + dAnime)  *(iDeltaV2 / 2.0))) - iDeltaV1 - iDeltaDark,
              255 - iDeltaAzul - 23 - iDeltaDark);
         pgraphics->fill_solid_rect_dim(x,iTop,iRight - x,cy,cr);
      }
   }


   operation_info_view::operation_info_view()
   {

      m_dAnime = 0.0;

   }


   void operation_info_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {



      /*::fill_rect(hdc, &rectProgress, g_hbrushProgress3);
      rectProgress.left++;
      rectProgress.right--;
      rectProgress.top++;
      rectProgress.bottom--;*/
      ::rect rectClient;
      get_client_rect(rectClient);
      i32 iLineCount = 23;
      double dBarHeight = (double)rectClient.height() / (double)iLineCount;
      double dTop = 0.0;
      ::rect rectProgress;
      rectProgress = rectClient;
      //rectProgress.left += 23;
      //rectProgress.right -= 23;
      rectProgress.top += (LONG)dTop;
      rectProgress.bottom = (LONG)(dTop + dBarHeight);
      double dProgressL = 0.0;
      double dProgressU;
      double dProgressD = 1.0 / (double)iLineCount;
      ::rect rectBar;
      double dProgress;
      dProgress = get_document()->m_thread.get_progress_rate();
      for(i32 iLine = 0; iLine < iLineCount; iLine++)
      {

         rectBar = rectProgress;
         dProgressU = dProgressL + dProgressD;
         if(dProgress < dProgressU)
         {
            pgraphics->fill_rect(rectProgress,RGB(255,240,200));
         }
         if(dProgress > dProgressL)
         {
            if(dProgress < dProgressU)
            {
               rectBar.right = ((i32)((rectProgress.right - rectProgress.left) * (dProgress - dProgressL) * ((double)iLineCount))) + rectProgress.left;
            }
            DoBar(pgraphics,rectBar.left,rectBar.top,
                  rectBar.right - rectBar.left,rectBar.bottom - rectBar.top,m_dAnime);
         }
         dTop += dBarHeight;
         rectProgress.top = (LONG)dTop;
         rectProgress.bottom = (LONG)(dTop + dBarHeight);
         dProgressL = dProgressU;
      }
      //::fill_rect(hdc, &rectProgress, g_hbrushProgress1);

   }

   void operation_info_view::OnFileOperationStep(i32 iOperation,bool bFinal)
   {
      UNREFERENCED_PARAMETER(iOperation);
      UNREFERENCED_PARAMETER(bFinal);
   }

   __pointer(operation_document) operation_info_view::get_document()
   {
      return  (::user::impact::get_document());
   }

   void operation_info_view::_001OnTimer(::timer * ptimer)
   {
      ::user::impact::_001OnTimer(ptimer);
      if(ptimer->m_uEvent == 123)
      {
      }
   }

   void operation_info_view::_001OnCreate(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //SetTimer(123, 184, nullptr);
   }

   void operation_info_view::install_message_routing(::channel * pchannel)
   {
      ::user::impact::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_create,pchannel,this,&operation_info_view::_001OnCreate);
//      //MESSAGE_LINK(WM_TIMER,pchannel,this,&operation_info_view::_001OnTimer);
   }

   void operation_info_view::assert_valid() const
   {
      ::user::impact::assert_valid();
   }
   void operation_info_view::dump(dump_context & context) const
   {
      ::user::impact::dump(context);
   }


} // namespace filemanager

























