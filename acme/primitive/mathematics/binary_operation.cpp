#include "framework.h"
#include "binary_operation.h"


namespace mathematics
{


   binary_operation::binary_operation()
   {
      m_pimpl = new value_impl;
   }

   binary_operation::~binary_operation()
   {
      delete m_pimpl;
   }

   
   void binary_operation::set_value_string(const char * psz)
   {
      
      __throw(error_not_implemented, "not implemented");

   }


   string binary_operation::get_value_string(e_get_value egetvalue)
   {
      if(egetvalue == get_value_formula)
      {
         if(m_etype == type_addition)
         {
            return "(" + m_pvalue1->get_value_string(egetvalue) + " + " +
                   m_pvalue2->get_value_string(egetvalue) + ")";
         }
         else if(m_etype == type_subtraction)
         {
            return "(" + m_pvalue1->get_value_string(egetvalue) + " - " +
                   m_pvalue2->get_value_string(egetvalue) + ")";
         }
         else if(m_etype == type_multiplication)
         {
            return "(" + m_pvalue1->get_value_string(egetvalue) + " * " +
                   m_pvalue2->get_value_string(egetvalue) + ")";
         }
         else if(m_etype == type_division)
         {
            return "(" + m_pvalue1->get_value_string(egetvalue) + " / " +
                   m_pvalue2->get_value_string(egetvalue) + ")";
         }
         else
         {
            return "";
         }
      }
      else
      {
         double d = 0.0;
         if(m_etype == type_addition)
         {
            d = atof(m_pvalue1->get_value_string(egetvalue)) +
                   atof(m_pvalue2->get_value_string(egetvalue));
         }
         else if(m_etype == type_subtraction)
         {
            d = atof(m_pvalue1->get_value_string(egetvalue)) - 
                   atof(m_pvalue2->get_value_string(egetvalue));
         }
         else if(m_etype == type_multiplication)
         {
            d = atof(m_pvalue1->get_value_string(egetvalue)) *
                   atof(m_pvalue2->get_value_string(egetvalue));
         }
         else if(m_etype == type_division)
         {
            d = atof(m_pvalue1->get_value_string(egetvalue)) /
                   atof(m_pvalue2->get_value_string(egetvalue));
         }
         string str;
         str.Format("%d", d);
         return str;

      }
   }

} // namespace mathematics
