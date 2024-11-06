#include "framework.h"
#include "container.h"
#include "listener.h"


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

      return m_spdata->synchronization()->is_locked();

   }


   void data_container::on_update_data(int iHint)
   {
      __UNREFERENCED_PARAMETER(iHint);
   }


   data_container_base::data_container_base()
   {

   }


   data_container_base::~data_container_base()
   {

   }


   void data_container_base::destroy()
   {

      m_datamap.clear();

      ::object::destroy();

   }


   bool data_container_base::set_data(const ::atom & atom, ::data::data * pdata)
   {

      pdata->m_atom = atom;

      if(!add_data(pdata))
      {

         return false;

      }

      return true;

   }


   bool data_container_base::add_data(::data::data * pdata)
   {

      pdata->initialize_data();

      m_datamap.set_at(pdata->m_atom, pdata);

      return true;

   }


   bool data_container_base::erase_data(::data::data * pdata)
   {

      auto bRemove = m_datamap.erase_item(pdata->m_atom);

      return bRemove;

   }


   data * data_container_base::get_data(const ::atom & atom)
   {

      auto p = m_datamap.plookup(atom);

      if (p.is_null())
      {

         auto & pdata = m_datamap[atom];

         auto pdataNew = create_data(atom);

         if (pdataNew)
         {

            pdata = pdataNew;

         }

         if (pdata)
         {

            pdata->initialize_data();

         }

         p = m_datamap.plookup(atom);

      }

      return p->element2();

   }


   ::pointer < data > data_container_base::create_data(const ::atom & atom)
   {

      return {};

   }


   ::collection::count data_container_base::get_count() const
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

      for(auto & data : m_datamap)
      {

         synca.add_item(data.element2());

      }

      return synca;

   }


} // namespace data




