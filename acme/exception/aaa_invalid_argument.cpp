﻿#include "framework.h"


invalid_argument_exception::invalid_argument_exception(const char * pszMessage):
   ::exception(pszMessage)
{

}


invalid_argument_exception::~invalid_argument_exception()
{

}



