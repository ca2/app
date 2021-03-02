#pragma once


class CLASS_DECL_ACME temporary_exception :
   public ::exception::exception
{
public:


   temporary_exception(const char * pszMessage = nullptr);
   virtual ~temporary_exception();


};


