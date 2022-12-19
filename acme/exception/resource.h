#pragma once


//#include "exception.h"


class CLASS_DECL_ACME resource_exception :
   public ::exception
{
public:


   resource_exception(const scoped_string & strMessage = nullptr);
   ~resource_exception() override;


};
