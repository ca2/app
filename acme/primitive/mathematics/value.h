#pragma once


// #include "acme/primitive/string/string.h"


namespace mathematics
{


   class value_impl;


   class CLASS_DECL_ACME value
   {
   public:


      enum e_get_value
      {
         get_value_formula,
         get_value_number,
      };


      value_impl * m_pimpl;


      void parse_numeric_formula(const ::scoped_string & scopedstr);

      virtual void set_value_string(const ::scoped_string & scopedstr);
      virtual string get_value_string(e_get_value egetvalue);



   };



   class CLASS_DECL_ACME value_impl :
      virtual public value
   {
   public:
      



      string m_str;


      value_impl();
      virtual ~value_impl();


      virtual void set_value_string(const ::scoped_string & scopedstr);
      virtual string get_value_string(e_get_value egetvalue);



   };


} // namespace mathematics



