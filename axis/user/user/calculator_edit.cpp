#include "framework.h"
#include "calculator_edit.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/synchronous_lock.h"
#include "axis/mathematics/calculator/parser.h"
#include "axis/mathematics/calculator/element.h"


namespace calculator
{


   edit::edit()
   {

      m_pcallback = nullptr;

      m_result.m_dR = 0.0;
      m_result.m_dI = 0.0;

   }


   edit::~edit()
   {

   }


   bool edit::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && is_window_visible();

   }


   ::payload edit::get_payload()
   {

      ::payload payload;

      payload["real"] = m_result.m_dR;
      payload["imaginary"] = m_result.m_dI;
      payload["text"] = ::user::plain_edit::get_payload();

      return payload;

   }


   void edit::install_message_routing(::channel * pchannel)
   {
    
      ::user::plain_edit::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &edit::on_message_create);
      
   }


   void edit::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

      auto pplaineditview = this;

      //auto ptopic = pplaineditview->topic(id_after_change_text);

      //ptopic->add_listener(this);

      add_handler(this);

   }


   void edit::set_format(const string& strFormat)
   {

      m_strFormat = strFormat;

   }


   void edit::set_callback(callback* pcallback)
   {

      m_pcallback = pcallback;

   }


   void edit::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->id() == id_after_change_text)
      {

         {

            synchronous_lock synchronouslock(m_pcallback == nullptr ? nullptr : m_pcallback->synchronization());

            string strExp;

            strExp = as_text();

            auto pparser = __create_new< parser >();

            ::pointer < ::user::plain_edit_error > perror;

            ::calculator::element * pcalculatorelement = nullptr;

            string strSource;

            if (strExp.case_insensitive_ends_eat("FPS"))
            {
               
               strSource = "Hz";

            }
            else if (strExp.case_insensitive_ends_eat("Frames Per Second"))
            {
               
               strSource = "Hz";

            }
            else if (strExp.case_insensitive_ends_eat("SPF"))
            {
               
               strSource = "s";

            }
            else if (strExp.case_insensitive_ends_eat("Seconds per frame"))
            {
               
               strSource = "s";

            }
            else if (strExp.case_insensitive_ends_eat("Hz"))
            {
               
               strSource = "Hz";

            }
            else if (strExp.case_insensitive_ends_eat("minute"))
            {
               
               strSource = "minimum";

            }
            else if (strExp.case_insensitive_ends_eat("minutes"))
            {
               
               strSource = "minimum";

            }
            else if (strExp.case_insensitive_ends_eat("minimum"))
            {
               
               strSource = "minimum";

            }
            else if (strExp.case_insensitive_ends_eat("mins"))
            {
               
               strSource = "minimum";

            }
            else if (strExp.case_insensitive_ends_eat("days"))
            {
               
               strSource = "day";

            }
            else if (strExp.case_insensitive_ends_eat("minutes"))
            {
               
               strSource = "minimum";

            }
            else if (strExp.case_insensitive_ends_eat("hours"))
            {
               
               strSource = "hour";

            }
            else if (strExp.case_insensitive_ends_eat("hour"))
            {
               
               strSource = "hour";

            }
            else if (strExp.case_insensitive_ends_eat("day"))
            {
               
               strSource = "day";

            }
            else if (strExp.case_insensitive_ends_eat("ms"))
            {
               
               strSource = "ms";

            }
            else if (strExp.case_insensitive_ends_eat("s"))
            {
               
               strSource = "s";

            }
            else
            {
               
               strSource = m_strFormat;

            }
            
            string strFormat(m_strFormat);

            if (strFormat.case_insensitive_ends_eat("FPS"))
            {
               
               strFormat = "Hz";

            }
            else if (strFormat.case_insensitive_ends_eat("Frames Per Second"))
            {
               
               strFormat = "Hz";

            }
            else if (strFormat.case_insensitive_ends_eat("SPF"))
            {
               
               strFormat = "s";

            }
            else if (strFormat.case_insensitive_ends_eat("Seconds per frame"))
            {
               
               strFormat = "s";

            }
            else if (strFormat.case_insensitive_ends_eat("Hz"))
            {
               
               strFormat = "Hz";

            }
            else if (strFormat.case_insensitive_ends_eat("s"))
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

               perror = __create_new < ::user::plain_edit_error >();
               
               perror->m_strMessage = exception.get_message();
               perror->m_iStart = 0;
               perror->m_iEnd = strExp.length();


            }

            string str;

            if (pcalculatorelement != nullptr)
            {

               m_result = pcalculatorelement->get_result();

               str = strExp;

            }

            string strVal;
            bool bConv = true;

            if (::is_null(perror))
            {

               if (strSource.has_character())
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
                  if (!perror)
                  {
                     perror = __create_new < ::user::plain_edit_error >();

                  }
                  perror->m_strMessage = "(unknown conversion)";
                  perror->m_iStart = -1;
                  perror->m_iEnd = -1;
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
               if (!perror)
               {

                  perror = __create_new < ::user::plain_edit_error >();

               }
               perror->m_iStart = (strExp + string(" ")).length();
               perror->m_iEnd = perror->m_iStart + strSource.length();

            }
            str = strExp + string(" ") + strSource + string(" = ") + strVal;

            if (m_pcallback != nullptr)
            {

               if (m_strFormat.has_character())
               {

                  m_pcallback->set_expression(str + " " + m_strFormat);

               }
               else
               {

                  m_pcallback->set_expression(str);

               }

            }

            if (::is_set(perror))
            {
               m_errora.add(perror);
            }
            else
            {
               m_errora.erase_all();
            }


         }

         /*         if(m_ptopimpact != nullptr)
                  {

                     m_ptopimpact->m_pimpact->post_message(message_impact_update);

                  }*/

      }

   }


   void edit::plain_edit_on_after_change_text(::draw2d::graphics_pointer& pgraphics, const ::action_context& context)
   {

      auto pplaineditview = this;

      auto ptopic = create_topic(id_after_change_text);

      ptopic->m_puserelement = this;

      route(ptopic);

      plain_edit::plain_edit_on_after_change_text(pgraphics, context);

   }


} // namespace calculator






