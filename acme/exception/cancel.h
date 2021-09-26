#pragma once




class CLASS_DECL_ACME cancel_exception :
   public ::exception
{
public:


   cancel_exception(const char * pszMessage = nullptr);
   virtual ~cancel_exception();


   //virtual bool get_error_message(string & str,P::u32 pnHelpContext = nullptr);


};


