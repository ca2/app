#pragma once


class property_object;


namespace acme
{


   namespace ::property_set
   {


      inline bool get_string(string & strResult, const ::property_object& object, const ::scoped_string & scopedstrKey);
      inline bool get_string(string & strResult, const ::property_object& object, string& strKey);
      inline bool get_evaluation(string & strResult, const ::property_object& object, const ::scoped_string & scopedstrKey);
      inline bool get_evaluation(string & strResult, const ::property_object& object, string& strKey);
      inline bool get_evaluation(string & strResult, const ::property_set & set, string & strExpression);


      inline string get_string(const ::property_set & set, const ::scoped_string & scopedstrKey)
      {

         return set[strKey];

      }


      //inline string get_string(const ::matter & matter, const ::scoped_string & scopedstrKey)
      //{

      //   return matter.property_set_get_string(strKey);

      //}


      inline bool get_string(string & strResult, const ::property_set & set, const ::scoped_string & scopedstrKey)
      {

         return set.get_string(strResult, strKey);

      }


      inline bool get_evaluation(string & strResult, const ::property_set & set, const ::scoped_string & scopedstrExpression)
      {

         auto pproperty = set.find_property(strExpression);

         if (::is_null(pproperty))
         {

            return false;

         }

         strResult = *pproperty;

         return true;

      }


      inline bool get_evaluation(string & strResult, const ::property_set & set, string & strExpression)
      {

         return get_evaluation(strResult, set, (const string &) strExpression);

      }


   } // namespace ::property_set


} // namespace acme




#pragma once


namespace acme
{


   namespace ::property_set
   {


      //inline string get_string(const ::property_set & set, const ::scoped_string & scopedstrKey)
      //{

      //   return set[strKey].get_string();

      //}


      inline string get_string(const ::property_object & object, const ::scoped_string & scopedstrKey)
      {

         return object.property_set_get_string(strKey);

      }


      inline bool get_string(string & strResult, const ::property_object& object, const ::scoped_string & scopedstrKey)
      {

         return object.property_set_get_string(strResult, strKey);

      }


      inline bool get_string(string & strResult, const ::property_object& object, string& strKey)
      {

         return object.property_set_get_string(strResult, strKey);

      }



      inline bool get_evaluation(string & strResult, const ::property_object& object, const ::scoped_string & scopedstrKey)
      {

         return object.property_set_get_evaluation(strResult, strKey);

      }


      inline bool get_evaluation(string & strResult, const ::property_object& object, string& strKey)
      {

         return get_evaluation(strResult, object, (const string &)strKey);

      }



      //inline bool get_evaluation(string & strResult, const ::property_set & set, const ::scoped_string & scopedstrExpression)
      //{

      //   auto pproperty = set.find_property(strExpression);

      //   if (::is_null(pproperty))
      //   {

      //      return false;

      //   }

      //   strResult = pproperty->get_string();

      //   return true;

      //}


      inline string get_evaluation(const ::property_object & object, const ::scoped_string & scopedstrExpression)
      {

         return object.property_set_get_evaluation(strExpression);

      }


      //// ::property_set set;
      ////
      //// set["var5"] = "searching value";
      ////
      //// str = "SELECT field1, field2, field3 FROM table1 WHERE table1.field5 = '$var5'"
      ////
      //// real-ization: "SELECT field1, field2, field3 FROM table1 WHERE table1.field5 = 'searching value'"
      //template < typename PROPERTY_SOURCE >
      //string evaluate(const PROPERTY_SOURCE & set, const ::scoped_string & scopedstrSource)
      //{

      //   string str(strSource);

      //   character_count iPos;

      //   char ch;

      //   char chNext;

      //   for (iPos = 0; iPos < str.length(); iPos++)
      //   {

      //      ch = str[iPos];

      //      if (iPos + 1 < str.length())
      //      {

      //         chNext = str[iPos + 1];

      //      }
      //      else
      //      {

      //         chNext = '\0';

      //      }

      //      if (ch == '\\')
      //      {

      //         iPos++;

      //         continue;

      //      }
      //      else if (ch == '{' && chNext == '$')
      //      {

      //         character_count iEnd = str.find('}', iPos + 1);

      //         if (iEnd < 0)
      //         {

      //            //error

      //            break;

      //         }

      //         string strKey = str.substr(iPos + 2, iEnd - iPos - 2);

      //         string strEval;

      //         if (get_string(strEval, set, strKey))
      //         {

      //            str = str.left(iPos) + strEval + str.substr(iEnd + 1);

      //            iPos += strEval.length() - 1;

      //         }
      //         else
      //         {

      //            iPos = iEnd;

      //         }


      //      }
      //      else if (ch == '$')
      //      {

      //         if (!(ansi_char_isalpha(chNext) || chNext == '_'))
      //         {

      //            // error

      //            break;

      //         }

      //         character_count iStart = iPos;

      //         character_count iEnd = iStart + 2;

      //         for (; iEnd < str.length(); iEnd++)
      //         {

      //            ch = str[iEnd];

      //            if (!(ansi_char_isalpha(ch) || ch == '_' || ansi_char_isdigit(ch)))
      //            {

      //               break;

      //            }

      //         }

      //         string strExpression = str.substr(iStart, iEnd - iStart);

      //         string strEval;

      //         if (get_evaluation(strEval, set, strExpression))
      //         {

      //            str = str.left(iPos) + strEval + str.substr(iEnd);

      //            iPos += strEval.length() - 1;

      //         }
      //         else
      //         {

      //            iPos = iEnd;

      //         }

      //      }

      //   }

      //   return str;

      //}




   } // namespace ::property_set


} // namespace acme







