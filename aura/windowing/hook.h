// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#pragma once


namespace windowing
{


   class CLASS_DECL_AURA hook :
      virtual public ::matter
   {
   public:


      hook();


      virtual bool process_event(display * pdisplay, event * pevent);

      virtual ::e_status do_hook();

      virtual ::e_status unhook();

      virtual void on_idle(display * pdisplay);


   };


   using hook_map = map < hook *, __pointer(hook) >;


} // namespace windowing



