#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE frame :
      virtual public simple_frame_window
   {
   public:

      


      id m_idTab;


      frame();
      virtual ~ frame();


      virtual bool on_create_bars();


      virtual void install_message_routing(::channel * pchannel);


      DECL_GEN_SIGNAL(_001OnSetText);
      DECL_GEN_SIGNAL(_001OnCreate);

   };


} // namespace filamanager





