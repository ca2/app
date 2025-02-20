#pragma once



//namespace str
//{


   class CLASS_DECL_ACME base64 :
      virtual public ::particle
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


      ///virtual void initialize(::particle * pparticle) override;


      // from arbitrary binary data to Base 64
      void encode(::file::file * pfileOutput, unsigned char * pdata, memsize size, e_mode emode);
      void encode(::file::file * pfileOutput, ::file::file * pfileInput, e_mode emode = mode_normal);
      //string encode(memory_base & memory, e_mode emode = mode_normal);
      string encode(const ::block & block, e_mode emode = mode_normal);
      //string encode(void  * point, ::collection::count ca, e_mode emode = mode_normal);
      //string encode(const ::scoped_string & scopedstr, e_mode emode = mode_normal);
      //string encode_element(::matter & matter, e_mode emode = mode_normal);

      // from Base 64 to binary data
      bool decode(::file::file * pfileOutput, ::file::file * pfileInput);
      long long decode(const ::block & block, ::file::file * pfileInput);
      bool decode(memory_base & storageBinary, const ::scoped_string & scopedstrBase64);
      long long decode(const ::block & block, const ::scoped_string & scopedstrBase64);
      string decode(const ::scoped_string & scopedstr);
      //bool decode(::matter & matter, const ::scoped_string & scopedstrBase64);

      bool is(int iChar);

   };

//
//} // namespace str
//


