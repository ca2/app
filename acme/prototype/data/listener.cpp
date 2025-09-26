#include "framework.h"
#include "listener.h"


namespace data
{


   listener::listener()
   {

   }


   listener::~listener()
   {

      listen(nullptr, false);

   }


   bool listener::listen(data * pdata, bool bListen)
   {

      if(bListen)
      {

         if(pdata == nullptr)
            return false;

         pdata->m_listenera.add_unique(this);

         m_datamap.set_at(pdata->id(), pdata);

         return true;

      }
      else if(::is_set(pdata))
      {

         pdata->m_listenera.erase(this);

         m_datamap.erase(pdata->id());

         //::acme::map_base::erase_value(m_datamap, pdata);

         return true;

      }

      return false;

   }


   void listener::on_update_data(data *, int)
   {

   }


} // namespace data



