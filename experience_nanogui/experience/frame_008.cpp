#include "framework.h"
#include "frame_008.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/pen.h"
#include "base/user/experience/frame_window.h"
#include "base/user/experience/size_manager.h"
#include "base/user/experience/dock_manager.h"
#include "base/user/experience/move_manager.h"


#define GRIP_CORNER_LARGE_CX 16
#define GRIP_CORNER_SMALL_CX 5
#define GRIP_CORNER_LARGE_CY 16
#define GRIP_CORNER_SMALL_CY 5


#define GRIP_CENTER_LARGE_CX 36
#define GRIP_CENTER_SMALL_CX 7
#define GRIP_CENTER_LARGE_CY 36
#define GRIP_CENTER_SMALL_CY 7


namespace experience_nanogui
{


   frame_008::frame_008()
   {

      m_bHollow = false;

   }


   frame_008::~frame_008()
   {

   }


   //string frame_008::get_default_user_style() const
   //{

   //   return "LightGreen";

   //}


   ::experience::enum_frame frame_008::experience_frame_hit_test(const ::point_i32 & pointCursor)
   {
      ::experience::enum_frame etest = ::experience::e_frame_client;
      {
         //      m_pframewindow->screen_to_client()(point);
         ::rectangle_i32 rectangleEvent;
         m_pframewindow->get_window_rect(rectangleEvent);
         ::rectangle_i32 rectangle;
         ::point_i32 pointCenter = rectangleEvent.center();
         enum_grip egrip = m_pframewindow->size_manager()->GetGripMask();

         ::point_i32 pointHitTest = pointCursor;

         //if(rectangleEvent.left < 0)
         // pointHitTest.x -= rectangleEvent.left;
         //if(rectangleEvent.top < 0)
         // pointHitTest.y -= rectangleEvent.top;

         if((egrip & e_grip_top_left) == e_grip_top_left)
         {
            rectangle = rectangleEvent;
            rectangle.right = rectangle.left + 16;
            rectangle.bottom = rectangle.top + 5;
            if(rectangle.contains(pointHitTest))
            {
               etest = ::experience::e_frame_sizing_top_left;
               goto SizingSuccess;
            }
            rectangle = rectangleEvent;
            rectangle.right = rectangle.left + 5;
            rectangle.bottom = rectangle.top + 16;
            if(rectangle.contains(pointHitTest))
            {
               etest = ::experience::e_frame_sizing_top_left;
               goto SizingSuccess;
            }
         }
         if((egrip & e_grip_top_right) == e_grip_top_right)
         {
            rectangle = rectangleEvent;
            rectangle.left = rectangle.right - 16;
            rectangle.bottom = rectangle.top + 5;
            if(rectangle.contains(pointHitTest))
            {
               etest = ::experience::e_frame_sizing_top_right;
               goto SizingSuccess;
            }
            rectangle = rectangleEvent;
            rectangle.left = rectangle.right - 5;
            rectangle.bottom = rectangle.top + 16;
            if(rectangle.contains(pointHitTest))
            {
               etest = ::experience::e_frame_sizing_top_right;
               goto SizingSuccess;
            }
         }
         if((egrip & e_grip_bottom_right) == e_grip_bottom_right)
         {
            rectangle = rectangleEvent;
            rectangle.left = rectangle.right - 16;
            rectangle.top = rectangle.bottom - 5;
            if(rectangle.contains(pointHitTest))
            {
               etest = ::experience::e_frame_sizing_bottom_right;
               goto SizingSuccess;
            }
            rectangle = rectangleEvent;
            rectangle.left = rectangle.right - 5;
            rectangle.top = rectangle.bottom - 16;
            if(rectangle.contains(pointHitTest))
            {
               etest = ::experience::e_frame_sizing_bottom_right;
               goto SizingSuccess;
            }
         }
         if((egrip & e_grip_bottom_left) == e_grip_bottom_left)
         {
            rectangle = rectangleEvent;
            rectangle.right = rectangle.left + 16;
            rectangle.top = rectangle.bottom - 5;
            if(rectangle.contains(pointHitTest))
            {
               etest = ::experience::e_frame_sizing_bottom_left;
               goto SizingSuccess;
            }
            rectangle = rectangleEvent;
            rectangle.right = rectangle.left + 5;
            rectangle.top = rectangle.bottom - 16;
            if(rectangle.contains(pointHitTest))
            {
               etest = ::experience::e_frame_sizing_bottom_left;
               goto SizingSuccess;
            }
         }
         if((egrip & e_grip_top) == e_grip_top)
         {
            rectangle.top = rectangleEvent.top;
            rectangle.left = pointCenter.x - 8;
            rectangle.right = pointCenter.x + 8;
            rectangle.bottom = rectangleEvent.top + 5;
            if(rectangle.contains(pointHitTest))
            {
               etest = ::experience::e_frame_sizing_top;
               goto SizingSuccess;
            }
         }
         if((egrip & e_grip_bottom) == e_grip_bottom)
         {
            rectangle.top = rectangleEvent.bottom - 5;
            rectangle.left = pointCenter.x - 8;
            rectangle.right = pointCenter.x + 8;
            rectangle.bottom = rectangleEvent.bottom;
            if(rectangle.contains(pointHitTest))
            {
               etest = ::experience::e_frame_sizing_bottom;
               goto SizingSuccess;
            }
         }
         if((egrip & e_grip_left) == e_grip_left)
         {
            rectangle.top = pointCenter.y - 8;
            rectangle.left = rectangleEvent.left;
            rectangle.right = rectangleEvent.left + 5;
            rectangle.bottom = pointCenter.y + 8;
            if(rectangle.contains(pointHitTest))
            {
               etest = ::experience::e_frame_sizing_left;
               goto SizingSuccess;
            }
         }
         if((egrip & e_grip_right) == e_grip_right)
         {
            rectangle.top = pointCenter.y - 8;
            rectangle.left = rectangleEvent.right - 5;
            rectangle.right = rectangleEvent.right;
            rectangle.bottom = pointCenter.y + 8;
            if(rectangle.contains(pointHitTest))
            {
               etest = ::experience::e_frame_sizing_right;
               goto SizingSuccess;
            }
         }
         goto SizingNone;
SizingSuccess:
         return etest;
SizingNone:;
      }
      return ::experience::e_frame_client;
   }






   void frame_008::draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient, enum_border eside)
   {

      auto pframewindow = m_pframewindow;

      if (pframewindow == nullptr)
      {

         return;

      }

      //auto psession = get_session();

      status < ::color::color > crMoveableBorder;
      status < ::color::color > crMoveableBorderHilight;
      status < ::color::color > crMoveableBorderShadow;

      if(pframewindow->is_active_window())
      {
         crMoveableBorder = m_colorMoveableBorder;
         crMoveableBorderHilight = m_colorMoveableBorderHilight;
         crMoveableBorderShadow = m_colorMoveableBorderShadow;
      }
      else
      {

         auto pstyle = pframewindow->get_style(pgraphics);

         crMoveableBorder = pframewindow->get_color(pstyle, ::e_element_button_background);

         crMoveableBorderHilight = pframewindow->get_color(pstyle, ::e_element_button_hilite);

         crMoveableBorderShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

      }

      enum_dock edock = m_pframewindow->dock_manager()->get_dock_mask();
      ::rectangle_i32 rectangleA(rectangleClient);

      if(m_bHollow)
      {

         ::rectangle_i32 rectangle;
         GetBorderRect(rectangleA, rectangle, eside);

         pgraphics->fill_rectangle(rectangle, opaque(crMoveableBorder));//m_colorMoveableBorderDkShadow);

         // rgb(255, 170, 136) RedOrange
      }
      else if(m_pframewindow->m_estyle == ::user::StyleLightBlue || m_pframewindow->m_estyle == ::user::StyleRedOrange)
      {
         rectangleA.deflate(1,1,1,1);
         Draw3dRectSide(pgraphics,rectangleA,eside,crMoveableBorder,0);//m_colorMoveableBorderDkShadow);

         if(!m_bHollow)
         {

            rectangleA.deflate(1,1,1,1);
                     
            Draw3dRectSide(pgraphics,rectangleA,eside,crMoveableBorderHilight,crMoveableBorderShadow);

            rectangleA.deflate(1,1,1,1);
                     
            Draw3dRectSide(pgraphics,rectangleA,eside,crMoveableBorder,crMoveableBorder);

            rectangleA.deflate(1,1,1,1);
                     
            Draw3dRectSide(pgraphics,rectangleA,eside,crMoveableBorder,crMoveableBorder);

            ::rectangle_i32 rectangle;
                     
            GetBorderRect(rectangleClient,rectangle,eside);
                     
            pgraphics->fill_rectangle(rectangle, ::color::color(crMoveableBorder,127));

         }

      }
      else if(m_pframewindow->m_estyle == ::user::StyleTranslucidWarmGray
               || m_pframewindow->m_estyle == ::user::StyleTranslucidLightBlue
               || m_pframewindow->m_estyle == ::user::StyleTranslucidLightGreen)
      {
                  
         ::rectangle_i32 rectangle;
                  
         GetBorderRect(rectangleClient, rectangle, eside);
                  
         pgraphics->fill_rectangle(rectangle, ::color::color(crMoveableBorder, 127));
                  
      }
      else
      {
                  
         ::rectangle_i32 rectangle;
                  
         GetBorderRect(rectangleClient, rectangle, eside);
                  
         pgraphics->fill_rectangle(rectangle, ::color::color(crMoveableBorder,127));

         ::rectangle_i32 rectangleClientB = rectangleA;

         rectangleClientB.bottom--;
         rectangleClientB.right--;

         rectangleA.top++;
         rectangleA.bottom--;
         rectangleA.left++;
         rectangleA.right--;
         if(edock == e_dock_none)
         {
            Draw3dRectSide(pgraphics, rectangleA, eside, m_colorDkShadow, m_colorDkShadow);
         }

         rectangleA.top++;
         rectangleA.bottom--;
         rectangleA.left++;
         rectangleA.right--;
         Draw3dRectSide(pgraphics, rectangleA, eside, m_colorDkShadow, m_colorDkShadow);

         rectangleA.top++;
         rectangleA.bottom--;
         rectangleA.left++;
         rectangleA.right--;
         if(edock == e_dock_none)
         {
            Draw3dRectSide(pgraphics, rectangleA, eside, m_colorDkShadow, m_colorDkShadow);
         }
      }

   }

   void frame_008::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
   {

      auto pframewindow = m_pframewindow;

      if (pframewindow == nullptr)
      {

         return;

      }

      if (!pframewindow->is_frame_experience_enabled())
      {

         return;

      }

      bool bZoomed = pframewindow->layout().is_zoomed() != 0;

      string str;

      ::rectangle_i32 rectangleNClient;

      pframewindow->get_window_rect(rectangleNClient);

      rectangleNClient -= rectangleNClient.top_left();

      ////////////////////
      //
      // Routine:
      // draw frame border
      //
      ////////////////////


      if(!pframewindow->layout().is_full_screen())
      {

         DrawBorder(pgraphics, rectangleNClient);

      }



      ///////////////////////
      //
      // Routine:
      // draw resize grip set
      //
      ///////////////////////

      if(!bZoomed && !pframewindow->layout().is_full_screen())
      {
         DrawGripSet(pgraphics, rectangleNClient);
      }

      //            pgraphics->SetBkMode(iOriginalBkMode);
      //          pgraphics->set_text_color(crOriginalTextColor);

   }


   void frame_008::DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient)
   {

      // glxxx
      //return;

      auto pmovemanager = m_pframewindow->move_manager();

      enum_border eborder = pmovemanager->GetBorderMask();

      if(m_pframewindow->layout().is_zoomed())
      {
         eborder = (enum_border)
                     (eborder &
                     ~(e_border_right
                        | e_border_bottom
                        | e_border_left));
      }



      if(m_bHollow && eborder == e_border_all)
      {



         ::rectangle_i32 rectangleA(rectangleClient);

         rectangleA.bottom--;
         rectangleA.right--;

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->set(m_ppenHollow0);

         pgraphics->draw_rectangle(rectangleA);

         //Draw3dRectSide(pgraphics,rectangleA,eside,argb(8,50,100,200),argb(8,50,100,200));
         rectangleA.deflate(1,1,1,1);

         pgraphics->set(m_ppenHollow1);

         pgraphics->draw_rectangle(rectangleA);

         //Draw3dRectSide(pgraphics,rectangleA,eside,argb(11,50,100,200),argb(11,50,100,200));
         rectangleA.deflate(1,1,1,1);

         pgraphics->set(m_ppenHollow2);

         pgraphics->draw_rectangle(rectangleA);

         //Draw3dRectSide(pgraphics,rectangleA,eside,argb(23,50,100,200),argb(23,50,100,200));
         rectangleA.deflate(1,1,1,1);

         pgraphics->set(m_ppenHollow3);

         pgraphics->draw_rectangle(rectangleA);

         //Draw3dRectSide(pgraphics,rectangleA,eside,argb(49,50,100,200),argb(49,50,100,200));
         rectangleA.deflate(1,1,1,1);

         pgraphics->set(m_ppenHollow4);

         pgraphics->draw_rectangle(rectangleA);

         //Draw3dRectSide(pgraphics,rectangleA,eside,argb(49 +23,50,100,200),argb(49+23,50,100,200));
         rectangleA.deflate(1,1,1,1);

         pgraphics->set(m_ppenHollow5);

         pgraphics->draw_rectangle(rectangleA);

         //Draw3dRectSide(pgraphics,rectangleA,eside,m_colorMoveableBorderDkShadow,m_colorMoveableBorderDkShadow);

      }
      else
      {

         if(eborder & e_border_top)
         {
            draw_border_side(pgraphics,rectangleClient,e_border_top);
         }
         if(eborder & e_border_right)
         {
            draw_border_side(pgraphics,rectangleClient,e_border_right);
         }
         if(eborder & e_border_bottom)
         {
            draw_border_side(pgraphics,rectangleClient,e_border_bottom);
         }
         if(eborder & e_border_left)
         {
            draw_border_side(pgraphics,rectangleClient,e_border_left);
         }

      }

   }


   void frame_008::GetBorderRect(const ::rectangle_i32 & rectangleClient, RECTANGLE_I32 * lprect, enum_border eside)
   {
      ::rectangle_i32 rectangleBig(rectangleClient);

      rectangleBig.deflate(m_rectangleMarginDock);
      ::rectangle_i32 rectangleSmall(rectangleBig);
      rectangleSmall.deflate(1);

      ::rectangle_i32 rectangle;
      if(eside == e_border_top)
      {
         rectangle.left = rectangleBig.left;
         rectangle.right = rectangleBig.right;
         rectangle.top = rectangleBig.top;
         rectangle.bottom = rectangleSmall.top;
      }
      else if(eside == e_border_left)
      {
         rectangle.left = rectangleBig.left;
         rectangle.right = rectangleSmall.left;
         rectangle.top = rectangleSmall.top;
         rectangle.bottom = rectangleSmall.bottom;
         rectangle.bottom++;
      }
      else if(eside == e_border_right)
      {
         rectangle.left = rectangleSmall.right;
         rectangle.right = rectangleBig.right;
         rectangle.top = rectangleSmall.top;
         rectangle.bottom = rectangleSmall.bottom;
         rectangle.bottom++;
      }
      else if(eside == e_border_bottom)
      {
         rectangle.left = rectangleBig.left;
         rectangle.right = rectangleBig.right;
         rectangle.top = rectangleSmall.bottom;
         rectangle.bottom = rectangleBig.bottom;
      }
      *lprect = rectangle;
   }


   void frame_008::_on_style_change(::draw2d::graphics_pointer & pgraphics)
   {

      on_style_change_001_and_002(pgraphics);

      ::color::color color = m_colorMoveableBorderDkShadow;

      m_ppenHollow0.defer_create(this);
      m_ppenHollow1.defer_create(this);
      m_ppenHollow2.defer_create(this);
      m_ppenHollow3.defer_create(this);
      m_ppenHollow4.defer_create(this);
      m_ppenHollow5.defer_create(this);

      color.alpha = 8;

      m_ppenHollow0->create_solid(1.0,color);

      color.alpha = 11;

      m_ppenHollow1->create_solid(1.0,color);

      color.alpha = 23;

      m_ppenHollow2->create_solid(1.0,color);

      color.alpha = 49;

      m_ppenHollow3->create_solid(1.0,color);

      color.alpha = 72;

      m_ppenHollow4->create_solid(1.0, color);

      color.alpha = 255;

      m_ppenHollow5->create_solid(1.0,color);


   }

#define BEVEL_SMALL 2
#define BEVEL_LARGE 5
#define GRIP_SMALL 8
#define GRIP_LARGE 30


   void frame_008::DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClientParam, enum_grip egrip)
   {

      // glxxx
      //return;


      const i32 size = 16;

      auto rectangleClient(rectangleClientParam);
      //            ::rectangle_i32 rectangleClientB(rectangleClient);
      ::rectangle_i32 rectangleA;
      ::point_i32 pointA;
      ::point_i32 pointB;
      ::point_i32 pointC;
      //            ::rectangle_i32 rectangle(rectangleClient);
      switch(egrip)
      {
      case e_grip_top_left:
      {

         rectangleA = rectangleClient;

         rectangleA.right = 4;
         rectangleA.bottom = size;

         pgraphics->fill_rectangle(rectangleA, argb(255, 0x60, 0x65, 0x55));

         rectangleA.right = size;
         rectangleA.bottom = 4;

         pgraphics->fill_rectangle(rectangleA, argb(255, 0x60, 0x65, 0x55));

      }
      break;
      case e_grip_top_right:
      {
         rectangleA = rectangleClient;

         rectangleA.left = rectangleA.right - 4;
         rectangleA.bottom = size;

         pgraphics->fill_rectangle(rectangleA, argb(255, 0x60, 0x65, 0x55));

         rectangleA.left = rectangleA.right - size;
         rectangleA.bottom = 4;

         pgraphics->fill_rectangle(rectangleA, argb(255, 0x60, 0x65, 0x55));
      }
      break;
      case e_grip_bottom_left:
      {
         rectangleA = rectangleClient;

         rectangleA.right = 4;
         rectangleA.top = rectangleA.bottom - size;

         pgraphics->fill_rectangle(rectangleA, argb(255, 0x60, 0x65, 0x55));

         rectangleA.right = size;
         rectangleA.top = rectangleA.bottom - 4;

         pgraphics->fill_rectangle(rectangleA, argb(255, 0x60, 0x65, 0x55));
      }
      break;
      case e_grip_bottom_right:
      {
         rectangleA = rectangleClient;

         rectangleA.left = rectangleA.right - 4;
         rectangleA.top = rectangleA.bottom - size;

         pgraphics->fill_rectangle(rectangleA, argb(255, 0x60, 0x65, 0x55));

         rectangleA.left = rectangleA.right - size;
         rectangleA.top = rectangleA.bottom - 4;

         pgraphics->fill_rectangle(rectangleA, argb(255, 0x60, 0x65, 0x55));
      }
      break;
      case e_grip_top:
      {
         rectangleA = rectangleClient;

         rectangleA.left = rectangleA.left + rectangleA.width() / 2 - size / 2;
         rectangleA.right = rectangleA.left + size;
         rectangleA.bottom = 4;

         pgraphics->fill_rectangle(rectangleA, argb(255, 0x60, 0x65, 0x55));

      }
      break;
      case e_grip_bottom:
      {
         rectangleA = rectangleClient;

         rectangleA.left = rectangleA.left + rectangleA.width() / 2 - size / 2;
         rectangleA.right = rectangleA.left + size;
         rectangleA.top = rectangleA.bottom - 4;

         pgraphics->fill_rectangle(rectangleA, argb(255, 0x60, 0x65, 0x55));
      }
      break;
      case e_grip_left:
      {
         rectangleA = rectangleClient;

         rectangleA.right = 4;
         rectangleA.top = rectangleA.top + rectangleA.height() / 2 - size / 2;
         rectangleA.bottom = rectangleA.top + size;

         pgraphics->fill_rectangle(rectangleA, argb(255, 0x60, 0x65, 0x55));
      }
      break;
      case e_grip_right:
      {
         rectangleA = rectangleClient;

         rectangleA.left = rectangleA.right - 4;
         rectangleA.top = rectangleA.top + rectangleA.height() / 2 - size / 2;
         rectangleA.bottom = rectangleA.top + size;

         pgraphics->fill_rectangle(rectangleA, argb(255, 0x60, 0x65, 0x55));
      }
      break;
      default:
         break;
      }


   }


   void frame_008::DrawRectGrip(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectangleParam)
   {

      //auto psession = get_session();

      ::rectangle_i32 rectangle(rectangleParam);

      auto pframewindow = m_pframewindow;

      auto pstyle = pframewindow->get_style(pgraphics);

      auto crButtonHilite = pframewindow->get_color(pstyle, ::e_element_button_hilite);

      auto crButtonDarkShadow = pframewindow->get_color(pstyle, ::e_element_button_dark_shadow);

      auto crButtonFace = pframewindow->get_color(pstyle, ::e_element_button_background);

      auto crButtonShadow = pframewindow->get_color(pstyle, ::e_element_button_shadow);

      pgraphics->draw_inset_3d_rectangle(rectangle, crButtonFace, crButtonDarkShadow);

      rectangle.top++;
      rectangle.bottom--;
      rectangle.left++;
      rectangle.right--;

      pgraphics->draw_inset_3d_rectangle(rectangle, crButtonHilite, crButtonShadow);

      rectangle.top++;
      rectangle.bottom--;
      rectangle.left++;
      rectangle.right--;

      pgraphics->fill_rectangle(rectangle, crButtonFace);

   }


   void frame_008::DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient)
   {

      auto psizenager = m_pframewindow->size_manager();

      enum_grip egrip = psizenager->GetGripMask();

      if(egrip & e_grip_top)
      {
         DrawGrip(pgraphics, rectangleClient, e_grip_top);
      }
      if((egrip & e_grip_top_right) == e_grip_top_right)
      {
         DrawGrip(pgraphics, rectangleClient, e_grip_top_right);
      }
      if(egrip & e_grip_right)
      {
         DrawGrip(pgraphics, rectangleClient, e_grip_right);
      }
      if((egrip & e_grip_bottom_right) == e_grip_bottom_right)
      {
         DrawGrip(pgraphics, rectangleClient, e_grip_bottom_right);
      }
      if(egrip & e_grip_bottom)
      {
         DrawGrip(pgraphics, rectangleClient, e_grip_bottom);
      }
      if((egrip & e_grip_bottom_left) == e_grip_bottom_left)
      {
         DrawGrip(pgraphics, rectangleClient, e_grip_bottom_left);
      }
      if(egrip & e_grip_left)
      {
         DrawGrip(pgraphics, rectangleClient, e_grip_left);
      }
      if((egrip & e_grip_top_left) == e_grip_top_left)
      {
         DrawGrip(pgraphics, rectangleClient, e_grip_top_left);
      }

   }


} // namespace experience_nanogui



