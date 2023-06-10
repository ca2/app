#include "framework.h"
#include "frame.h"
#include "frame_array.h"
#include "image.h"
//#include "acme/primitive/geometry2d/_geometry2d.h"
#include "aura/graphics/image/drawing.h"


image_frame::image_frame()
{

}


image_frame::~image_frame()
{


}


void image_frame::gif_set_disposal(int iDisposal)
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

void image_frame::_001Process(::image * pimageCompose, ::image * pimageFrame, image_frame_array * pframea)
{

   ::point_i32 point = m_rectangle.top_left();

   ::size_i32 size = m_rectangle.size();

   if (m_edisposal == ::draw2d::e_disposal_background
      || m_edisposal == ::draw2d::e_disposal_undefined
      || m_edisposal == ::draw2d::e_disposal_previous)
   {

      pimageCompose->copy_from(pimageFrame, ::e_flag_none);

      //pimageCompose->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);

      //::color::color crBack = pframea->m_colorBack;

      //::u8 bAlpha = color32_u8_opacity(crBack);

      //if (bAlpha == 0)
      //{

      //   crBack = 0;

      //}
      //else
      //{

      //   output_debug_string("non zero alpha");

      //}

      //::rectangle_i32 rectangle = pframea->element_at(m_iFrame - 1)->m_rectangle;

      //pimageCompose->g()->fill_rectangle(rectangle, crBack);

   }
   else if (m_edisposal == ::draw2d::e_disposal_none)
   {

      if (m_iFrame <= 0)
      {

         //pimageCompose->map();

         //pimageCompose->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);

         pimageCompose->copy_from(pimageFrame, ::e_flag_none);

      }
      else
      {

         //pimageCompose->map();

         //pimageCompose->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         //pimageCompose->g()->draw(pimageFrame);
         pimageCompose->precision_blend(point, pimageFrame, {}, size);


      }

   }
   else
   {

      INFORMATION("Don't know how to handle this GIF Disposal");

   }


   /*     if (uFrameIndex <= 0)
        {

           pimageCompose->set_alpha_mode(::draw2d::e_alpha_mode_set);

           pimageCompose->g()->fill_rectangle(pframea->rectangle(), 0);

        }*/


   m_pimage->copy_from(pimageCompose, ::e_flag_none);

   pframea->m_timeTotal += m_time;

}


void image_frame::create(image_frame * pframeSource, const ::image_drawing & imagedrawing, ::image_frame_array * pframea)
{

   auto dx = (double) imagedrawing.m_rectangleTarget.width() / (double) imagedrawing.image()->width();
   auto dy = (double)imagedrawing.m_rectangleTarget.height() / (double)imagedrawing.image()->height();

   m_rectangle.left = (decltype(m_rectangle.left))(pframeSource->m_rectangle.left * dx);
   m_rectangle.top = (decltype(m_rectangle.top))(pframeSource->m_rectangle.top * dy);
   m_rectangle.right = (decltype(m_rectangle.right))(pframeSource->m_rectangle.right * dx);
   m_rectangle.bottom = (decltype(m_rectangle.bottom))(pframeSource->m_rectangle.bottom * dy);

   __construct(m_pimage);

   ::size_f64 size = pframea->m_size;

   m_pimage->create(size);

   ::rectangle_f64 r1(pframeSource->m_rectangle.size());

   ::image_source imagesourceFrame(pframeSource->m_pimage);

   ::rectangle_f64 r(size);

   ::image_drawing_options imagedrawingoptionsFrame(r);

   ::image_drawing imagedrawingFrame(imagedrawingoptionsFrame, imagesourceFrame);

   m_pimage->draw(imagedrawingFrame);

   m_time = pframeSource->m_time;
   m_iFrame= pframeSource->m_iFrame;
   m_edisposal= pframeSource->m_edisposal;
   m_colorTransparent= pframeSource->m_colorTransparent;
   m_bTransparent= pframeSource->m_bTransparent;
   m_bLocalPalette= pframeSource->m_bLocalPalette;

   m_pimage->m_estatus = ::success;

   m_pimage->set_ok_flag();

}



