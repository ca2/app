#pragma once


//#include "exception_installing.h"


class CLASS_DECL_ACME installing_exception :
   public temporary_exception
{
public:


   installing_exception(const char * pszMessage = nullptr);
   virtual ~installing_exception();


};
