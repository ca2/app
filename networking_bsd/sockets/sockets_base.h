#pragma once


namespace networking_bsd
{


   class CLASS_DECL_NETWORKING_BSD sockets_base :
      virtual public ::object
   {
   public:


      interlocked_i32                              m_lHttpGetSerial;

      i32                                          m_iErrorCode;

      sockets_base();
      virtual ~sockets_base();

      virtual void initialize(::particle * pparticle) override;

      virtual void destroy() override;


   };


} // namespace networking_bsd



