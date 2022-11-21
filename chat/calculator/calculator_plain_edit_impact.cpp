#include "framework.h"


namespace calculator
{


   plain_edit_impact::plain_edit_impact(::particle * pparticle):
      object(pparticle),
      ::user::interaction(pparticle),
      ::user::plain_edit(pparticle)
   {

      m_pcallback = nullptr;

      m_val.m_dR = 0.0;
      m_val.m_dI = 0.0;

   }

   plain_edit_impact::~plain_edit_impact()
   {

   }


   void plain_edit_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      if(eupdate == 2000)
      {

         {

            synchronous_lock synchronouslock(m_pcallback == nullptr ? nullptr : m_pcallback->get_mutex());

            string strExp;

            _001GetText(strExp);


            parser parser(this);

            error e;

            e.m_iEnd = -1;
            e.m_iStart = -1;
            e.m_dwTime= ::get_tick();

            ::calculator::matter * pmatter = nullptr;

            string strSource;

            if(strExp.ends_eat_ci("FPS"))
            {
               strSource = "Hz";
            }
            else if(strExp.ends_eat_ci("Frames Per Second"))
            {
               strSource = "Hz";
            }
            else if(strExp.ends_eat_ci("SPF"))
            {
               strSource = "s";
            }
            else if(strExp.ends_eat_ci("Seconds per frame"))
            {
               strSource = "s";
            }
            else if(strExp.ends_eat_ci("Hz"))
            {
               strSource = "Hz";
            }
            else if(strExp.ends_eat_ci("minute"))
            {
               strSource = "minimum";
            }
            else if(strExp.ends_eat_ci("days"))
            {
               strSource = "day";
            }
            else if(strExp.ends_eat_ci("minutes"))
            {
               strSource = "minimum";
            }
            else if(strExp.ends_eat_ci("hours"))
            {
               strSource = "hour";
            }
            else if(strExp.ends_eat_ci("hour"))
            {
               strSource = "hour";
            }
            else if(strExp.ends_eat_ci("day"))
            {
               strSource = "day";
            }
            else if(strExp.ends_eat_ci("ms"))
            {
               strSource = "ms";
            }
            else if(strExp.ends_eat_ci("s"))
            {
               strSource = "s";
            }
            else
            {
               strSource = m_strFormat;
            }
            string strFormat(m_strFormat);

            if(strFormat.ends_eat_ci("FPS"))
            {
               strFormat = "Hz";
            }
            else if(strFormat.ends_eat_ci("Frames Per Second"))
            {
               strFormat = "Hz";
            }
            else if(strFormat.ends_eat_ci("SPF"))
            {
               strFormat = "s";
            }
            else if(strFormat.ends_eat_ci("Seconds per frame"))
            {
               strFormat = "s";
            }
            else if(strFormat.ends_eat_ci("Hz"))
            {
               strFormat = "Hz";
            }
            else if(strFormat.ends_eat_ci("s"))
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

               pmatter = parser.parse(strExp);

            }
            catch(numeric_parsing_exception & exp)
            {

               e.m_strMessage = exp.m_strMessage;
               e.m_iStart = 0;
               e.m_iEnd = strExp.length();

            }

            string str;

            if(pmatter != nullptr)
            {

               m_val = pmatter->get_value();

               str = strExp;

            }

            string strVal;
            bool bConv = true;

            if(e.m_iStart < 0)
            {

               if(strSource.has_char())
               {
                  if(strSource != strFormat)
                  {

                     if(strFormat == "s")
                     {
                        if(strSource == "Hz")
                        {
                           if(m_val.mod() == 0.0)
                           {
                              strVal = "(infinite)";
                           }
                           else
                           {
                              strVal = as_string(1.0 / m_val.mod());
                           }
                        }
                     }
                     else if(strFormat == "Hz")
                     {
                        if(m_val.mod() == 0.0)
                        {
                           strVal = "(infinite)";
                        }
                        else if(strSource == "ms")
                        {
                           m_val.m_dR = 1000.0 / m_val.m_dR;
                           m_val.m_dI = 0.0;
                           strVal = m_val.to_string();
                        }
                        else if(strSource == "s")
                        {
                           m_val.m_dR = 1.0 / m_val.m_dR;
                           m_val.m_dI = 0.0;
                           strVal = m_val.to_string();
                        }
                        else if(strSource == "minimum")
                        {
                           m_val.m_dR = 1.0 / (60.0 * m_val.m_dR);
                           m_val.m_dI = 0.0;
                           strVal = m_val.to_string();

                        }
                        else if(strSource == "hour")
                        {
                           m_val.m_dR = 1.0 / (60.0 * 60.0 * m_val.m_dR);
                           m_val.m_dI = 0.0;
                           strVal = m_val.to_string();
                        }
                        else if(strSource == "day")
                        {
                           m_val.m_dR = 1.0 / (24.0 * 60.0 * 60.0 * m_val.m_dR);
                           m_val.m_dI = 0.0;
                           strVal = m_val.to_string();
                        }
                        else
                        {
                           strVal = m_val.to_string();
                        }
                     }

                  }
               }
               else
               {
                  e.m_strMessage = "(unknown conversion)";
                  bConv = false;
                  strVal = m_val.to_string();
               }
            }
            else
            {
               strVal = m_val.to_string();
            }

            if(!bConv)
            {
               e.m_iStart = (strExp + string(" ")).length();
               e.m_iEnd = e.m_iStart + strSource.length();

            }
            str = strExp + string(" ") + strSource + string(" = ") + strVal;

            if(m_pcallback != nullptr)
            {

               if(m_strFormat.has_char())
               {

                  m_pcallback->set_expression(str + " " + m_strFormat);

               }
               else
               {

                  m_pcallback->set_expression(str);

               }

            }

            if(e.m_iStart >= 0)
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


   void plain_edit_impact::_001OnAfterChangeText(const ::action_context & context)
   {

      if(context.is_user_source())
      {


         //      if(m_ptopview == nullptr || m_ptopview->m_pimpact == nullptr)
         //       return;

         on_update(nullptr,2000,nullptr);

      }

      plain_edit::_001OnAfterChangeText(context);
   }


   bool plain_edit_impact::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && is_window_visible();

   }


   i64 plain_edit_impact::increment_reference_count()
   {
      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
   }
   i64 plain_edit_impact::decrement_reference_count()
   {
      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
   }



} // namespace calculator




