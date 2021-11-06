#pragma once


namespace android
{


   namespace axis
   {


      class CLASS_DECL_AXIS dir :
         virtual public ::android::dir,
         virtual public ::file::dir::axis::system
      {
      public:




         string      m_strca2;


         dir(::object * pobject);


         //         virtual bool  ls_pattern(::aura::application *  papp, const ::string & lpcsz, const ::string & lpcszPattern, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr, bool_array * pbaIsDir = nullptr, i64_array * piaSize = nullptr);
         //         virtual bool  ls(::aura::application *  papp, const ::string & lpcsz, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr, bool_array * pbaIsDir = nullptr, i64_array * piaSize = nullptr);
         //         virtual bool  rls_pattern(::aura::application *  papp, const ::string & lpcsz, const ::string & lpcszPattern, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr, string_array * pstraRelative = nullptr, bool_array * pbaIsDir = nullptr, i64_array * piaSize = nullptr, e_extract eextract = extract_first);
         //         virtual bool  rls(::aura::application *  papp, const ::string & lpcsz, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr, string_array * pstraRelative = nullptr, e_extract eextract = extract_first);
         //         virtual bool  rls_dir(::aura::application *  papp, const ::string & lpcsz, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr, string_array * pstraRelative = nullptr);
         //         virtual bool  ls_dir(::aura::application *  papp, const ::string & lpcsz, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr);
         //         virtual bool  ls_file(::aura::application *  papp, const ::string & lpcsz, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr);

         virtual ::file::listing & ls(::aura::application * app, ::file::listing & listing);


         virtual bool  is(const ::file::path & lpcsz, ::aura::application * papp);
         virtual bool  name_is(const ::file::path & str, ::aura::application * papp);


         virtual bool initialize();
      };


   } // namespace axis


} // namespace android


















