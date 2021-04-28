#pragma once


namespace user
{


   class CLASS_DECL_BASE main_frame : 
      public simple_frame_window
   {
   public:


      bool           m_bPlacing;
      
      
      main_frame();
      virtual ~main_frame();

      virtual void install_message_routing(::channel * pchannel);


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      DECLARE_MESSAGE_HANDLER(on_message_create);

   };


} // namespace user


