#pragma once

#ifdef new
#undef new
#endif

#define new ACME_NEW


namespace factory
{


   CLASS_DECL_ACME critical_section * get_factory_critical_section();


} // namespace factory


template < typename TYPE, typename BASE_TYPE>
inline __pointer(::factory::factory_base < BASE_TYPE >) create_factory(const ::id & id)
{

   critical_section_lock lock(::factory::get_factory_critical_section());

   auto pfactory = __new(::factory::factory< TYPE, BASE_TYPE >());

   ::factory::get_factory_map()->set_at(id, pfactory);

   return pfactory;

}


template < typename TYPE, typename BASE_TYPE>
inline __pointer(::factory::factory_base < BASE_TYPE >) create_factory()
{

   critical_section_lock lock(::factory::get_factory_critical_section());

   auto pfactory = __new(::factory::factory< TYPE, BASE_TYPE >());

   ::factory::get_factory < BASE_TYPE >() = pfactory;

   return pfactory;

}


template < typename TYPE, typename BASE_TYPE>
inline __pointer(::factory::factory_base < BASE_TYPE >) create_reusable_factory()
{

   critical_section_lock lock(::factory::get_factory_critical_section());

   auto pfactory = __new(::factory::reusable_factory< TYPE, BASE_TYPE >());

   ::factory::get_factory < BASE_TYPE >() = pfactory;

   return pfactory;

}




template < typename TYPE1, typename TYPE2 >
inline void __dynamic_cast(TYPE1*& ptype1, const __pointer(TYPE2)& ptype2)
{

   ptype1 = ptype2.template cast < TYPE1 >().m_p;

}


class context_object;


namespace papaya
{


   namespace property_set
   {


      inline string get_string(const ::context_object & object, const string & strKey);

      // ::property_set set;
      //
      // set["var5"] = "searching value";
      //
      // str = "SELECT field1, field2, field3 FROM table1 WHERE table1.field5 = '$var5'"
      //
      // real-ization: "SELECT field1, field2, field3 FROM table1 WHERE table1.field5 = 'searching value'"
      template < typename PROPERTY_SOURCE >
      string evaluate(const PROPERTY_SOURCE & set, const string & strSource)
      {

         string str(strSource);

         strsize iPos;

         char ch;

         char chNext;

         for (iPos = 0; iPos < str.get_length(); iPos++)
         {

            ch = str[iPos];

            if (iPos + 1 < str.get_length())
            {

               chNext = str[iPos + 1];

            }
            else
            {

               chNext = '\0';

            }

            if (ch == '\\')
            {

               iPos++;

               continue;

            }
            else if (ch == '{' && chNext == '$')
            {

               strsize iEnd = str.find('}', iPos + 1);

               if (iEnd < 0)
               {

                  //error

                  break;

               }

               string strKey = str.Mid(iPos + 2, iEnd - iPos - 2);

               string strEval;

               if (get_string(strEval, set, strKey))
               {

                  str = str.Left(iPos) + strEval + str.Mid(iEnd + 1);

                  iPos += strEval.get_length() - 1;

               }
               else
               {

                  iPos = iEnd;

               }


            }
            else if (ch == '$')
            {

               if (!(ansi_char_is_alphabetic(chNext) || chNext == '_'))
               {

                  // error

                  break;

               }

               strsize iStart = iPos;

               strsize iEnd = iStart + 2;

               for (; iEnd < str.get_length(); iEnd++)
               {

                  ch = str[iEnd];

                  if (!(ansi_char_is_alphabetic(ch) || ch == '_' || ansi_char_is_digit(ch)))
                  {

                     break;

                  }

               }

               string strExpression = str.Mid(iStart, iEnd - iStart);

               string strEval;

               if (get_evaluation(strEval, set, strExpression))
               {

                  str = str.Left(iPos) + strEval + str.Mid(iEnd);

                  iPos += strEval.get_length() - 1;

               }
               else
               {

                  iPos = iEnd;

               }

            }

         }

         return str;

      }




   } // namespace property_set


} // namespace papaya



namespace factory
{


   template < typename TYPE, typename BASE_TYPE >
   inline __pointer(BASE_TYPE) reusable_factory < TYPE, BASE_TYPE >::_call_new()
   {

      {

         critical_section_lock lock(&m_criticalsection);

         if (m_pfree)
         {

            auto pNew = m_pfree;

            m_pfree = pNew->m_pnext;

            pNew->reuse();

            return pNew;

         }

      }

      return factory < TYPE, BASE_TYPE >::_call_new();

   }


   template < typename TYPE, typename BASE_TYPE >
   inline void reusable_factory < TYPE, BASE_TYPE >::return_back(BASE_TYPE * p)
   {

      critical_section_lock lock(&m_criticalsection);

      p->m_pnext = m_pfree;

      m_pfree = p;

   }


} // namespace factory



