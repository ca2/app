#pragma once
#include "acme/exception/parsing.h"

namespace dynamic_source
{
   class browser_build_error : public ::parsing_exception
   {
   public:
      explicit browser_build_error(const ::scoped_string & message) : parsing_exception(message) {}
   };
}
