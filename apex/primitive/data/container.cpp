#include "framework.h"


namespace data
{


   data_container::data_container()
   {

   }


   data_container::~data_container()
   {

   }


   bool data_container::set_data(::data::data * pdata)
   {
      m_spdata = pdata;
      return true;
   }

   data * data_container::get_data()
   {
      return m_spdata;
   }

   bool data_container::is_data_locked() const
   {
      return m_spdata->mutex()->is_locked();
   }

   void data_container::on_update_data(i32 iHint)
   {
      UNREFERENCED_PARAMETER(iHint);
   }


   data_container_base::data_container_base()
   {

   }


   data_container_base::~data_container_base()
   {

   }


   bool data_container_base::set_data(const ::id & id, ::data::data * pdata)
   {

      pdata->m_id = id;

      pdata->initialize_data(this);

      m_datamap.set_at(pdata->m_id, pdata);

      return true;

   }


   bool data_container_base::add_data(::data::data * pdata)
   {
      
      if (m_datamap.contains(pdata->m_id))
      {

         return false;

      }

      pdata->initialize_data(this);

      m_datamap.set_at(pdata->m_id, pdata);

      return true;

   }


   bool data_container_base::remove_data(::data::data * pdata)
   {

      auto bRemove = m_datamap.remove_key(pdata->m_id);

      return bRemove;

   }


   data * data_container_base::get_data(const ::id & id)
   {

      auto p = m_datamap.plookup(id);

      if (!p)
      {

         return nullptr;

      }

      return p->element2();

   }


   ::count data_container_base::get_count() const
   {

      return m_datamap.get_count();

   }


   bool data_container_base::is_empty() const
   {

      return m_datamap.is_empty();

   }


   sync_array data_container_base::get_synca()
   {

      sync_array synca;

      for(auto & pdata : m_datamap.values())
      {

         synca.add_item(pdata->mutex());

      }

      return synca;

   }


} // namespace data




