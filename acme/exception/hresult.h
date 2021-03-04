#pragma once


#ifdef WINDOWS


class CLASS_DECL_ACME hresult_exception :
   public ::exception::exception
{
public:


   hresult_exception(HRESULT hresult, const char * pszMessage = nullptr);
   virtual ~hresult_exception();


};


#endif



