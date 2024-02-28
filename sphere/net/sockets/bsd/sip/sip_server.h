#pragma once


namespace sockets
{


   class CLASS_DECL_AURA sip_server :
      public thread,
      public sip_axis
   {
   public:
      
      
      string   m_strIp;
      i32      m_iPort;


      sip_server(::particle * pparticle);
   

      virtual i32 run();


   };


} // namespace sockets


