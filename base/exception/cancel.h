#pragma once




class CLASS_DECL_AURA cancel_exception :
   public ::exception::exception
{
public:


   cancel_exception(const char * pszMessage = nullptr);
   virtual ~cancel_exception();


   //virtual bool get_error_message(string & str,PUINT pnHelpContext = nullptr);


};


