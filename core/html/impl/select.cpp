#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_impl.h"
#endif



namespace html
{


   namespace impl
   {


      select::select()
      {

         m_iFont = -1;

      }


      select::~select()
      {

         try
         {

            if (m_pcombo->is_window())
            {

               m_pcombo->destroy_window();

            }

         }
         catch (...)
         {

         }

         try
         {

            m_pcombo.release();

         }
         catch (...)
         {

         }

      }


      void select::implement_phase1(html_data * pdata, ::html::element * pelement)
      {

         m_bHasChar = true;

         element::implement_phase1(pdata, pelement);
         if (pelement->m_pbase->get_type() != ::html::base::type_tag)
         {

            return;

         }


         if(pelement->m_pbase->get_type() == ::html::base::type_tag && (!m_pcombo || !m_pcombo->is_window()))
         {

            m_pcombo = __create_new < ::user::combo_box>();

            m_pcombo->m_bMultiLine = false;

            
            m_pcombo->create_child(pdata->m_pcoredata->m_puserinteraction);
            
            pdata->on_create_interaction(m_pcombo);
            
            m_pcombo->m_bPassword = pelement->m_propertyset["type"].compare_ci("password") == 0;
            m_pcombo->m_strName = pelement->m_pbase->get_tag()->get_attr_value("name");
            m_pcombo->m_id = pelement->m_pbase->get_tag()->get_attr_value("id");

            if (pelement->m_pbase->get_tag()->baseptra().has_elements())
            {
               m_pcombo->m_edatamode = ::user::combo_box::data_mode_string;

               for (index i = 0; i < pelement->m_pbase->get_tag()->baseptra().get_count(); i++)
               {
                  if (i == 0)
                  {
                  }
                  if (pelement->m_pbase->get_tag()->baseptra()[i]->get_type() != ::html::base::type_tag)
                     continue;
                  string strText = pelement->m_pbase->get_tag()->baseptra()[i]->get_tag()->baseptra()[0]->get_value()->get_value();
                  string strValue = pelement->m_pbase->get_tag()->baseptra()[i]->get_tag()->get_attr_value("value");
                  m_pcombo->add_string(strText, strValue);
               }
               string strValue = pelement->m_pbase->get_tag()->get_attr_value("value");

               if (strValue.has_char())
               {

                  m_pcombo->_001SetText(pelement->m_pbase->get_tag()->get_attr_value("value"), ::action_context(::e_source_data) +  ::e_source_load);

               }
               
            }

            //m_pcombo->m_puserstyle = pelement;

            m_pcombo->m_bEdit = false;

            pdata->m_pcoredata->m_pform->_001OnInitializeControl(m_pcombo);

         }

         pdata->m_pcoredata->m_focusptra.add_unique(m_pcombo);

         m_cxMax = 200;

         m_cxMin = 200;

      }



      void select::layout_phase1_end(html_data * pdata)
      {

         if (m_pelemental->m_pbase->get_type() != ::html::base::type_tag)
            return;

         ::html::impl::element::layout_phase1_end(pdata);

      }

      void select::layout_phase3_end(html_data * pdata)
      {
         if (m_pelemental->m_pbase->get_type() != ::html::base::type_tag)
            return;

         ::html::impl::element::layout_phase3_end(pdata);

      }






      bool select::layout_phase1(html_data * pdata)
      {

         if (m_pelemental->m_pbase->get_type() != ::html::base::type_tag)
         {

            return false;

         }

         string strSize = m_pelemental->m_pbase->get_tag()->get_attr_value("size_i32");

         int iSize = 20;

         if (strSize.has_char())
            iSize = maximum(1, atoi(strSize));

         m_box.set_size(iSize * 10.f, 23.f);

         return true;

      }


      void select::layout_phase3(html_data * pdata)
      {

         if (m_pelemental->m_pbase->get_type() != ::html::base::type_tag)
         {

            return;

         }

         element::layout_phase3(pdata);

         m_pcombo->place(m_box);

         m_pcombo->display(::e_display_normal, e_activation_no_activate);

      }


      void select::_001OnDraw(html_data * pdata)
      {

         if (m_pelemental->m_pbase->get_type() != ::html::base::type_tag)
         {

            return;

         }

         ::draw2d::graphics_pointer & pgraphics = pdata->m_pcoredata->m_pgraphics;

         //::rectangle_i32 rectWindow;

         //m_pcombo->get_window_rect(rectWindow);

         //m_pcombo->screen_to_client(rectWindow);

         //::draw2d::savedc savedc(pgraphics);

         //pgraphics->SetViewportOrg(rectWindow.top_left());

         m_pcombo->_000CallOnDraw(pgraphics);

      }


      void select::on_change_layout(html_data * pdata)
      {

         if (m_pelemental->m_pbase->get_type() != ::html::base::type_tag)
            return;

         __UNREFERENCED_PARAMETER(pdata);

         m_pcombo->place(m_box);

      }

   }


} // namespace html



