#include "framework.h"


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

         m_datamap.set_at(pdata->m_atom, pdata);

         return true;

      }
      else
      {

         pdata->m_listenera.erase(this);

         m_datamap.erase_key(pdata->m_atom);

         //::papaya::map::erase_value(m_datamap, pdata);

         return true;

      }

   }


   void listener::on_update_data(data *, i32)
   {

   }


} // namespace data



