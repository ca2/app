#pragma once


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_CORE text_format :
         virtual public ::object
      {
      public:


         virtual ::e_status     text_format_load(data * pdata, ::file::file * pfileIn);

         virtual ::e_status     text_format_save(::file::file* pfileOut, data * pdata);


      };


   } // namespace rich_text


} // namespace user



