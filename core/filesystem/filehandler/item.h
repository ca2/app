#pragma once


namespace filehandler
{


   class CLASS_DECL_CORE item :
      public ::data::item
   {
   public:


      enum id_type
      {
         topic_type_root,
         topic_type_extension,
         topic_type_mime_type
      };
      
      
      id_type   m_etopictype;
      string         m_strTopic;
      string_array        m_straHandlerLibrary;
      string_array        m_straMenuLibrary;
      string_array        m_straApp;


      string data_item_get_text(object * pobject) const;
     index data_item_get_image(object * pobject) const;


   

   };


} // namespace filehandler


inline binary_stream & operator <<(binary_stream & s, const ::filehandler::item & item)
{

   s << (::i32) item.m_etopictype;
   s << item.m_strTopic;
   s << item.m_straHandlerLibrary;
   s << item.m_straMenuLibrary;
   s << item.m_straApp;
   return s;

}


inline binary_stream & operator >>(binary_stream & s, ::filehandler::item & item)
{

   s >> (int &) item.m_etopictype;
   s >> item.m_strTopic;
   s >> item.m_straHandlerLibrary;
   s >> item.m_straMenuLibrary;
   s >> item.m_straApp;

   return s;

}




