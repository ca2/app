#pragma once


class context_object;


namespace papaya
{


   namespace property_set
   {


      inline bool get_string(string & strResult, const ::context_object& object, const string& strKey);
      inline bool get_string(string & strResult, const ::context_object& object, string& strKey);
      inline bool get_evaluation(string & strResult, const ::context_object& object, const string& strKey);
      inline bool get_evaluation(string & strResult, const ::context_object& object, string& strKey);
      inline bool get_evaluation(string & strResult, const ::property_set & set, string & strExpression);


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


      inline bool get_evaluation(string & strResult, const ::property_set & set, string & strExpression)
      {

         return get_evaluation(strResult, set, (const string &) strExpression);

      }


   } // namespace property_set


} // namespace papaya



