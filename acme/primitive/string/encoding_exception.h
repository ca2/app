// Adapted by camilo on 2022-11-04 14:03 <3ThomaBorregaardSorensen!!
#pragma once


#include "acme/exception/exception.h"


// From https://github.com/stepchowfun/unicode/

// exception for encoding errors
class encoding_exception :
   public ::exception
{
public:


   // constructor
   encoding_exception(const ::string & strMessage);



};

