#pragma once


//#include "acme/primitive/collection/string_array.h"
#include "acme/primitive/data/item.h"



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


      string data_item_get_text(object * pparticle) const;
     index data_item_get_image(object * pparticle) const;


   

   };


} // namespace filehandler


