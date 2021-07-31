#pragma once


class CLASS_DECL_APEX channel :
   virtual public ::subject::manager
{
public:


   static __pointer(::mutex)                    s_pmutexChannel;
   __pointer(::channel)                         m_pchannel;
   id_array                                     m_idaHandledCommands;
   ::message::handler_map                       m_handlermap;
   ::message::handler_map                       m_handlermapNew;
   bool                                         m_bNewChannel;
   ::routine_map                                m_routinemap;


   channel();
   virtual ~channel();


   void channel_common_construct();

   
   virtual void install_message_routing(::channel* pchannel) override;


   static inline ::mutex * channel_mutex() { return s_pmutexChannel; }

   virtual ::e_status destroy() override;

   virtual void erase_receiver(::object * preceiver);

   virtual void transfer_receiver(::message::handler_map & handlermap, ::object * preceiver);

   virtual void erase_all_routes();

//   template < typename RECEIVER, typename MESSAGE >
//   ::message::typed_route < MESSAGE > & get_typed_route(const ::id & id, RECEIVER * preceiverDerived);

   template < typename RECEIVER >
   bool add_handler(const ::id & id, RECEIVER * preceiver, void (RECEIVER:: * phandler)(::message::message * pmessage));
   template < typename RECEIVER >
   bool add_message_handler(::i64 iMessage, RECEIVER* preceiver, void (RECEIVER::* phandler)(::message::message* pmessage))
   {

      return add_handler((const ::id&)(::enum_message)iMessage, preceiver, phandler);

   }

   template < typename MESSAGE_PRED >
   //bool add_handler(const ::id & id, ::object * preceiver, void * phandler, MESSAGE_PRED pred);
   bool add_handler(const ::id & id, MESSAGE_PRED pred);

   bool _add_handler(const ::id & id, ::object * preceiver, void * phandler, const ::message::handler & handler);


   virtual void route_message(::message::message * pmessage);

   virtual __pointer(::message::message) get_message(MESSAGE * pmessage);
   //virtual __pointer(::message::message) get_message(const ::id & id, wparam wparam, lparam lparam, const ::point_i32& point);
   virtual __pointer(::message::message) get_message(const ::id& id, wparam wparam, lparam lparam);

   ///virtual __pointer(::user::message) get_message_base(::windowing::window * pwindow, const ::id & id, wparam wparam, lparam lparam);


//#ifdef LINUX
//
//   virtual __pointer(::user::message) get_message_base(void * pevent, ::user::interaction * puserinteraction = nullptr);
//
//#endif

    ::e_status id_notify(const ::id & id, ::matter * pmatter);


   template < class T >
   void connect_command_probe(const ::id & id, void (T:: * pfn)(::message::message *))
   {

      connect_command_probe(id, dynamic_cast <T *> (this), pfn);

   }


   template < class T >
   void connect_command(const ::id & id, void (T:: * pfn)(::message::message *))
   {

      connect_command(id, dynamic_cast <T *> (this), pfn);

   }


   template < class T >
   void connect_command_probe(const ::id & id, T * p, void (T:: * pfn)(::message::message *))
   {

      add_handler(id.compounded(::id::e_type_command_probe), p, pfn);

   }


   template < class T >
   void connect_command(const ::id & id, T * p, void (T:: * pfn)(::message::message *))
   {

      add_handler(id.compounded(::id::e_type_command), p, pfn);

   }


   template < typename MESSAGE_PRED >
   void connect_command_predicate(const ::id & id, MESSAGE_PRED pred)
   {

      _add_handler(id.compounded(::id::e_type_command), nullptr, nullptr, __handler(pred));

   }


//   template < typename RECEIVER, typename MESSAGE_PRED >
//   void add_update_route_predicate(RECEIVER * preceiver, const ::id & id, MESSAGE_PRED pred)
//   {
//
//      add_route(id.compounded(::id::e_type_update), preceiver) = pred;
//
//   }

   
   virtual void on_property_changed(property* pproperty, const ::action_context& actioncontext) override;


   void default_toggle_check_handling(const ::id& id);


//   template < typename RECEIVER >
//   void add_update_route(RECEIVER * preceiver, const ::id & id)
//   {
//
//      m_routinemap[id].add(__routine([preceiver, id]()
//        {
//
//            preceiver->process_subject(id, preceiver);
//
//        });
//
//   }

   
   void _001SendCommand(::message::command * pmessage);
   void _001SendCommandProbe(::message::command * pmessage);


   virtual void on_command(::message::command * pcommand);
   virtual bool has_command_handler(::message::command * pcommand);
   virtual void on_command_probe(::message::command * pcommand);


   virtual void route_command_message(::message::command * pcommand);


   virtual void on_command_message(::message::command* pcommand);


   void BeginWaitCursor();
   void EndWaitCursor();
   void RestoreWaitCursor();       // call after messagebox


   virtual ::e_status handle(::message::command * pcommand);


};



