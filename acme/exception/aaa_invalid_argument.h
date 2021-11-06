#pragma once


class CLASS_DECL_ACME invalid_argument_exception :
   public ::exception
{
public:


   invalid_argument_exception(const char * pszMessage = nullptr);
   virtual ~invalid_argument_exception();


};

