#pragma once


class CLASS_DECL_APEX channel :
   virtual public ::object
{
public:


   static __pointer(::mutex)                       s_pmutexChannel;
   __pointer(::channel)                            m_pchannel;
   id_array                                        m_idaHandledCommands;
   ::message::dispatcher_map                       m_dispatchermap;
   //::message::dispatcher_map                       m_dispatchermapNew;
   //bool                                            m_bNewChannel;
   ::routine_map                                   m_routinemap;


   channel();
   ~channel() override;


   void channel_common_construct();

   
   virtual void install_message_routing(::channel* pchannel) override;


   static inline ::mutex * channel_mutex() { return s_pmutexChannel; }

   virtual void destroy() override;

   virtual void erase_handler(::matter * pmatter);

   virtual void transfer_handler(::message::dispatcher_map & dispatchermap, ::matter * pmatter);

   virtual void erase_all_routes();

   //template < typename RECEIVER >
   //bool add_message_handler(const ::id & id, RECEIVER * preceiver, void (RECEIVER:: * phandler)(::message::message * pmessage));

   //template < typename RECEIVER >
   //bool add_message_handler(::i64 iMessage, RECEIVER* preceiver, void (RECEIVER::* phandler)(::message::message* pmessage))
   //{

      //return add_message_handler((const ::id&)(::enum_message)iMessage, preceiver, phandler);

   //}

   //template < typename MESSAGE_PRED >
   //bool add_message_handler(const ::id & id, MESSAGE_PRED pred);


   virtual void route_message(::message::message * pmessage);

   virtual __pointer(::message::message) get_message(MESSAGE * pmessage);

   virtual __pointer(::message::message) get_message(const ::id& id, wparam wparam, lparam lparam);


   void id_notify(const ::id & id, ::matter * pmatter);


   //template < class T >
   //void add_command_prober(const ::id & id, void (T:: * pfn)(::message::message *))
   //{

   //   add_command_prober(id, dynamic_cast <T *> (this), pfn);

   //}


   ::matter * add_message_handler(const ::id & id, const ::message::dispatcher & dispatcher);


   template < typename T1, typename T2 >
   ::matter * add_message_handler(const ::id & id, T1 * p, void (T2:: * pfn)(::message::message *))
   {

      return add_message_handler(id, { p, pfn });

   }


   ::matter * add_command_prober(const ::id & id, const ::message::dispatcher & dispatcher)
   {

      return add_message_handler(id.compounded(::id::e_type_command_probe), dispatcher);

   }


   template < typename T1, typename T2 >
   ::matter * add_command_prober(const ::id & id, T1 * p, void (T2:: * pfn)(::message::message *))
   {

      return add_command_prober(id, { p, pfn });

   }


   ::matter * add_command_handler(const ::id & id, const ::message::dispatcher & dispatcher)
   {

      return add_message_handler(id.compounded(::id::e_type_command), dispatcher);

   }


   template < typename T1, typename T2 >
   ::matter * add_command_handler(const ::id & id, T1 * p, void (T2:: * pfn)(::message::message *))
   {

      return add_command_handler(id, { p, pfn });

   }


   void default_toggle_check_handling(const ::id& id);

   
   void _001SendCommand(::message::command * pmessage);
   void _001SendCommandProbe(::message::command * pmessage);


   virtual void on_command(::message::command * pcommand);
   virtual bool has_command_handler(::message::command * pcommand);
   virtual void on_command_probe(::message::command * pcommand);


   virtual void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false);


   virtual void command_handler(::message::command * pcommand);
   virtual void message_handler(::message::message * pcommand);
  

};



