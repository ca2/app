#pragma once


#include "exception.h"


class CLASS_DECL_ACME not_implemented :
   public ::exception
{
public:


   not_implemented(const char * pszMessage = nullptr, const ::e_status & estatus = error_not_implemented);
   ~not_implemented() override;


};
