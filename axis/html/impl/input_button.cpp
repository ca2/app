#include "framework.h"
#include "input_button.h"
#include "acme/primitive/data/listener.h"
#include "aura/user/user/button.h"
#include "axis/html/element/element.h"
#include "axis/html/graphics/base.h"
#include "axis/html/graphics/tag.h"
#include "axis/html/graphics/font.h"
#include "axis/html/graphics/style.h"
#include "axis/html/html/data.h"
#include "axis/html/html/core_data.h"


namespace html
{


   namespace impl
   {


      input_button::input_button()
      {

         m_iFont = -1;

      }


      input_button::~input_button()
      {

         try
         {

            if(m_pbutton->is_window())
            {

               m_pbutton->destroy_window();

            }

         }
         catch(...)
         {

         }

         try
         {

            //m_pbutton.release();

         }
         catch(...)
         {

         }

      }


      void input_button::implement_phase1(html_data * pdata, ::html::element * pelemental)
      {

         m_bHasChar = true;

         __defer_construct_new(m_pbutton);

         m_pbutton->m_atom = pelemental->m_phtmlbase->get_tag()->get_attr_value("id");

         if (m_pbutton->m_atom.is_empty())
         {

            m_pbutton->m_atom = pelemental->m_phtmlbase->get_tag()->get_attr_value("name");

         }

         if(!m_pbutton->is_window())
         {

            m_pbutton->create_child(pdata->m_pcoredata->m_puserinteraction);

            pdata->on_create_interaction(m_pbutton);

         }

         element::implement_phase1(pdata, pelemental);

         auto value = pelemental->m_phtmlbase->get_tag()->get_attr_value("value");

         m_pbutton->set_window_text(value);

         m_cxMax = 200;

         m_cxMin = 200;

      }


      bool input_button::layout_phase1(html_data * pdata)
      {

         m_pbutton->resize_to_fit(pdata->m_pcoredata->m_pgraphics);

         auto size = m_pbutton->const_layout().sketch().size();

         m_box.set_size(size);

         return true;

      }


      void input_button::layout_phase3(html_data * pdata)
      {

         element::layout_phase3(pdata);

         m_pbutton->place(m_box);

         m_pbutton->display(::e_display_normal);

      }


      void input_button::_001OnDraw(html_data * pdata)
      {

         ::draw2d::graphics_pointer & pgraphics = pdata->m_pcoredata->m_pgraphics;

         //::rectangle_i32 rectangleWindow;
         //m_pbutton->window_rectangle(rectangleWindow);
         //m_pbutton->GetWindow()->screen_to_client(rectangleWindow);
         //auto pointPreviousContextOrg = pgraphics->get_origin();
         //pgraphics->offset_origin((i32) m_box.left(), (i32) m_box.top());
         m_pbutton->_000CallOnDraw(pgraphics);
         //pgraphics->set_origin(pointPreviousContextOrg);

      }


      void input_button::on_change_layout(html_data * pdata)
      {

         __UNREFERENCED_PARAMETER(pdata);

         m_pbutton->place(m_box);

      }


   } // namespace impl


} // namespace html





