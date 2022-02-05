#pragma once


#define APPLICATION_CONSUMER_BODY                                                      \
                                                                                       \
                                                                                       \
void assert_ok() const override                                                     \
{                                                                                      \
                                                                                       \
   BASE1::assert_ok();                                                              \
                                                                                       \
   BASE2::assert_ok();                                                              \
                                                                                       \
   BASE3::assert_ok();                                                              \
                                                                                       \
   BASE4::assert_ok();                                                              \
                                                                                       \
}                                                                                      \
                                                                                       \
                                                                                       \
void dump(dump_context & dumpcontext) const override                                   \
{                                                                                      \
                                                                                       \
   BASE1::dump(dumpcontext);                                                           \
                                                                                       \
   BASE2::dump(dumpcontext);                                                           \
                                                                                       \
   BASE3::dump(dumpcontext);                                                           \
                                                                                       \
   BASE4::dump(dumpcontext);                                                           \
                                                                                       \
}                                                                                      \
                                                                                       \
                                                                                       \
void on_initialize_object() override                                             \
{                                                                                      \
                                                                                       \
   m_papplication = m_pcontext ? m_pcontext->m_papexapplication : nullptr;             \
                                                                                       \
   BASE1::on_initialize_object();                                      \
                                                                       \
   BASE2::on_initialize_object();                                      \
                                                                       \
   BASE3::on_initialize_object();                                      \
                                                                       \
   BASE4::on_initialize_object();                                      \
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
                                                                                       \



template <  typename APPLICATION, typename BASE1 = optional_base1, typename BASE2 = optional_base2, typename BASE3 = optional_base3, typename BASE4 = optional_base4 >
class application_consumer :
   virtual public ::object,
   virtual public BASE1,
   virtual public BASE2,
   virtual public BASE3,
   virtual public BASE4
{
public:


   __pointer(APPLICATION) m_papplication;


   application_consumer()
   {

   }


   APPLICATION_CONSUMER_BODY


   inline APPLICATION* get_application() { return m_papplication.get(); }
   inline APPLICATION* get_application() const { return (APPLICATION*)m_papplication.get(); }


};


template <  typename APPLICATION, typename BASE1 = optional_interaction1, typename BASE2 = optional_interaction2, typename BASE3 = optional_interaction3, typename BASE4 = optional_interaction4 >
class application_interaction :
   virtual public ::object,
   virtual public BASE1, 
   virtual public BASE2,
   virtual public BASE3,
   virtual public BASE4
{
public:


   __pointer(APPLICATION) m_papplication;


   application_interaction()
   {

   }


   void initialize(::object* pobject) override
   {

      //auto estatus = 
      
      BASE1::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      BASE2::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      BASE3::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus =
      
      BASE4::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }

   APPLICATION_CONSUMER_BODY


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


   inline APPLICATION* get_application() { return m_papplication.get(); }
   inline APPLICATION* get_application() const { return (APPLICATION *) m_papplication.get(); }


};



