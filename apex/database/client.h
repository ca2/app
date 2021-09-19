#pragma once


namespace database
{


   class CLASS_DECL_APEX client :
      virtual public ::object
   {
   protected:

      /// Value to be add to data key on defer_update_data_id
      ::database::key            m_datakeyModifier;
      /// Cached Value from calc_data_id
      ::database::key            m_datakey;


   public:


      friend class client_array;
      friend class server;


      server *    m_pdataserver;


      client();
      virtual ~client();


      virtual bool set_data_server(server * pserver);


      void initialize_data_client(server * pserver);

//      DECLARE_MESSAGE_HANDLER(data_on_before_change);
      DECLARE_MESSAGE_HANDLER(data_on_after_change);

      virtual bool data_on_before_change(client* pclient, const key& id, ::payload& payload, ::subject * psubject);
      virtual void data_on_after_change(client* pclient, const key& id, const ::payload & payload, ::subject * psubject);



      virtual bool _data_set(const key& key, const ::payload & payload, ::subject * psubject = nullptr);
      virtual bool _data_set(const selection & selection, const ::payload & payload, ::subject * psubject = nullptr);


      template < typename TYPE >
      inline bool binary_set(const key & key, const TYPE & t);


      template < typename TYPE >
      inline bool binary_set(const key & key, const __pointer(TYPE) & p)
      {

         return binary_set(key, *p);

      }


      template < typename TYPE >
      inline bool data_set(const key & key, const TYPE & t)
      {

         var_stream stream;

         stream.set_storing();

         __exchange(stream, (TYPE &) t);

         if (stream.fail())
         {

            return false;

         }

         if (!binary_set(key, stream.payload()))
         {

            return false;

         }

         return true;

      }


      virtual bool _data_get(const key& key, ::payload & payload);

      template < typename TYPE >
      inline bool binary_get(const key & key, TYPE & t);

      template < typename TYPE >
      inline bool binary_get(const key & key, __pointer(TYPE) & p)
      {

         return binary_get(key, *p);

      }


      virtual ::payload data_get(const key & key)
      {

         ::payload payload;

         if (!_data_get(key, payload))
         {

            return ::error_not_found;

         }

         return payload;

      }


      template < typename TYPE >
      inline bool data_get(const key & key, TYPE & t)
      {

         var_stream stream;

         if (!binary_get(key, stream.payload()))
         {

            return false;

         }

         stream.set_loading();

         __exchange(stream, t);

         if (stream.fail())
         {

            return false;

         }

         return true;

      }

      virtual void default_data_save_handling(const ::id & id);

      virtual bool data_pulse_change(const key & key, ::subject * psubject);


      virtual void set_data_key_modifier(const key & key);
      virtual key get_data_key_modifier();


      virtual key calc_data_key(const key & key);


      virtual key calc_parent_data_key();
      virtual key calc_data_key();
      virtual void defer_update_data_key();
      virtual void update_data_key();
      virtual bool is_local_data();
      virtual void set_local_data(bool bLocalData = true);



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


#define CHANGE_EVENT_DATA_GET(pchange, key) pchange->m_pclient->data_get(pchange->m_datakey, key)
