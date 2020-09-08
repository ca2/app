#pragma once


class CLASS_DECL_AQUA resource_exception :
   public ::exception::exception
{
public:


   resource_exception(const char * pszMessage = nullptr);
   virtual ~resource_exception();


};
