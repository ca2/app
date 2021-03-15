#pragma once


namespace str
{


   class CLASS_DECL_ACME base64 :
      virtual public ::matter
   {
   public:

      enum e_mode
      {

         mode_normal,
         mode_url_safe,
         mode_ex,

      };

   protected:


      uchar etable[3][256];
      uchar dtable[256];


   public:


      base64();
      virtual ~base64();


      ///virtual ::e_status initialize(::context_object * pcontextobject) override;


      // from arbitrary binary data to Base 64
      void encode(::file::file * pfileOutput, u8 * pdata, memsize size, e_mode emode);
      void encode(::file::file * pfileOutput, ::file::file * pfileInput, e_mode emode = mode_normal);
      //string encode(memory_base & memory, e_mode emode = mode_normal);
      string encode(const ::block & block, e_mode emode = mode_normal);
      //string encode(void  * point, ::count ca, e_mode emode = mode_normal);
      //string encode(const char * psz, e_mode emode = mode_normal);
      string encode_element(::matter & matter, e_mode emode = mode_normal);

      // from Base 64 to binary data
      bool decode(::file::file * pfileOutput, ::file::file * pfileInput);
      i64 decode(const ::block & block, ::file::file * pfileInput);
      bool decode(memory_base & storageBinary, const char * pszBase64, strsize s = -1);
      i64 decode(const ::block & block, const char * pszBase64, strsize s = -1);
      string decode(const char * psz);
      bool decode(::matter & matter, const char * pszBase64);

      bool is(int iChar);

   };


} // namespace str



