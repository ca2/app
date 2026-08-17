#include "platform.h"
#include "frame.h"
#include "frame_array.h"
#include "pixmap.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"
//#include "aura/graphics/image/drawing.h"


namespace image
{


   image_frame::image_frame()
   {

   }


   image_frame::~image_frame()
   {


   }


   void image_frame::gif_set_disposal(::i32 iDisposal)
   {

      switch (iDisposal)
      {
         case 0:
            m_edisposal = ::draw2d::e_disposal_undefined;
         break;
         case 1:
            m_edisposal = ::draw2d::e_disposal_none;
         break;
         case 2:
            m_edisposal = ::draw2d::e_disposal_background;
         break;
         case 3:
            m_edisposal = ::draw2d::e_disposal_previous;
         break;
         default:
            m_edisposal = ::draw2d::e_disposal_undefined;
         break;
      }

   }

   void image_frame::_001Process(::pixmap * ppixmapImageCompose, ::pixmap * ppixmapImageFrame, image_frame_array * pframea)
   {

      ::i32_point point = m_rectangle.top_left();

      ::i32_size size = m_rectangle.size();

      if (m_edisposal == ::draw2d::e_disposal_background
         || m_edisposal == ::draw2d::e_disposal_undefined
         || m_edisposal == ::draw2d::e_disposal_previous)
      {

         //auto ppixmapImageCompose = pimageCompose->map();

         //auto ppixmapImageFrame = pimageFrame->map();

         ppixmapImageCompose->copy_from(ppixmapImageFrame, ::e_flag_none);

         //pgraphicsImageCompose->set_alpha_mode(::draw2d::e_alpha_mode_set);

         //::color::color crBack = pframea->m_colorBack;

         //::u8 bAlpha = color32_u8_opacity(crBack);

         //if (bAlpha == 0)
         //{

         //   crBack = 0;

         //}
         //else
         //{

         //   informationf("non zero alpha");

         //}

         //::i32_rectangle rectangle = pframea->element_at(m_iFrame - 1)->m_rectangle;

         //pgraphicsImageCompose->fill_rectangle(rectangle, crBack);

      }
      else if (m_edisposal == ::draw2d::e_disposal_none)
      {

         if (m_iFrame <= 0)
         {

            //pimageCompose->map();

            //pgraphicsImageCompose->set_alpha_mode(::draw2d::e_alpha_mode_set);

            //auto ppixmapImageCompose = pimageCompose->map();

            //auto ppixmapImageFrame = pimageFrame->map();

            ppixmapImageCompose->copy_from(ppixmapImageFrame, ::e_flag_none);

         }
         else
         {

            //pimageCompose->map();

            //pgraphicsImageCompose->set_alpha_mode(::draw2d::e_alpha_mode_blend);
            //auto ppixmapImageCompose = pimageCompose->map();

            //auto ppixmapImageFrame = pimageFrame->map();

            //pgraphicsImageCompose->draw(pimageFrame);
            ppixmapImageCompose->precision_blend(point, ppixmapImageFrame, {}, size);


         }

      }
      else
      {

         information() << "Don't know how to handle this GIF Disposal";

      }


      /*     if (uFrameIndex <= 0)
           {

              pimageCompose->set_alpha_mode(::draw2d::e_alpha_mode_set);

              pgraphicsImageCompose->fill_rectangle(pframea->rectangle(), 0);

           }*/
      //auto ppixmapImage = m_pimage->map();

      //auto ppixmapImageFrame = pimageFrame->map();


      m_ppixmap->copy_from(ppixmapImageFrame, ::e_flag_none);

      pframea->m_timeTotal += m_time;

   }


   //
   // void image_frame::create(::image::image_frame * pframeSource, const ::image::image_drawing & imagedrawing, ::image::image_frame_array * pframea)
   // {
   //
   //    auto dx = (::f64) imagedrawing.m_rectangleTarget.width() / (::f64) imagedrawing.image()->width();
   //    auto dy = (::f64)imagedrawing.m_rectangleTarget.height() / (::f64)imagedrawing.image()->height();
   //
   //    m_rectangle.left = (decay<decltype(m_rectangle.left)>)(pframeSource->m_rectangle.left * dx);
   //    m_rectangle.top = (decay<decltype(m_rectangle.top)>)(pframeSource->m_rectangle.top * dy);
   //    m_rectangle.right = (decay<decltype(m_rectangle.right)>)(pframeSource->m_rectangle.right * dx);
   //    m_rectangle.bottom = (decay<decltype(m_rectangle.bottom)>)(pframeSource->m_rectangle.bottom * dy);
   //
   //    constructø(m_pimage);
   //
   //    ::f64_size size = pframea->m_size;
   //
   //    m_pimage->create_as_descriptor(size);
   //
   //    ::f64_rectangle r1(pframeSource->m_rectangle.size());
   //
   //    ::image::image_source imagesourceFrame(pframeSource->m_pimage);
   //
   //    ::f64_rectangle r(size);
   //
   //    ::image::image_drawing_options imagedrawingoptionsFrame(r);
   //
   //    ::image::image_drawing imagedrawingFrame(imagedrawingoptionsFrame, imagesourceFrame);
   //
   //    m_pimage->draw(imagedrawingFrame);
   //
   //    m_time = pframeSource->m_time;
   //    m_iFrame= pframeSource->m_iFrame;
   //    m_edisposal= pframeSource->m_edisposal;
   //    m_colorTransparent= pframeSource->m_colorTransparent;
   //    m_bTransparent= pframeSource->m_bTransparent;
   //    m_bLocalPalette= pframeSource->m_bLocalPalette;
   //
   //    m_pimage->m_estatus = ::success;
   //
   //    m_pimage->set_ok_flag();
   //
   // }


   void image_frame::create_frame(::image::image_frame * pframeSource, const ::pixmap * ppixmap, ::image::image_frame_array * pframea)
   {

      //auto dx = (::f64) imagedrawing.m_rectangleTarget.width() / (::f64) imagedrawing.image()->width();
      //auto dy = (::f64)imagedrawing.m_rectangleTarget.height() / (::f64)imagedrawing.image()->height();

      //m_rectangle.left = (decay<decltype(m_rectangle.left)>)(pframeSource->m_rectangle.left * dx);
      //m_rectangle.top = (decay<decltype(m_rectangle.top)>)(pframeSource->m_rectangle.top * dy);
      //m_rectangle.right = (decay<decltype(m_rectangle.right)>)(pframeSource->m_rectangle.right * dx);
      //m_rectangle.bottom = (decay<decltype(m_rectangle.bottom)>)(pframeSource->m_rectangle.bottom * dy);

      m_rectangle.left = pframeSource->m_rectangle.left;
      m_rectangle.top = pframeSource->m_rectangle.top;
      m_rectangle.right = pframeSource->m_rectangle.right;
      m_rectangle.bottom = pframeSource->m_rectangle.bottom;

      m_ppixmap = ((::pixmap *)ppixmap)->clone();

      // constructø(m_pimage);
      //
      // ::f64_size size = pframea->m_size;
      //
      // m_pimage->create_as_descriptor(size);
      //
      // ::f64_rectangle r1(pframeSource->m_rectangle.size());
      //
      // ::image::image_source imagesourceFrame(pframeSource->m_pimage);
      //
      // ::f64_rectangle r(size);
      //
      // ::image::image_drawing_options imagedrawingoptionsFrame(r);
      //
      // ::image::image_drawing imagedrawingFrame(imagedrawingoptionsFrame, imagesourceFrame);
      //
      // m_pimage->draw(imagedrawingFrame);

      m_time = pframeSource->m_time;
      m_iFrame= pframeSource->m_iFrame;
      m_edisposal= pframeSource->m_edisposal;
      m_colorTransparent= pframeSource->m_colorTransparent;
      m_bTransparent= pframeSource->m_bTransparent;
      m_bLocalPalette= pframeSource->m_bLocalPalette;

      m_ppixmap->m_estatus = ::success;

      m_ppixmap->set_ok_flag();

   }


} // namespace image



