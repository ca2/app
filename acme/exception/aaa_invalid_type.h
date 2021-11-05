#pragma once


class invalid_type :
   virtual public ::exception
{
public:


   invalid_type(const char* pszMessage) :
      exception(pszMessage)
   {
   }


};
