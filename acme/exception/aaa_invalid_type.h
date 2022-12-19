#pragma once


class invalid_type :
   virtual public ::exception
{
public:


   invalid_type(const scoped_string & strMessage) :
      exception(pszMessage)
   {
   }


};
