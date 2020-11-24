#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif


namespace user
{

   ////////////////////////////////////////////////////////////
   //
   //   return nok rules
   //
   //   m_iMin - integer min
   //   m_iMax - integer max
   //
   //string_array validate::nok(const payload & val)
   //{

   //   string_array stra;

   //   if(m_rules.has_property("natural"))
   //   {

   //      if(val.get_string().is_empty())
   //      {

   //         stra.add("You should enter non negative integer.");

   //      }
   //      else
   //      {

   //         string str = val.get_string();

   //         for(index i = 0; i < str.length(); i++)
   //         {

   //            if(!ansi_char_is_digit(str[i]))
   //            {

   //               stra.add("You should enter non negative integer.");

   //               break;

   //            }

   //         }

   //      }

   //   }

   //   if(m_rules.has_property("m_iMin"))
   //   {

   //      if(val.i64() < m_rules["m_iMin"].i64())
   //      {

   //         string strText = "You should enter an integer greater or equal " + m_rules["m_iMin"].get_string();

   //         stra.add(strText);

   //      }

   //   }

   //   if(m_rules.has_property("m_iMax"))
   //   {

   //      if(val.i64() > m_rules["m_iMax"].i64())
   //      {

   //         string strText = "You should enter an integer lesser or equal " + m_rules["m_iMax"].get_string();

   //         stra.add(strText);

   //      }

   //   }


   //   return stra;

   //}


}
