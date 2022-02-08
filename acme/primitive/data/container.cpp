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
      __UNREFERENCED_PARAMETER(iHint);
   }


   data_container_base::data_container_base()
   {

   }


   data_container_base::~data_container_base()
   {

   }


   bool data_container_base::set_data(const ::atom & atom, ::data::data * pdata)
   {

      pdata->m_atom = atom;

      pdata->initialize_data(this);

      m_datamap.set_at(pdata->m_atom, pdata);

      return true;

   }


   bool data_container_base::add_data(::data::data * pdata)
   {
      
      if (m_datamap.contains(pdata->m_atom))
      {

         return false;

      }

      pdata->initialize_data(this);

      m_datamap.set_at(pdata->m_atom, pdata);

      return true;

   }


   bool data_container_base::erase_data(::data::data * pdata)
   {

      auto bRemove = m_datamap.erase_key(pdata->m_atom);

      return bRemove;

   }


   data * data_container_base::get_data(const ::atom & atom)
   {

      auto p = m_datamap.plookup(atom);

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


   synchronization_array data_container_base::get_synca()
   {

      synchronization_array synca;

      for(auto & pdata : m_datamap.values())
      {

         synca.add_item(pdata->mutex());

      }

      return synca;

   }


} // namespace data




