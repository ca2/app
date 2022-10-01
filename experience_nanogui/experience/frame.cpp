#include "framework.h"
#include "frame.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/icon.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/imaging.h"
#include "aura/platform/system.h"
#include "base/user/experience/control_box.h"
#include "base/user/experience/frame_window.h"


namespace experience_nanogui
{

   frame::frame()
   {

      m_pointWindowIcon.x = 5;

      m_sizeIcon.cx = 32;

      m_sizeIcon.cy = 32;

      m_colorCaptionText = argb(255, 0, 0, 0);

      m_rectangleClient.set(0, 0, 0, 0);

   }


   frame::~frame()
   {

   }


   void frame::on_initialize_experience_frame()
   {

      __construct(m_ppenText1);
         __construct(m_ppenFace1);
         __construct(m_ppenHilight1);
         __construct(m_ppenShadow1);
         __construct(m_ppenDkShadow1);


/*               auto estyle = translate_style(m_strStyle);

      set_style(estyle)*/;

   }


   string frame::get_default_user_style() const
   {

      return "TranslucidWarmLiteGray";

   }


   void frame::OnMove(__pointer(::user::interaction) pframewindow)
   {

      __UNREFERENCED_PARAMETER(pframewindow);

   }


   void frame::Glass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleParam)
   {

      auto pframewindow = m_pframewindow;

      auto psystem = m_psystem->m_paurasystem;

      auto imaging = psystem->imaging();

      ::rectangle_i32 rectangleClient(rectangleParam);

      ::rectangle_i32 rectangleInflate;

      if(rectangleClient.is_empty())
      {

         return;

      }


      i32 iInflate = 5; // raio 2 pixels + centro 1 pixel

      rectangleInflate = rectangleClient;

      rectangleInflate.inflate(iInflate, iInflate);

      ::rectangle_i32 rectangleScreen;

      pframewindow->best_monitor(rectangleScreen);

      ::image_pointer pimage1;

      ::image_pointer pimage2;

      pimage1 = m_pcontext->m_pauracontext->create_image({rectangleClient.width() + iInflate * 2,  rectangleClient.height() + iInflate * 2});

      pimage2 = m_pcontext->m_pauracontext->create_image({rectangleClient.width() + iInflate * 2,  rectangleClient.height() + iInflate * 2});

      ::rectangle_i32 rectangleWindow = rectangleClient;

      pframewindow->client_to_screen()(rectangleWindow);

      ::point_i32 pointInflate(iInflate, iInflate);

      auto point = rectangleClient.top_left();

      point -= pointInflate;

      //bool b;

      {

         rectangle_f64 rectangleSource(point, pimage1->get_size());

         image_source imagesource(pgraphics, rectangleSource);

         rectangle_f64 rectangleTarget(pimage1->get_size());

         image_drawing_options imagedrawingoptions(rectangleTarget);

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         //b = 
            
         pimage2->g()->draw(imagedrawing);

      }

      //b = 
         
      imaging.blur(pimage2, 2);

      {

         rectangle_f64 rectangleSource(pointInflate, rectangleClient.size());

         image_source imagesource(pimage2, rectangleSource);

         rectangle_f64 rectangleTarget(rectangleClient);

         image_drawing_options imagedrawingoptions(rectangleTarget);

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);

      }

   }


   status < ::color::color > frame::get_border_main_body_color()
   {

      return rgb(63, 150, 106);

   }


   void frame::ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, const ::color::color & color32, byte bAlpha)
   {

      pgraphics->fill_rectangle(rectangle, ::color::color(color32, bAlpha));

   }


   //void frame::set_user_style(::user::enum_style estyle)
   //{

   //   m_pframewindow->m_estyle = estyle;

   //   if (get_control_box().is_null())
   //   {

   //      return;

   //   }

   //   on_style_change();

   //}


   //frame::e_style frame::translate_style(const ::string & pszStyle)
   //{

   //   string strStyle(pszStyle);

   //   if(strStyle == "TranslucidLightBlue")
   //   {

   //      return StyleTranslucidLightBlue;

   //   }
   //   else if (strStyle == "TranslucidLightGreen")
   //   {

   //      return StyleTranslucidLightGreen;

   //   }
   //   else if (strStyle == "TranslucidWarmGray")
   //   {

   //      return StyleTranslucidWarmGray;

   //   }
   //   else if (strStyle == "TranslucidWarmLiteGray")
   //   {

   //      return StyleTranslucidWarmLiteGray;

   //   }
   //   else if(strStyle == "DarkWarmBlue")
   //   {

   //      return StyleDarkWarmBlue;

   //   }
   //   else if(strStyle == "WarmGray")
   //   {

   //      return StyleTranslucidWarmGray;

   //   }
   //   else if(strStyle == "BlueRedPurple")
   //   {

   //      return StyleBlueRedPurple;

   //   }
   //   else if(strStyle == "RedOrange")
   //   {

   //      return StyleRedOrange;

   //   }
   //   else if(strStyle == "LightBlue")
   //   {

   //      return StyleLightBlue;

   //   }
   //   else if (strStyle == "BlackBorder")
   //   {

   //      return StyleBlackBorder;

   //   }
   //   else if (strStyle == "LightGreen")
   //   {

   //      return StyleLightGreen;

   //   }
   //   else if (strStyle == "EveningSun")
   //   {

   //      return StyleEveningSun;

   //   }
   //   else if (strStyle == "BlackPiano")
   //   {

   //      return StyleBlackPiano;

   //   }
   //   else
   //   {

   //      return StyleLightBlue;

   //   }

   //}


   //frame::enum_element operator++(frame::enum_element & eelement, i32 i)
   //{
   //   __UNREFERENCED_PARAMETER(i);
   //   return (frame::enum_element) (*((i32*)&eelement))++;
   //}

   bool frame::get_element_rect(RECTANGLE_I32 * lprect, enum_element eelement)
   {
      switch(eelement)
      {
      case e_element_top_left_icon:
      {

         auto pdrawicon = m_pframewindow->get_draw_icon();

         if (m_pframewindow == nullptr || pdrawicon == nullptr)
         {

            return false;

         }

         lprect->left = m_pointWindowIcon.x;
         lprect->top = m_pointWindowIcon.y;
         lprect->right = lprect->left + m_sizeIcon.cx;
         lprect->bottom = lprect->top + m_sizeIcon.cy;

         //lprect->right = lprect->left + pdrawicon->get_size().cx;
         //lprect->bottom = lprect->top + pdrawicon->get_size().cy;

         return true;

      }

      case e_element_move_grip_minimal:

         if (m_pframewindow == nullptr || m_pframewindow->const_layout().design().display() != ::e_display_minimal)
         {
                   
            return false;

         }

         //lprect->left = m_pointMoveGripMinimal.x + 2;
         //lprect->top = m_pointMoveGripMinimal.y + 2;
         lprect->right = lprect->left + m_iCaptionHeight - 4;
         lprect->bottom = lprect->top + m_iCaptionHeight - 4;

         return true;

      default:
         break;
      }
      return false;

   }

   
   ::experience::enum_frame frame::experience_frame_hit_test(const ::point_i32 &point)
   {
      return ::experience::frame::experience_frame_hit_test(point);
//               ::rectangle_i32 rectangle;
//               for(enum_element eelement = (enum_element)(::e_element_none + 1);
//                     eelement < ElementEnd;
//                     eelement++)
//               {
//                  get_element_rect(rectangle, eelement);
//                  if(rectangle.contains(point))
//                  {
//                     eelementParam = eelement;
//                     return true;
//                  }
//               }
//               return false;
   }


   void frame::set_moveable_border_color(const ::color::color& colorMoveableBorder)
   {
               
      m_colorMoveableBorder = colorMoveableBorder;

      ::color::color color;

      color.set_rgb(colorMoveableBorder);
      color.hls_rate(0.0, 0.5, 0.0);
      m_colorMoveableBorderHilight = color;
      m_colorMoveableBorderHilight.alpha = 255;

      color.set_rgb(colorMoveableBorder);
      color.hls_rate(0.0, -0.3, 0.0);
      m_colorMoveableBorderShadow = color;
      m_colorMoveableBorderShadow.alpha = 255;

      color.set_rgb(colorMoveableBorder);
      color.hls_rate(8.0, -0.8, 0.0);
      m_colorMoveableBorderDkShadow = color;
      m_colorMoveableBorderDkShadow.alpha = 255;

      m_colorCaptionTextBk = m_colorMoveableBorderShadow;

   }


   void frame::set_button_color_schema_001(const ::color::color& colorMoveableBorder)
   {

//               defer_create_user_schema(schema_button);

//               ::color::color crBase = crMoveableBorder;
//
//               color ca;
//
//               ca.set_rgb(crBase);
//               ca.hls_rate(0.0, -0.49, -0.49);
//               create_color(color_border, ca.get_rgb() | (0xff << 24));
//
//               ca.set_rgb(crBase);
//               ca.hls_rate(0.0, -0.11, -0.11);
//               create_color(color_background, ca.get_rgb() | (0xff << 24));
//
//               ca.set_rgb(crBase);
//               ca.hls_rate(0.0, -0.49, -0.49);
//               create_color(color_text_normal, ca.get_rgb() | (0xff << 24));
//
//
//
//
//               ca.set_rgb(crBase);
//               ca.hls_rate(0.0, -0.45, 0.11);
//               create_color(color_border_hover, ca.get_rgb() | (0xff << 24));
//
//               ca.set_rgb(crBase);
//               ca.hls_rate(0.0, 0.33, 0.0);
//               create_color(color_background_hover,ca.get_rgb() | (0xff << 24));
//
//               ca.set_rgb(crBase);
//               ca.hls_rate(0.0, -0.55, 0.11);
//               create_color(color_text_hover, ca.get_rgb() | (0xff << 24));

   }


   void frame::set_frame_color_system_default_001()
   {

      auto pframewindow = m_pframewindow;

      auto psystem = m_psystem->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(m_pframewindow);

      auto pstyle = pframewindow->get_style(pgraphics);

      m_ppenText1->create_solid(1, pframewindow->get_color(pstyle, ::e_element_button_text));
      m_ppenFace1->create_solid(1, pframewindow->get_color(pstyle, ::e_element_button_background));
      m_ppenHilight1->create_solid(1, pframewindow->get_color(pstyle, ::e_element_button_hilite));
      m_ppenShadow1->create_solid(1, pframewindow->get_color(pstyle, ::e_element_button_shadow));
      m_ppenDkShadow1->create_solid(1, pframewindow->get_color(pstyle, ::e_element_button_dark_shadow));
      m_colorDkShadow = pframewindow->get_color(pstyle, ::e_element_button_dark_shadow);
      m_colorFrameBorder = argb(255, 0, 0, 0);

   }


   void frame::on_style_change_001_and_002(::draw2d::graphics_pointer & pgraphics)
   {

      auto pcontrolbox = get_control_box();

      m_minSize = size_i32(144, 48);

      m_minSize.cy = 48;

      if (pcontrolbox)
      {

         pcontrolbox->set_button_color_system_default_001();

      }

      set_frame_color_system_default_001();

      auto pframewindow = m_pframewindow;

      //auto estyle = pframewindow->m_estyle;

      auto colorBorder = pframewindow->get_moveable_border_color();

      set_moveable_border_color(colorBorder);

      set_button_color_schema_001(m_colorMoveableBorder);

      if(m_pframewindow->m_estyle == ::user::StyleTranslucidWarmGray || m_pframewindow->m_estyle == ::user::StyleDarkWarmBlue)
      {

         pcontrolbox->m_colorBackground = m_colorCaptionTextBk;

         m_colorCaptionText = argb(255, 255, 255, 255);

      }
      else if (m_pframewindow->m_estyle == ::user::StyleBlackPiano || m_pframewindow->m_estyle == ::user::StyleBlackBorder)
      {

         pcontrolbox->m_colorBackground = m_colorCaptionTextBk;

         m_colorCaptionText = argb(255, 255, 255, 255);

      }

   }


   //::color::color frame::get_style_moveable_border_color(::user::enum_style estyle)
   //{
   //   switch(m_pframewindow->m_estyle)
   //   {
   //   case ::user::StyleLightBlue:
   //   case ::user::StyleTranslucidLightBlue:
   //      return rgb(116, 160, 220);
   //   case ::user::StyleBlackPiano:
   //   case ::user::StyleBlackBorder:
   //      return rgb(0, 0, 0);
   //   case ::user::StyleTranslucidWarmGray:
   //      return argb(255, 190, 184, 177);
   //      break;
   //   case ::user::StyleDarkWarmBlue:
   //      return argb(255,34,54,75);
   //      break;
   //   case ::user::StyleLightGreen:
   //   case ::user::StyleTranslucidLightGreen:
   //      return rgb(116, 220, 160) | 0xff000000;
   //   case ::user::StyleRedOrange:
   //      return rgb(255, 170, 136) | 0xff000000;
   //   case ::user::StyleBlueRedPurple:
   //      return rgb(200, 100, 220) | 0xff000000;
   //   case ::user::StyleEveningSun:
   //      return rgb(255, 210, 100) | 0xff000000;
   //   case ::user::StyleTranslucidWarmLiteGray:
   //      return rgb(239, 230, 219) | 0xff000000;
   //   }


   //   // Light Green/Translucid Light Green
   //   return rgb(116, 220, 160) | 0xff000000;

   //}


   //bool frame::is_translucid_style(e_style estyle)
   //{


   //}


   void frame::Draw3dRectSide(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectangleParam,enum_border eborder, const ::color::color & colorTopLeft, const ::color::color& colorBottomRight)
   {

      ::rectangle_i32 rectangle(rectangleParam);

      i32 x = rectangle.left;
      i32 y = rectangle.top;
      i32 cx = rectangle.width();
      i32 cy = rectangle.height();

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::draw2d::pen_pointer ppen;

      if(eborder & e_border_top || eborder & e_border_left)
      {

         ppen.create(this);

         ppen->create_solid(1.0, colorTopLeft);

         pgraphics->set(ppen);

      }

      if(eborder & e_border_top)
      {

         pgraphics->set_current_point(x,y);

         pgraphics->line_to(x + cx,y);

      }

      if(eborder & e_border_left)
      {

         pgraphics->set_current_point(x,y);

         pgraphics->line_to(x,y+cy);

      }

      if((eborder & e_border_right || eborder & e_border_bottom) && (!ppen || ppen->m_color != colorBottomRight))
      {

         ppen.create(this);

         ppen->create_solid(1.0,colorBottomRight);

         pgraphics->set(ppen);

      }

      if(eborder & e_border_right)
      {

         pgraphics->set_current_point(x + cx,y);

         pgraphics->line_to(x + cx,y + cy);

      }

      if(eborder & e_border_bottom)
      {

         pgraphics->set_current_point(x,y + cy);

         pgraphics->line_to(x + cx,y + cy);

      }

   }


   void frame::_on_style_change(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void frame::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //return; // abcxxx


      if (!m_pframewindow->is_frame_experience_enabled())
      {

         return;

      }

      //auto psession = get_session();

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      auto pframewindow = m_pframewindow;

      if(!pframewindow->layout().is_full_screen() && !pframewindow->layout().is_zoomed() && !pframewindow->layout().is_iconic() && !m_pframewindow->frame_is_transparent() && m_pframewindow->m_bShowControlBox)
      {

         on_draw_frame(pgraphics);

      }

      if(pframewindow->layout().is_minimal())
      {

         ::rectangle_i32 rectangleIcon;

         if(get_element_rect(rectangleIcon, e_element_top_left_icon))
         {

            auto pdrawicon = m_pframewindow->get_draw_icon();

            if(::is_set(pdrawicon))
            {

               image_source imagesource(pdrawicon);

               image_drawing_options imagedrawingoptions(rectangleIcon);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

         }

         ::rectangle_i32 rectangleGrip;

         if(get_element_rect(rectangleGrip, e_element_move_grip_minimal))
         {

            int i = 0;

            while(i < rectangleGrip.width() - 5 + 1)
            {

               ::rectangle_f64 rectangle(rectangleGrip.left + i, rectangleGrip.top, 3, rectangleGrip.height());

               pgraphics->draw_inset_3d_rectangle(rectangle, argb(110,230,230,230),argb(110,130,130,130));

               i += 5;

            }

         }

      }
      else if(!pframewindow->layout().is_full_screen() && !m_pframewindow->frame_is_transparent())
      {

         //pgraphics->fill_rectangle(m_rectangleCaptionTextBk, m_colorCaptionTextBk);
         pgraphics->fill_rectangle(m_rectangleCaption, m_colorCaptionTextBk);

         ::rectangle_i32 rectangleIcon;

         auto pframewindow = m_pframewindow;

         status < ::color::color > crMoveableBorder;

         status < ::color::color > crMoveableBorderHilight;

         status < ::color::color > crMoveableBorderShadow;

         string str;

         pframewindow->get_window_text(str);

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

         ::rectangle_i32 rectangle;

         pframewindow->get_window_rect(rectangle);

         rectangle -= rectangle.top_left();

         if(get_element_rect(rectangleIcon, e_element_top_left_icon))
         {

            auto pdrawicon = m_pframewindow->get_draw_icon();

            if(::is_ok(pdrawicon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               image_source imagesource(pdrawicon);

               image_drawing_options imagedrawingoptions(rectangleIcon);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

         }

         string wstrWindowText;

         pframewindow->get_window_text(wstrWindowText);

         pgraphics->set_text_color(m_colorCaptionText);

         pgraphics->set_font(pframewindow, ::e_element_window_title);

         pgraphics->_DrawText(wstrWindowText, m_rectangleWindowText, { e_align_left, e_align_vertical_center}, e_draw_text_no_prefix);

      }


   }


   void frame::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
   {

      __UNREFERENCED_PARAMETER(pgraphics);

   }


} // namespace experience_nanogui



