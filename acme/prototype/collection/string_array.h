#pragma once


#include "array_base.h"
//#include "comparable_eq_array.h"
//#include "comparable_array.h"
//
#include "acme/prototype/collection/address_array.h"
////#include "acme/prototype/prototype/payload.h"
//#include "acme/array.h"

template < typename CHARACTER >
constexpr std::strong_ordering case_insensitive_compare_string(const CHARACTER * pszA, const CHARACTER * pszB)
{

   return case_insensitive_string_order(pszA, pszB);

}

//namespace str
//{

class CLASS_DECL_ACME strsize_range
{
public:


   strsize_range(character_count iBegin = -1, character_count iEnd = -1) : m_iBegin(iBegin), m_iEnd(iEnd) { }


   character_count     m_iBegin;
   character_count     m_iEnd;

   character_count begin() const { return m_iBegin; }
   character_count end() const { return m_iEnd; }
   character_count count() const { return m_iEnd - m_iBegin; }
   character_count upper_bound() const { return m_iEnd - 1; }

};

using strsize_range_array = ::array < strsize_range >;


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
class string_base_array :
   public comparable_array_base < Type, const Type &, comparable_eq_array_base < Type, const Type &, array_base < Type, const Type &, ::typed::def < Type >, ::heap::typed_memory < Type, ::heap::e_memory_array >, t_etypeContainer > > >
{
public:


   using BASE_ARRAY = comparable_array_base < Type, const Type &, comparable_eq_array_base < Type, const Type &, array_base < Type, const Type &, ::typed::def < Type >, ::heap::typed_memory < Type, ::heap::e_memory_array >, t_etypeContainer > > >;
   using RAW_BASE_ARRAY = typename BASE_ARRAY::RAW_BASE_ARRAY;
   using BASE_STRING = Type;
   using BASE_RAW_STRING = RawType;
   using BASE_RAW_STRING_ARRAY = ::string_base_array < RawType, RawType, t_etypeContainer >;
   using CHARACTER = typename BASE_STRING::CHARACTER;
   using RAW_RANGE = typename BASE_RAW_STRING::RANGE;
   using BASE_TYPE = BASE_STRING;
   using BASE_ARG_TYPE = const BASE_STRING &;
   using SCOPED_STRING = typename BASE_STRING::SCOPED_STRING;

   using THIS_RAW_RANGE = typename BASE_ARRAY::THIS_RAW_RANGE;
   using CONST_RAW_RANGE = typename BASE_ARRAY::CONST_RAW_RANGE;
   using this_iterator = typename BASE_ARRAY::this_iterator;

   using BASE_ARRAY::BASE_ARRAY;
   //using BASE_ARRAY::operator =;


   string_base_array(const RAW_BASE_ARRAY& a) : BASE_ARRAY(a) {}
   string_base_array(CHARACTER * const * ppsz, ::collection::count c);
   ~string_base_array();

   template < prototype_container CONTAINER >
   string_base_array & operator = (const CONTAINER & container)
   {
      this->assign_a_container(container);
      return *this;
   }

   ::collection::count get_size() const;
   ::collection::count get_count() const;
   ::collection::index get_lower_bound(::collection::index i = 0) const;
   ::collection::index get_upper_bound(::collection::index i = -1) const;
   ::collection::index get_middle_index(::collection::index i = 0) const;


   void erase_duplicates();

   void case_insensitive_erase_duplicates();


   ::collection::index _007FindLine(const SCOPED_STRING & strKey, ::collection::index iStart = 0) const;
   void _007SetLine(const SCOPED_STRING & strKey, const SCOPED_STRING & strValue, ::collection::index iStart = 0);
   ::collection::index _007GetLine(RawType & rawtype, const SCOPED_STRING & strKey, ::collection::index iStart = 0) const;
   RawType _007GetLine(const SCOPED_STRING & strKey, ::collection::index iStart = 0) const;


   ::collection::index _007FindSection(const SCOPED_STRING & strSection) const;
   ::collection::index _007FindLine(const SCOPED_STRING & strSection, const SCOPED_STRING & strKey) const;
   ::collection::index _007OpenSection(const SCOPED_STRING & strSection);
   void _007SetLine(const SCOPED_STRING & strSection, const SCOPED_STRING & strKey, const SCOPED_STRING & strValue);
   ::collection::index _007GetLine(RawType & rawtype, const SCOPED_STRING & strSection, const SCOPED_STRING & strKey) const;
   RawType _007GetLine(const SCOPED_STRING & strSection, const SCOPED_STRING & strKey) const;


   void order();
   void case_insensitive_order();
   void collate_order();
   void case_insensitive_collate_sort();


   Type safe_at(::collection::index nIndex, Type tDefault = "") const;
   Type safe_at(::collection::index nIndex, Type tDefault = "");

   Type get_at(::collection::index nIndex) const;
   void set_at(::collection::index nIndex, const Type & newElement);

   Type & element_at(::collection::index nIndex);
   const Type & element_at(::collection::index nIndex) const;

   //Type & add_new();
   //Type * add_new(::collection::count c);

   Type & first(::collection::index i = 0);
   Type first(::collection::index i = 0) const;

   Type & last(::collection::index i = -1);
   Type last(::collection::index i = -1) const;

   const Type * get_data() const;
   Type * get_data();

   using BASE_ARRAY::add;

   Type & set_at_grow(::collection::index nIndex, const Type & newElement);


   Type & add_get(const Type & newElement);


   void copy(const string_base_array & src);

   template < prototype_array ARRAY >
   void copy(const ARRAY & src);


   using BASE_ARRAY::copy;


   ::collection::index add(::strsize_range_array & stra, const SCOPED_STRING & str)
   {

      ::collection::index i = -1;

      for (auto & size_range : stra)
      {

         i = add(RawType(str.begin() + size_range.m_iBegin, str.begin() + size_range.m_iEnd));

      }

      return i;

   }

   string_base_array & c_stra(string_base_array & stra) const;
   string_base_array c_stra() const;

   Type & insert_at(::collection::index nIndex, const Type & strElement);
   void insert_at(::collection::index nIndex, const Type & strElement, ::collection::count nCount);
   template < prototype_container CONTAINER >
   void insert_at(::collection::index nStartIndex, const CONTAINER & container);


   string_base_array slice(::collection::index iStart, ::collection::count iCount = -1) const;

   //string_base_array & operator =(const string_base_array & stra);


   Type & insert_empty(::collection::index nIndex);

   void insert_empty(::collection::index nIndex, ::collection::count c);


   ::collection::count truncate_on_find_character(CHARACTER ch);


   //class ::memory GetFormatV004();
   ::collection::count erase_prefixed(const ::scoped_string & scopedstrPrefix);
   ::collection::count erase_empty();
   ::collection::count erase_empty_end();
   ::collection::count erase_empty_begin();
   ::collection::count erase_empty_trimmed_end();
   ::collection::count erase_empty_trimmed_begin();
   ::collection::index add_normal(const Type & str);

   void trim_right(const SCOPED_STRING & strChars);
   void trim_left(const SCOPED_STRING & strChars);
   void trim(const SCOPED_STRING & strChars);
   void trim_right();
   void trim_left();
   void trim();

   ::collection::index add_unique(const Type & str);
   ::collection::index case_insensitive_add_unique(const Type & str);

   ::collection::count append_unique(const string_base_array & stra);
   ::collection::count case_insensitive_append_unique(const string_base_array & stra);

   void make_lower();
   void make_upper();

   auto & append_formatf(const CHARACTER * psz, ...)
   {

      va_list arguments;

      va_start(arguments, psz);

      auto & str = this->add_new().formatf_arguments(psz, arguments);

      va_end(arguments);

      return str;

   }


   template<typename... Args>
   auto & append_format(std::format_string<Args...> fmt, Args&&... args)
   {

      return this->add_new().format(fmt, std::forward<Args>(args)...);

   }


   auto & add_trace(enum_trace_level etracelevel, const SCOPED_STRING & scopedstr)
   {

      return append_formatf("%c: %s\n", trace_level_letter(etracelevel), ::string(scopedstr).c_str());

   }

   //void debug_output(::collection::index iStart = 0, ::collection::count c = -1);

   operator ::collection::count() const
   {
      return get_count();
   }


   ::collection::index get_random_index() const;

   Type & random_element();
   const Type & random_element() const;

   Type pop_random_element();

   Type pop(::collection::index i = -1);
   void slice(string_base_array & stra, ::collection::index i, ::collection::count ca = -1);
   void erase(::collection::index i, ::collection::count count);
   void splice(const string_base_array & stra, ::collection::index i, ::collection::count ca = -1);
   void splice(const string_base_array & stra, ::collection::index i, string_base_array & straRemoved, ::collection::count ca = -1);


   // if Type is found, transfer it to specified position
   bool case_insensitive_move(const SCOPED_STRING & str, ::collection::index iIndex);


   // transfer preferred in order
   bool preferred(const SCOPED_STRING & str);

   ::collection::count preferred(string_base_array & stra);


   ::collection::count case_insensitive_count(const SCOPED_STRING & strFind, ::collection::index iFind = 0, ::collection::index iLast = -1) const;
   ::collection::count count(const SCOPED_STRING & strFind, ::collection::index iFind = 0, ::collection::index iLast = -1) const;


   ::collection::index case_insensitive_find_first(const SCOPED_STRING & strFind, ::collection::index iFind = 0, ::collection::index iLast = -1) const;
   ::collection::index find_first(const SCOPED_STRING & strFind, ::collection::index iFind = 0, ::collection::index iLast = -1) const;


   ::collection::index case_insensitive_find_last(const SCOPED_STRING & strFind, ::collection::index iFind = -1, ::collection::index iLast = 0) const;
   ::collection::index find_last(const SCOPED_STRING & strFind, ::collection::index iFind = -1, ::collection::index iLast = 0) const;


   ::collection::index case_insensitive_reverse_find(const SCOPED_STRING & strFind, ::collection::index iFind = -1, ::collection::index iLast = 0) const;
   ::collection::index rear_find(const SCOPED_STRING & strFind, ::collection::index iFind = -1, ::collection::index iLast = 0) const;


   ::collection::index _066Find(const SCOPED_STRING & str) const;

   ::collection::index _case_insensitive_find_first_prefixed(const SCOPED_STRING & strStarting, ::collection::index iFind = 0, ::collection::index iLast = -1) const;
   ::collection::index _find_first_prefixed(const SCOPED_STRING & strStarting, ::collection::index iFind = 0, ::collection::index iLast = -1) const;

   ::collection::index _find_first_with_starting_word(const SCOPED_STRING & strStartingWord, ::collection::index iFind = 0, ::collection::index iLast = -1) const;

   ::collection::index case_insensitive_find_first_prefixed(const SCOPED_STRING & strStarting, ::collection::index iFind = 0, ::collection::index iLast = -1) const;
   ::collection::index find_first_prefixed(const SCOPED_STRING & strStarting, ::collection::index iFind = 0, ::collection::index iLast = -1) const;

   ::collection::index _case_insensitive_find_first_suffixed(const SCOPED_STRING & strEnding, ::collection::index iFind = 0, ::collection::index iLast = -1) const;
   ::collection::index _find_first_suffixed(const SCOPED_STRING & strEnding, ::collection::index iFind = 0, ::collection::index iLast = -1) const;

   ::collection::index case_insensitive_find_first_suffixed(const SCOPED_STRING & strEnding, ::collection::index iFind = 0, ::collection::index iLast = -1) const;
   ::collection::index find_first_suffixed(const SCOPED_STRING & strEnding, ::collection::index iFind = 0, ::collection::index iLast = -1) const;

   ::collection::index case_insensitive_find_first_begins(const SCOPED_STRING & strStarting, ::collection::index iFind = 0, ::collection::index iLast = -1) const { return case_insensitive_find_first_prefixed(strStarting, iFind, iLast); }
   ::collection::index find_first_begins(const SCOPED_STRING & strStarting, ::collection::index iFind = 0, ::collection::index iLast = -1) const { return find_first_prefixed(strStarting, iFind, iLast); }

   ::collection::index find_first_with_starting_word(const SCOPED_STRING & strStartingWord, ::collection::index iFind = 0, ::collection::index iLast = -1) const;

   ::collection::index case_insensitive_find_first_ends(const SCOPED_STRING & strEnding, ::collection::index iFind = 0, ::collection::index iLast = -1) const { return case_insensitive_find_first_suffixed(strEnding, iFind, iLast); }
   ::collection::index find_first_ends(const SCOPED_STRING & strEnding, ::collection::index iFind = 0, ::collection::index iLast = -1) const { return find_first_suffixed(strEnding, iFind, iLast); }

   ::collection::index _case_insensitive_find_first_contains(const SCOPED_STRING & strSubstring, ::collection::index iFind = 0, ::collection::index iLast = -1, const CHARACTER ** ppszBeg = nullptr, const CHARACTER ** ppszEnd = nullptr) const;
   ::collection::index _find_first_contains(const SCOPED_STRING & strSubstring, ::collection::index iFind = 0, ::collection::index iLast = -1, const CHARACTER ** ppszBeg = nullptr, const CHARACTER ** ppszEnd = nullptr) const;

   ::collection::index case_insensitive_find_first_contains(const SCOPED_STRING & strSubstring, ::collection::index iFind = 0, ::collection::index iLast = -1, const CHARACTER ** ppszBeg = nullptr, const CHARACTER ** ppszEnd = nullptr) const;
   ::collection::index find_first_contains(const SCOPED_STRING & strSubstring, ::collection::index iFind = 0, ::collection::index iLast = -1, const CHARACTER ** ppszBeg = nullptr, const CHARACTER ** ppszEnd = nullptr) const;

   ::collection::index case_insensitive_find_first_begins_eat(Type & strFoundAndEaten, const SCOPED_STRING & strStarting, ::collection::index iFind = 0, ::collection::index iLast = -1) const;
   ::collection::index find_first_begins_eat(Type & strFoundAndEaten, const SCOPED_STRING & strStarting, ::collection::index iFind = 0, ::collection::index iLast = -1) const;

   ::collection::index find_first_with_starting_word_eat(Type & strFoundAndEaten, const SCOPED_STRING & strStartingWord, ::collection::index iFind = 0, ::collection::index iLast = -1) const;

   ::collection::index case_insensitive_find_first_ends_eat(Type & strFoundAndEaten, const SCOPED_STRING & strEnding, ::collection::index iFind = 0, ::collection::index iLast = -1) const;
   ::collection::index find_first_ends_eat(Type & strFoundAndEaten, const SCOPED_STRING & strEnding, ::collection::index iFind = 0, ::collection::index iLast = -1) const;

   ::collection::index case_insensitive_find_first_contains_eat(Type & strFoundAndEaten, const SCOPED_STRING & strEnding, ::collection::index iFind = 0, ::collection::index iLast = -1) const;
   ::collection::index find_first_contains_eat(Type & strFoundAndEaten, const SCOPED_STRING & strEnding, ::collection::index iFind = 0, ::collection::index iLast = -1) const;


   ::collection::index case_insensitive_prefix_find_first(const SCOPED_STRING & strTopic, ::collection::index iFind = 0, ::collection::index iLast = -1) const;
   ::collection::index prefix_find_first(const SCOPED_STRING & strTopic, ::collection::index iFind = 0, ::collection::index iLast = -1) const;

   inline bool case_insensitive_prefixes(const SCOPED_STRING & strTopic, ::collection::index iFind = 0, ::collection::index iLast = -1) const { return found(case_insensitive_prefix_find_first(strTopic, iFind, iLast)); }
   inline bool prefixes(const SCOPED_STRING & strTopic, ::collection::index iFind = 0, ::collection::index iLast = -1) const { return found(prefix_find_first(strTopic, iFind, iLast)); }

   ::collection::index case_insensitive_suffix_find_first(const SCOPED_STRING & strTopic, ::collection::index iFind = 0, ::collection::index iLast = -1) const;
   ::collection::index suffix_find_first(const SCOPED_STRING & strTopic, ::collection::index iFind = 0, ::collection::index iLast = -1) const;

   inline bool case_insensitive_suffixes(const SCOPED_STRING & strTopic, ::collection::index iFind = 0, ::collection::index iLast = -1) const { return found(case_insensitive_suffix_find_first(strTopic, iFind, iLast)); }
   inline bool suffixes(const SCOPED_STRING & strTopic, ::collection::index iFind = 0, ::collection::index iLast = -1) const { return found(suffix_find_first(strTopic, iFind, iLast)); }

   ::collection::index case_insensitive_substring_find_first(const SCOPED_STRING & strTopic, ::collection::index iFind = 0, ::collection::index iLast = -1, const CHARACTER ** ppszBeg = nullptr, const CHARACTER ** ppszEnd = nullptr) const;
   ::collection::index substring_find_first(const SCOPED_STRING & strTopic, ::collection::index iFind = 0, ::collection::index iLast = -1, const CHARACTER ** ppszBeg = nullptr, const CHARACTER ** ppszEnd = nullptr) const;

   inline bool case_insensitive_is_part_of(const SCOPED_STRING & strTopic, ::collection::index iFind = 0, ::collection::index iLast = -1) const { return found(case_insensitive_substring_find_first(strTopic, iFind, iLast)); }
   inline bool is_part_of(const SCOPED_STRING & strTopic, ::collection::index iFind = 0, ::collection::index iLast = -1) const { return found(substring_find_first(strTopic, iFind, iLast)); }



   bool _067CaseInsensitiveContains(const SCOPED_STRING & strFind, ::collection::index iFind = 0, ::collection::index iLast = -1, ::collection::count countMin = 1, ::collection::count countMax = -1) const;
   bool _067Contains(const SCOPED_STRING & str, ::collection::index iFind = 0, ::collection::index iLast = -1, ::collection::count countMin = 1, ::collection::count countMax = -1) const;


   bool _067CaseInsensitiveContainsSubstring(const SCOPED_STRING & str, ::collection::index iFind = 0, ::collection::index iLast = -1, ::collection::count countMin = 1, ::collection::count countMax = -1) const;
   bool _067ContainsSubstring(const SCOPED_STRING & str, ::collection::index iFind = 0, ::collection::index iLast = -1, ::collection::count countMin = 1, ::collection::count countMax = -1) const;


   bool case_insensitive_contains(const SCOPED_STRING & strFind, ::collection::index iFind = 0, ::collection::index iLast = -1) const { return found(case_insensitive_find_first(strFind, iFind, iLast)); }
   bool contains(const SCOPED_STRING & strFind, ::collection::index iFind = 0, ::collection::index iLast = -1) const { return found(case_insensitive_find_first(strFind, iFind, iLast)); }


   bool case_insensitive_theres(const SCOPED_STRING & strSubstring, ::collection::index iFind = 0, ::collection::index iLast = -1, const CHARACTER ** ppszBeg = nullptr, const CHARACTER ** ppszEnd = nullptr) const { return found(case_insensitive_substring_find_first(strSubstring, iFind, iLast, ppszBeg, ppszEnd)); }
   bool theres(const SCOPED_STRING & strSubstring, ::collection::index iFind = 0, ::collection::index iLast = -1, const CHARACTER ** ppszBeg = nullptr, const CHARACTER ** ppszEnd = nullptr) const { return found(case_insensitive_substring_find_first(strSubstring, iFind, iLast, ppszBeg, ppszEnd)); }


   template < prototype_array INDEX_ARRAY >
   ::collection::count case_insensitive_begins(INDEX_ARRAY & ia, const SCOPED_STRING & strPrefix, ::collection::index first = 0, ::collection::index iLast = -1);

   template < prototype_array INDEX_ARRAY >
   ::collection::count begins(INDEX_ARRAY & ia, const SCOPED_STRING & strPrefix, ::collection::index first = 0, ::collection::index iLast = -1);


   template < prototype_array STRING_ARRAY >
   ::collection::count case_insensitive_ends(STRING_ARRAY & stra, const SCOPED_STRING & strSuffix, ::collection::index first = 0, ::collection::index iLast = -1);

   template < prototype_array STRING_ARRAY >
   ::collection::count ends(STRING_ARRAY & stra, const SCOPED_STRING & strSuffix, ::collection::index first = 0, ::collection::index iLast = -1);


   template < prototype_array STRING_ARRAY >
   ::collection::count case_insensitive_search(STRING_ARRAY & stra, const SCOPED_STRING & strSubstring, ::collection::index first = 0, ::collection::index iLast = -1);

   template < prototype_array STRING_ARRAY >
   ::collection::count search(STRING_ARRAY & stra, const SCOPED_STRING & strSubstring, ::collection::index first = 0, ::collection::index iLast = -1);


   //::collection::count case_insensitive_begins(string_base_array & straPrefixed,const SCOPED_STRING &strPrefix,::collection::index first = 0,::collection::index iLast = -1);
   //::collection::count begins(string_base_array& straPrefixed, const SCOPED_STRING &strPrefix, ::collection::index first = 0, ::collection::index iLast = -1);


   //::collection::count case_insensitive_ends(string_base_array& straSuffixed, const SCOPED_STRING &strPrefix, ::collection::index first = 0, ::collection::index iLast = -1);
   //::collection::count ends(string_base_array& straSuffixed, const SCOPED_STRING &strPrefix, ::collection::index first = 0, ::collection::index iLast = -1);


   //::collection::count case_insensitive_search(string_base_array& straResult, const SCOPED_STRING &strSubstring, ::collection::index first = 0, ::collection::index iLast = -1);
   //::collection::count search(string_base_array& straResult, const SCOPED_STRING &strSubstring, ::collection::index first = 0, ::collection::index iLast = -1);


   ::collection::count case_insensitive_filter_begins(const SCOPED_STRING & strPrefix, ::collection::index first = 0, ::collection::index iLast = -1);
   ::collection::count filter_begins(const SCOPED_STRING & strPrefix, ::collection::index first = 0, ::collection::index iLast = -1);


   template < typename Pred >
   ::collection::count filter(Pred pred, ::collection::index first = 0, ::collection::index iLast = -1);

   template < typename Pred >
   ::collection::count filter_out(Pred pred, ::collection::index first = 0, ::collection::index iLast = -1);

   template < typename Pred, typename ArrayOut >
   ::collection::count filter_out(Pred pred, ArrayOut & a, ::collection::index first = 0, ::collection::index iLast = -1);

   using BASE_ARRAY::erase_first;
   ::collection::count case_insensitive_erase_first(const SCOPED_STRING & str, ::collection::index iFind = 0, ::collection::index iLast = -1);

   ::collection::count erase_first(const SCOPED_STRING & str, ::collection::index iFind = 0, ::collection::index iLast = -1);


   ::collection::count case_insensitive_erase_last(const SCOPED_STRING & str, ::collection::index iFind = 0, ::collection::index iLast = -1);

   using BASE_ARRAY::erase_last;
   ::collection::count erase_last(const SCOPED_STRING & str, ::collection::index iFind = 0, ::collection::index iLast = -1);

   ::collection::count _067CaseInsensitiveRemove(const SCOPED_STRING & str, ::collection::index iFind = 0, ::collection::index iLast = -1, ::collection::count countMin = 0, ::collection::count countMax = -1);

   ::collection::count _067Remove(const SCOPED_STRING & str, ::collection::index iFind = 0, ::collection::index iLast = -1, ::collection::count countMin = 0, ::collection::count countMax = -1);

   ::collection::count case_insensitive_erase(const SCOPED_STRING & str, ::collection::index iFind = 0, ::collection::index iLast = -1);

   ::collection::count erase(const SCOPED_STRING & str, ::collection::index iFind = 0, ::collection::index iLast = -1);


   template < prototype_container CONTAINER >
   ::collection::count case_insensitive_erase(const CONTAINER & container);

   template < prototype_container CONTAINER >
   ::collection::count erase(const CONTAINER & container);

   string_base_array & explode(const SCOPED_STRING & strSeparator, const SCOPED_STRING & str, bool bAddEmpty = true);

   string_base_array & _001Explode(const SCOPED_STRING & str);

   // csstidy: Same as explode, but not within a Type
   //string_base_array & csstidy_explode_ws(char sep,const SCOPED_STRING &str);


   //template < typename PRED >
   //void predicate_implode(Type & rwstr,PRED pred, const SCOPED_STRING &strSeparator = nullptr,::collection::index iStart = 0,::collection::count iCount = -1) const;


   template < typename PRED >
   Type predicate_implode(PRED pred, const SCOPED_STRING & strSeparator = nullptr, ::collection::index iStart = 0, ::collection::count iCount = -1) const;


   //void implode(Type & rwstr,const SCOPED_STRING &strSeparator = nullptr,::collection::index iStart = 0,::collection::count iCount = -1) const;

   Type implode(const SCOPED_STRING & strSeparator = nullptr, ::collection::index iStart = 0, ::collection::count iCount = -1) const;

   Type postfix_implode(const SCOPED_STRING& strSuffix = nullptr, ::collection::index iStart = 0, ::collection::count iCount = -1) const;

   ///void reverse_implode(Type & rwstr,const SCOPED_STRING &strSeparator = nullptr,::collection::index iStart = 0,::collection::count iCount = -1) const;

   Type reverse_implode(const SCOPED_STRING & strSeparator = nullptr, ::collection::index iStart = 0, ::collection::count iCount = -1) const;


   //void _008Implode(Type & rwstr, const SCOPED_STRING &strSeparator = nullptr, const SCOPED_STRING &strLastSeparator = nullptr, ::collection::index iStart = 0, ::collection::count iCount = -1) const;

   Type _008Implode(const SCOPED_STRING & strSeparator = nullptr, const SCOPED_STRING & strLastSeparator = nullptr, ::collection::index iStart = 0, ::collection::count iCount = -1) const;


   //void _008IfImplode(Type & rwstr, const SCOPED_STRING &strIfHasElementPrefix = nullptr, const SCOPED_STRING &strSeparator = nullptr, const SCOPED_STRING &strLastSeparator = nullptr, bool bUseLast = true, ::collection::index iStart = 0, ::collection::count iCount = -1) const;

   Type _008IfImplode(const SCOPED_STRING & strIfHasElementPrefix = nullptr, const SCOPED_STRING & strSeparator = nullptr, const SCOPED_STRING & strLastSeparator = nullptr, bool bUseLast = true, ::collection::index iStart = 0, ::collection::count iCount = -1) const;


   void surround(const SCOPED_STRING & strPrefix = nullptr, const SCOPED_STRING & strSuffix = nullptr, ::collection::index iStart = 0, ::collection::count iCount = -1);
   Type surround_and_implode(const SCOPED_STRING & strSeparator = nullptr, const SCOPED_STRING & strPrefix = nullptr, const SCOPED_STRING & strSuffix = nullptr, ::collection::index iStart = 0, ::collection::count iCount = -1);


   //comparable_array < atom > get_comparable_ida() const;

   //::collection::count explode_command_line(const SCOPED_STRING &str, address_array < char * > * argv = nullptr);



   //   void XFV001Expand();

   //string_base_array & operator =(const ::payload & payload);
   //   string_base_array & operator =(const string_base_array & stra);
   //string_base_array & operator =(const long_long_array_base & ia);
   //   string_base_array & operator =(const string_base_array & stra);
   //string_base_array & operator -=(const string_base_array & stra);
   //string_base_array & operator +=(const string_base_array & stra);

   using BASE_ARRAY::operator +=;
   //using BASE_ARRAY::operator -=;


   //string_base_array operator -(const string_base_array & stra) const;
   //string_base_array operator +(const string_base_array & stra) const;
   //   string_base_array operator -(const string_base_array & stra) const;
   //   string_base_array operator +(const string_base_array & stra) const;


   bool operator == (const BASE_RAW_STRING_ARRAY & a) const;
   bool operator != (const BASE_RAW_STRING_ARRAY & a) const;


   void replace_with(const SCOPED_STRING & strNew, const SCOPED_STRING & strOld);


   //void write(stream & ostream) const;
   //void read(stream & istream);


   void get_format_string(Type & str, const SCOPED_STRING & strSeparator) const;

   void add_tokens(const SCOPED_STRING & str, const SCOPED_STRING & strSeparator, bool bAddEmpty = true);

   void add_smallest_tokens(const SCOPED_STRING & str, const BASE_RAW_STRING_ARRAY & straSeparator, bool bAddEmpty = true, bool bWithSeparator = false);

   void add_words(const SCOPED_STRING & str);


   /// @brief Add Lines in a string that contains at least one '\r' character and one '\n' character
   /// @tparam bAddEmpty true to add empty lines
   /// @param scopedstr lines to add lines for
   /// @param bWithEOL true to include EOL
   /// @return Last Line without separator
   template < bool bAddEmpty >
   typename Type::const_iterator _____add_lines_rn(const SCOPED_STRING & scopedstr, bool bWithEOL);
   //template < CHARACTER chSeparator, bool bAddEmpty >
   //typename Type::const_iterator _____add_lines(const SCOPED_STRING & scopedstr);
   /// @brief Add Last Line when adding lines in a string
   /// @tparam bAddEmpty true to add empty lines
   /// @param start line start
   /// @param end line end
   template < bool bAddEmpty >
   void __add_lines_suffix(typename Type::const_iterator start, typename Type::const_iterator end)
   {

      if (start < end)
      {

         this->add_item({ start, end });

      }
      else if (bAddEmpty)
      {

         this->add_item({});

      }

   }
   template < bool bAddEmpty >
   void __add_lines_rn(const SCOPED_STRING & scopedstr) { __add_lines_suffix<bAddEmpty>(__add_lines_rn<bAddEmpty>(scopedstr), scopedstr.end()); }
   template < CHARACTER chSeparator, bool bAddEmpty >
   void __add_lines(const SCOPED_STRING & scopedstr) { __add_lines_suffix<bAddEmpty>(__add_lines<chSeparator, bAddEmpty>(scopedstr), scopedstr.end()); }
   template < bool bAddEmpty >
   void _add_lines(const SCOPED_STRING & scopedstr, bool bWithEOL = false);
   void add_lines(const SCOPED_STRING & scopedstr, bool bAddEmpty = true, bool bWithEOL = false)
   {
      if (bAddEmpty)_add_lines<true>(scopedstr, bWithEOL); else _add_lines<false>(scopedstr, bWithEOL);
   }

   /// @brief Add Lines in a string that contains only one type of separator @chSeparator
   /// @tparam chSeparator the EOL character
   /// @tparam bAddEmpty true to add empty lines
   /// @param scopedstr string with lines to add lines for
   /// @param bWithEOL true to include EOL
   /// @return Last Line without separator
   template < CHARACTER chSeparator, bool bAddEmpty >
   typename Type::const_iterator  _____add_lines(const SCOPED_STRING & scopedstr, bool bWithEOL = false)
   {

      auto range = scopedstr();

      while (true)
      {

         auto p = range.find(chSeparator);

         if (::is_null(p))
         {

            return range.begin();

         }

         __add_lines_suffix<bAddEmpty>(range.begin(), bWithEOL ? p + 1 : p);

         range.begin(p + 1);

      }

   }



   void _001AddTokens(const SCOPED_STRING & str);



   bool is_empty(::collection::count countMinimum = 1) const;
   bool has_elements(::collection::count countMinimum = 1) const;

   Type encode_v16();


   void decode_v16(const SCOPED_STRING & str);

   ::collection::count count_except(const SCOPED_STRING & str);
   ::collection::count count_except(const string_base_array & stra);

   ::collection::count case_insensitive_count_except(const SCOPED_STRING & str);
   ::collection::count case_insensitive_count_except(const string_base_array & stra);

   Type & get_network_payload(Type & str, bool bNewLine = true) const;



   // c_get
   ::array_base < const_char_pointer >c_ansi_get(bool bMemoryAlloc = false) const;
   //::array < const ::wide_character * > c_wide_get(bool bMemoryAlloc = false) const;
   void c_add(char ** ppsz, ::collection::count iCount, bool bMemoryAlloc = false);
   void c_add(char ** ppsz, bool bMemoryAlloc = false);
   void c_add(wchar_t ** ppsz, ::collection::count iCount, bool bMemoryAlloc = false);
   void c_add(wchar_t ** ppsz, bool bMemoryAlloc = false);

   void feed_line(const ::scoped_string& scopedstr, bool bCarriage)
   {
      if (this->m_erange & e_range_array_carriage_return)
      {
         if (this->has_elements())
         {
            this->last() = scopedstr;
         }
         else
         {
            this->add(scopedstr);
         }
         if (!bCarriage)
         {
            this->m_erange = (::enum_range) (this->m_erange & ~e_range_array_carriage_return);
         }
      }
      else
      {
         this->add(scopedstr);
         if (bCarriage)
         {
            this->m_erange = (::enum_range)(this->m_erange | e_range_array_carriage_return);
         }

      }
   }

   string_base_array & intersect(const string_base_array & a)
   {

      for (::collection::index i = 0; i < get_size(); )
      {

         if (!a.contains(element_at(i)))
         {

            this->erase_at(i);

         }
         else
         {

            i++;

         }

      }

      return *this;

   }

   string_base_array & case_insensitive_intersect(const string_base_array & a)
   {

      for (::collection::index i = 0; i < get_size(); )
      {

         if (!a.case_insensitive_contains(element_at(i)))
         {

            this->erase_at(i);

         }
         else
         {

            i++;

         }

      }

      return *this;

   }

   string_base_array & operator &=(const string_base_array & a)
   {

      return intersect(a);

   }


   ::std::strong_ordering case_insensitive_order(const THIS_RAW_RANGE & rawrange) const
   {

      return BASE_ARRAY::order(rawrange, ::comparison::case_insensitive < Type >());

   }


};


//typedef CLASS_DECL_ACME string_base_array < string > string_array_base;



class CLASS_DECL_ACME string_array_array_base :
   public ::array_base < string_array_base >
{
public:


   void add_csv(const ::scoped_string & scopedstr);


};


CLASS_DECL_ACME bool next_csv(string & str, const string_array_base & stra);
CLASS_DECL_ACME void add_csv(string_array_base & stra, const ::scoped_string & scopedstr);

CLASS_DECL_ACME string_array_base string_array_from_strdup_count(const_char_pointer *pszaUrl, long lCount);





