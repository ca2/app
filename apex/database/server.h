#pragma once


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
      virtual ~server();

      virtual ::e_status initialize(::layered * pobjectContext) override;


      virtual bool _data_server_load(client * pclient, const key & key, get_memory getmemory, ::promise::subject * psubject = nullptr);


      virtual bool _data_server_save(client * pclient, const key & key, block block, ::promise::subject * psubject = nullptr);


      virtual bool data_pulse_change      (client * pclient, const key & key, ::promise::subject * psubject = nullptr);


      virtual bool on_before_data_change  (client * pclient, const key & key, payload & varNew, ::promise::subject * psubject = nullptr);
      virtual bool on_after_data_change   (client * pclient, const key & key, const payload & payload, ::promise::subject * psubject = nullptr);


      virtual payload data_load(client * pclient, const key & key, ::promise::subject * psubject = nullptr);
      virtual bool data_save(client * pclient, const key & key, payload & payload, ::promise::subject * psubject = nullptr);


   };


} // namespace database



