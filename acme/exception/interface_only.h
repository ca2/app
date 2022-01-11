#pragma once


class CLASS_DECL_ACME interface_only_exception :
   public not_implemented_exception
{
public:


   interface_only_exception(const char * pszMessage = nullptr, const ::e_status3 & estatus = error_interface_only);
   ~interface_only_exception() override;


};
