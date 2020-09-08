#pragma once


class CLASS_DECL_AQUA invalid_argument_exception :
   public ::exception::exception
{
public:


   invalid_argument_exception(const char * pszMessage = nullptr);
   virtual ~invalid_argument_exception();


};

