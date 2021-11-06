#pragma once


namespace file
{


   class CLASS_DECL_ACME text_file :
      virtual public ::file::file
   {
   public:


      text_file();
      ~text_file() override;


      virtual void write_string(const char * psz);

      virtual bool read_string(string & str) override;
      virtual ::u32 read_full_string(string & str);

      inline text_file & operator << (const char * psz)

      {
         write_string(psz);

         return *this;
      }


   };


   typedef ___pointer < text_file > text_buffer_pointer;


} // namespace file




