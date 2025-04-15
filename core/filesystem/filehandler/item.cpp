#include "framework.h"
#include "item.h"


namespace filehandler
{


   string item::get_item_text(object * pparticle) const
   {

      __UNREFERENCED_PARAMETER(pparticle);

      return m_strTopic;

   }


   ::collection::index item::get_item_image(object * pparticle) const
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



