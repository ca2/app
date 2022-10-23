#pragma once


#include "not_implemented.h"


class CLASS_DECL_ACME interface_only :
   public not_implemented
{
public:


   interface_only(const char * pszMessage = nullptr, const ::e_status & estatus = error_interface_only);
   ~interface_only() override;


};
