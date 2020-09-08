#pragma once


class CLASS_DECL_AQUA os_exception :
   public ::exception::exception
{
public:


   os_exception(const char * pszMessage = nullptr);
   virtual ~os_exception();


};

