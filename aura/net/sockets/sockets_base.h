#pragma once


namespace sockets
{


   class CLASS_DECL_AURA sockets_base :
      virtual public ::object
   {
   public:


      interlocked_long                             m_lHttpGetSerial;

      i32                                          m_iErrorCode;

      sockets_base();
      virtual ~sockets_base();

      virtual ::estatus initialize(::object * pobjectContext) override;

      virtual void finalize() override;


   };


} // namespace sockets



