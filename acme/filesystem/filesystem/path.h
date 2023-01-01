#pragma once


#include "file_path.h"
#include "acme/primitive/datetime/file_time_span.h"
//#include "acme/primitive/datetime/file_time.h"
#include "acme/primitive/primitive/particle.h"
//#include "acme/primitive/primitive/pointer.h"
// #include "acme/primitive/string/string.h"


namespace file
{


   struct  path_meta :
      public file_time_set
   {

      enum_path                  m_epath;

      i64                        m_iSize; // if negative, not set/calculated/retrieved the file size_i32(for directories would be all contained elements total sum size_i32)
      int                        m_iDir; // if negative, not set/calculated/retrieved whether is a directory/folder/(file/folder/(...) container)
      strsize                    m_iName; // if negative, not set/calculated/retrieved where name starts
      strsize                    m_iBasePathLength; // if negative, not set/calculated/retrieved base path length in the path
      ::pointer<::particle>      m_pparticleOsPath;
       enumeration < ::file::enum_flag > m_flags;

      path_meta(enum_path epath = e_path_none, i64 iSize = -1, i32 iDir = -1, i64 iName = -1, strsize iBasePathLength = -1, enumeration < ::file::enum_flag > eflag = ::file::e_flag_none);

      ~path_meta();


       enumeration < ::file::enum_flag > & flags() {return m_flags;}
       const enumeration < ::file::enum_flag > & flags() const {return m_flags;}



   };


   // not rigorous at all file::path ... more "ryg"orous with performance and like you should know what are you doing
   class path :
      public string,
      public path_meta
   {
   public:


      using RANGE = typename ::string::RANGE;


      path() { m_epath = e_path_file; }
      path(enum_path epath) { m_epath = epath; }
      path(enum_no_initialize) : string(e_no_initialize) { }
      path(nullptr_t) { }
      //path(enum_for_moving) { }
      //path(enum_get_buffer, strsize len) { get_string_buffer(len); }
      path(const path & path) : string(path), path_meta(path) {}
      path(const ::ansi_string & str, enum_path epath = e_path_none, int iDir = -1, bool bNormalize = true, i64 iSize = -1);
      path(const ::wd16_string & str, enum_path epath = e_path_none, int iDir = -1, bool bNormalize = true, i64 iSize = -1);
      path(const ::wd32_string & str, enum_path epath = e_path_none, int iDir = -1, bool bNormalize = true, i64 iSize = -1);
      path(const ::ansi_character * pansisz, enum_path epath = e_path_none, int iDir = -1, bool bNormalize = true, i64 iSize = -1);
      path(const ::wd16_character * pansisz, enum_path epath = e_path_none, int iDir = -1, bool bNormalize = true, i64 iSize = -1);
      path(const ::wd32_character * pansisz, enum_path epath = e_path_none, int iDir = -1, bool bNormalize = true, i64 iSize = -1);
      path(const ::scoped_string & scopedstr, enum_path epath = e_path_none, int iDir = -1, bool bNormalize = true, i64 iSize = -1);

      //template<typed_range<::ansi_character *> RANGE>
      //path(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str); }
      //template<typed_range<const ::ansi_character *> RANGE>
      //path(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str); }
      //template<typed_range<::wd16_character *> RANGE>
      //path(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str); }
      //template<typed_range<const ::wd16_character *> RANGE>
      //path(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str); }
      //template<typed_range<::wd32_character *> RANGE>
      //path(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str); }
      //template<typed_range<const ::wd32_character *> RANGE>
      //path(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str); }


      //template<typed_range<::ansi_character *> RANGE>
      //path(const RANGE & str, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, count); }
      //template<typed_range<const ::ansi_character *> RANGE>
      //path(const RANGE & str, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, count); }
      //template<typed_range<::wd16_character *> RANGE>
      //path(const RANGE & str, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, count); }
      //template<typed_range<const ::wd16_character *> RANGE>
      //path(const RANGE & str, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, count); }
      //template<typed_range<::wd32_character *> RANGE>
      //path(const RANGE & str, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, count); }
      //template<typed_range<const ::wd32_character *> RANGE>
      //path(const RANGE & str, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, count); }



      //template<typed_range<::ansi_character *> RANGE>
      //path(const RANGE & str, strsize start, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, start, count); }
      //template<typed_range<const ::ansi_character *> RANGE>
      //path(const RANGE & str, strsize start, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, start, count); }
      //template<typed_range<::wd16_character *> RANGE>
      //path(const RANGE & str, strsize start, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, start, count); }
      //template<typed_range<const ::wd16_character *> RANGE>
      //path(const RANGE & str, strsize start, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, start, count); }
      //template<typed_range<::wd32_character *> RANGE>
      //path(const RANGE & str, strsize start, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, start, count); }
      //template<typed_range<const ::wd32_character *> RANGE>
      //path(const RANGE & str, strsize start, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, start, count); }

      //   path(const ::const_ansi_range & ansirange) : NATURAL_POINTER(e_no_initialize){construct2(ansirange);}
   //   path(const ::const_wd16_range & wd16range) : NATURAL_POINTER(e_no_initialize){construct2(wd16range);}
   //   path(const ::const_wd32_range & wd32range) : NATURAL_POINTER(e_no_initialize){construct2(wd32range);}
      //path(const const_ansi_range & ansirange) : NATURAL_POINTER(e_no_initialize) { construct2(ansirange, 0, -1); }
      //path(const const_wd16_range & wd16range) : NATURAL_POINTER(e_no_initialize) { construct2(wd16range, 0, -1); }
      //path(const const_wd32_range & wd32range) : NATURAL_POINTER(e_no_initialize) { construct2(wd32range, 0, -1); }
      //path(const const_ansi_range & ansirange, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(ansirange, 0, len); }
      //path(const const_wd16_range & wd16range, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(wd16range, 0, len); }
      //path(const const_wd32_range & wd32range, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(wd32range, 0, len); }
      //path(const const_ansi_range & ansirange, strsize start, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(ansirange, start, len); }
      //path(const const_wd16_range & wd16range, strsize start, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(wd16range, start, len); }
      //path(const const_wd32_range & wd32range, strsize start, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(wd32range, start, len); }
      template < primitive_character CHARACTER2 >
      path(const CHARACTER2 * start, const CHARACTER2 * end) : path(start, end-start) {}
      template < primitive_character CHARACTER2 >
      path(const CHARACTER2 * start) : path(start, 0, string_safe_length(start)) {}
      template < primitive_character CHARACTER2 >
      path(const CHARACTER2 * start, strsize len) : path(::string(start, len)) {}
//      template < primitive_character CHARACTER2 >
//      path(const CHARACTER2 * pszSource, strsize start, strsize len) :path(::string(pszSource, start, len)){}
      template < primitive_character CHARACTER2, strsize sizeMaximumLength >
      path(const inline_string < CHARACTER2, sizeMaximumLength > & inlinestring) :
         path(inlinestring.begin(), inlinestring.end())
      { }
      //   path(const ::ansi_character * pansichar, strsize len);
         //path(::str < iterator > str) : path((const_iterator)str.begin(), (const_iterator)str.end()) {}
         //path(::str < const_iterator > str) : path(str.begin(), str.end()) {}
         //path(::block block) : path((const_iterator)block.begin(), (const_iterator)block.end()) {}
         //path(const path & str);
          //path(const ::wd16_character * pwd16char);
      //   path(const ::wd16_character * pwd16char, strsize len);
         //path(const ::wd32_character * pwd32char);
      //   path(const ::wd32_character * pwd32char, strsize len);
      //   path(const ::wd32_character * pwd32char, strsize len, strsize pos) : path(pwd32char + pos, len) { }
         //template < primitive_character CHARACTER2 >
      path(const_iterator begin, const_iterator end) : path(begin, end - begin) { }
      //path(const path & str) : path(str, 0, str.size()) { }
      //path(const path & str, strsize len) : path(str, 0, len) { }
      //path(const path & str, strsize start, strsize len);
   //   template < primitive_character CHARACTER2 >
   //   path(const ::range < const CHARACTER2 * > & strSource) : path(strSource, 0, strSource.size()) {}
   //   template < primitive_character CHARACTER2 >
   //   path(const ::range < const CHARACTER2 * > & strSource, strsize len) : path(strSource, 0, minimum(strSource.size(), len)) {}
   //   template < primitive_character CHARACTER2 >
   //   path(const ::range < const CHARACTER2 * > & strSource, strsize start, strsize len);
      //path(const simple_ansistring& simpleansistr);
      //path(const simple_wd16string& simplewd16str);
      //path(const simple_wd32string& simplewd32str);
      template < primitive_character CHARACTER2 >
      path(CHARACTER2 chSrc, strsize repeat);
      path(::ansi_character ansich) : path(::string(ansich)) {}
      path(::wd16_character wd16ch) : path(::string(wd16ch)) {}
      path(::wd32_character wd32ch) : path(::string(wd32ch)) {}
      //path(const character & character, strsize repeat = 1) :path(character.m_wd32char, repeat) {}
      path(const ::atom & atom);
      path(const ::payload & payload);
      path(const ::property & property);

      template < character_range RANGE >
      path(const RANGE & range) : path(::string(range)) { }


      //template < has_as_string HAS_AS_STRING >
      //path(const HAS_AS_STRING & has_as_string) : path(has_as_string.as_string()) {}
      //inline ~path() {}

//      path() { m_epath = e_path_file; }
//      path(nullptr_t) {}
//      path(const ::ansi_string & str, enum_path epath = e_path_none, int iDir = -1, bool bNormalize = true, i64 iSize = -1);
////      path(const ::wd16_string & wd16str, enum_path epath = e_path_none, int iDir = -1, bool bNormalize = true, i64 iSize = -1) :
////         path((const::ansi_string &)wd16str, epath, iDir, bNormalize, iSize) {}
////      path(const ::wd32_string & wd32str, enum_path epath = e_path_none, int iDir = -1, bool bNormalize = true, i64 iSize = -1) :
////         path((const::ansi_string &)wd32str, epath, iDir, bNormalize, iSize) {}
//      path(const ::scoped_string & scopedstr, enum_path epath = e_path_none, int iDir = -1, bool bNormalize = true, i64 iSize = -1) :
//         path((const::ansi_string &)psz, epath, iDir, bNormalize, iSize) {}
////      path(const ::wd16_character * pwd16sz, enum_path epath = e_path_none, int iDir = -1, bool bNormalize = true, i64 iSize = -1) :
////         path((const::ansi_string &)pwd16sz, epath, iDir, bNormalize, iSize) {}
////      path(const ::wd32_character * pwd32sz, enum_path epath = e_path_none, int iDir = -1, bool bNormalize = true, i64 iSize = -1) :
////         path((const::ansi_string &)pwd32sz, epath, iDir, bNormalize, iSize) {}
//      //path(::ansi_character ch, enum_path epath = e_path_none, int iDir = -1, bool bNormalize = true, i64 iSize = -1) :
//        // path((const::ansi_string &)ch, epath, iDir, bNormalize, iSize) {}
//      path(enum_path epath) { m_epath = epath; }
//      path(const path& path);
//      path(const ::atom & atom) : path(::string(atom)){}
//      path(const ::payload & payload);
//      path(const ::property & property);
////      path(const ::string & str);
      ~path() noexcept;


      //void construct() { *this = ::file::path(); }
      


      
      void set_type(enum_path epath);

      //::file::path replace_extension(const ::scoped_string & scopedstrNewExtension, const ::scoped_string & scopedstrOldExtension);
      void set_all_extensions(const ::ansi_string & strNewExtension);
      void set_final_extension(const ::ansi_string & strNewExtension);

      ::file::path with_all_extensions(const ::ansi_string & strNewExtension) const;
      ::file::path with_final_extension(const ::ansi_string & strNewExtension) const;

      inline char separator() const
      {

         return file_path_separator(m_epath);

      }

      inline const char* separator_sz() const
      {

         return file_path_separator_sz(m_epath);

      }

      inline char other_separator() const
      {

         return file_path_other_separator(m_epath);

      }


      path & operator = (const ::file::path & path);

      template < character_range RANGE >
      path & operator = (const RANGE & range)
      {

         return operator = (::file::path(range));

      }


      //path & operator = (const ::ansi_string & str);

//      bool is_equal_full(const path & path) const
//      {
//
//#ifdef WINDOWS
//
//         if (_stricmp(c_str(), path.c_str()) == 0) // undoubtely eaqual...
//            return true;
//
//#else
//
//         if (strcmp(c_str(), path.c_str()) == 0) // undoubtely eaqual...
//            return true;
//
//#endif
//
//         return __node_further_file_is_equal(*this, path);
//
//      }


      bool is_equal_fast(const path & path) const
      {

#ifdef WINDOWS

         if (_stricmp(c_str(), path.c_str()) == 0) // undoubtely eaqual...
            return true;

#else

         if (strcmp(c_str(), path.c_str()) == 0) // undoubtely eaqual...
            return true;

#endif

         return false;

      }


      bool operator == (const path & path) const
      {

         return is_equal_fast(path);

      }

      template < strsize n >
      bool operator == (const char (&cha)[n]) const
      {

         return operator ==(::string(cha));

      }

      bool operator == (const ::string & str) const;
      /*{

         return is_equal_fast(path(block));

      }*/



      //bool operator == (const ::ansi_string & str) const;


      bool operator == (const ::scoped_string & scopedstr) const;


      bool operator != (const path & path) const;

      bool operator != (const ::ansi_string & str) const;

      bool operator != (const ::scoped_string & scopedstr) const;
      //      bool operator == (const path & path) const;

      //      bool operator == (const ::ansi_string & str) const;
      //      bool operator == (const ::scoped_string & scopedstr) const;
      //bool operator == (const ::payload & payload) const;

      //      bool operator != (const path & path) const;

      //      bool operator != (const ::ansi_string & str) const;
      //      bool operator != (const ::scoped_string & scopedstr) const;
      //bool operator != (const ::payload & payload) const;

      //path operator + (const path & path) const;



      //path & operator += (const path & path);
      path & operator += (const ::string & str);
      //path & operator += (const ::const_ansi_range & ansirange);
      //using path_meta::operator+=;

      //template < typename T > path slashed_path(const T & t) const {return ::transfer(_slashed_path(::file::path(t)));}
      path slashed_path(const ::scoped_string & scopedstr) const;
      path operator / (const ::scoped_string & scopedstr) const;
      //path operator / (const path & path) const;
      //path operator / (const ::ansi_character * psz) const;
      //path operator / (const ::string & str) const;

      path slash_path(const ::scoped_string & scopedstr) const;
      //path & operator /= (const path & path);
      //path & operator /= (const ::ansi_string & str);
      //path & operator /= (const ::inline_number_string &inlinenumberstring);
      path & operator /= (const ::scoped_string & scopedstr);
      //path & operator /= (const ::atom & atom);


      bool is_empty() const;
      bool has_char() const;


//      template <
//

      //::file::path & file_cat(const ::ansi_string & str) { return *this + str; }

      //::file::path & operator | (const ::ansi_string & str) { return file_cat(str); } // what is good here is the operator precedence

      //string arg(const ::ansi_string & str) const { return ((const string &)*this) + str; }

      //string operator << (const ::ansi_string & str) const { return arg(str); }

      //path & operator = (const ::scoped_string & scopedstr);
      //path & operator += (const ::scoped_string & scopedstr);

      //path & operator = (const ::payload & payload);
      //path & operator += (const ::payload & payload);

      //path & operator = (const property & property);
      //path & operator += (const property & property);

      //path & operator = (const wstring & wstr);
      //path & operator += (const wstring & wstr);

      //path & operator = (const ::wide_character * psz);
      //path & operator += (const ::wide_character * psz);

      //path operator * () const;

      //path operator -- () const;
      //path operator -- (int) const { return operator --(); }


//      void to_string(string & str) const;

      path sibling(const path & path) const;
      path sibling(const ::ansi_string & str) const;
      path sibling(const ::scoped_string & scopedstr) const;

      path operator * (const path & path) const;

      path operator * (const ::ansi_string & str) const;
      path operator * (const ::scoped_string & scopedstr) const;
      //path operator * (const property & property) const;

      path & operator *= (const path & path);

      path & operator *= (const ::ansi_string & str);
      path & operator *= (const ::scoped_string & scopedstr);
      //path & operator *= (const property & property);

      ::file::path title() const;

      string name() const;

      //string name(index i /* = -1 */) const;

      /// return index pointing to beginning of name
      const_iterator find_name() const;

      /// return index just after first dot in file name
      /// -1 if not found
      const_iterator find_all_extensions() const;

      /// return index just after last dot in file name
      /// -1 if not found
      const_iterator find_final_extension() const;

      //      bool is_equal(const ::file::path & path2) const;

      string all_extensions() const;

      //string ext() const;

      string final_extension() const;

      //void split(string_array & patha) const;
      bool is_relative();

      //string_array & ascendants_name(string_array & namea) const;
      //string_array ascendants_name() const;

      path relative() const;


      path folder() const;
      path folder(int i) const;
      path parent() const;
      path ascendant(int i) const;
      path & ascend();
      path & ascend(int i);
      path operator - (int i) const { return this->ascendant(i); }
      path & operator -= (int i);
      //using path_meta::operator -=;


      //inline path operator | (enum_flag e) const { path path(*this); path |= e; return path; }


      ::file::path & patch_base_path(const ::file::path & pathBase);


   };


   // e_path file_path_get_type(const ::ansi_string & str, e_path epathForce);


    bool case_insensitive_begins_eat(string & str, const ::scoped_string & scopedstrPrefix);




} // namespace file





inline const char * FormatArgument(const ::file::path & value) noexcept;


template<>
inline u32hash u32_hash < const ::file::path & >(const ::file::path & key);


// ::file::path node_full_file_path(file::path path);


// ::file::path __xxxnode_full_file_path(file::path path);



//inline ::file::path operator / (const ::ansi_character * psz, const ::file::path & pathConcat)
//{
//
//   string str(psz);
//
//   ::file::path path(str);
//
//   return path / pathConcat;
//
//}


template < character_range RANGE1, character_range RANGE2 >
::file::path operator / (const RANGE1 & range1, const RANGE2 & range2)
{

   return ::transfer(::file::path(range1).slashed_path(range2));

}



template < primitive_character CHARACTER2, character_range RANGE >
::file::path operator / (const CHARACTER2 * psz, const RANGE & range)
{

   return ::transfer(::file::path(psz) / ::string(range));

}


template < character_range RANGE1, primitive_character CHARACTER2 >
::file::path operator / (const RANGE1 & range1, const CHARACTER2 * psz)
{

   return ::transfer(::file::path(range1) / ::file::path(psz));

}



