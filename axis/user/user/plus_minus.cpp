// From design/text_format/user_plus_minus.cpp by camilo on
// 2022-09-04 00:14 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "plus_minus.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "aura/message/user.h"
#include "aura/user/user/button.h"
#include "aura/user/user/still.h"


namespace user
{


   plus_minus::plus_minus()
   {

      m_bLabel = true;

      m_i = 100;
      m_iMin = 0;
      m_iMax = 100;
      m_iStep = 5;


   }


   plus_minus::~plus_minus()
   {

   }


   void plus_minus::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &::user::plus_minus::on_message_create);

   }


   void plus_minus::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (m_bLabel)
      {

         m_puiLabel = m_pstill;

         m_pstill->create_control(get_parent(), "still_" + m_atom);

      }

      m_pbuttonMinus->create_control(this, m_atom + "_minus");

      m_pbuttonMinus->set_window_text("-");

      m_pbuttonPlus->create_control(this, m_atom + "_plus");

      m_pbuttonPlus->set_window_text("+");

   }


   void plus_minus::set_value(int iValue, const ::action_context & context)
   {

      m_i = iValue;

      on_update();

      auto ptopic = create_topic(::id_action);

      ptopic->m_puserelement = this;

      ptopic->m_actioncontext = context;

      route(ptopic);

   }


   void plus_minus::on_update()
   {

      int i = m_i;

      __sort(m_iMin, m_iMax);

      if (m_iStep <= 0)
      {

         m_iStep = 1;

      }

      i = m_iMin + (i - m_iMin) / m_iStep * m_iStep;

      if (m_iMin == m_iMax)
      {

         i = m_iMin;

         m_pbuttonMinus->enable_window(false);
         m_pbuttonPlus->enable_window(false);

      }
      else if (i <= m_iMin)
      {

         i = m_iMin;

         m_pbuttonMinus->enable_window(false);
         m_pbuttonPlus->enable_window(true);

      }
      else if (i >= m_iMax)
      {

         i = m_iMax;

         m_pbuttonMinus->enable_window(true);
         m_pbuttonPlus->enable_window(false);

      }
      else
      {

         m_pbuttonMinus->enable_window(true);
         m_pbuttonPlus->enable_window(true);

      }

      m_i = i;

      if (m_bLabel)
      {

         m_pstill->set_window_text(calc_still_label());

      }

   }


   string plus_minus::calc_still_label()
   {

      __sort(m_iMin, m_iMax);

      if (m_i >= m_iMax)
      {

         if (m_strMax.has_char())
         {

            return m_strMax;

         }

      }
      else if (m_i <= m_iMin)
      {

         if (m_strMin.has_char())
         {

            return m_strMin;

         }

      }

      if (m_strFormat.has_char())
      {

         string str;

         str.format(m_strFormat, m_i);

         return str;

      }

      return "";

   }


   void plus_minus::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      int wPadding = 10;

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      int iM = rectangleClient.center().x;

      ::rectangle_i32 rectangleL(rectangleClient);

      rectangleL.right = iM - wPadding / 2;

      m_pbuttonMinus->order_top_most();
      
      m_pbuttonMinus->place(rectangleL);
      
      m_pbuttonMinus->display();

      ::rectangle_i32 rectangleR(rectangleClient);

      rectangleR.left = iM + wPadding / 2;

      m_pbuttonPlus->order_top();
      
      m_pbuttonPlus->place(rectangleR);
      
      m_pbuttonPlus->display();

   }


   void plus_minus::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->m_atom == ::id_click)
      {

         if (ptopic->user_interaction() == m_pbuttonMinus || ptopic->user_interaction() == m_pbuttonPlus)
         {

            int i = m_i;

            if (m_iStep <= 0)
            {

               m_iStep = 1;

            }

            if (ptopic->user_interaction() == m_pbuttonMinus)
            {

               i -= m_iStep;

            }
            else
            {

               i += m_iStep;

            }

            set_value(i, ::e_source_user);

            ptopic->m_bRet = true;

            return;

         }

      }

      ::user::interaction::handle(ptopic, pcontext);

   }


} //  namespace user



