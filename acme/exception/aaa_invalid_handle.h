#pragma once


class CLASS_DECL_ACME invalid_handle_exception :
   public os_exception
{
public:


   invalid_handle_exception(const char * pszMessage = nullptr);
   virtual ~invalid_handle_exception();


};

