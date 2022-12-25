#pragma once


#include "client.h"
#include "acme/primitive/primitive/get_memory.h"


namespace database
{


   class key;


   class CLASS_DECL_APEX server :
      virtual public ::object
   {
   public:


      bool                    m_bRemote;
      client_array            m_clienta;


      server();
      ~server() override;


      virtual void initialize(::particle * pparticle) override;


      virtual bool _data_server_load(client * pclient, const ::scoped_string & strKey, get_memory getmemory, ::topic * ptopic = nullptr);


      virtual void _data_server_save(client * pclient, const ::scoped_string & strKey, block block, ::topic * ptopic = nullptr);


      virtual void data_pulse_change(client * pclient, const ::scoped_string & strKey, ::topic * ptopic = nullptr);


      virtual void on_before_data_change(client * pclient, const ::scoped_string & strKey, ::payload & varNew, ::topic * ptopic = nullptr);
      virtual void on_after_data_change(client * pclient, const ::scoped_string & strKey, const ::payload & payload, ::topic * ptopic = nullptr);


      virtual ::payload data_load(client * pclient, const ::scoped_string & strKey, ::topic * ptopic = nullptr);
      virtual void data_save(client * pclient, const ::scoped_string & strKey, ::payload & payload, ::topic * ptopic = nullptr);


   };


} // namespace database



