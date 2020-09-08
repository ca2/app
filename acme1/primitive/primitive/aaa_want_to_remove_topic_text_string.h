#pragma once


class CLASS_DECL_ACME topic_text_string :
   virtual public stick
{
public:


   string                        m_strTopicText;


   inline void set_topic_text(const char * psz) { m_strTopicText = psz; m_sticker.raw_set_topic_text(m_strTopicText); }


   inline void format_topic_text(const char * psz, ...)
   {
      
      va_list valist;
      va_start(valist, psz);
      string str;
      str.Format(psz, valist);
      set_topic_text(str);
      va_end(valist);

   }


};


template < typename TYPE >
TYPE & operator |=(TYPE & o, e_object eobject)
{

   o.set_flag(eobject);

   return o;

}


template < typename TYPE >
TYPE & operator +=(TYPE & o, e_object eobject)
{

   o.set_flag(eobject);

   return o;

}


template < typename TYPE >
TYPE & operator -=(TYPE & o, e_object eobject)
{

   o.clear_flag(eobject);

   return o;

}



