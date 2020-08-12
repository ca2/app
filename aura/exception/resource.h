#pragma once


class CLASS_DECL_AURA resource_exception :
   public ::exception::exception
{
public:


   resource_exception(const char * pszMessage = nullptr);
   virtual ~resource_exception();


};
