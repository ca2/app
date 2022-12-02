#pragma once


#include "acme/platform/context.h"


//void assert_ok() const override                                                     \
//{                                                                                      \
//                                                                                       \
//   BASE1::assert_ok();                                                              \
//                                                                                       \
//   BASE2::assert_ok();                                                              \
//                                                                                       \
//   BASE3::assert_ok();                                                              \
//                                                                                       \
//   BASE4::assert_ok();                                                              \
//                                                                                       \
//}                                                                                      \
//                                                                                       \
//                                                                                       \
//void dump(dump_context & dumpcontext) const override                                   \
//{                                                                                      \
//                                                                                       \
//   BASE1::dump(dumpcontext);                                                           \
//                                                                                       \
//   BASE2::dump(dumpcontext);                                                           \
//                                                                                       \
//   BASE3::dump(dumpcontext);                                                           \
//                                                                                       \
//   BASE4::dump(dumpcontext);                                                           \
//                                                                                       \
//}                                                                                      \


#define APP_CONSUMER_BODY                                                      \
                                                                                       \
                                                                                       \
                                                                                       \
                                                                                       \
void on_initialize_particle() override                                             \
{                                                                                      \
                                                                                       \
   m_papplicationForConsumer = m_pcontext ? m_pcontext->m_pacmeapplication : nullptr;             \
                                                                                       \
   BASE1::on_initialize_particle();                                      \
                                                                       \
   BASE2::on_initialize_particle();                                      \
                                                                       \
   BASE3::on_initialize_particle();                                      \
                                                                       \
   BASE4::on_initialize_particle();                                      \
                                                                                       \
       \
                                                                                       \
}                                                                                      \
                                                                                       \
void handle(::topic * ptopic, ::context * pcontext) override \
{                                                                                      \
                                                                                       \
   BASE1::handle(ptopic, pcontext);                                              \
                                                                                       \
   BASE2::handle(ptopic, pcontext);                                              \
                                                                                       \
   BASE3::handle(ptopic, pcontext);                                              \
                                                                                       \
   BASE4::handle(ptopic, pcontext);                                              \
                                                                                       \
}            
//void signal(::signal * psignal) override                            \
//{                                                                                      \
//                                                                                       \
//   BASE1::signal(psignal);                                                   \
//                                                                                       \
//   BASE2::signal(psignal);                                                   \
//                                                                                       \
//   BASE3::signal(psignal);                                                   \
//                                                                                       \
//   BASE4::signal(psignal);                                                   \
//                                                                                       \
//}                                                                                      \



#define OPTIONAL_BASE_BODY                                                          \
public:                                                                             \
   void on_initialize_particle() override {}         \
   void handle(::topic*,::context*) override {}

//   void assert_ok() const override {}                                    \
//   void dump(dump_context&) const override {}                               \
   //void on_subject(::topic::topic*, ::context*) override {} \

#define OPTIONAL_INTERACTION_BODY                                                   \
   OPTIONAL_BASE_BODY                                                               \
   void install_message_routing(::channel*) override {}                     \
   void on_layout(::draw2d::graphics_pointer&) {}



class optional_base1 : virtual public ::particle { OPTIONAL_BASE_BODY };
class optional_base2 : virtual public ::particle { OPTIONAL_BASE_BODY };
class optional_base3 : virtual public ::particle { OPTIONAL_BASE_BODY };
class optional_base4 : virtual public ::particle { OPTIONAL_BASE_BODY };

class optional_interaction1 : virtual public ::particle { OPTIONAL_INTERACTION_BODY };
class optional_interaction2 : virtual public ::particle { OPTIONAL_INTERACTION_BODY };
class optional_interaction3 : virtual public ::particle { OPTIONAL_INTERACTION_BODY };
class optional_interaction4 : virtual public ::particle { OPTIONAL_INTERACTION_BODY };


template <  typename APP, typename BASE1 = optional_base1, typename BASE2 = optional_base2, typename BASE3 = optional_base3, typename BASE4 = optional_base4 >
class app_consumer :
   virtual public ::particle,
   virtual public BASE1,
   virtual public BASE2,
   virtual public BASE3,
   virtual public BASE4
{
public:


   ::pointer<APP>m_papplicationForConsumer;


   app_consumer()
   {

   }


   APP_CONSUMER_BODY


   inline APP * get_app() { return m_papplicationForConsumer.get(); }
   inline APP * get_app() const { return (APP*)m_papplicationForConsumer.get(); }


};


template <  typename APP, typename BASE1 = optional_interaction1, typename BASE2 = optional_interaction2, typename BASE3 = optional_interaction3, typename BASE4 = optional_interaction4 >
class application_interaction :
   virtual public ::object,
   virtual public BASE1, 
   virtual public BASE2,
   virtual public BASE3,
   virtual public BASE4
{
public:


   ::pointer<APP>m_papplicationForConsumer;


   application_interaction()
   {

   }


   void initialize(::particle * pparticle) override
   {

      //auto estatus = 
      
      BASE1::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      BASE2::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      BASE3::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus =
      
      BASE4::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }

   APP_CONSUMER_BODY


   virtual void install_message_routing(::channel* pchannel) override                     
   {                                                                                      
      
      BASE1::install_message_routing(pchannel);                                           
      
      BASE2::install_message_routing(pchannel);                                           
      
      BASE3::install_message_routing(pchannel);                                           
      
      BASE4::install_message_routing(pchannel);                                           
      
   }                                                                                      
      
      
   void on_layout(::draw2d::graphics_pointer& pgraphics) override
   {

      BASE1::on_layout(pgraphics);

      BASE2::on_layout(pgraphics);

      BASE3::on_layout(pgraphics);

      BASE4::on_layout(pgraphics);

   }


   inline APP* get_app() { return m_papplicationForConsumer.get(); }
   inline APP* get_app() const { return (APP *)m_papplicationForConsumer.get(); }


};



