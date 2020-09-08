#pragma once


class CLASS_DECL_ACME exit_exception :
   public ::exception::exception
{
public:


   int                        m_iCheck;
   __pointer(::generic)       m_pgenericExit;


   exit_exception(::generic * pgenericExit = nullptr, const char * pszMessage = nullptr);
   virtual ~exit_exception();


   virtual void set_finish();


};



