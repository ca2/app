#pragma once


#include "apex/message/dispatcher.h"
#include "acme/prototype/collection/atom_array.h"
////#include "acme/prototype/prototype/object.h"
#include "acme/constant/message_prototype.h"


class CLASS_DECL_APEX channel :
   virtual public ::object
{
public:


   //static critical_section                            s_criticalsectionChannel;
   
   bool m_bTestChannel1 = true;
   ::pointer<::channel>                               m_pchannel;
   atom_array                                         m_atomaHandledCommands;
   ::message::command_map                             m_commandmap;
   ::message::command_map                             m_commandmapProbe;
   ::message::message_map                             m_messagemap;
   //::procedure_map                                  m_proceduremap;
   bool m_bTestChannel2 = true;

   channel();
   ~channel() override;


   void channel_common_construct();

   
   void install_message_routing(::channel* pchannel) override;


   virtual void destroy() override;

   virtual void erase_handler(::particle * pparticle);
   
   virtual void erase_message_handler(::particle * pparticle);

   virtual void erase_command_handler(::particle * pparticle);

   virtual void erase_command_probe_handler(::particle * pparticle);

   virtual void transfer_handler(channel * pchannelReceiver, ::particle* pparticle);
   virtual void transfer_message_handler(channel * pchannelReceiver, ::particle * pparticle);
   virtual void transfer_command_handler(channel * pchannelReceiver, ::particle * pparticle);
   virtual void transfer_command_probe_handler(channel * pchannelReceiver, ::particle * pparticle);

   virtual void erase_all_routes();
   
   ::message::command_map * get_command_map();
   ::message::command_map * get_command_probe_map();
   ::message::message_map * get_message_map();

   //template < typename RECEIVER >
   //bool add_message_handler(const ::atom & atom, RECEIVER * preceiver, void (RECEIVER:: * phandler)(::message::message * pmessage));

   //template < typename RECEIVER >
   //bool add_message_handler(long long iMessage, RECEIVER* preceiver, void (RECEIVER::* phandler)(::message::message* pmessage))
   //{

      //return add_message_handler((const ::atom&)(::enum_message)iMessage, preceiver, phandler);

   //}

   //template < typename MESSAGE_PRED >
   //bool add_message_handler(const ::atom & atom, MESSAGE_PRED pred);


   virtual void route_message(::message::message * pmessage);
   virtual void _route_command(::message::command * pcommand);
   virtual void _route_command_probe(::message::command * pcommand);

   //virtual ::pointer<::message::message>get_message(enum_message_prototype e)

   virtual ::pointer<::message::message>get_message(MESSAGE * pmessage);

   virtual ::pointer<::message::message>get_message(::enum_message emessage, ::wparam wparam, ::lparam lparam, ::message::enum_prototype eprototype = ::message::e_prototype_none);




   //void id_notify(const ::atom & atom, const ::matter * pmatter);


   //template < class T >
   //void add_command_prober(const ::atom & atom, void (T:: * pfn)(::message::message *))
   //{

   //   add_command_prober(atom, dynamic_cast <T *> (this), pfn);

   //}


   ::particle * add_message_handler(::enum_message emessage, const ::message::dispatcher & dispatcher);
   ::particle * add_command_handler(const ::atom & atom, const ::message::dispatcher & dispatcher);
   ::particle * add_command_prober(const ::atom & atom, const ::message::dispatcher & dispatcher);


   template < typename T1, typename T2 >
   ::particle* add_message_handler(::enum_message emessage, T1 * p, void (T2:: * pfn)(::message::message *))
   {

      return add_message_handler(emessage, { p, pfn });

   }

   template < typename T1, typename T2 >
   ::particle* add_command_prober(const ::atom & atom, T1 * p, void (T2:: * pfn)(::message::message *))
   {

      return add_command_prober(atom, { p, pfn });

   }
   

   //::particle* add_command_handler(const ::atom & atom, const ::message::dispatcher & dispatcher)
   //{

   //   return add_command_handler(atom, dispatcher);

   //}


   //::particle* add_command_handler(const ::atom & atom, const ::function < void(::message::message * ) > & functionHandler)
   //{

   //   return add_message_handler(atom.compounded(::atom::e_type_command), functionHandler);

   //}


   //template < typename T1, typename T2 >
   //::particle* add_command_handler(const ::atom & atom, T1 * p, void (T2:: * pfn)(::message::message *))
   //{

   //   return add_command_handler(atom, { p, pfn });

   //}


   //void default_toggle_check_handling(const ::atom& atom);

   
   void _001SendCommand(::message::command * pmessage);
   void _001SendCommandProbe(::message::command * pmessage);


   virtual void on_command(::message::command * pcommand);
   virtual bool has_command_handler(::message::command * pcommand);
   virtual void on_command_probe(::message::command * pcommand);
   bool on_command_final(const ::atom & atom, ::user::activation_token * puseractivationtoken) override;


   virtual void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false);


   virtual void command_handler(::message::command * pcommand);
   virtual void message_handler(::message::message * pcommand);
  

};


#define MESSAGE_LINK(emessage, pchannel, preceiver, phandler) \
   pchannel->add_message_handler((enum_message)(emessage), { preceiver, phandler })








