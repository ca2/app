#pragma once


class CLASS_DECL_ACME exit_exception :
   public ::exception
{
public:


   int                           m_iCheck;
   ::pointer<::task>             m_ptaskExit;


   exit_exception(::pointer<::task> playeredThreadExit = nullptr, const char * pszMessage = nullptr);
   virtual ~exit_exception();


   virtual ::e_status finish(::property_object* pcontextobjectFinish = nullptr);


};



