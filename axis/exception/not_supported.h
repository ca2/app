#pragma once


class CLASS_DECL_AURA not_supported_exception :
   virtual public interface_only_exception
{
public:


   not_supported_exception(const char * pszMessage = nullptr);
   virtual ~not_supported_exception();


};
