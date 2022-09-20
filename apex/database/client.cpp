#include "framework.h"





namespace database
{


   client::client()
   {

      m_pdataserver = nullptr;

   }


   void client::default_data_save_handling(const ::atom & idParam)
   {

      ::atom atom(idParam);

      auto linkedproperty = fetch_property(atom);

      ::payload payload;

      if(data_get(atom, payload))
      {

         linkedproperty->convert(payload);

      }

      //auto idProcedure = translate_property_id(atom);

      //auto linkedproperty = fetch_property(atom);

      auto psignal = get_app()->m_papexapplication->get_signal(linkedproperty->m_atom);

      psignal->add_handler(predicate([this, atom, linkedproperty](::topic * ptopic, ::context * pcontext)

      //connect(atom, [atom, linkedproperty](::message::message* pmessage)
         {

            data_set(atom, (const ::payload&)*linkedproperty.m_pproperty);

         }));

      //::add_procedure(get_app()->m_proceduremap[idProcedure], [this, atom]()
      //   {

      //      auto pproperty = fetch_property(atom);

      //      data_set(atom, (const ::payload &) *pproperty);

      //   });

   }


   void client::initialize_data_client(server * pserver)
   {

      set_data_server(pserver);

   }


   bool client::set_data_server(server * pserver)
   {

      if (m_pdataserver == pserver)
      {

         return true;

      }

      if (m_pdataserver != nullptr)
      {

         synchronous_lock synchronouslock(m_pdataserver->mutex());

         m_pdataserver->m_clienta.erase_client(this);

      }

      if(pserver != nullptr)
      {

         synchronous_lock synchronouslock(pserver->mutex());

         pserver->m_clienta.add_client(this);

      }

      m_pdataserver = pserver;

      return true;

   }


   client::~client()
   {

      if(m_pdataserver != nullptr)
      {

         synchronous_lock synchronouslock(m_pdataserver->mutex());

         try
         {

            m_pdataserver->m_clienta.erase_client(this);

         }
         catch(...)
         {

         }

      }

   }

   //void client::data_on_before_change(::message::message * pmessage)
   //{

   //   __UNREFERENCED_PARAMETER(pmessage);

   //}


   //void client::data_on_after_change(::message::message * pmessage)
   //{

   //   __UNREFERENCED_PARAMETER(pmessage);

   //}


   void client::_data_set(const key & key, const ::payload & payload, ::topic * ptopic)
   {

      if(::is_null(m_pdataserver))
      {

         throw ::exception(error_null_pointer);

      }

      ::memory_stream os;

      os << payload;

      m_pdataserver->_data_server_save(this, key, os->memory(), ptopic);

   }


   void client::_data_set(const selection & selection, const ::payload & payload, ::topic * ptopic)
   {

      if (::is_null(m_pdataserver))
      {

         throw ::exception(error_null_pointer);

      }

      ::memory_stream os;

      os << payload;

      ::count iCount = selection.get_item_count();

      bool bOk = true;

      for (index iItem = 0; iItem < iCount; iItem++)
      {

         auto & item = selection.get_item(iItem);

         m_pdataserver->_data_server_save(this, item.m_datakey, os->memory(), ptopic);
         //{

         //   bOk = false;

         //}

      }

      //return bOk;

   }


   bool client::_data_get(const key & key, ::payload & payload)
   {

      if (m_pdataserver != nullptr)
      {

         if (payload.get_type() == ::e_type_memory)
         {

            if (!m_pdataserver->_data_server_load(this, key, *payload.m_pmemory))
            {

               return false;

            }

         }
         else
         {

            ::memory_stream is;

            if (!m_pdataserver->_data_server_load(this, key, is->memory()))
            {

               return false;

            }

            is.initialize(this);

            try
            {

               is >> payload;

            }
            catch (::exception&)
            {

               return false;

            }

            //if (is.fail())
            //{

            //   return false;

            //}

         }

         return true;

      }

      return false;

   }


   bool client::data_pulse_change(const key & key, ::topic * ptopic)
   {

      if(m_pdataserver != nullptr)
      {


         m_pdataserver->data_pulse_change(this, key, ptopic);

         //if (!m_pdataserver->data_pulse_change(this, key, ptopic))
         //{

         //   return false;

         //}

         return true;

      }

      return false;

   }


   client_array::client_array()
   {

   }


   client_array::~client_array()
   {

      for(i32 i = 0; i < this->get_count(); i++)
      {

         this->element_at(i)->m_pdataserver = nullptr;

      }

   }


   void client_array::add_client(client * pclient)
   {

      if(pclient != dynamic_cast < client * > (this))
      {

         add_unique(pclient);

      }

   }


   ::count client_array::get_client_count()
   {

      return this->get_size();

   }


   client * client_array::client_at(index iClient)
   {

      return this->element_at(iClient);

   }


   void client_array::erase_client(client *pclient)
   {

      erase(pclient);

   }


   void client::set_data_key_modifier(const key & key)
   {

      m_datakeyModifier = key;

      m_datakey.m_strDataKey.Empty();

      update_data_key();

   }


   key client::get_data_key_modifier()
   {

      return m_datakeyModifier;

   }


   key client::calc_data_key(const key & datakey)
   {

      defer_update_data_key();

      return m_datakey + datakey;

   }


   key client::calc_parent_data_key()
   {

      return get_app()->m_papexapplication->calc_data_key();

   }


   key client::calc_data_key()
   {

      ::database::key key(calc_parent_data_key(), is_local_data());

      defer_update_object_id();

      key.m_strDataKey += "/" + __string(m_atom);

      return key;

   }


   void client::update_data_key()
   {

      m_datakey = key(calc_data_key()) + m_datakeyModifier;

   }


   void client::defer_update_data_key()
   {

      if(m_datakey.m_strDataKey.is_empty())
      {

         update_data_key();

      }

   }


   bool client::is_local_data()
   {

      return m_datakey.m_bLocalData;

   }


   void client::set_local_data(bool bLocalData)
   {

      return m_datakey.set_local_data(bLocalData);

   }


   void client::data_on_before_change(client* pclient, const key& atom, ::payload& payload, ::topic * ptopic)
   {

      //return true;

   }

   void client::data_on_after_change(client* pclient, const key& atom, const ::payload & payload, ::topic * ptopic)
   {

   }



} // namespace database



