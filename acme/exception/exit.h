#pragma once


//#include "exception.h"
#include "acme/parallelization/task.h"
//#include "acme/primitive/primitive/pointer.h"


class CLASS_DECL_ACME exit_exception :
   public ::exception
{
public:


   int                           m_iCheck;
   ::pointer<::task>             m_ptaskExit;


   exit_exception(const ::e_status & estatus = error_failed, ::task * playeredThreadExit = nullptr, const ::scoped_string & scopedstrMessage = nullptr);
   exit_exception(::acme::application * papplication, const ::scoped_string & scopedstrMessage = nullptr);
   exit_exception(::acme::session * psession, const ::scoped_string & scopedstrMessage = nullptr);
   exit_exception(::acme::system * psystem, const ::scoped_string & scopedstrMessage = nullptr);
   ~exit_exception() override;


   virtual ::e_status finish(::property_object* pcontextobjectFinish = nullptr);


};



