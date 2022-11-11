#pragma once


#include "exception.h"


class CLASS_DECL_ACME resource_exception :
   public ::exception
{
public:


   resource_exception(const char * pszMessage = nullptr);
   ~resource_exception() override;


};
