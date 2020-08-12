#pragma once


namespace html
{


   class value : 
      public base
   {
   public:


      index             m_iIndex;
      string            m_strValue;


      value(class tag * pparent);
      virtual ~value();


      virtual type get_type();

      void set_value(const char * pszValue);
      string get_value();

   };


} // namespace html


