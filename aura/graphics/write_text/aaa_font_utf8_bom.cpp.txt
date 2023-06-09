#include "framework.h"
#include "font.h"
#include "acme/platform/node.h"
#include "acme/primitive/string/international.h"


namespace write_text
{


   string font::get_sample_text(enum_character_set echaracterset)
   {

      return acmenode()->get_character_set_default_sample_text(echaracterset);

   }


} // namespace write_text



