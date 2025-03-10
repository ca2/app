#pragma once


////#include "acme/prototype/prototype/object.h"


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_CORE text_format :
         virtual public ::object
      {
      public:


         virtual void text_format_read(data * pdata, ::binary_stream & binarystream);

         virtual void text_format_write(::binary_stream & binarystream, data * pdata);


      };


   } // namespace rich_text


} // namespace user



