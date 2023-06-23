#include "framework.h"
#include "stream.h"
#include "server.h"
#include "selection.h"
#include "acme/filesystem/file/binary_stream.h"
#include "acme/parallelization/event.h"
#include "acme/parallelization/synchronous_lock.h"
//#include "apex/handler/predicate.h"
#include "apex/platform/application.h"


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

      if(data_get_payload(atom, payload))
      {

         linkedproperty->convert(payload);

      }

      //auto idProcedure = translate_property_id(atom);

      //auto linkedproperty = fetch_property(atom);

      auto psignal = get_app()->m_papexapplication->get_signal(linkedproperty->m_atom);

      psignal->add_signal_handler([this, atom, linkedproperty](::topic * ptopic, ::context * pcontext)

      //connect(atom, [atom, linkedproperty](::message::message* pmessage)
         {

            data_set_payload(atom, *linkedproperty.m_pproperty);

         });

      //::add_procedure(get_app()->m_proceduremap[idProcedure], [this, atom]()
      //   {

      //      auto pproperty = fetch_property(atom);

      //      datastream()->set(atom, (const ::payload &) *pproperty);

      //   });

   }


   void client::data_set_memory(const ::scoped_string & strKey, const ::block & block)
   {

      if (!m_pdataserver)
      {

         throw ::exception(error_wrong_state);

      }

      m_pdataserver->_data_server_save(this, strKey, block);

   }

   
   bool client::data_get_memory(const ::scoped_string & strKey, ::memory_base & memory)
   {

      if (!m_pdataserver)
      {

         return false;

      }

      if (!m_pdataserver->_data_server_load(this, strKey, memory))
      {

         return false;

      }

      return true;

   }


   void client::data_set_block(const ::scoped_string & strKey, const ::block & block)
   {

      if (!m_pdataserver)
      {

         throw ::exception(error_wrong_state);

      }

      m_pdataserver->_data_server_save(this, strKey, block);

   }


   bool client::data_get_block(const ::scoped_string & strKey, ::block & block)
   {

      if (!m_pdataserver)
      {

         return false;

      }

      if (!m_pdataserver->_data_server_load(this, strKey, block))
      {

         return false;

      }

      return true;

   }


   void client::data_set_payload(const ::scoped_string & strKey, const ::payload & payload)
   {

      _data_set(strKey, payload);

   }
   
   
   bool client::data_get_payload(const ::scoped_string & strKey, ::payload & payload)
   {

      return _data_get(strKey, payload);

   }


   void client::initialize_data_client(server * pserver)
   {

      __defer_construct_new(m_pstream);

      m_pstream->m_pclient = this;

      //set_data_server(pserver);

      if (m_pdataserver == pserver)
      {

         return;

      }

      if (m_pdataserver != nullptr)
      {

         synchronous_lock synchronouslock(m_pdataserver->synchronization());

         m_pdataserver->m_clienta.erase_client(this);

      }

      if (pserver != nullptr)
      {

         synchronous_lock synchronouslock(pserver->synchronization());

         pserver->m_clienta.add_client(this);

      }

      m_pdataserver = pserver;

      //return true;

   }


   //bool client::set_data_server(server * pserver)
   //{

   //   if (m_pdataserver == pserver)
   //   {

   //      return true;

   //   }

   //   if (m_pdataserver != nullptr)
   //   {

   //      synchronous_lock synchronouslock(m_pdataserver->synchronization());

   //      m_pdataserver->m_clienta.erase_client(this);

   //   }

   //   if(pserver != nullptr)
   //   {

   //      synchronous_lock synchronouslock(pserver->synchronization());

   //      pserver->m_clienta.add_client(this);

   //   }



   //   m_pdataserver = pserver;

   //   return true;

   //}


   client::~client()
   {

      if(m_pdataserver != nullptr)
      {

         synchronous_lock synchronouslock(m_pdataserver->synchronization());

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

   //   UNREFERENCED_PARAMETER(pmessage);

   //}


   //void client::data_on_after_change(::message::message * pmessage)
   //{

   //   UNREFERENCED_PARAMETER(pmessage);

   //}


   void client::_data_set(const ::scoped_string & strKey, const ::payload & payload, ::topic * ptopic)
   {

      if(::is_null(m_pdataserver))
      {

         throw ::exception(error_null_pointer);

      }

      auto pmemoryfile = create_memory_file();

      auto stream = __binary_stream(pmemoryfile);

      stream << payload;

      m_pdataserver->_data_server_save(this, strKey, pmemoryfile->memory(), ptopic);

   }


   void client::_data_set(const ::string_array & straKey, const ::payload & payload, ::topic * ptopic)
   {

      if (::is_null(m_pdataserver))
      {

         throw ::exception(error_null_pointer);

      }

      auto pmemoryfile = create_memory_file();

      auto stream = __binary_stream(pmemoryfile);

      stream << payload;

      for (auto & strKey : straKey)
      {

         m_pdataserver->_data_server_save(this, strKey, pmemoryfile->memory(), ptopic);

      }

   }


   bool client::_data_get(const ::scoped_string & strKey, ::payload payload)
   {

      if (m_pdataserver == nullptr)
      {

         throw ::exception(error_wrong_state);

      }

      if (payload.get_type() == ::e_type_memory)
      {

         if (!m_pdataserver->_data_server_load(this, strKey, *payload.m_pmemory))
         {

            return false;

         }

      }
      else
      {

         ::memory_file memoryfile;

         if (!m_pdataserver->_data_server_load(this, strKey, memoryfile.memory()))
         {

            return false;

         }

         auto stream = __binary_stream(&memoryfile);

         try
         {

            stream >> payload;

         }
         catch (::exception&)
         {

            return false;

         }

      }

      return true;

   }


   bool client::data_pulse_change(const ::scoped_string & strKey, ::topic * ptopic)
   {

      if(m_pdataserver != nullptr)
      {


         m_pdataserver->data_pulse_change(this, strKey, ptopic);

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


   void client::set_data_key_modifier(const ::scoped_string & strKey)
   {

      m_strKeyModifier = strKey;

      m_strDataKey.empty();

      update_data_key();

   }


   ::string client::get_data_key_modifier()
   {

      return m_strKeyModifier;

   }


   ::string client::calculate_data_key(const ::scoped_string & strKey)
   {

      defer_update_data_key();

      return m_strDataKey + strKey;

   }


   ::string client::calculate_parent_data_key()
   {

      return get_app()->m_papexapplication->calculate_data_key();

   }


   ::string client::calculate_data_key()
   {

      ::string strKey = calculate_parent_data_key();

      defer_update_object_id();

      strKey += "/" + m_atom;

      return strKey;

   }


   void client::update_data_key()
   {

      m_strDataKey = calculate_data_key() + "/" + m_strKeyModifier;

   }


   void client::defer_update_data_key()
   {

      if(m_strDataKey.is_empty())
      {

         update_data_key();

      }

   }


//   bool client::is_local_data()
//   {
//
//      return m_strKey.m_bLocalData;
//
//   }
//
//
//   void client::set_local_data(bool bLocalData)
//   {
//
//      return m_strKey.set_local_data(bLocalData);
//
//   }


   void client::data_on_before_change(client* pclient, const ::scoped_string & strKey, ::payload& payload, ::topic * ptopic)
   {

      //return true;

   }


   void client::data_on_after_change(client* pclient, const ::scoped_string & strKey, const ::payload & payload, ::topic * ptopic)
   {

   }


} // namespace database



