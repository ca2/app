#pragma once


class CLASS_DECL_ACME interface_only_exception :
   public not_implemented
{
public:


   interface_only_exception(const char * pszMessage = nullptr);
   virtual ~interface_only_exception();


};
