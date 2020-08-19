#pragma once


class CLASS_DECL_AURA range_error :
   public ::exception::error
{
   // aura class for resource-critical aura API exceptions
   // handles composite and initialization of an error message
public:


   range_error(const char * pszMessage = nullptr);
   virtual ~range_error();


};



