//#pragma once
//
//
//#ifdef WINDOWS_DESKTOP
//
//
//namespace user
//{
//
//   // top level window for receiving system messages broadcasted to top level windows in Windows
//
//   class CLASS_DECL_AURA system_interaction :
//      virtual public ::user::interaction
//   {
//      public:
//
//         
//         system_interaction();
//         virtual ~system_interaction();
//
//
//         virtual void install_message_routing(::channel * pchannel) override;
//
//         DECLARE_MESSAGE_HANDLER(_001OnMessage);
//         DECLARE_MESSAGE_HANDLER(_001OnDestroy);
//
//
//         virtual bool DestroyWindow() override;
//         
//         virtual bool is_system_message_window() override;
//   
//
//   };
//
//
//} // namespace base
//
//
//#endif
//
//
