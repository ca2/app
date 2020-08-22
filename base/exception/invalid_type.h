#pragma once


class invalid_type :
   virtual public ::exception::exception
{
public:


   invalid_type(const char* pszMessage) :
      exception(pszMessage)
   {
   }


};
