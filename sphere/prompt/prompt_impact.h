#pragma once


namespace prompt
{

   class CLASS_DECL_SPHERE impact :
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

      impact(::particle * pparticle);
      virtual ~impact();



//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;



      void GetDateTime(string & strDateTime);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      void install_message_routing(::channel * pchannel) override;
      virtual bool pre_create_window(::user::system * pusersystem) override;
      virtual void OnDraw(::draw2d::graphics_pointer & pgraphics);      // overridden to draw this ::impact
      void handle(::topic * ptopic, ::context * pcontext) override;
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      void _001OnTimer(::timer * ptimer) override;
      DECLARE_MESSAGE_HANDLER(on_message_right_button_up);

      ::user::document * get_document();

      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(_001OnPaint);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_context_menu);
      //DECLARE_MESSAGE_HANDLER(on_message_set_cursor);
      DECLARE_MESSAGE_HANDLER(_001OnOp);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      virtual void _001OnTabClick(i32 iTab);
   };


} // namespace prompt


