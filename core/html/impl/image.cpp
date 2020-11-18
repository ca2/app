#include "framework.h"
#include "_impl.h"


namespace html
{


   namespace impl
   {


      void image::_001OnDraw(html_data * pdata)
      {

         ::draw2d::graphics_pointer pgraphics = pdata->m_pcoredata->m_pgraphics;

         if (m_pelemental->m_pbase->get_type() == ::html::base::type_tag)
         {

            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
            
            if(m_pimage)
            {

               m_pimage->defer_realize(pgraphics);

               pgraphics->draw(::point((LONG) left(),(LONG) top()),
                                 m_pimage->get_graphics(), ::rect(m_pimage->size()));
               
            }

         }

      }


      void image::implement_phase1(html_data * pdata, ::html::element * pelement)
      {

         m_bHasChar = true;

         element::implement_phase1(pdata, pelement);

         if (pelement->m_pbase->get_type() == ::html::base::type_tag)
         {

            string strSrc = pelement->m_propertyset["src"];

            m_pimage = pdata->get_image(strSrc);

            int cx = m_pimage->width();

            int cy = m_pimage->height();

            if (pelement->m_propertyset.has_property("width"))
            {

               cx = pelement->m_propertyset["width"];

            }

            if (pelement->m_propertyset.has_property("height"))
            {
               
               cy = pelement->m_propertyset["height"];

            }

            m_cxMax = (float)cx;

            m_cxMin = (float)cy;

         }

      }


      bool image::layout_phase1(html_data * pdata)
      {

         if (m_pelemental->m_pbase->get_type() == ::html::base::type_tag)
         {

            single_lock lockImage(mutex());

            if (lockImage.lock(0))
            {

               int cx = m_pimage->width();
               
               int cy = m_pimage->height();

               if (m_pelemental->m_propertyset.has_property("width"))
               {
                  
                  cx = m_pelemental->m_propertyset["width"];

               }

               if (m_pelemental->m_propertyset.has_property("height"))
               {
                  
                  cy = m_pelemental->m_propertyset["height"];

               }

               m_box.set_size((float) cx, (float) cy);

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
         
         if (m_pelemental->m_pbase->get_type() == ::html::base::type_tag)
         {
            
            single_lock lockImage(mutex());

            if (lockImage.lock(duration::zero()))
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


