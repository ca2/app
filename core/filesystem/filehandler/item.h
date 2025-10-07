#pragma once


//#include "acme/prototype/collection/string_array.h"
#include "acme/handler/item.h"



namespace filehandler
{


   class CLASS_DECL_CORE item :
      public ::item
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
      string_array_base        m_straHandlerLibrary;
      string_array_base        m_straMenuLibrary;
      string_array_base        m_straApp;


      string get_item_text(object * pparticle) const;
     ::collection::index get_item_image(object * pparticle) const;


   

   };


} // namespace filehandler


