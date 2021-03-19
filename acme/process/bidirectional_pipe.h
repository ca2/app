#pragma once


namespace process
{


   class CLASS_DECL_ACME bidirectional_pipe :
      virtual public ::matter
   {
   public:


      __pointer(pipe)    m_ppipeIn;
      __pointer(pipe)    m_ppipeOut;


      bidirectional_pipe();
      virtual ~bidirectional_pipe();


      virtual bool create(bool bBlock = true,bool bInherit = false);


   };


} // namespace process



