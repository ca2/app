#pragma once


#include "file_path.h"
#include "acme/primitive/datetime/file_time_span.h"
//#include "acme/primitive/datetime/file_time.h"
#include "acme/primitive/primitive/particle.h"
//#include "acme/primitive/primitive/pointer.h"
#include "acme/primitive/string/string.h"


namespace file
{


   struct  path_meta :
      public enumeration < ::file::enum_flag >,
      public file_time_set
   {

      enum_path                  m_epath;

      i64                        m_iSize; // if negative, not set/calculated/retrieved the file size_i32(for directories would be all contained elements total sum size_i32)
      int                        m_iDir; // if negative, not set/calculated/retrieved whether is a directory/folder/(file/folder/(...) container)
      strsize                    m_iName; // if negative, not set/calculated/retrieved where name starts
      strsize                    m_iBasePathLength; // if negative, not set/calculated/retrieved base path length in the path
      ::pointer<::particle>      m_pparticleOsPath;


      path_meta(enum_path epath = e_path_none, i64 iSize = -1, i32 iDir = -1, i64 iName = -1, strsize iBasePathLength = -1, enumeration < ::file::enum_flag > eflag = ::file::e_flag_none);

      ~path_meta();

      using enumeration < ::file::enum_flag >::operator -=;


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
      path(const string & str, enum_path epath = e_path_none, int iDir = -1, bool bNormalize = true, i64 iSize = -1);


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

      //   path(const ::const_ansi_raw_range & ansirange) : NATURAL_POINTER(e_no_initialize){construct2(ansirange);}
   //   path(const ::const_wd16_raw_range & wd16range) : NATURAL_POINTER(e_no_initialize){construct2(wd16range);}
   //   path(const ::const_wd32_raw_range & wd32range) : NATURAL_POINTER(e_no_initialize){construct2(wd32range);}
      //path(const const_ansi_raw_range & ansirange) : NATURAL_POINTER(e_no_initialize) { construct2(ansirange, 0, -1); }
      //path(const const_wd16_raw_range & wd16range) : NATURAL_POINTER(e_no_initialize) { construct2(wd16range, 0, -1); }
      //path(const const_wd32_raw_range & wd32range) : NATURAL_POINTER(e_no_initialize) { construct2(wd32range, 0, -1); }
      //path(const const_ansi_raw_range & ansirange, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(ansirange, 0, len); }
      //path(const const_wd16_raw_range & wd16range, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(wd16range, 0, len); }
      //path(const const_wd32_raw_range & wd32range, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(wd32range, 0, len); }
      //path(const const_ansi_raw_range & ansirange, strsize start, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(ansirange, start, len); }
      //path(const const_wd16_raw_range & wd16range, strsize start, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(wd16range, start, len); }
      //path(const const_wd32_raw_range & wd32range, strsize start, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(wd32range, start, len); }
      template < primitive_character CHARACTER2 >
      path(const CHARACTER2 * pszSource) : path(pszSource, 0, string_safe_length(pszSource)) {}
      template < primitive_character CHARACTER2 >
      path(const CHARACTER2 * pszSource, strsize len) : path(pszSource, 0, len) {}
      template < primitive_character CHARACTER2 >
      path(const CHARACTER2 * pszSource, strsize start, strsize len) :path(::string(pszSource, start, len)){}
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
   //   path(const ::string_range < const CHARACTER2 * > & strSource) : path(strSource, 0, strSource.size()) {}
   //   template < primitive_character CHARACTER2 >
   //   path(const ::string_range < const CHARACTER2 * > & strSource, strsize len) : path(strSource, 0, minimum(strSource.size(), len)) {}
   //   template < primitive_character CHARACTER2 >
   //   path(const ::string_range < const CHARACTER2 * > & strSource, strsize start, strsize len);
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
//      path(const char * psz, enum_path epath = e_path_none, int iDir = -1, bool bNormalize = true, i64 iSize = -1) :
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

      //::file::path replace_extension(const char * pszNewExtension, const char * pszOldExtension);
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


      bool operator == (const ::string & str) const;
      /*{

         return is_equal_fast(path(block));

      }*/



      //bool operator == (const ::ansi_string & str) const;


      bool operator == (const char * psz) const
      {

         return operator == (string(psz));

      }


      bool operator != (const path & path) const
      {

         return !operator==(path);

      }

      bool operator != (const ::ansi_string & str) const;

      bool operator != (const char * psz) const
      {

         return operator != (string(psz));

      }
      //      bool operator == (const path & path) const;

      //      bool operator == (const ::ansi_string & str) const;
      //      bool operator == (const char * psz) const;
      //bool operator == (const ::payload & payload) const;

      //      bool operator != (const path & path) const;

      //      bool operator != (const ::ansi_string & str) const;
      //      bool operator != (const char * psz) const;
      //bool operator != (const ::payload & payload) const;

      //path operator + (const path & path) const;



      //path & operator += (const path & path);
      path & operator += (const ::string & str);
      //path & operator += (const ::const_ansi_raw_range & ansirange);
      //using path_meta::operator+=;
      path operator / (const path & path) const;
      path operator / (const ::ansi_string & str) const;
      path operator / (const char * psz) const;
      path operator / (const ::atom & atom) const;

      path & operator /= (const path & path);
      path & operator /= (const ::ansi_string & str);
      path & operator /= (const ::inline_number_string &inlinenumberstring);
      path & operator /= (const char * psz);
      path & operator /= (const ::atom & atom);


      bool is_empty() const;
      bool has_char() const;


      
      

      //::file::path & file_cat(const ::ansi_string & str) { return *this + str; }

      //::file::path & operator | (const ::ansi_string & str) { return file_cat(str); } // what is good here is the operator precedence

      //string arg(const ::ansi_string & str) const { return ((const string &)*this) + str; }

      //string operator << (const ::ansi_string & str) const { return arg(str); }

      //path & operator = (const char * psz);
      //path & operator += (const char * psz);

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
      path sibling(const char * psz) const;

      path operator * (const path & path) const;

      path operator * (const ::ansi_string & str) const;
      path operator * (const char * psz) const;
      //path operator * (const property & property) const;

      path & operator *= (const path & path);

      path & operator *= (const ::ansi_string & str);
      path & operator *= (const char * psz);
      //path & operator *= (const property & property);

      ::file::path title() const;

      string name() const;

      //string name(index i /* = -1 */) const;

      /// return index pointing to beginning of name
      index find_name() const;

      /// return index just after first dot in file name
      /// -1 if not found
      index find_all_extensions() const;

      /// return index just after last dot in file name
      /// -1 if not found
      index find_final_extension() const;

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
      using path_meta::operator -=;


      inline path operator | (enum_flag e) const { path path(*this); path |= e; return path; }


      ::file::path & patch_base_path(const ::file::path & pathBase)
      {

         auto iBasePathLength = m_iBasePathLength;

         if (iBasePathLength < 0)
         {

            iBasePathLength = 0;

         }

         auto pszRelative = c_str() + iBasePathLength;

         *this = pathBase / pszRelative;

         m_iBasePathLength = pathBase.length() + 1;

         return *this;

      }


   };


   // e_path file_path_get_type(const ::ansi_string & str, e_path epathForce);


    bool case_insensitive_begins_eat(string & str, const char * pcszPrefix);




} // namespace file





inline const char * FormatArgument(const ::file::path & value) noexcept;


template<>
inline u32hash u32_hash < const ::file::path & >(const ::file::path & key);


// ::file::path node_full_file_path(file::path path);


// ::file::path __xxxnode_full_file_path(file::path path);



inline ::file::path  operator / (const ::ansi_character * psz, const ::file::path & pathConcat)
{

   string str(psz);

   ::file::path path(str);

   return path / pathConcat;

}







namespace file
{


   inline path_meta::path_meta(enum_path epath, i64 iSize, i32 iDir, i64 iName, strsize iBasePathLength, enumeration < ::file::enum_flag > eflag)
   {

      m_epath = epath;
      m_iSize = iSize;
      m_iDir = iDir;
      m_iName = (strsize)iName;
      m_iBasePathLength = iBasePathLength;
      enumeration < ::file::enum_flag >::m_eenum = eflag.enumeration < ::file::enum_flag >::m_eenum;

   }


   inline path_meta::~path_meta()
   {


   }


   //inline path::path(const ::payload& payload) :
   //   path(payload.file_path())
   //{


   //}


   //inline path::path(const ::property& property) :
   //   path(property.file_path())
   //{


   //}


   //inline path::path(const ::atom& atom) :
   //   path(atom.string())
   //{


   //}

   //   path::path(nullptr_t)
   //   {
   //
   //      m_epath = path_file;
   //
   //   }


   //   path::path(e_path epath)
   //   {
   //
   //      m_epath = epath;
   //
   //   }
      //namespace file
      //{

   //inline path::path(const path& path) :
   //   string((const string&)path),
   //   path_meta(path)
   //{

   //}


   //inline path::path(const path_object& path) :
   //   ::file::path((const ::file::path&)path)
   //{

   //}


   inline path::path(const ::ansi_string& str, enum_path epath, int iDir, bool bNormalizePath, i64 iSize) :
      string(str)
   {

      m_iSize = iSize;

      if (epath == e_path_none)
      {

         m_epath = file_path_get_type(str, epath);

      }
      else
      {

         m_epath = epath;

      }

      if (bNormalizePath)
      {

         bool bCertainlySyntathicallyDir = file_path_normalize_inline(*this, m_epath);

         if (bCertainlySyntathicallyDir)
         {

            m_iDir = 1;

         }
         else
         {

            m_iDir = iDir;

         }

      }
      else
      {

         m_iDir = iDir;

      }

   }




   //
   //} // namespace file
   //


   //   path::path(const unichar * pwsz, strsize iCount, e_path epath, int iDir, bool bNormalizePath, i64 iSize) :
   //      string(pwsz, iCount),
   //      path_meta(epath, iSize, iDir)
   //   {
   //
   //      if (m_epath == path_none)
   //      {
   //
   //         m_epath = file_path_get_type(*this, epath);
   //
   //      }
   //
   //      if (bNormalizePath)
   //      {
   //
   //         bool bCertainlySyntathicallyDir = normalize_path_inline(*this, m_epath);
   //
   //         if (bCertainlySyntathicallyDir)
   //         {
   //
   //            m_iDir = 1;
   //
   //         }
   //         else
   //         {
   //
   //            m_iDir = iDir;
   //
   //         }
   //
   //      }
   //
   //   }



   //   path::path(const atom & atom,e_path epath, int iDir) :
   //      path(string(atom), epath, iDir)
   //   {
   //
   //   }


   //   path::path(const ::payload & payload, e_path epath, int iDir) :
   //      path(payload.get_string(), epath, iDir)
   //   {
   //
   //
   //   }


   //   path::path(const path & path) :
   //      ::ansi_string((const string &)path),
   //      path_meta((path_meta &)path),
   //      path_os((path_os &) path)
   //   {
   //
   //   }


   //   path::path(path && path) :
   //      string(::move(path)),
   //      path_meta((path_meta &) path),
   //      path_os(::move(path))
   //   {
   //
   //   }


   //   path::path(const char * psz, e_path epath, int iDir):
   //      path(string(psz), epath, iDir)
   //   {
   //
   //   }

   //   path::path(const unichar * psz, e_path epath, int iDir) :
   //      path(string(psz), epath, iDir)
   //   {
   //
   //   }


   //   path::path(const wstring & wstr, e_path epath, int iDir):
   //      path(string(wstr), epath, iDir)
   //   {
   //
   //   }

   inline path::~path() noexcept
   {


   }


   //   bool path::is_equal(const path & path) const
   //   {
   //
   //
   //#ifdef WINDOWS
   //
   //      if (((const string &)*this).case_insensitive_order((const string &)path) == 0) // undoubtely eaqual...
   //         return true;
   //
   //#else
   //
   //      if (((const string &)*this).operator == ((const string &)path)) // undoubtely eaqual...
   //         return true;
   //
   //#endif
   //
   //      return false;
   //
   //      // find extend equalitys..
   //
   //      ::file::path_array patha1;
   //
   //      split(patha1);
   //
   //      ::file::path_array patha2;
   //
   //      path.split(patha2);
   //
   //      if(patha1.get_size() == patha2.get_size())
   //      {
   //
   //         for(index i = 0; i < patha1.get_size(); i++)
   //         {
   //
   //            if(patha1[i].::ansi_string::operator!=(patha2[i]))
   //            {
   //
   //               goto there_s_difference_in_this_step_1;
   //
   //            }
   //
   //         }
   //
   //         return true;
   //
   //      }
   //
   //      there_s_difference_in_this_step_1:
   //
   //
   //      return false;
   //
   //   }


   //inline void path::split(string_array& patha) const
   //{

   //   ascendants_name(patha);

   //}




   //inline string path::name(index i) const
   //{


   //   string_array patha;

   //   ascendants_name(patha);

   //   if (i < 0)
   //   {

   //      i += patha.get_size();

   //   }


   //   if (i < 0)
   //   {

   //      return "";

   //   }

   //   if (i >= patha.get_size())
   //   {

   //      return "";

   //   }

   //   return patha[i];

   //}


   //inline string_array& path::ascendants_name(string_array& straParam) const
   //{

   //   string strPath = *this;

   //   if (strPath == "/")
   //   {

   //      straParam.add("/");

   //      return straParam;

   //   }

   //   strsize iFirstColon = find(':');
   //   strsize iFirstSlash = find('/');
   //   strsize iSecondSlash = find('/', iFirstSlash + 1);

   //   if (iFirstColon > 0 && iFirstSlash == iFirstColon + 1 && iSecondSlash == iFirstSlash + 1)
   //   {

   //      ::file::path path = Left(iSecondSlash + 1);

   //      straParam.add(path);

   //      strPath = Mid(iSecondSlash + 1);

   //   }

   //   bool bWin1 = strPath.begins_eat("\\\\?\\");

   //   index iFind = 0;
   //   while (true)
   //   {

   //      index iFind1 = strPath.find('/', iFind);
   //      index iFind2 = strPath.find('\\', iFind);
   //      index iFind3 = minimum_non_negative(iFind1, iFind2);
   //      if (iFind3 < 0)
   //      {
   //         string str = strPath.Mid(iFind);
   //         straParam.add(str);
   //         break;
   //      }
   //      string str = strPath.Mid(iFind, iFind3 - iFind);
   //      straParam.add(str);
   //      iFind = iFind3 + 1;
   //   }


   //   if (bWin1)
   //   {
   //      straParam[0] = "\\\\?\\" + straParam[0];
   //   }
   //   else if (this->case_insensitive_begins("/"))
   //   {
   //      straParam[0] = "/" + straParam[0];
   //   }
   //   else if (this->case_insensitive_begins("\\\\"))
   //   {
   //      straParam[0] = "\\\\" + straParam[0];
   //   }

   //   return straParam;

   //}


   inline path path::folder(int i) const
   {

      ::file::path path(*this);

      while (i > 0)
      {

         path = path.folder();

         i--;

      }

      return path;

   }


   inline path& path::ascend()
   {

      return *this = parent();

   }


   inline path& path::ascend(int i)
   {

      while (i > 0)
      {

         ascend();

         i--;

      }

      return *this;

   }


//   inline path& path::operator += (const path& path)
//   {
//
//      string str = path;
//
//      str.trim_left("\\/");
//
//      string::operator += (str);
//
//      return *this;
//
//   }


   //inline path& path::operator += (const ::const_ansi_raw_range & range)
   //{

   //   string str(range);

   //   str.trim_left("\\/");

   //   string strThis = *this;

   //   string ::operator = (file_path_normalize(strThis + str, m_epath));

   //   return *this;

   //}


   inline path & path::operator += (const ::string & str)
   {

      str.span("\\/");

      auto pathThis = *this;

      pathThis.::string::operator = (file_path_normalize(pathThis + str, this->m_epath));

      return *this;

   }



   //   path_array path::operator / (const string_array & stra) const
   //   {
   //
   //      path_array patha;
   //
   //      for (auto str : stra)
   //      {
   //
   //         patha.add(*this / str);
   //
   //      }
   //
   //      return patha;
   //
   //   }


   inline path path::operator / (const path& path) const
   {

      string strPath;

      strPath = c_str();

      if (strPath.is_empty())
      {

         return path;

      }

      string str = path;

      bool bJustAfterProtocol = strPath.Right(3) == "://";

      if (bJustAfterProtocol || m_epath == e_path_url)
      {

         str.replace_with("/", "\\");

         //str.trim_left("/");

         if (bJustAfterProtocol)
         {

            return ::file::path(strPath + str, m_epath, path.m_iDir);

         }
         else
         {

            return ::file::path(strPath + "/" + str, m_epath, path.m_iDir);

         }

      }

      strPath += separator();

      str.trim_left("\\/");

      return ::file::path(strPath + str, m_epath, path.m_iDir);

   }


   inline path path::operator / (const ::ansi_string& str) const
   {

      return operator /(::file::path(str));

   }


   //template < primitive_atom ATOM >
   //inline path path::operator / (const ATOM & atom) const
   //{

   //   return operator /(::file::path(atom));

   //}


   inline path path::operator / (const char* psz) const
   {

      return operator /(::file::path(psz));

   }

   inline path& path::operator /= (const path& path)
   {

      string strPath;

      strPath = string(*this);

      string str = path;

      if (strPath.Right(3) == "://")
      {

         return operator = (::file::path(strPath + str, m_epath));

      }

      if (strPath.is_empty())
      {

         strPath = separator();

      }
      else if (strPath.size() == 1 && strPath[0] == separator())
      {

      }
      else
      {

         strPath += separator();

         str.trim_left("\\/");

      }

      return operator = (::file::path(strPath + str, m_epath));

   }


   inline path& path::operator /= (const ::ansi_string& str)
   {

      return operator /=(::file::path(str));

   }


   inline path & path::operator /= (const ::inline_number_string & inlinenumberstring)
   {

      return operator /=(::file::path(::string(inlinenumberstring)));

   }


   inline path& path::operator /= (const ::atom & atom)
   {

      return operator /=(::file::path(atom));

   }


   inline path& path::operator /= (const char* psz)
   {

      return operator /=(::file::path(psz));

   }


   //::file::path path::replace_extension(const char * pszNewExtension, const char * pszOldExtension)
   //{

   //   string strNewExtension(pszNewExtension);

   //   strNewExtension.case_insensitive_begins_eat(".");

   //   string strOldExtension(pszOldExtension);

   //   strOldExtension.case_insensitive_begins_eat(".");

   //   ::file::path path(*this);

   //   path.case_insensitive_ends_eat(strOldExtension);

   //   path += strNewExtension;

   //   return path;

   //}


   inline void path::set_all_extensions(const ::ansi_string& strNewExtension)
   {

      string strExtension(strNewExtension);

      strExtension.case_insensitive_begins_eat(".");

      auto iFind = find_all_extensions();

      if (iFind >= 1)
      {

         this->operator = (Left(iFind) + strExtension);

      }
      else
      {

         this->operator += ("." + strExtension);

      }

   }


   inline void path::set_final_extension(const ::ansi_string& strNewExtension)
   {

      string strExtension(strNewExtension);

      strExtension.case_insensitive_begins_eat(".");

      auto iFind = find_final_extension();

      if (iFind >= 1)
      {

         this->operator = (Left(iFind) + strExtension);

      }
      else
      {

         this->operator += ("." + strExtension);

      }

   }


   inline ::file::path path::with_all_extensions(const ::ansi_string& strNewExtension) const
   {

      ::file::path path(*this);

      path.set_all_extensions(strNewExtension);

      return ::move(path);

   }


   inline ::file::path path::with_final_extension(const ::ansi_string& strNewExtension) const
   {

      ::file::path path(*this);

      path.set_final_extension(strNewExtension);

      return ::move(path);

   }


   inline void path::set_type(enum_path epath)
   {

      if (epath != m_epath)
      {

         m_epath = epath;

         ::ansi_string ::operator = (file_path_normalize(*this, m_epath));

      }

   }





   inline path& path::operator = (const ::file::path& path)
   {

      if (&path != this)
      {

         string::operator  = ((const string&)path);
         *((path_meta*)this) = (const path_meta&)path;
         //#ifdef WINDOWS_DESKTOP
         //         m_idlist = path.m_idlist;
         //#endif

      }

      return *this;


   }


//   inline path& path::operator = (const ::ansi_string& str)
//   {
//
//      *((path_meta*)this) = path_meta();
//
//      m_epath = file_path_get_type(str);
//
//      string ::operator  = (file_path_normalize(str, m_epath));
//
//      return *this;
//
//   }


   //inline path path::operator + (const path& path) const
   //{

   //   return ::file::path((const string&)*this + string((const string&)path), m_epath);

   //}


   //inline path path::operator + (const ::ansi_string& str) const
   //{

   //   return ::file::path((const string&)*this + (m_iDir > 0 ? separator_sz() : "") + string((const string&)str), m_epath);

   //}


   //inline path path::operator + (const char* psz) const
   //{

   //   return operator + (string(psz));

   //}



//   inline path& path::operator = (const char* psz)
//   {
//
//      return operator = (string(psz));
//
//   }


   //inline path& path::operator += (const char* psz)
   //{

   //   return operator += (string(psz));

   //}

//   inline path& path::operator = (const wstring& wstr)
//   {
//
//      return operator = (string(wstr));
//
//   }

   //inline path& path::operator += (const wstring& wstr) { return operator += (string(wstr)); }

   ////inline path& path::operator = (const ::wide_character* psz) { return operator = (wstring(psz)); }
   //inline path& path::operator += (const ::wide_character* psz) { return operator += (wstring(psz)); }

   //void path::to_string(string & str) const
   //{
   //   
   //   str = *this;

   //}

   inline path path::operator * (const path& path) const
   {

      return sibling(path);

   }

   inline path path::operator * (const ::ansi_string& str) const { return operator * (::file::path(str)); }
   inline path path::operator * (const char* psz) const { return operator * (::file::path(psz)); }

   inline path& path::operator *= (const path& path)
   {

      if (this != &path)
      {

         *this = sibling(path);

      }

      return *this;

   }

   inline path& path::operator *= (const ::ansi_string& str) { return operator *= (::file::path(str)); }
   inline path& path::operator *= (const char* psz) { return operator *= (::file::path(psz)); }


   inline ::file::path path::title() const
   {

      return ::file_path_title(operator const char* ());

   }


   inline string path::name() const
   {

      return ::file_path_name(operator const char* ());

   }


   //void path::calc_name() const
   //{
   //   m_iName = find_file_name();
   //   m_strName = Mid(m_iName);
   //}





   inline index path::find_name() const
   {

      return maximum(0, rear_find(separator()) + 1);

   }


   inline index path::find_final_extension() const
   {

      auto psz = file_path_final_extension(c_str());

      if (!psz)
      {

         return -1;

      }

      return psz - c_str() + 1;

   }


   inline index path::find_all_extensions() const
   {

      auto psz = file_path_all_extensions(c_str());

      if (!psz)
      {

         return -1;

      }

      return psz - c_str() + 1;

   }


   inline bool path::is_relative()
   {

      return file_path_is_relative(*this) != false;

   }


   inline path path::relative() const
   {

      return Mid(maximum(0, m_iBasePathLength));

   }


   inline path path::parent() const
   {

      return folder();

   }


   inline path path::ascendant(int i) const
   {

      return folder(i);

   }


   inline path& path::operator -= (int i)
   {

      return ascend(i);

   }


   inline bool path::is_empty() const
   {

      return ::ansi_string::is_empty();

   }


   inline bool path::has_char() const
   {

      return !is_empty();

   }

//
//   inline bool path::operator == (const ::ansi_string& str) const
//   {
//
//      return operator == (path(str));
//
//   }

   inline bool path::operator == (const ::string & str) const
   {

      return operator == (path(str));

   }

   inline bool path::operator != (const ::ansi_string& str) const
   {

      return operator != (path(str));

   }


} // namespace file


inline ::file::path operator+(const ::file::path & path1, const ::file::path & path2)
{

   return ::move(::file::path(((const::string &)path1) + ((const ::string&)path2)));

}


inline ::file::path operator+(const ::file::path & path, const ::string & str)
{

   return ((const::string &)path) + str;
}


inline ::file::path operator+ (const ::file::path & path, const char * psz) 
{

   return ((const::string &)path) + psz;
}


inline ::file::path operator+ (const ::file::path & path, const ::atom & atom) 
{

   return ((const::string &)path) + atom;

}


inline ::file::path operator+(const ::file::path & path, const ::file::path::RANGE & range)
{

   return ((const::string &)path) + ::string(range);

}



template < strsize m_sizeMaximumLength >
inline ::file::path operator +(const ::file::path & path, const ::inline_string < char, m_sizeMaximumLength > & inlinestring)
{

   return ((const ::string &)path) + ::string(inlinestring);

}




inline ::file::path operator+(const ::string & str, const ::file::path & path)
{

   return str + ((const::string &)path);
}


inline ::file::path operator+(const ::const_ansi_range & range, const ::file::path & path)
{

   return ::string(range) + ((const::string &)path);

}



template < ::count c >
inline ::file::path operator +(const char(&sz)[c], const ::file::path & path)
{

   return ::string(sz) + ((const::string &)path);

}





