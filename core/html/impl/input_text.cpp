#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_impl.h"
#endif



::user::plain_edit* new_calculator_plain_edit();


namespace html
{


   namespace impl
   {


      input_text::input_text(const ::string & strType, const ::string & strUnit) 
      {

         m_iFont = -1;
         
         m_strType = strType;
         
         m_strUnit = strUnit;

      }


      input_text::~input_text()
      {

         try
         {

            if(m_pedit->is_window())
            {

               m_pedit->destroy_window();

            }

         }
         catch(...)
         {

         }

      }


      void input_text::implement_phase1(html_data * pdata, ::html::element * pelemental)
      {

         m_bHasChar = true;

         element::implement_phase1(pdata, pelemental);

         ::atom atom = pelemental->m_pbase->get_tag()->get_attr_value("atom");

         atom = translate_property_id(atom);

         if(!m_pedit || !m_pedit->is_window())
         {

            if (m_strType.compare_ci("calculator") == 0)
            {
               m_pedit = move_transfer(new_calculator_plain_edit());
               m_pedit->set_format(m_strUnit);
               m_pedit->set_callback(this);
            }
            else
            {
               m_pedit = __new(::user::plain_edit);
            }

            m_pedit->initialize(this);

            m_pedit->m_bMultiLine = false;

            m_pedit->m_pform = pdata->m_pcoredata->m_pform;

            m_pedit->create_control(pdata->m_pcoredata->m_puserinteraction, atom);

            pdata->on_create_interaction(m_pedit);

            m_pedit->m_bPassword = pelemental->m_propertyset["type"].compare_ci("password") == 0;

            m_pedit->m_strName = pelemental->m_pbase->get_tag()->get_attr_value("name");

            bool bValue = pelemental->m_pbase->get_tag()->get_attr("value") != nullptr;

            if(bValue)
            {

               m_pedit->_001SetText(pelemental->m_pbase->get_tag()->get_attr_value("value"), ::e_source_data | ::e_source_load);

            }

            ///m_pedit->m_puserstyle = pelemental;

         }

         pdata->m_pcoredata->m_focusptra.add_unique(m_pedit);

         m_cxMax = 200;

         m_cxMin = 200;

      }


      bool input_text::layout_phase1(html_data * pdata)
      {

         string strSize = m_pelemental->m_pbase->get_tag()->get_attr_value("ize");

         int iSize = 20;

         if (strSize.has_char())
         {

            iSize = maximum(1, atoi(strSize));

         }

         m_box.set_size(iSize * 10.f, 23.f);

         return true;

      }


      void input_text::layout_phase3(html_data * pdata)
      {

         element::layout_phase3(pdata);

         //m_box.offset_x(300);

         //m_box.offset_y(100);

         m_pedit->place(m_box);

         m_pedit->display(::e_display_normal);

         //m_pedit->m_pointRequest.offset(500, 100);


      }


      void input_text::_001OnDraw(html_data * pdata)
      {

         //::draw2d::graphics_pointer & pgraphics = pdata->m_pcoredata->m_pgraphics;

         //::rectangle_i32 rectangleWindow;

         //m_pedit->get_window_rect(rectangleWindow);

         //m_pedit->get_wnd()->screen_to_client(rectangleWindow);

         //::draw2d::savedc savedc(pgraphics);

         //pgraphics->SetViewportOrg(rectangleWindow.top_left());

         m_pedit->_000CallOnDraw(pdata->m_pcoredata->m_pgraphics);

      }


      void input_text::on_change_layout(html_data * pdata)
      {

         __UNREFERENCED_PARAMETER(pdata);

         m_pedit->place(m_box);

      }


   }


} // namespace html



