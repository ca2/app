#pragma once


class CLASS_DECL_BASE simple_main_frame :
   virtual public simple_frame_window
{
public:


   bool                       m_bPlacing;
   bool                       m_bExplicitTranslucency;




   simple_main_frame();
   virtual ~simple_main_frame();


   virtual void assert_valid() const override;
   virtual void dump(dump_context & dumpcontext) const override;


   virtual void install_message_routing(::channel * pchannel) override;


   DECLARE_MESSAGE_HANDLER(on_message_create);

   


};



