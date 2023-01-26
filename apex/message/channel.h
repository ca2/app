#pragma once


#include "dispatcher.h"
#include "acme/primitive/collection/atom_array.h"
////#include "acme/primitive/primitive/object.h"
#include "acme/constant/message_prototype.h"


class CLASS_DECL_APEX channel :
   virtual public ::object
{
public:


   //static critical_section                            s_criticalsectionChannel;
   ::pointer<::channel>                               m_pchannel;
   atom_array                                         m_atomaHandledCommands;
   ::message::dispatcher_map                          m_dispatchermapNormal;
   ::message::dispatcher_map                          m_dispatchermapProbe;
   //::procedure_map                                  m_proceduremap;


   channel();
   ~channel() override;


   void channel_common_construct();

   
   virtual void install_message_routing(::channel* pchannel) override;


   virtual void destroy() override;

   virtual void erase_handler(::particle * pparticle);
   
   virtual void erase_handler(::particle * pparticle, bool bProber);

   virtual void transfer_handler(::message::dispatcher_map & dispatchermap, ::particle* pparticle, bool bProber);

   virtual void erase_all_routes();
   
   ::message::dispatcher_map * get_dispatcher_map(bool bProber);

   //template < typename RECEIVER >
   //bool add_message_handler(const ::atom & atom, RECEIVER * preceiver, void (RECEIVER:: * phandler)(::message::message * pmessage));

   //template < typename RECEIVER >
   //bool add_message_handler(::i64 iMessage, RECEIVER* preceiver, void (RECEIVER::* phandler)(::message::message* pmessage))
   //{

      //return add_message_handler((const ::atom&)(::enum_message)iMessage, preceiver, phandler);

   //}

   //template < typename MESSAGE_PRED >
   //bool add_message_handler(const ::atom & atom, MESSAGE_PRED pred);


   virtual void route_message(::message::message * pmessage);

   //virtual ::pointer<::message::message>get_message(enum_message_prototype e)

   virtual ::pointer<::message::message>get_message(MESSAGE * pmessage);

   virtual ::pointer<::message::message>get_message(const ::atom& atom, wparam wparam, lparam lparam, ::message::enum_prototype eprototype = ::message::e_prototype_none);




   //void id_notify(const ::atom & atom, const ::matter * pmatter);


   //template < class T >
   //void add_command_prober(const ::atom & atom, void (T:: * pfn)(::message::message *))
   //{

   //   add_command_prober(atom, dynamic_cast <T *> (this), pfn);

   //}


   ::particle * add_message_handler(const ::atom & atom, const ::message::dispatcher & dispatcher, bool bProber);


   template < typename T1, typename T2 >
   ::particle* add_message_handler(const ::atom & atom, T1 * p, void (T2:: * pfn)(::message::message *), bool bProber)
   {

      return add_message_handler(atom, { p, pfn }, bProber);

   }


   ::particle* add_command_prober(const ::atom & atom, const ::message::dispatcher & dispatcher)
   {

      return add_message_handler(atom, dispatcher, true);

   }


   template < typename T1, typename T2 >
   ::particle* add_command_prober(const ::atom & atom, T1 * p, void (T2:: * pfn)(::message::message *))
   {

      return add_command_prober(atom, { p, pfn }, true);

   }
   

   ::particle* add_command_handler(const ::atom & atom, const ::message::dispatcher & dispatcher)
   {

      return add_message_handler(atom, dispatcher, false);

   }


   //::particle* add_command_handler(const ::atom & atom, const ::function < void(::message::message * ) > & functionHandler)
   //{

   //   return add_message_handler(atom.compounded(::atom::e_type_command), functionHandler);

   //}


   //template < typename T1, typename T2 >
   //::particle* add_command_handler(const ::atom & atom, T1 * p, void (T2:: * pfn)(::message::message *))
   //{

   //   return add_command_handler(atom, { p, pfn });

   //}


   void default_toggle_check_handling(const ::atom& atom);

   
   void _001SendCommand(::message::command * pmessage);
   void _001SendCommandProbe(::message::command * pmessage);


   virtual void on_command(::message::command * pcommand);
   virtual bool has_command_handler(::message::command * pcommand);
   virtual void on_command_probe(::message::command * pcommand);


   virtual void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false);


   virtual void command_handler(::message::command * pcommand);
   virtual void message_handler(::message::message * pcommand);
  

};


#define MESSAGE_LINK(atom, pchannel, preceiver, phandler) \
   pchannel->add_message_handler((enum_message) (atom), { preceiver, phandler }, false )



