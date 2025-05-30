#pragma once


namespace networking_bsd
{


   class CLASS_DECL_NETWORKING_BSD sockets_base :
      virtual public ::object
   {
   public:


      interlocked_int                              m_lHttpGetSerial;

      int                                          m_iErrorCode;

      sockets_base();
      virtual ~sockets_base();

      virtual void initialize(::particle * pparticle) override;

      virtual void destroy() override;


   };


} // namespace networking_bsd



