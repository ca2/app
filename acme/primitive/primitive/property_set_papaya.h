#pragma once


namespace papaya
{


   namespace property_set
   {


      inline string get_string(const ::property_set & set, const string & strKey)
      {

         return set[strKey].get_string();

      }


      //inline string get_string(const ::generic & generic, const string & strKey)
      //{

      //   return generic.property_set_get_string(strKey);

      //}


      inline bool get_string(string & strResult, const ::property_set& set, const string& strKey)
      {

         return set.get_string(strResult, strKey);

      }


      inline bool get_evaluation(string & strResult, const ::property_set & set, const string & strExpression)
      {

         auto pproperty = set.find_property(strExpression);

         if (::is_null(pproperty))
         {

            return false;

         }

         strResult = pproperty->get_string();

         return true;

      }


   } // namespace property_set


} // namespace papaya



