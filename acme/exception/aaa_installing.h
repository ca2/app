#pragma once


//#include "exception_installing.h"


class CLASS_DECL_ACME installing_exception :
   public temporary_exception
{
public:


   installing_exception(const ::scoped_string & scopedstrMessage = nullptr);
   virtual ~installing_exception();


};
