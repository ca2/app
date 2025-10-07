#pragma once


#include "base.h"



namespace html
{


   class value : 
      public base
   {
   public:


      ::collection::index             m_iIndex;
      string            m_strValue;


      value(class tag * pparent);
      virtual ~value();


      virtual type get_type();

      void set_value(const ::scoped_string & scopedstrValue);
      string get_value();

   };


} // namespace html


