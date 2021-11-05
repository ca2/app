#pragma once


#ifdef WINDOWS

class CLASS_DECL_ACME bstr
{
public:

   
   static void copy(BSTR &bstrDest, const BSTR bstrSrc);
   static void copy(BSTR &bstrDest, const string &strSrc);
   static void copy(string &strDest, const BSTR bstrSrc);
   static bool IsEqual(const BSTR bstrA, const BSTR bstrB);



};

#endif
