#pragma once


namespace database
{


   class key;


   class CLASS_DECL_AQUA server :
      virtual public ::object
   {
   public:


      bool                    m_bRemote;
      client_array            m_clienta;


      server();
      virtual ~server();

      virtual ::estatus initialize(::object * pobjectContext) override;


      virtual bool _data_server_load(client * pclient, const key & key, get_memory getmemory, ::update * pupdate = nullptr);


      virtual bool _data_server_save(client * pclient, const key & key, block block, ::update * pupdate = nullptr);


      virtual bool data_pulse_change      (client * pclient, const key & key, ::update * pupdate = nullptr);


      virtual bool on_before_data_change  (client * pclient, const key & key, var & varNew, ::update * pupdate = nullptr);
      virtual bool on_after_data_change   (client * pclient, const key & key, const var & var, ::update * pupdate = nullptr);


      virtual var data_load(client * pclient, const key & key, ::update * pupdate = nullptr);
      virtual bool data_save(client * pclient, const key & key, var & var, ::update * pupdate = nullptr);


   };


} // namespace database



