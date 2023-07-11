#pragma once


#include "key.h"
////#include "acme/primitive/primitive/object.h"
#include "acme/primitive/collection/address_array.h"


namespace database
{


   class CLASS_DECL_APEX client :
      virtual public ::object
   {
   protected:

      /// Value to be add to data key on defer_update_data_id
      ::string                   m_strKeyModifier;
      /// Cached Value from calc_data_id
      ::string                   m_strDataKey;


   public:
      ::pointer < ::database::stream > m_pstream;

      friend class client_array;
      friend class server;


      server *    m_pdataserver;


      client();
      ~client() override;


      //virtual bool set_data_server(server * pserver);


      void initialize_data_client(server * pserver);

//      DECLARE_MESSAGE_HANDLER(data_on_before_change);
      DECLARE_MESSAGE_HANDLER(data_on_after_change);


      virtual void data_on_before_change(client* pclient, const ::scoped_string & strKey, ::payload& payload, ::topic * ptopic);
      virtual void data_on_after_change(client* pclient, const ::scoped_string & strKey, const ::payload & payload, ::topic * ptopic);


      virtual void _data_set(const ::scoped_string & strKey, const ::payload & payload, ::topic * ptopic = nullptr);
      virtual void _data_set(const ::string_array & straKey, const ::payload & payload, ::topic * ptopic = nullptr);


      inline stream * datastream() { return m_pstream; }
      //template < typename TYPE >
      //inline void binary_set(const key & key, const TYPE & t);


      //template < typename TYPE >
      //inline void binary_set(const key & key, const ::pointer<TYPE>& p)
      //{

      //   binary_set(key, *p);

      //}


      //template < typename TYPE >
      //inline void datastream()->set(const key & key, const TYPE & t)
      //{

      //   memory_file memoryfile;

      //   binary_stream stream(&memoryfile);

      //   stream.set_storing();

      //   stream << t;

      //   //if (stream.fail())
      //   //{

      //   //   return false;

      //   //}
      //   binary_set(key, memoryfile.memory());
      //   //if (!)
      //   //{

      //   //   return false;

      //   //}

      //   //return true;

      //}

      virtual bool _data_get(const ::scoped_string & strKey, ::payload payload);


      //template < typename TYPE >
      //inline bool binary_get(const key & key, ::pointer<TYPE>& p)
      //{

      //   return binary_get(key, *p);

      //}


      virtual bool data_get_block(const ::scoped_string & strKey, ::block & block);
      virtual void data_set_block(const ::scoped_string & strKey, const ::block & block);

      virtual bool data_get_payload(const ::scoped_string & strKey, ::payload & payload);
      virtual void data_set_payload(const ::scoped_string & strKey, const ::payload & payload);

      virtual bool data_get_memory(const ::scoped_string & strKey, ::memory_base & memory);
      virtual void data_set_memory(const ::scoped_string & strKey, const block & block);


      //template < typename TYPE >
      //inline bool datastream()->get(const ::scoped_string & strKey, TYPE & t)
      //{

      //   memory_file memoryfile;

      //   if (!binary_get(key, memoryfile.memory()))
      //   {

      //      return false;

      //   }

      //   auto stream = __binary_stream(memoryfile);

      //   stream.set_loading();

      //   stream >> t;

      //   if (stream.nok())
      //   {

      //      return false;

      //   }

      //   return true;

      //}

      virtual void default_data_save_handling(const ::atom & atom);

      virtual bool data_pulse_change(const ::scoped_string & strKey, ::topic * ptopic);


      virtual void set_data_key_modifier(const ::scoped_string & strKey);
      virtual ::string get_data_key_modifier();


      virtual ::string calculate_data_key(const ::scoped_string & strKey);


      virtual ::string calculate_parent_data_key();
      virtual ::string calculate_data_key();
      virtual void defer_update_data_key();
      virtual void update_data_key();
      //virtual bool is_local_data();
      //virtual void set_local_data(bool bLocalData = true);



   };


   class CLASS_DECL_APEX client_array :
      public address_array < client * >
   {
   public:


      client_array();
      virtual ~client_array();


      virtual void add_client(client * pclient);
      virtual void erase_client(client * pclient);
      client * client_at(index iClient);
      ::count get_client_count();


   };


} // namespace database


#define CHANGE_EVENT_DATA_GET(pchange, key) pchange->m_pclient->datastream()->get(pchange->m_strDataKey, key)
