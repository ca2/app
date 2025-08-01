#include "framework.h"
#include "input_text.h"
#include "aura/user/user/check_box.h"
#include "axis/html/element/element.h"
#include "axis/html/graphics/base.h"
#include "axis/html/graphics/tag.h"
#include "axis/html/graphics/value.h"
#include "axis/html/graphics/font.h"
#include "axis/html/graphics/style.h"
#include "axis/html/html/data.h"
#include "axis/html/html/core_data.h"
#include "axis/html/user/form.h"
#include "axis/user/user/user.h"


namespace html
{


   namespace impl
   {


      input_text::input_text(const ::scoped_string & scopedstrType, const ::scoped_string & scopedstrUnit) 
      {

         m_iFont = -1;
         
         m_strType = scopedstrType;

         m_strUnit = scopedstrUnit;

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

         ::atom atom = pelemental->m_phtmlbase->get_tag()->get_attr_value("id");

         //atom = translate_property_id(atom);

         if(!m_pedit || !m_pedit->is_window())
         {

            if (m_strType.case_insensitive_order("calculator") == 0)
            {

               auto puser = pdata->m_pcoredata->m_pform->user();

               m_pedit = puser->create_calculator_edit();

               m_pedit->set_format(m_strUnit);

               m_pedit->set_callback(this);

            }
            else
            {
               m_pedit = __allocate ::user::plain_edit();
            }

            m_pedit->initialize(this);

            m_pedit->m_bMultiLine = false;

            m_pedit->m_pform = pdata->m_pcoredata->m_pform;

            m_pedit->create_control(pdata->m_pcoredata->m_puserinteraction, atom);

            pdata->on_create_interaction(m_pedit);

            m_pedit->m_bPassword = pelemental->m_propertyset["type"].case_insensitive_order("password") == 0;

            m_pedit->m_strName = pelemental->m_phtmlbase->get_tag()->get_attr_value("name");

            bool bValue = pelemental->m_phtmlbase->get_tag()->get_attr("value") != nullptr;

            if(bValue)
            {

               m_pedit->set_text(pelemental->m_phtmlbase->get_tag()->get_attr_value("value"), ::e_source_data | ::e_source_load);

            }

            ///m_pedit->m_puserstyle = pelemental;

         }

         pdata->m_pcoredata->m_focusptra.add_unique(m_pedit);

         m_cxMax = 200;

         m_cxMin = 200;

      }


      bool input_text::layout_phase1(html_data * pdata)
      {

         string strSize = m_pelemental->m_phtmlbase->get_tag()->get_attr_value("ize");

         int iSize = 20;

         if (strSize.has_character())
         {

            iSize = maximum(1, atoi(strSize));

         }

         auto preferredDensity = m_pedit->preferred_density();

         m_box.set_size(iSize * 10.f * preferredDensity, 23.f * preferredDensity);

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

         //::int_rectangle rectangleWindow;

         //m_pedit->window_rectangle(rectangleWindow);

         //m_pedit->get_wnd()->screen_to_client(rectangleWindow);

         //::draw2d::save_context savecontext(pgraphics);

         //pgraphics->set_origin(rectangleWindow.top_left());

         m_pedit->_000CallOnDraw(pdata->m_pcoredata->m_pgraphics);

      }


      void input_text::on_change_layout(html_data * pdata)
      {

         __UNREFERENCED_PARAMETER(pdata);

         m_pedit->place(m_box);

      }


   }


} // namespace html



