#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_filehandler.h"
#endif


namespace filehandler
{


   string item::data_item_get_text(object * pobject) const
   {

      __UNREFERENCED_PARAMETER(pobject);

      return m_strTopic;

   }


   index item::data_item_get_image(object * pobject) const
   {

      return -1;

   }


   //stream & item::write(stream & s) const
   //{



   //   return s;

   //}


   //stream & item::read(stream & s)
   //{

   //   s >> m_etopictype;
   //   s >> m_strTopic;
   //   s >> m_straHandlerLibrary;
   //   s >> m_straMenuLibrary;
   //   s >> m_straApp;

   //   return s;

   //}


} // namespace filehandler



