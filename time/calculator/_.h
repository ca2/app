#pragma once


#include "_constant.h"



namespace datetime
{


   class token;
   class scanner;


} // namespace datetime


//#include "acme/primitive/datetime/result.h"


//#include "token.h"
//#include "scanner.h"
//#include "element.h"
//#include "parser.h"
//#include "parser_exception.h"

CLASS_DECL_CA2_TIME bool should_avoid_datetime_parsing_exception();
CLASS_DECL_CA2_TIME bool throw_datetime_parsing_exception(const ::string & strMessage);



