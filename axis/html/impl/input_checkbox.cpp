#include "framework.h"
#include "input_checkbox.h"
#include "acme/constant/id.h"
#include "acme/handler/extended_topic.h"
#include "acme/prototype/data/listener.h"
#include "aura/user/user/check_box.h"
#include "axis/html/element/element.h"
#include "axis/html/graphics/base.h"
#include "axis/html/graphics/tag.h"
#include "axis/html/graphics/font.h"
#include "axis/html/graphics/style.h"
#include "axis/html/html/data.h"
#include "axis/html/html/core_data.h"
#include "axis/html/user/form.h"


namespace html
{


   namespace impl
   {


      namespace user
      {


         class CLASS_DECL_AXIS check_box:
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


      void input_checkbox::implement_phase1(html_data * pdata, ::html::element * pelement)
      {

         m_bHasChar = true;

         element::implement_phase1(pdata, pelement);

         ::atom atom = pelement->m_phtmlbase->get_tag()->get_attr_value("id");

         //atom = translate_property_id(atom);

         //atom = atom);

         if(!m_pcheckbox || !m_pcheckbox->is_window())
         {

            m_pcheckbox = __create_new < user::check_box > ();

            m_pcheckbox->m_pform = pdata->m_pcoredata->m_pform;

            m_pcheckbox->create_control(pdata->m_pcoredata->m_puserinteraction, atom);

            pdata->on_create_interaction(m_pcheckbox);

            bool bCheck = pelement->m_phtmlbase->get_tag()->get_attr("checked") != nullptr;

            if(bCheck)
            {

               m_pcheckbox->set_check(e_check_checked, ::action_context(::e_source_data) +  ::e_source_load);

            }
            else if(m_pcheckbox->echeck() == ::e_check_undefined)
            {

               m_pcheckbox->set_check(e_check_unchecked, ::action_context(::e_source_data) +  ::e_source_load);

            }

         }
         else
         {

            m_pcheckbox->id() = atom;

         }

         m_pcheckbox->m_strName = pelement->m_phtmlbase->get_tag()->get_attr_value("name");

         if(pdata->m_pcoredata->m_pform != nullptr)
         {

            auto pextendedtopic = create_extended_topic(::id_initialize_control);

            pextendedtopic->m_puserelement = m_pcheckbox;

            pextendedtopic->m_actioncontext = ::action_context(::e_source_data) +  ::e_source_load;

            pextendedtopic->m_uiEvent = 0;

            pdata->m_pcoredata->m_pform->route(pextendedtopic);

         }

      }


      bool input_checkbox::layout_phase1(html_data * pdata)
      {

         auto preferredDensity = m_pcheckbox->preferred_density();

         m_box.set_size(26 * preferredDensity, 26 * preferredDensity);

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

         //::int_rectangle rectangleWindow;
         //m_pcheckbox->window_rectangle(rectangleWindow);
  //       ::int_point pointPreviousContextOrg = pgraphics->get_origin();

    //     pgraphics->offset_origin((int) m_box.left(), (int) m_box.top());

         m_pcheckbox->_000CallOnDraw(pdata->m_pcoredata->m_pgraphics);

      //   pgraphics->set_origin(pointPreviousContextOrg);

      }


      void input_checkbox::on_change_layout(html_data * pdata)
      {

         __UNREFERENCED_PARAMETER(pdata);

         m_pcheckbox->place(m_box);

      }


   }


}



