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


      virtual bool on_create_bars();


      virtual void install_message_routing(::channel * pchannel);


      DECLARE_MESSAGE_HANDLER(_001OnSetText);
      DECLARE_MESSAGE_HANDLER(on_message_create);

   };


} // namespace filamanager





