#pragma once


namespace app_app
{


   class CLASS_DECL_APP_APP_APP window :
      virtual public ::user::interaction
   {
   public:


      window();
      virtual ~window();


      virtual void install_message_routing(::channel* pchannel) override;


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      DECL_GEN_SIGNAL(_001OnClose);
      DECL_GEN_SIGNAL(_001OnDisplayChange);


   };


} // namespace app_app












