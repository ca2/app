#pragma once


// with tbs in <3!! (Thomas Boregaard Soerensen)


namespace message
{

   class messageable :
      virtual public ::context_object
   {
   public:


      virtual void on_message(message * pmessage) = 0;


   };


   template < typename MESSAGE_PRED, typename MESSAGE >
   class pred_route :
      virtual public messageable
   {
   public:


      MESSAGE_PRED m_messagepred;


      pred_route(MESSAGE_PRED messagepred) : m_messagepred(messagepred) { }


      void on_message(message * pobject)
      {

         SCAST_PTR(MESSAGE, pmessage, pobject);

         m_messagepred(pmessage);

      }


   };


   template < typename RECEIVER, typename MESSAGE >
   class receiver_route :
      virtual public messageable
   {
   public:


      RECEIVER * m_preceiver;
      
      void (RECEIVER::* m_phandler)(::message::message* pmessage);


      receiver_route(RECEIVER * preceiver, void (RECEIVER::* phandler)(MESSAGE* pmessage))
      : m_preceiver(preceiver), m_phandler(phandler){ }


      void on_message(MESSAGE * pmessage) { (m_preceiver->*m_phandler)(pmessage); }


   };



   class route :
      virtual public ::context_object
   {
   public:

      id                   m_id;
      ::object *           m_preceiver;
      object *             m_pobjectReceiver;
      ::type               m_typeReceiver;
      __pointer(messageable)      m_pmessageable;


      route(::object * preceiver, ::object * pobjectReceiver, const ::type & typeReceiver) :
         m_preceiver(preceiver),
         m_pobjectReceiver(pobjectReceiver),
         m_typeReceiver(typeReceiver)
      {


      }

      virtual ~route() { }




      template < typename MESSAGE_PRED >
      route & operator = (MESSAGE_PRED pred)
      {

         m_pmessageable = __new(pred_route<MESSAGE_PRED, ::message::message >(pred));

         return *this;

      }


   };


   template < typename MESSAGE >
   class typed_route :
      virtual public route
   {
   public:


      typed_route(::object * preceiver, ::object * pobjectReceiver, const ::type & typeReceiver) :
         route(preceiver, pobjectReceiver, typeReceiver)
      {

      }


      virtual ~typed_route() { }


      typed_route & operator = (messageable * pmessageable)
      {

         m_pmessageable = pmessageable;

         return *this;

      }


      template < typename MESSAGE_PRED >
      typed_route& operator = (MESSAGE_PRED pred)
      {

         m_pmessageable = __new(pred_route<MESSAGE_PRED, MESSAGE >(pred));

         return *this;

      }



   };


   template < typename MESSAGE >
   inline __pointer(typed_route < MESSAGE >) create_typed_route(::object * preceiver, ::object * pobjectReceiver, const ::type & typeReceiver)
   {

      return __new(typed_route<MESSAGE>(preceiver, pobjectReceiver, typeReceiver));

   }


   inline __pointer(typed_route < message >) create_route(::object * preceiver, ::object * pobjectReceiver, const ::type & typeReceiver)
   {

      return create_typed_route < message > (preceiver, pobjectReceiver, typeReceiver);

   }


   using route_array = __pointer_array(route);

   __class(CLASS_DECL_APEX, id_route, ::map < ::message::id, const ::message::id &, __pointer(route_array) >);

   using type_id_route = ::map < e_type, e_type, id_route >;


} // namespace message
