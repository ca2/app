#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_impl.h"
#endif



namespace html
{


   namespace impl
   {


      namespace user
      {


         class CLASS_DECL_CORE check_box:
            virtual public ::user::check_box
         {
         public:

            
            check_box(){}
            virtual ~check_box() {}

            virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics) {}


         };


      } // namespace user


      input_checkbox::input_checkbox()
      {

      }


      input_checkbox::~input_checkbox()
      {

         try
         {

            if(m_pcheckbox->is_window())
            {

               m_pcheckbox->destroy_window();

            }

         }
         catch(...)
         {

         }

         try
         {

            m_pcheckbox.release();

         }
         catch(...)
         {

         }

      }


      void input_checkbox::implement_phase1(html_data * pdata, ::html::element* pelement)
      {

         m_bHasChar = true;

         element::implement_phase1(pdata, pelement);

         ::id id = pelement->m_pbase->get_tag()->get_attr_value("id");

         id = translate_property_id(id);

         if(!m_pcheckbox || !m_pcheckbox->is_window())
         {

            m_pcheckbox = __create_new < user::check_box > ();

            m_pcheckbox->m_pform = pdata->m_pcoredata->m_pform;

            m_pcheckbox->create_control(pdata->m_pcoredata->m_puserinteraction, id);

            pdata->on_create_interaction(m_pcheckbox);

            bool bCheck = pelement->m_pbase->get_tag()->get_attr("checked") != nullptr;

            if(bCheck)
            {

               m_pcheckbox->_001SetCheck(check_checked, ::action_context(::e_source_data) +  ::e_source_load);

            }
            else if(m_pcheckbox->echeck() == ::check_undefined)
            {

               m_pcheckbox->_001SetCheck(check_unchecked, ::action_context(::e_source_data) +  ::e_source_load);

            }

         }
         else
         {

            m_pcheckbox->m_id = id;

         }

         m_pcheckbox->m_strName = pelement->m_pbase->get_tag()->get_attr_value("name");

         if(pdata->m_pcoredata->m_pform != nullptr)
         {

            auto ptopic = create_subject(::id_initialize_control);

            ptopic->m_puserelement = m_pcheckbox;

            ptopic->m_actioncontext = ::action_context(::e_source_data) +  ::e_source_load;

            ptopic->m_uiEvent = 0;

            pdata->m_pcoredata->m_pform->route(ptopic);

         }

      }


      bool input_checkbox::layout_phase1(html_data * pdata)
      {

         m_box.set_size(26, 26);

         return true;

      }


      void input_checkbox::layout_phase3(html_data * pdata)
      {

         element::layout_phase3(pdata);

         auto rect = m_box;

         rect.deflate(5, 5);

         m_pcheckbox->place(rect);

         m_pcheckbox->display(::e_display_normal);

      }


      void input_checkbox::_001OnDraw(html_data * pdata)
      {

//         ::draw2d::graphics_pointer & pgraphics = pdata->m_pcoredata->m_pgraphics;

         //::rectangle_i32 rectangleWindow;
         //m_pcheckbox->get_window_rect(rectangleWindow);
  //       ::point_i32 pointPreviousImpactportOrg = pgraphics->GetImpactportOrg();

    //     pgraphics->OffsetImpactportOrg((i32) m_box.left, (i32) m_box.top);

         m_pcheckbox->_000CallOnDraw(pdata->m_pcoredata->m_pgraphics);

      //   pgraphics->SetImpactportOrg(pointPreviousImpactportOrg);

      }


      void input_checkbox::on_change_layout(html_data * pdata)
      {

         __UNREFERENCED_PARAMETER(pdata);

         m_pcheckbox->place(m_box);

      }


   }


}



