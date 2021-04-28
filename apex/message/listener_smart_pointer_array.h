#pragma once


namespace message
{


   template < class RECEIVER >
   class listener_smart_pointer_array :
      virtual public channel
   {
   public:

      DECLARE_ARRAY_ACCESSOR_OF(listener, m_listenera, RECEIVER);

      inline void add(RECEIVER * preceiver)
      {

         install_handlers(preceiver);

         m_listenera.add(preceiver);

      }


      inline void erase(RECEIVER * preceiver)
      {

         m_listenera.erase(preceiver);

         erase_receiver(preceiver);

      }

      virtual void install_handlers(RECEIVER *)
      {

      }



   };



} // namespace message



#define message_listener_spa(receiver) ::message::listener_smart_pointer_array < receiver >