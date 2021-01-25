#pragma once


namespace calculator
{

   class document;


   class CLASS_DECL_SPHERE view :
      virtual public ::user::impact
   {
   public:
      view(::layered * pobjectContext);
      virtual ~view();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      virtual __pointer(::user::interaction) BackViewGetWnd();

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      virtual void install_message_routing(::channel * pchannel) override;
      virtual bool pre_create_window(::user::system * pusersystem) override;
      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;

      ::user::document * get_document();

      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnPaint);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnContextMenu);
      DECL_GEN_SIGNAL(_001OnSetCursor);
      DECL_GEN_SIGNAL(_001OnUpdateViewEncoding);
      DECL_GEN_SIGNAL(_001OnViewEncoding);
      DECL_GEN_SIGNAL(_001OnWavePlayerEvent);

      virtual void _001OnTabClick(i32 iTab);

   };

} // namespace calculator
