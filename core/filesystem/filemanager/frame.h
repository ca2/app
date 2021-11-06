#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE frame :
      virtual public simple_frame_window
   {
   public:


      id m_idTab;


      frame();
      ~frame() override;


      ::e_status on_create_bars() override;


      void install_message_routing(::channel * pchannel) override;


      DECLARE_MESSAGE_HANDLER(_001OnSetText);
      DECLARE_MESSAGE_HANDLER(on_message_create);

   };


} // namespace filamanager





