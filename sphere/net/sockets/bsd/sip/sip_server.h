#pragma once


namespace sockets
{


   class CLASS_DECL_AURA sip_server :
      public thread,
      public sip_axis
   {
   public:
      
      
      string   m_strIp;
      int      m_iPort;


      sip_server(::particle * pparticle);
   

      virtual int run();


   };


} // namespace sockets


