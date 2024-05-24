#pragma once


//#include "exception.h"
#include "acid/parallelization/task.h"
//#include "acid/primitive/primitive/pointer.h"


class CLASS_DECL_ACID exit_exception :
   public ::exception
{
public:


   int                           m_iCheck;
   ::pointer<::task>             m_ptaskExit;


   exit_exception(const ::e_status & estatus = error_failed, ::task * playeredThreadExit = nullptr, const ::scoped_string & scopedstrMessage = nullptr);
   exit_exception(::acid::application * papplication, const ::scoped_string & scopedstrMessage = nullptr);
   exit_exception(::acid::session * psession, const ::scoped_string & scopedstrMessage = nullptr);
   exit_exception(::acid::system * psystem, const ::scoped_string & scopedstrMessage = nullptr);
   ~exit_exception() override;


   virtual ::e_status finish(::property_object* pcontextobjectFinish = nullptr);


};



