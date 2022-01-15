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
      ~server() override;


      virtual void initialize(::object * pobject) override;


      virtual bool _data_server_load(client * pclient, const key & key, get_memory getmemory, ::subject * psubject = nullptr);


      virtual void _data_server_save(client * pclient, const key & key, block block, ::subject * psubject = nullptr);


      virtual void data_pulse_change      (client * pclient, const key & key, ::subject * psubject = nullptr);


      virtual void on_before_data_change  (client * pclient, const key & key, ::payload & varNew, ::subject * psubject = nullptr);
      virtual void on_after_data_change   (client * pclient, const key & key, const ::payload & payload, ::subject * psubject = nullptr);


      virtual ::payload data_load(client * pclient, const key & key, ::subject * psubject = nullptr);
      virtual void data_save(client * pclient, const key & key, ::payload & payload, ::subject * psubject = nullptr);


   };


} // namespace database



