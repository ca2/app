#include "framework.h"


image_frame::image_frame()
{

   m_tick = 0;

}


image_frame::~image_frame()
{


}







void image_frame::gif_set_disposal(int iDisposal)
{

   switch (iDisposal)
   {
   case 0:
      m_edisposal = ::draw2d::disposal_undefined;
      break;
   case 1:
      m_edisposal = ::draw2d::disposal_none;
      break;
   case 2:
      m_edisposal = ::draw2d::disposal_background;
      break;
   case 3:
      m_edisposal = ::draw2d::disposal_previous;
      break;
   default:
      m_edisposal = ::draw2d::disposal_undefined;
      break;
   }

}

void image_frame::_001Process(::image * pimageCompose, ::image * pimageFrame, image_frame_array * pframea)
{

   ::point_i32 point = m_rectangle.top_left();

   ::size_i32 size = m_rectangle.size();

   if (m_edisposal == ::draw2d::disposal_none)
   {

      if (m_iFrame <= 0)
      {

         //pimageCompose->map();

         //pimageCompose->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);

         pimageCompose->copy_from(pimageFrame, ::e_object_none);

      }
      else
      {

         //pimageCompose->map();

         //pimageCompose->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         //pimageCompose->g()->draw(pimageFrame);
         pimageCompose->precision_blend(point, pimageFrame, nullptr, size);


      }

   }
   else if (m_edisposal == ::draw2d::disposal_background)
   {

      pimageCompose->copy_from(pimageFrame, ::e_object_none);

      //pimageCompose->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);

      //::color::color crBack = pframea->m_colorBack;

      //byte bAlpha = colorref_get_a_value(crBack);

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
   else
   {

      output_debug_string("test");

   }


   /*     if (uFrameIndex <= 0)
        {

           pimageCompose->set_alpha_mode(::draw2d::e_alpha_mode_set);

           pimageCompose->g()->fill_rectangle(pframea->rectangle(), 0);

        }*/


   m_pimage->copy_from(pimageCompose, ::e_object_none);

   //m_pimage->create_helper_map();

   pframea->m_millisTotal += m_tick;

}



