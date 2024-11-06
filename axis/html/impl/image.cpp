#include "framework.h"
#include "image.h"
#include "acme/parallelization/single_lock.h"
#include "acme/prototype/data/listener.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/drawing.h"
#include "axis/html/html/data.h"
#include "axis/html/html/core_data.h"
#include "axis/html/element/element.h"
#include "axis/html/graphics/base.h"
#include "axis/html/graphics/font.h"
#include "axis/html/graphics/style.h"
#include "aura/user/user/interaction.h"


namespace html
{


   namespace impl
   {


      void image::_001OnDraw(html_data * pdata)
      {

         ::draw2d::graphics_pointer pgraphics = pdata->m_pcoredata->m_pgraphics;

         if (m_pelemental->m_phtmlbase->get_type() == ::html::base::type_tag)
         {

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
            
            if (m_pimage)
            {

               m_pimage->defer_realize(pgraphics);

               auto pointDst = ::point_f64((int)left(), (int)top());

               auto sizeDst = m_pimage->size();

               auto rectangleTarget = ::rectangle_f64(pointDst, sizeDst);

               ::image::image_source imagesource(m_pimage);

               ::image::image_drawing_options imagedrawingoptions(rectangleTarget);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);
               
            }

         }

      }


      void image::implement_phase1(html_data * pdata, ::html::element * pelement)
      {

         m_bHasChar = true;

         element::implement_phase1(pdata, pelement);

         if (pelement->m_phtmlbase->get_type() == ::html::base::type_tag)
         {

            string strSrc(pelement->m_propertyset["src"].as_string());

            m_pimage = pdata->get_image(strSrc);

            int cx = m_pimage->width();

            int cy = m_pimage->height();

            if (pelement->m_propertyset.has_property("width"))
            {

               cx = pelement->m_propertyset["width"].as_i32();

            }

            if (pelement->m_propertyset.has_property("height"))
            {
               
               cy = pelement->m_propertyset["height"].as_i32();

            }

            m_cxMax = (float)cx;

            m_cxMin = (float)cy;

         }

      }


      bool image::layout_phase1(html_data * pdata)
      {

         if (m_pelemental->m_phtmlbase->get_type() == ::html::base::type_tag)
         {

            single_lock lockImage(synchronization());

            if (lockImage.lock(0_s))
            {

               int cx = m_pimage->width();
               
               int cy = m_pimage->height();

               if (m_pelemental->m_propertyset.has_property("width"))
               {
                  
                  cx = m_pelemental->m_propertyset["width"].as_i32();

               }

               if (m_pelemental->m_propertyset.has_property("height"))
               {
                  
                  cy = m_pelemental->m_propertyset["height"].as_i32();

               }

               m_box.set_size((float)cx, (float)cy);

            }
            else
            {

               m_box.set_size(0, 0);

            }

         }

         return true;

      }


      void image::layout_phase3(html_data * pdata)
      {

         element::layout_phase3(pdata);
         
         if (m_pelemental->m_phtmlbase->get_type() == ::html::base::type_tag)
         {
            
            single_lock lockImage(synchronization());

            if (lockImage.lock(0_s))
            {
               pdata->m_pcoredata->m_layoutstate3.m_cx = (float)m_pimage->width();
               if (m_pimage->height() > pdata->m_pcoredata->m_layoutstate3.m_cya.last())
               {
                  pdata->m_pcoredata->m_layoutstate3.m_cya.last() = (float)m_pimage->height();
               }
            }
            else
            {
               pdata->m_pcoredata->m_layoutstate3.m_cx = 0;
               pdata->m_pcoredata->m_layoutstate3.m_cya.last() = 0;
            }

            m_box.set_size(m_pimage->size());

         }

      }


   } // namespace impl


} // namespace html_impl


