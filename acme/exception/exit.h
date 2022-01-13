#pragma once


class CLASS_DECL_ACME exit_exception :
   public ::exception
{
public:


   int                           m_iCheck;
   __pointer(::task)             m_ptaskExit;


   exit_exception(__pointer(::task) playeredThreadExit = nullptr, const char * pszMessage = nullptr);
   virtual ~exit_exception();


   virtual ::e_status3 finish(::property_object* pcontextobjectFinish = nullptr);


};



