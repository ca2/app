#pragma once


class CLASS_DECL_ACME not_implemented_exception :
   public ::exception
{
public:


   not_implemented_exception(const char * pszMessage = nullptr, const ::e_status & estatus = error_not_implemented);
   ~not_implemented_exception() override;


};
