#pragma once


namespace file
{


   class CLASS_DECL_APEX text_file :
      virtual public ::file::file
   {
   public:

            text_file();
      virtual ~text_file();


      virtual void write_string(const char * psz);

      virtual bool read_string(string & str);
      virtual UINT read_full_string(string & str);

      inline text_file & operator << (const char * psz)

      {
         write_string(psz);

         return *this;
      }


   };


   typedef pointer < text_file > text_buffer_pointer;


} // namespace file




