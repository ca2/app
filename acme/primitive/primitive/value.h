#pragma once


namespace mathematics
{


   class value_impl;


   class value
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



   class value_impl :
      virtual public value
   {
   public:


      string m_str;


      virtual void set_value_string(const ::scoped_string & scopedstr);
      virtual string get_value_string(e_get_value egetvalue);



   };


} // namespace mathematics


