#pragma once


//#include "exception.h"
#include "acme/parallelization/task.h"
//#include "acme/prototype/prototype/pointer.h"


class CLASS_DECL_ACME exit_exception :
   public ::exception
{
public:


   int                           m_iCheck;
   ::pointer<::task>             m_ptaskExit;


   exit_exception(const ::e_status & estatus = error_failed, ::task * playeredThreadExit = nullptr, const ::scoped_string & scopedstrMessage = nullptr);
   exit_exception(::platform::application * papplication, const ::scoped_string & scopedstrMessage = nullptr);
   exit_exception(::platform::session * psession, const ::scoped_string & scopedstrMessage = nullptr);
   exit_exception(::platform::system * psystem, const ::scoped_string & scopedstrMessage = nullptr);
   ~exit_exception() override;


   virtual ::e_status finish(::property_object* pcontextobjectFinish = nullptr);


};



