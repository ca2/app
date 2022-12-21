#include "framework.h"
#include "value.h"
#include "number.h"
#include "acme/primitive/collection/address_array.h"
#include "acme/exception/not_implemented.h"
#if defined(LINUX)
#include <ctype.h>
#endif

//#include "acme/exception/not_implemented.h"


namespace mathematics
{


   void value::set_value_string(const ::scoped_string & scopedstr)
   {

      m_pimpl->set_value_string(scopedstr);

   }


   string value::get_value_string(e_get_value egetvalue)
   {

      return m_pimpl->get_value_string(egetvalue);

   }


   value_impl::value_impl()
   {


   }

   value_impl::~value_impl()
   {


   }


   void value_impl::set_value_string(const ::scoped_string & scopedstr)
   {

      m_str = scopedstr;

   }


   string value_impl::get_value_string(e_get_value egetvalue)
   {

      return m_str;

   }


   void value::parse_numeric_formula(const ::scoped_string & scopedstr)
   {
//      i32 iOpen               = 0;
      //    bool bLeft              = false;
      //  bool bNumber            = false;
      m_pimpl                 = memory_new number();
//      const ::scoped_string & scopedstrNumber  = nullptr;
      //    value_impl * pimpl      = m_pimpl;

      string strNumber;
//      binary_operation * pbinopNew;
      address_array < number * > stackptra;

      throw ::not_implemented();

      /*

      while(*psz != '\0')
      {
         if(isdigit(*psz))
         {
            if(!bNumber)
            {
               pszNumber = psz;
               bNumber = true;
            }
         }
         else if(!isdigit(*psz))
         {
            if(bNumber)
            {
               string str(pszNumber, psz - pszNumber - 1);
               strNumber = str;
               if(dynamic_cast < binary_operation * > (pimpl) != nullptr)
               {
                  dynamic_cast < binary_operation * > (pimpl)->m_pvalue2 = memory_new number();
                  dynamic_cast < binary_operation * > (pimpl)->m_pvalue2->set_value_string(strNumber);
                  dynamic_cast < binary_operation * > (pimpl)->m_pvalue2->m_pbinop = dynamic_cast < binary_operation * > (pimpl);
                  pimpl = dynamic_cast < binary_operation * > (pimpl)->m_pvalue2;

               }
               else(dynamic_cast < number * > (pimpl) != nullptr)
               {
                  dynamic_cast < number * > (pimpl)->set_value_string(strNumber);
               }
            }
            if(*psz == '(')
            {
               stackptra.Push(pimpl);
            }
            else if(*psz == ')')
            {
               pimpl = stackptra.Pop();
            }
            else if(*psz == '+')
            {
               ASSERT(dynamic_cast < number * > (pimpl) != nullptr);
               pbinopNew = memory_new binary_operation;
               pbinopNew->m_etype = binary_operation::type_addition;
               pbinopNew->m_pvalue1 = dynamic_cast < number * > (pimpl);
            }
            else if(*psz == '-')
            {
               ASSERT(dynamic_cast < number * > (pimpl) != nullptr);
               pbinopNew = memory_new binary_operation;
               pbinopNew->m_etype = binary_operation::type_subtraction;
               pbinopNew->m_pvalue1 = dynamic_cast < number * > (pimpl);
            }
            else if(*psz == '*')
            {
               ASSERT(dynamic_cast < number * > (pimpl) != nullptr);
               pbinopNew = memory_new binary_operation;
               pbinopNew->m_etype = binary_operation::type_multiplication;
               pbinopNew->m_pvalue1 = dynamic_cast < number * > (pimpl);
            }
            else if(*psz == '/')
            {
               ASSERT(dynamic_cast < number * > (pimpl) != nullptr);
               pbinopNew = memory_new binary_operation;
               pbinopNew->m_etype = binary_operation::type_division;
               pbinopNew->m_pvalue1 = dynamic_cast < number * > (pimpl);
            }

         }
      }*/

   }


} // namespace mathematics




