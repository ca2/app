#pragma once


// with tbs in <3!! (Thomas Boregaard Soerensen)


namespace message
{

//   class messageable :
//      virtual public ::object
//   {
//   public:
//
//
//      virtual void on_message(message * pmessage) = 0;
//
//
//   };


//   template < typename MESSAGE_PRED, typename MESSAGE >
//   class predicate_route :
//      virtual public messageable
//   {
//   public:
//
//
//      MESSAGE_PRED m_messagepred;
//
//
//      predicate_route(MESSAGE_PRED messagepred) : m_messagepred(messagepred) { }
//
//
//      void on_message(message * pobject)
//      {
//
//         __pointer(MESSAGE) pmessage(pobject);
//
//         m_messagepred(pmessage);
//
//      }
//
//
//   };


//   template < typename RECEIVER, typename MESSAGE >
//   class receiver_route :
//      virtual public messageable
//   {
//   public:
//
//
//      RECEIVER * m_preceiver;
//
//      void (RECEIVER::* m_phandler)(::message::message* pmessage);
//
//
//      receiver_route(RECEIVER * preceiver, void (RECEIVER::* phandler)(MESSAGE* pmessage))
//      : m_preceiver(preceiver), m_phandler(phandler){ }
//
//
//      void on_message(MESSAGE * pmessage) { (m_preceiver->*m_phandler)(pmessage); }
//
//
//   };



   class handler_item
   {
   public:


      enum_message                  m_emessage;
      ::object *                    m_preceiver;
      void *                        m_pHandler;
      ::message::handler            m_handler;


      handler_item() :
      m_preceiver(nullptr),
      m_pHandler(nullptr)
      {


      }
        
      
      handler_item(::object * preceiver, void  * pHandler) :
         m_preceiver(preceiver),
         m_pHandler(pHandler)
      {


      }

   };


//   template < typename MESSAGE >
//   class typed_route :
//      virtual public route
//   {
//   public:
//
//
//      typed_route(::object * preceiver, ::object * pobjectReceiver, const ::type & typeReceiver) :
//         route(preceiver, pobjectReceiver, typeReceiver)
//      {
//
//      }
//
//
//      virtual ~typed_route() { }
//
//
//      typed_route & operator = (messageable * pmessageable)
//      {
//
//         m_pmessageable = pmessageable;
//
//         return *this;
//
//      }
//
//
//      template < typename MESSAGE_PRED >
//      typed_route& operator = (MESSAGE_PRED pred)
//      {
//
//         m_pmessageable = __new(predicate_route<MESSAGE_PRED, MESSAGE >(pred));
//
//         return *this;
//
//      }
//
//
//
//   };


//   template < typename MESSAGE >
//   inline __pointer(typed_route < MESSAGE >) create_typed_route(::object * preceiver, ::object * pobjectReceiver, const ::type & typeReceiver)
//   {
//
//      return __new(typed_route<MESSAGE>(preceiver, pobjectReceiver, typeReceiver));
//
//   }


//   inline __pointer(typed_route < message >) create_route(::object * preceiver, ::object * pobjectReceiver, const ::type & typeReceiver)
//   {
//
//      return create_typed_route < message > (preceiver, pobjectReceiver, typeReceiver);
//
//   }


   using handler_item_array = ::array < handler_item >;

   using handler_map = ::id_map < handler_item_array >;

   //using type_id_route = ::map < enum_type, enum_type, id_route >;


} // namespace message


using routine_map = ::id_map < ::routine_array >;



