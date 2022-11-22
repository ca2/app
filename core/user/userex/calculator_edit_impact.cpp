#include "framework.h"
#include "calculator_edit_impact.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
////#include "acme/exception/exception.h"
#include "axis/mathematics/calculator/parser.h"
#include "axis/mathematics/calculator/element.h"


namespace calculator
{


   plain_edit_impact::plain_edit_impact()
   {

      m_pcallback = nullptr;

      m_result.m_dR = 0.0;
      m_result.m_dI = 0.0;

   }


   plain_edit_impact::~plain_edit_impact()
   {

   }


   bool plain_edit_impact::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && is_window_visible();

   }


   ::payload plain_edit_impact::get_payload()
   {

      ::payload payload;

      payload["real"] = m_result.m_dR;
      payload["imaginary"] = m_result.m_dI;
      payload["text"] = ::user::plain_edit::get_payload();

      return payload;

   }


   void plain_edit_impact::install_message_routing(::channel * pchannel)
   {
    
      ::user::show < ::user::plain_edit >::install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &plain_edit_impact::on_message_create);
      
   }


   void plain_edit_impact::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

      auto pplaineditview = this;

      //auto ptopic = pplaineditview->topic(id_after_change_text);

      //ptopic->add_listener(this);

      add_handler(this);

   }


   void plain_edit_impact::set_format(const string& strFormat)
   {

      m_strFormat = strFormat;

   }


   void plain_edit_impact::set_callback(callback* pcallback)
   {

      m_pcallback = pcallback;

   }


   void plain_edit_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->m_atom == id_after_change_text)
      {

         {

            synchronous_lock synchronouslock(m_pcallback == nullptr ? nullptr : m_pcallback->synchronization());

            string strExp;

            _001GetText(strExp);

            auto pparser = __create_new< parser >();

            error e;

            e.m_iEnd = -1;
            e.m_iStart = -1;
            e.m_tick.Now();

            ::calculator::element * pcalculatorelement = nullptr;

            string strSource;

            if (strExp.ends_eat_ci("FPS"))
            {
               strSource = "Hz";
            }
            else if (strExp.ends_eat_ci("Frames Per Second"))
            {
               strSource = "Hz";
            }
            else if (strExp.ends_eat_ci("SPF"))
            {
               strSource = "s";
            }
            else if (strExp.ends_eat_ci("Seconds per frame"))
            {
               strSource = "s";
            }
            else if (strExp.ends_eat_ci("Hz"))
            {
               strSource = "Hz";
            }
            else if (strExp.ends_eat_ci("minute"))
            {
               strSource = "minimum";
            }
            else if (strExp.ends_eat_ci("minutes"))
            {
               strSource = "minimum";
            }
            else if (strExp.ends_eat_ci("minimum"))
            {
               strSource = "minimum";
            }
            else if (strExp.ends_eat_ci("mins"))
            {
               strSource = "minimum";
            }
            else if (strExp.ends_eat_ci("days"))
            {
               strSource = "day";
            }
            else if (strExp.ends_eat_ci("minutes"))
            {
               strSource = "minimum";
            }
            else if (strExp.ends_eat_ci("hours"))
            {
               strSource = "hour";
            }
            else if (strExp.ends_eat_ci("hour"))
            {
               strSource = "hour";
            }
            else if (strExp.ends_eat_ci("day"))
            {
               strSource = "day";
            }
            else if (strExp.ends_eat_ci("ms"))
            {
               strSource = "ms";
            }
            else if (strExp.ends_eat_ci("s"))
            {
               strSource = "s";
            }
            else
            {
               strSource = m_strFormat;
            }
            string strFormat(m_strFormat);

            if (strFormat.ends_eat_ci("FPS"))
            {
               strFormat = "Hz";
            }
            else if (strFormat.ends_eat_ci("Frames Per Second"))
            {
               strFormat = "Hz";
            }
            else if (strFormat.ends_eat_ci("SPF"))
            {
               strFormat = "s";
            }
            else if (strFormat.ends_eat_ci("Seconds per frame"))
            {
               strFormat = "s";
            }
            else if (strFormat.ends_eat_ci("Hz"))
            {
               strFormat = "Hz";
            }
            else if (strFormat.ends_eat_ci("s"))
            {
               strFormat = "s";
            }
            else
            {
               strFormat = m_strFormat;
            }
            
            strExp.trim();

            try
            {

               pcalculatorelement = pparser->parse(strExp);
               //throw ::exception(::exception("now a simple exception here"));

            }
            catch (const ::exception & exception)
            {

               e.m_strMessage = exception.get_message();
               e.m_iStart = 0;
               e.m_iEnd = strExp.length();


            }

            string str;

            if (pcalculatorelement != nullptr)
            {

               m_result = pcalculatorelement->get_result();

               str = strExp;

            }

            string strVal;
            bool bConv = true;

            if (e.m_iStart < 0)
            {

               if (strSource.has_char())
               {
                  if (strSource != strFormat)
                  {

                     if (strFormat == "s")
                     {
                        if (strSource == "Hz")
                        {
                           if (m_result.mod() == 0.0)
                           {
                              strVal = "(infinite)";
                           }
                           else
                           {
                              strVal = ::as_string(1.0 / m_result.mod());
                           }
                        }
                     }
                     else if (strFormat == "Hz")
                     {
                        if (m_result.mod() == 0.0)
                        {
                           strVal = "(infinite)";
                        }
                        else if (strSource == "ms")
                        {
                           m_result.m_dR = 1000.0 / m_result.m_dR;
                           m_result.m_dI = 0.0;
                           strVal = m_result.to_string();
                        }
                        else if (strSource == "s")
                        {
                           m_result.m_dR = 1.0 / m_result.m_dR;
                           m_result.m_dI = 0.0;
                           strVal = m_result.to_string();
                        }
                        else if (strSource == "minimum")
                        {
                           m_result.m_dR = 1.0 / (60.0 * m_result.m_dR);
                           m_result.m_dI = 0.0;
                           strVal = m_result.to_string();

                        }
                        else if (strSource == "hour")
                        {
                           m_result.m_dR = 1.0 / (60.0 * 60.0 * m_result.m_dR);
                           m_result.m_dI = 0.0;
                           strVal = m_result.to_string();
                        }
                        else if (strSource == "day")
                        {
                           m_result.m_dR = 1.0 / (24.0 * 60.0 * 60.0 * m_result.m_dR);
                           m_result.m_dI = 0.0;
                           strVal = m_result.to_string();
                        }
                        else
                        {
                           strVal = m_result.to_string();
                        }
                     }

                  }
               }
               else
               {
                  e.m_strMessage = "(unknown conversion)";
                  bConv = false;
                  strVal = m_result.to_string();
               }
            }
            else
            {
               strVal = m_result.to_string();
            }

            if (!bConv)
            {
               e.m_iStart = (strExp + string(" ")).length();
               e.m_iEnd = e.m_iStart + strSource.length();

            }
            str = strExp + string(" ") + strSource + string(" = ") + strVal;

            if (m_pcallback != nullptr)
            {

               if (m_strFormat.has_char())
               {

                  m_pcallback->set_expression(str + " " + m_strFormat);

               }
               else
               {

                  m_pcallback->set_expression(str);

               }

            }

            if (e.m_iStart >= 0)
            {
               m_errora.add(e);
            }
            else
            {
               m_errora.erase_all();
            }


         }

         /*         if(m_ptopview != nullptr)
                  {

                     m_ptopview->m_pimpact->post_message(message_impact_update);

                  }*/

      }

   }


   void plain_edit_impact::plain_edit_on_after_change_text(::draw2d::graphics_pointer& pgraphics, const ::action_context& context)
   {

      auto pplaineditview = this;

      auto ptopic = create_topic(id_after_change_text);

      ptopic->m_puserelement = this;

      route(ptopic);

      plain_edit::plain_edit_on_after_change_text(pgraphics, context);

   }


} // namespace calculator






