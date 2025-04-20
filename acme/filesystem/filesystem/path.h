#pragma once


#include "file_path.h"
#include "acme/prototype/datetime/file_time_span.h"
//#include "acme/prototype/datetime/file_time.h"
#include  "acme/prototype/prototype/particle.h"
//#include "acme/prototype/prototype/pointer.h"
#include "acme/prototype/string/character_range.h"


class windows_path;


namespace file
{


   DECLARE_ENUMERATION(e_type, enum_type);


   struct  path_meta :
      public file_time_set
   {

      enum_path                  m_epath;

      long long                        m_iSize; // if negative, not set/calculated/retrieved the file int_size(for directories would be all contained elements total sum int_size)
      e_type                     m_etype;
      character_count                    m_iName; // if negative, not set/calculated/retrieved where name starts
      character_count                    m_iBasePathLength; // if negative, not set/calculated/retrieved base path length in the path
      ::pointer<::particle>      m_pparticleOsPath;
       enumeration < ::file::enum_flag > m_flags;

      path_meta(enum_path epath = e_path_none, long long iSize = -1, e_type etype = e_type_unknown, long long iName = -1, character_count iBasePathLength = -1, enumeration < ::file::enum_flag > eflag = ::file::e_flag_none);

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
      using CHARACTER = typename RANGE::CHARACTER;
      using ITEM = CHARACTER;


      path() { m_epath = e_path_file; }
      path(enum_path epath) { m_epath = epath; }
      path(no_initialize_t) : string(no_initialize_t{}) { }
      path(nullptr_t) { }
      //path(enum_for_moving) { }
      //path(enum_get_buffer, character_count len) { get_buffer(len); }
      path(const path & path) : string(path), path_meta(path) {}
      template < typename ITERATOR_TYPE, int t_size >
      path(const const_string_range_static_array < ITERATOR_TYPE, t_size >& a, enum_path epath = e_path_none, e_type etype = e_type_unknown, bool bNormalize = true, long long iSize = -1);
      //template < character_range RANGE >
      //path(const RANGE & range, enum_path epath = e_path_none, e_type etype = e_type_unknown, bool bNormalize = true, long long iSize = -1);
      // 
      // 
      // 
      
      template < character_range RANGE >
      inline path(const RANGE& range, enum_path epath = e_path_none, e_type etype = e_type_unknown, bool bNormalizePath = true, long long iSize = -1)
         requires
         !(::std::is_base_of_v < path, RANGE >
            || ::std::is_same_v < path, RANGE >) :
         string(range)
      {

         m_iSize = iSize;

         if (epath == e_path_none)
         {

            m_epath = file_path_get_type(*this, epath);

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

               m_etype = (enum_type)((etype | e_type_folder2) & ~e_type_file2);

            }
            else
            {

               m_etype = etype;

            }

         }
         else
         {

            m_etype = etype;

         }

      }



      //path(const ::wd16_string & str, enum_path epath = e_path_none, e_type etype = e_type_unknown, bool bNormalize = true, long long iSize = -1);
      //path(const ::wd32_string & str, enum_path epath = e_path_none, e_type etype = e_type_unknown, bool bNormalize = true, long long iSize = -1);
      //path(const ::ansi_character * pansisz, enum_path epath = e_path_none, e_type etype = e_type_unknown, bool bNormalize = true, long long iSize = -1);
      //path(const ::wd16_character * pansisz, enum_path epath = e_path_none, e_type etype = e_type_unknown, bool bNormalize = true, long long iSize = -1);
      //path(const ::wd32_character * pansisz, enum_path epath = e_path_none, e_type etype = e_type_unknown, bool bNormalize = true, long long iSize = -1);
      //template < character_range CHARACTER_RANGE >
      //path(const CHARACTER_RANGE & range, enum_path epath = e_path_none, e_type etype = e_type_unknown, bool bNormalize = true, long long iSize = -1);

      //template<typed_range<::ansi_character *> RANGE>
      //path(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct2(str); }
      //template<typed_range<const ::ansi_character *> RANGE>
      //path(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct2(str); }
      //template<typed_range<::wd16_character *> RANGE>
      //path(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct2(str); }
      //template<typed_range<const ::wd16_character *> RANGE>
      //path(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct2(str); }
      //template<typed_range<::wd32_character *> RANGE>
      //path(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct2(str); }
      //template<typed_range<const ::wd32_character *> RANGE>
      //path(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct2(str); }


      //template<typed_range<::ansi_character *> RANGE>
      //path(const RANGE & str, character_count count) : NATURAL_POINTER(no_initialize_t{}) { construct2(str, count); }
      //template<typed_range<const ::ansi_character *> RANGE>
      //path(const RANGE & str, character_count count) : NATURAL_POINTER(no_initialize_t{}) { construct2(str, count); }
      //template<typed_range<::wd16_character *> RANGE>
      //path(const RANGE & str, character_count count) : NATURAL_POINTER(no_initialize_t{}) { construct2(str, count); }
      //template<typed_range<const ::wd16_character *> RANGE>
      //path(const RANGE & str, character_count count) : NATURAL_POINTER(no_initialize_t{}) { construct2(str, count); }
      //template<typed_range<::wd32_character *> RANGE>
      //path(const RANGE & str, character_count count) : NATURAL_POINTER(no_initialize_t{}) { construct2(str, count); }
      //template<typed_range<const ::wd32_character *> RANGE>
      //path(const RANGE & str, character_count count) : NATURAL_POINTER(no_initialize_t{}) { construct2(str, count); }



      //template<typed_range<::ansi_character *> RANGE>
      //path(const RANGE & str, character_count start, character_count count) : NATURAL_POINTER(no_initialize_t{}) { construct2(str, start, count); }
      //template<typed_range<const ::ansi_character *> RANGE>
      //path(const RANGE & str, character_count start, character_count count) : NATURAL_POINTER(no_initialize_t{}) { construct2(str, start, count); }
      //template<typed_range<::wd16_character *> RANGE>
      //path(const RANGE & str, character_count start, character_count count) : NATURAL_POINTER(no_initialize_t{}) { construct2(str, start, count); }
      //template<typed_range<const ::wd16_character *> RANGE>
      //path(const RANGE & str, character_count start, character_count count) : NATURAL_POINTER(no_initialize_t{}) { construct2(str, start, count); }
      //template<typed_range<::wd32_character *> RANGE>
      //path(const RANGE & str, character_count start, character_count count) : NATURAL_POINTER(no_initialize_t{}) { construct2(str, start, count); }
      //template<typed_range<const ::wd32_character *> RANGE>
      //path(const RANGE & str, character_count start, character_count count) : NATURAL_POINTER(no_initialize_t{}) { construct2(str, start, count); }

      //   path(const ::const_ansi_range & ansirange) : NATURAL_POINTER(no_initialize_t{}){construct2(ansirange);}
   //   path(const ::const_wd16_range & wd16range) : NATURAL_POINTER(no_initialize_t{}){construct2(wd16range);}
   //   path(const ::const_wd32_range & wd32range) : NATURAL_POINTER(no_initialize_t{}){construct2(wd32range);}
      //path(const const_ansi_range & ansirange) : NATURAL_POINTER(no_initialize_t{}) { construct2(ansirange, 0, -1); }
      //path(const const_wd16_range & wd16range) : NATURAL_POINTER(no_initialize_t{}) { construct2(wd16range, 0, -1); }
      //path(const const_wd32_range & wd32range) : NATURAL_POINTER(no_initialize_t{}) { construct2(wd32range, 0, -1); }
      //path(const const_ansi_range & ansirange, character_count len) : NATURAL_POINTER(no_initialize_t{})  { construct2(ansirange, 0, len); }
      //path(const const_wd16_range & wd16range, character_count len) : NATURAL_POINTER(no_initialize_t{})  { construct2(wd16range, 0, len); }
      //path(const const_wd32_range & wd32range, character_count len) : NATURAL_POINTER(no_initialize_t{})  { construct2(wd32range, 0, len); }
      //path(const const_ansi_range & ansirange, character_count start, character_count len) : NATURAL_POINTER(no_initialize_t{})  { construct2(ansirange, start, len); }
      //path(const const_wd16_range & wd16range, character_count start, character_count len) : NATURAL_POINTER(no_initialize_t{})  { construct2(wd16range, start, len); }
      //path(const const_wd32_range & wd32range, character_count start, character_count len) : NATURAL_POINTER(no_initialize_t{})  { construct2(wd32range, start, len); }
      template < primitive_character CHARACTER2 >
      path(const CHARACTER2 * start, const CHARACTER2 * end, enum_path epath = e_path_none, e_type etype = e_type_unknown, bool bNormalize = true, long long iSize = -1) : 
         path(::string(start, end), epath, etype, bNormalize, iSize) {}
      template < primitive_character CHARACTER2 >
      path(const CHARACTER2 * start, enum_path epath = e_path_none, e_type etype = e_type_unknown, bool bNormalize = true, long long iSize = -1) : 
         path(::string(start), epath, etype, bNormalize, iSize) {}
      template < primitive_character CHARACTER2 >
      path(const CHARACTER2 * start, character_count len, enum_path epath = e_path_none, e_type etype = e_type_unknown, bool bNormalize = true, long long iSize = -1) :
         path(::string(start, len), epath, etype, bNormalize, iSize) {}
//      template < primitive_character CHARACTER2 >
//      path(const CHARACTER2 * pszSource, character_count start, character_count len) :path(::string(pszSource, start, len)){}
      template < primitive_character CHARACTER2, character_count sizeMaximumLength >
      path(const inline_string < CHARACTER2, sizeMaximumLength > & inlinestring) :
         path(inlinestring.begin(), inlinestring.end())
      { }
      //   path(const ::ansi_character * pansichar, character_count len);
         //path(::str < iterator > str) : path((const_iterator)str.begin(), (const_iterator)str.end()) {}
         //path(::str < const_iterator > str) : path(str.begin(), str.end()) {}
         //path(::block block) : path((const_iterator)block.begin(), (const_iterator)block.end()) {}
         //path(const path & str);
          //path(const ::wd16_character * pwd16char);
      //   path(const ::wd16_character * pwd16char, character_count len);
         //path(const ::wd32_character * pwd32char);
      //   path(const ::wd32_character * pwd32char, character_count len);
      //   path(const ::wd32_character * pwd32char, character_count len, character_count pos) : path(pwd32char + pos, len) { }
         //template < primitive_character CHARACTER2 >
      path(const_iterator begin, const_iterator end) : path(begin, end - begin) { }
      //path(const path & str) : path(str, 0, str.size()) { }
      //path(const path & str, character_count len) : path(str, 0, len) { }
      //path(const path & str, character_count start, character_count len);
   //   template < primitive_character CHARACTER2 >
   //   path(const ::range < const CHARACTER2 * > & strSource) : path(strSource, 0, strSource.size()) {}
   //   template < primitive_character CHARACTER2 >
   //   path(const ::range < const CHARACTER2 * > & strSource, character_count len) : path(strSource, 0, minimum(strSource.size(), len)) {}
   //   template < primitive_character CHARACTER2 >
   //   path(const ::range < const CHARACTER2 * > & strSource, character_count start, character_count len);
      //path(const simple_ansistring& simpleansistr);
      //path(const simple_wd16string& simplewd16str);
      //path(const simple_wd32string& simplewd32str);
      template < primitive_character CHARACTER2 >
      path(CHARACTER2 chSrc, character_count repeat);
      path(::ansi_character ansich) : path(::string(ansich)) {}
      path(::wd16_character wd16ch) : path(::string(wd16ch)) {}
      path(::wd32_character wd32ch) : path(::string(wd32ch)) {}
      //path(const character & character, character_count repeat = 1) :path(character.m_wd32char, repeat) {}
      path(const ::atom & atom);
      path(const ::payload & payload);
      path(const ::property & property);
      //path(const ::range < const ::ansi_character * > & range) : path(::string(range)) { }


      ::url::url as_url() const;
      //template < has_as_string HAS_AS_STRING >
      //path(const HAS_AS_STRING & has_as_string) : path(has_as_string.as_string()) {}
      //inline ~path() {}

//      path() { m_epath = e_path_file; }
//      path(nullptr_t) {}
//      path(const ::ansi_string & str, enum_path epath = e_path_none, e_type etype = e_type_unknown, bool bNormalize = true, long long iSize = -1);
////      path(const ::wd16_string & wd16str, enum_path epath = e_path_none, e_type etype = e_type_unknown, bool bNormalize = true, long long iSize = -1) :
////         path((const::ansi_string &)wd16str, epath, iDir, bNormalize, iSize) {}
////      path(const ::wd32_string & wd32str, enum_path epath = e_path_none, e_type etype = e_type_unknown, bool bNormalize = true, long long iSize = -1) :
////         path((const::ansi_string &)wd32str, epath, iDir, bNormalize, iSize) {}
//      path(const ::scoped_string & scopedstr, enum_path epath = e_path_none, e_type etype = e_type_unknown, bool bNormalize = true, long long iSize = -1) :
//         path((const::ansi_string &)psz, epath, iDir, bNormalize, iSize) {}
////      path(const ::wd16_character * pwd16sz, enum_path epath = e_path_none, e_type etype = e_type_unknown, bool bNormalize = true, long long iSize = -1) :
////         path((const::ansi_string &)pwd16sz, epath, iDir, bNormalize, iSize) {}
////      path(const ::wd32_character * pwd32sz, enum_path epath = e_path_none, e_type etype = e_type_unknown, bool bNormalize = true, long long iSize = -1) :
////         path((const::ansi_string &)pwd32sz, epath, iDir, bNormalize, iSize) {}
//      //path(::ansi_character ch, enum_path epath = e_path_none, e_type etype = e_type_unknown, bool bNormalize = true, long long iSize = -1) :
//        // path((const::ansi_string &)ch, epath, iDir, bNormalize, iSize) {}
//      path(enum_path epath) { m_epath = epath; }
//      path(const path& path);
//      path(const ::atom & atom) : path(::string(atom)){}
//      path(const ::payload & payload);
//      path(const ::property & property);
////      path(const ::string & str);
      ~path() noexcept;


      //void construct() { *this = ::file::path(); }
      
      
      ::windows_path windows_path() const;

      
      void set_type(enum_path epath);

      path & set_file_path(const ::scoped_string & scopedstrFile);
      path & set_folder_path(const ::scoped_string & scopedstrFolder);

      path & set_file_path();
      path & set_folder_path();

      path& set_existent();

      path& set_existent_file();
      path& set_existent_folder();


      constexpr e_type type() const { return m_etype; }
      e_type & type() { return m_etype; }
      void set_type(e_type etype) { m_etype = etype; }


      constexpr bool does_exist() const { return (m_etype & e_type_exists) && !(m_etype & e_type_doesnt_exist); }
      constexpr bool is_file() const { return (m_etype & e_type_file2); }
      constexpr bool is_folder() const { return (m_etype & e_type_folder2); }
      constexpr bool is_file_or_folder() const { return is_file() || is_folder(); }
      constexpr bool not_file_or_folder() const { return !is_file_or_folder(); }
      constexpr bool is_existent_file() const { return is_file() && does_exist(); }
      constexpr bool is_existent_folder() const { return is_folder() && does_exist(); }
      constexpr bool is_existent_file_or_folder() const { return is_file_or_folder() && does_exist(); }


      //::file::path replace_extension(const ::scoped_string & scopedstrNewExtension, const ::scoped_string & scopedstrOldExtension);
      void set_all_extensions(const ::scoped_string& scopestrExtension);
      void set_final_extension(const ::scoped_string& scopestrExtension);
      void set_extension_if_no_extension(const ::scoped_string & scopestrExtension);

      /// <summary>
      /// Set Extension if No Extension
      /// or add extension if file name has dot and text
      /// after dot is not the extension.
      /// </summary>
      /// <param name="scopestrExtension"></param>
      void defer_set_extension(const ::scoped_string& scopestrExtension);

      ::file::path with_all_extensions(const ::scoped_string& scopestrExtension) const;
      ::file::path with_final_extension(const ::scoped_string& scopestrExtension) const;
      ::file::path with_extension_if_no_extension(const ::scoped_string& scopestrExtension) const;

      ::file::path with_deferred_extension(const ::scoped_string& scopestrExtension) const;

      //inline char separator() const
      //{

      //   return '/';

      //}

      //inline const char* separator_sz() const
      //{

      //   return "/";

      //}

      //inline char other_separator() const
      //{

      //   return file_path_other_separator(m_epath);

      //}


      path & operator = (const ::file::path & path);

      template < primitive_character CHARACTER2 >
      path & operator = (const ::range < const CHARACTER2 *> & range)
      {

         auto path = ::file::path(range);

         path.::file::path_meta::operator=(*this);

         return operator=(path);

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

         if (ansi_icmp(c_str(), path.c_str()) == 0) // undoubtely eaqual...
            return true;

#else

         if (ansi_cmp(c_str(), path.c_str()) == 0) // undoubtely eaqual...
            return true;

#endif

         return false;

      }


      bool operator == (const path & path) const
      {

         return is_equal_fast(path);

      }

      template < character_count n >
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
      //path operator / (const ::scoped_string & scopedstr) const;
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
      bool has_character() const;


//      template <
//

      //::file::path & file_cat(const ::ansi_string & str) { return *this + str; }

      //::file::path & operator | (const ::ansi_string & str) { return file_cat(str); } // what is good here is the operator precedence

      ::file::path operator | (::file::enum_flag eflag) const
      {

         auto path = *this;

         path.flags() |= eflag;

         return ::transfer(path);

      }

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

      //path sibling(const path & path) const;
      //path sibling(const ::ansi_string & str) const;
      path sibling(const ::scoped_string & scopedstr) const;

      //path operator * (const path & path) const;

      //path operator * (const ::ansi_string & str) const;
      path operator * (const ::scoped_string & scopedstr) const;
      //path operator * (const property & property) const;

      //path & operator *= (const path & path);

      //path & operator *= (const ::ansi_string & str);
      path & operator *= (const ::scoped_string & scopedstr);
      //path & operator *= (const property & property);

      ::const_ansi_range title() const;

      ::const_ansi_range name() const;

      //string name(::collection::index i /* = -1 */) const;

      /// return index pointing to beginning of name
      const_iterator find_name() const;

      /// return index just after first dot in file name
      /// -1 if not found
      ::const_ansi_range find_all_extensions() const;

      /// return index just after last dot in file name
      /// -1 if not found
      ::const_ansi_range find_final_extension() const;

      //      bool is_equal(const ::file::path & path2) const;

      ::const_ansi_range all_extensions() const;

      //string ext() const;

      ::const_ansi_range final_extension() const;

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


      /////if no extension present it adds "ext" otherwise do nothing
      //::file::path& defer_extension(const ::scoped_string & scopedstrExtension);

      /////force extension to be scopedstrExtension erasing possibly existing extension
      //::file::path& force_extension(const ::scoped_string& scopedstrExtension);
      
      using string::_get_count_parts_from_beginning;
      
      using string::get_count_parts_from_beginning;

      
      const_ansi_range _get_count_parts_from_beginning(::collection::count iPathPartCountToConsume) const;

      const_ansi_range get_count_parts_from_beginning(::collection::count iPathPartCountToConsume) const;
      
   };


   // e_path file_path_get_type(const ::ansi_string & str, e_path epathForce);


    bool case_insensitive_begins_eat(string & str, const ::scoped_string & scopedstrPrefix);




} // namespace file





inline const char * FormatArgument(const ::file::path & value) noexcept;


template < >
inline ::hash32 as_hash32 < const ::file::path & >(const ::file::path & key);


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






template < typename ITERATOR_TYPE2, character_count n, int t_size >
::file::path operator / (const ::erase_pointer < non_const <ITERATOR_TYPE2>>(&sz)[n], const const_string_range_static_array <ITERATOR_TYPE2, t_size >& a)
{

   return ::transfer(::file::path(sz) / ::string(a));

}


CLASS_DECL_ACME ::file::enum_type safe_get_file_system_item_type(const ::file::path & path);
CLASS_DECL_ACME ::file::enum_type get_file_system_item_type(const ::file::path & path);
CLASS_DECL_ACME ::file::path home_folder_path();
CLASS_DECL_ACME bool safe_file_exists(const ::file::path & path);
CLASS_DECL_ACME bool file_exists(const ::file::path & path);
CLASS_DECL_ACME bool safe_is_directory(const ::file::path & path);
CLASS_DECL_ACME bool is_directory(const ::file::path & path);
CLASS_DECL_ACME ::file::e_type safe_file_type(const ::file::path& path);
CLASS_DECL_ACME ::file::e_type file_type(const ::file::path& path);
CLASS_DECL_ACME void create_directory(const ::file::path & path);
CLASS_DECL_ACME void delete_file(const ::file::path & path);
CLASS_DECL_ACME void erase_directory(const ::file::path & path);
CLASS_DECL_ACME bool path_begins_eat(::string& strUri, const ::scoped_string& scopedstrPrefix);




template < primitive_character CHARACTER >
::file::path operator / (
   const ::range < const CHARACTER* >& range1,
   const ::range < const CHARACTER* >& range2)
{

   return ::file::path(range1).slashed_path(::string(range2));

}


template < primitive_character CHARACTER, character_count n >
::file::path operator / (
   const ::range < const CHARACTER* >& range,
   const CHARACTER(&s)[n])
{

   return ::file::path(range) / ::file::path(::as_string_literal< CHARACTER, n>(s));

}


template < primitive_character CHARACTER, character_count n >
::file::path operator / (
   const CHARACTER(&s)[n],
   const ::range < const CHARACTER* >& range)
{

   return ::file::path(::as_string_literal< CHARACTER, n>(s)) / ::file::path(range);

}


template < primitive_character CHARACTER, typed_character_pointer < CHARACTER > TYPED_CHARACTER_POINTER >
::file::path operator / (
   const ::range < const CHARACTER* >& range,
   TYPED_CHARACTER_POINTER p)
{

   return ::file::path(range) / ::file::path(p);

}


template < character_pointer CHARACTER_POINTER >
::file::path operator / (
   CHARACTER_POINTER p,
   const ::range < const ::decay< CHARACTER_POINTER > * > & range
   )
{

   return ::file::path(p) / ::file::path(range);

}


template < primitive_character CHARACTER, int t_size >
::file::path operator / (
   const ::range < const CHARACTER* >& range,
   const const_string_range_static_array< const CHARACTER *, t_size > & a)
{

   return ::file::path(range) / ::file::path(::string(a));

}




