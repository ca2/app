#pragma once


class CLASS_DECL_AURA runtime_error :
   public ::exception::error
{
   // aura class for resource-critical aura API exceptions
   // handles composite and initialization of an error message
public:


   runtime_error(const char * pszMessage = nullptr);
   virtual ~runtime_error();

};
