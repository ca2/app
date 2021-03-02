#pragma once


namespace prompt
{

   class CLASS_DECL_SPHERE view :
      virtual public ::user::impact,
      virtual public ::user::interaction
   {
   public:


      
      enum e_message
      {
         MessageOp = WM_USER + 1123,
      };

      enum EOp
      {
         OpUpdateCurrentArea,
      };

      view(::layered * pobjectContext);
      virtual ~view();



      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;



      void GetDateTime(string & strDateTime);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      virtual void install_message_routing(::channel * pchannel) override;
      virtual bool pre_create_window(::user::system * pusersystem) override;
      virtual void OnDraw(::draw2d::graphics_pointer & pgraphics);      // overridden to draw this ::view
      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;
      DECL_GEN_SIGNAL(on_message_left_button_down);
      DECL_GEN_SIGNAL(on_message_left_button_up);
      void _001OnTimer(::timer * ptimer) override;
      DECL_GEN_SIGNAL(_001OnRButtonUp);

      ::user::document * get_document();

      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnPaint);
      DECL_GEN_SIGNAL(on_message_create);
      DECL_GEN_SIGNAL(_001OnContextMenu);
      DECL_GEN_SIGNAL(_001OnSetCursor);
      DECL_GEN_SIGNAL(_001OnOp);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      virtual void _001OnTabClick(i32 iTab);
   };


} // namespace prompt


