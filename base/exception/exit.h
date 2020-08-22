#pragma once


class CLASS_DECL_AURA exit_exception :
   public ::exception::exception
{
public:


   int                        m_iCheck;
   __pointer(::thread)        m_pthreadExit;


   exit_exception(__pointer(::thread) pthreadExit = nullptr, const char * pszMessage = nullptr);
   virtual ~exit_exception();


   virtual void set_finish();


};



