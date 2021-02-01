// created by Camilo 2021-01-31 05:26 BRT <3CamiloSasukeThomasBorregaardSoerensen
#pragma once


namespace windows
{


   class CLASS_DECL_APEX interprocess_communication_rx :
      virtual public ::interprocess_communication::rx
   {
   public:


      interprocess_communication_rx();
      virtual ~interprocess_communication_rx();


      bool create(const char * pszChannel);
      bool destroy();


      virtual void * on_interprocess_receive(rx * prx, const char * pszMessage);
      virtual void * on_interprocess_receive(rx * prx, int message, void * pdata, memsize len);
      virtual void * on_interprocess_post(rx * prx, i64 a, i64 b);


      virtual bool on_idle();


      lresult message_queue_proc(UINT message, wparam wparam, lparam lparam);

   };


} // namespace windows







































