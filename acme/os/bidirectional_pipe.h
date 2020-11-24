#pragma once


namespace os
{


   class CLASS_DECL_ACME bidirectional_pipe :
      virtual public ::matter
   {
   public:


      __pointer(pipe)    m_sppipeIn;
      __pointer(pipe)    m_sppipeOut;


      bidirectional_pipe();
      virtual ~bidirectional_pipe();

      virtual bool create(bool bBlock = true,bool bInherit = false);


   };


} // namespace os



