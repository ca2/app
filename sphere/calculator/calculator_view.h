#pragma once


namespace calculator
{

   class document;


   class CLASS_DECL_SPHERE impact :
      virtual public ::user::impact
   {
   public:
      impact(::object * pobject);
      virtual ~impact();


      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;


      virtual __pointer(::user::interaction) BackViewGetWnd();

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      void install_message_routing(::channel * pchannel) override;
      virtual bool pre_create_window(::user::system * pusersystem) override;
      virtual void handle(::subject * psubject, ::context * pcontext) override;

      ::user::document * get_document();

      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(_001OnPaint);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_context_menu);
      //DECLARE_MESSAGE_HANDLER(on_message_set_cursor);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateViewEncoding);
      DECLARE_MESSAGE_HANDLER(_001OnViewEncoding);
      DECLARE_MESSAGE_HANDLER(_001OnWavePlayerEvent);

      virtual void _001OnTabClick(i32 iTab);

   };

} // namespace calculator
