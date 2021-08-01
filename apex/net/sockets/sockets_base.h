#pragma once


namespace sockets
{


   class CLASS_DECL_APEX sockets_base :
      virtual public ::object
   {
   public:


      interlocked_i32                              m_lHttpGetSerial;

      i32                                          m_iErrorCode;

      sockets_base();
      virtual ~sockets_base();

      virtual ::e_status initialize(::object * pobject) override;

      virtual ::e_status destroy() override;


   };


} // namespace sockets



