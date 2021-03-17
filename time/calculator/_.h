#pragma once


//#include "acme/primitive/datetime/result.h"


namespace datetime
{


   /* Tokens */
   enum enum_token
   {
      e_token_none,
      e_token_identifier,
      e_token_function,
      e_token_number,
      e_token_keyword,
      e_token_end,
      e_token_error,
      e_token_addition,
      e_token_subtraction,
      e_token_multiplication,
      e_token_division,
      e_token_equal,
      e_token_semi_colon,
      e_token_open_paren,
      e_token_close_paren,
      e_token_char_error,
      e_token_comma, // ,
   };


} // namespace datetime

#include "token.h"
#include "scanner.h"
#include "element.h"
#include "parser.h"
#include "parser_exception.h"









