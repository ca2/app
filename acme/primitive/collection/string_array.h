#pragma once


#include "array.h"
//#include "comparable_eq_array.h"
//#include "comparable_array.h"
//// #include "acme/primitive/string/string.h"
#include "acme/primitive/collection/address_array.h"
////#include "acme/primitive/primitive/payload.h"
//#include "acme/array.h"

template < typename CHARACTER >
constexpr std::strong_ordering compare_string_ci(const CHARACTER * pszA, const CHARACTER * pszB)
{

   return case_insensitive_string_order(pszA, pszB);

}

//namespace str
//{

   class CLASS_DECL_ACME strsize_range
   {
   public:


      strsize_range(strsize iBegin = -1, strsize iEnd = -1) : m_iBegin(iBegin), m_iEnd(iEnd) { }


      strsize     m_iBegin;
      strsize     m_iEnd;

      strsize begin() const { return m_iBegin; }
      strsize end() const { return m_iEnd; }
      strsize count() const { return m_iEnd - m_iBegin; }
      strsize upper_bound() const { return m_iEnd - 1; }

   };

   using strsize_range_array = ::array < strsize_range >;


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
class string_array_base :
        public comparable_array < Type, const Type &, comparable_eq_array < Type, const Type &, array < Type, const Type &, ::allocator::def < Type >, m_etypeContainer > > >
{
public:


    using BASE_ARRAY = comparable_array < Type, const Type &, comparable_eq_array < Type, const Type &, array < Type, const Type &, ::allocator::def < Type >, m_etypeContainer > > >;
    typedef Type                                                      String;
    typedef RawType                                                   RawString;
    typedef string_array_base < RawType, RawType, m_etypeContainer >    RawStringArray;
    using CHARACTER = typename Type::CHARACTER;
    using RANGE = typename RawType::RANGE;
    typedef Type BASE_TYPE;
    typedef const Type & BASE_ARG_TYPE;
    using SCOPED_STRING = typename RawType::SCOPED_STRING;

    using THIS_RAW_RANGE = typename BASE_ARRAY::THIS_RAW_RANGE;
    using CONST_RAW_RANGE = typename BASE_ARRAY::CONST_RAW_RANGE;

    string_array_base() {}

    template < typename T >
    string_array_base(const ::std::initializer_list < T > & l)
    {
       for(auto & e : l)
       {
          add(e);
       }
    }

    string_array_base(const string_array_base & array);
//#ifdef _UWP
//   string_array_base(Platform::Array < Platform::String ^ > ^ refstra);
//#endif
    string_array_base(CHARACTER * const * ppsz, ::count c);
    ~string_array_base() override;


    ::count get_size() const;
    ::count get_count() const;
    ::index get_lower_bound(::index i = 0) const;
    ::index get_upper_bound(::index i = -1) const;
    ::index get_middle_index(::index i = 0) const;


    void erase_duplicates();

    void erase_duplicates_ci();


    ::index _007FindLine(const RawType &strKey, ::index iStart = 0) const;
    void _007SetLine(const RawType &strKey, const RawType &strValue, ::index iStart = 0);
    ::index _007GetLine(RawType & rawtype, const RawType &strKey, ::index iStart = 0) const;
    RawType _007GetLine(const RawType &strKey, ::index iStart = 0) const;


    ::index _007FindSection(const RawType &strSection) const;
    ::index _007FindLine(const RawType &strSection, const RawType &strKey) const;
    ::index _007OpenSection(const RawType &strSection);
    void _007SetLine(const RawType &strSection, const RawType &strKey, const RawType &strValue);
    ::index _007GetLine(RawType & rawtype, const RawType &strSection, const RawType &strKey) const;
    RawType _007GetLine(const RawType &strSection, const RawType &strKey) const;


    void order();
    void case_insensitive_order();
    void collate_order();
    void collate_sort_ci();


    Type safe_at(::index nIndex, Type tDefault = "") const;
    Type safe_at(::index nIndex, Type tDefault = "");

    Type get_at(::index nIndex) const;
    void set_at(::index nIndex, const Type & newElement);

    Type & element_at(::index nIndex);
    const Type & element_at(::index nIndex) const;

//Type & add_new();
//Type * add_new(::count c);

    Type & first(::index i = 0);
    Type first(::index i = 0) const;

    Type & last(::index i = -1);
    Type last(::index i = -1) const;

    const Type* get_data() const;
    Type* get_data();

    using BASE_ARRAY::add;

    Type & set_at_grow(::index nIndex, const Type & newElement);


    Type & add_get(const Type & newElement);


    void copy(const string_array_base & src);

    template < primitive_array ARRAY >
    void copy(const ARRAY & src);


    using BASE_ARRAY::copy;


    ::index add(::strsize_range_array & stra, const RawType &str)
    {

       ::index i = -1;

       for(auto & size_range : stra)
       {

          i = add(RawType(str.begin() + size_range.m_iBegin, str.begin() + size_range.m_iEnd));

       }

       return i;

    }

    string_array_base & c_stra(string_array_base & stra) const;
    string_array_base c_stra() const;

    Type & insert_at(::index nIndex, const Type & strElement);
    void insert_at(::index nIndex, const Type & strElement,::count nCount);
    void insert_at(::index nStartIndex, const string_array_base & NewArray);


    string_array_base slice(::index iStart, ::count iCount = -1) const;

    string_array_base & operator =(const string_array_base & stra);


    Type & insert_empty(::index nIndex);

    void insert_empty(::index nIndex, ::count c);


//class ::memory GetFormatV004();
    ::count erase_empty();
    ::count erase_empty_end();
    ::count erase_empty_begin();
    ::count erase_empty_trimmed_end();
    ::count erase_empty_trimmed_begin();
    ::index add_normal(const Type & str);

    void trim_right(const RawType &strChars);
    void trim_left(const RawType &strChars);
    void trim(const RawType &strChars);
    void trim_right();
    void trim_left();
    void trim();

    ::index add_unique(const Type & str);
    ::index add_unique_ci(const Type & str);

    ::count append_unique(const string_array_base & stra);
    ::count append_unique_ci(const string_array_base & stra);

    void make_lower();
    void make_upper();


    void debug_output(::index iStart = 0, ::count c = -1);

    operator ::count() const
    {
       return get_count();
    }


    ::index get_random_index() const;

    Type & random_element();
    const Type & random_element() const;

    Type pop_random_element();

    Type pop(::index i = -1);
    void slice(string_array_base & stra,::index i,::count ca = -1);
    void erase(::index i,::count count);
    void splice(const string_array_base & stra,::index i,::count ca = -1);
    void splice(const string_array_base & stra,::index i,string_array_base & straRemoved,::count ca = -1);


// if Type is found, move it to specified position
    bool move_ci(const RawType &str,::index iIndex);


// move preferred in order
    bool preferred(const RawType &str);

    ::count preferred(string_array_base & stra);


    ::count count_ci(const RawType &strFind, ::index iFind = 0, ::index iLast = -1) const;
    ::count count(const RawType &strFind, ::index iFind = 0, ::index iLast = -1) const;


    ::index find_first_ci(const RawType &strFind,::index iFind = 0,::index iLast = -1) const;
    ::index find_first(const RawType &strFind,::index iFind = 0,::index iLast = -1) const;


    ::index find_last_ci(const RawType &strFind, ::index iFind = -1, ::index iLast = 0) const;
    ::index find_last(const RawType &strFind, ::index iFind = -1, ::index iLast = 0) const;


    ::index reverse_find_ci(const RawType &strFind, ::index iFind = -1, ::index iLast = 0) const;
    ::index rear_find(const RawType &strFind, ::index iFind = -1, ::index iLast = 0) const;


    ::index _066Find(const RawType &str) const;

    ::index _find_first_prefixed_ci(const RawType &strStarting, ::index iFind = 0, ::index iLast = -1) const;
    ::index _find_first_prefixed(const RawType &strStarting, ::index iFind = 0, ::index iLast = -1) const;

    ::index find_first_prefixed_ci(const RawType &strStarting, ::index iFind = 0, ::index iLast = -1) const;
    ::index find_first_prefixed(const RawType &strStarting, ::index iFind = 0, ::index iLast = -1) const;

    ::index _find_first_suffixed_ci(const RawType &strEnding, ::index iFind = 0, ::index iLast = -1) const;
    ::index _find_first_suffixed(const RawType &strEnding, ::index iFind = 0, ::index iLast = -1) const;

    ::index find_first_suffixed_ci(const RawType &strEnding, ::index iFind = 0, ::index iLast = -1) const;
    ::index find_first_suffixed(const RawType &strEnding, ::index iFind = 0, ::index iLast = -1) const;

    ::index find_first_begins_ci(const RawType &strStarting, ::index iFind = 0, ::index iLast = -1) const { return find_first_prefixed_ci(strStarting, iFind, iLast); }
    ::index find_first_begins(const RawType &strStarting, ::index iFind = 0, ::index iLast = -1) const { return find_first_prefixed(strStarting, iFind, iLast); }

    ::index find_first_ends_ci(const RawType &strEnding, ::index iFind = 0, ::index iLast = -1) const { return find_first_suffixed_ci(strEnding, iFind, iLast); }
    ::index find_first_ends(const RawType &strEnding, ::index iFind = 0, ::index iLast = -1) const { return find_first_suffixed(strEnding, iFind, iLast); }

    ::index _find_first_contains_ci(const RawType &strSubstring, ::index iFind = 0, ::index iLast = -1, const CHARACTER ** ppszBeg = nullptr, const CHARACTER ** ppszEnd = nullptr) const;
    ::index _find_first_contains(const RawType &strSubstring, ::index iFind = 0, ::index iLast = -1, const CHARACTER ** ppszBeg = nullptr, const CHARACTER ** ppszEnd = nullptr) const;

    ::index find_first_contains_ci(const RawType &strSubstring, ::index iFind = 0, ::index iLast = -1, const CHARACTER ** ppszBeg = nullptr, const CHARACTER ** ppszEnd = nullptr) const;
    ::index find_first_contains(const RawType &strSubstring, ::index iFind = 0, ::index iLast = -1, const CHARACTER ** ppszBeg = nullptr, const CHARACTER ** ppszEnd = nullptr) const;

    ::index find_first_begins_eat_ci(Type& strFoundAndEaten, const RawType &strStarting, ::index iFind = 0, ::index iLast = -1) const;
    ::index find_first_begins_eat(Type& strFoundAndEaten, const RawType &strStarting, ::index iFind = 0, ::index iLast = -1) const;

    ::index find_first_ends_eat_ci(Type& strFoundAndEaten, const RawType &strEnding, ::index iFind = 0, ::index iLast = -1) const;
    ::index find_first_ends_eat(Type& strFoundAndEaten, const RawType &strEnding, ::index iFind = 0, ::index iLast = -1) const;

    ::index find_first_contains_eat_ci(Type& strFoundAndEaten, const RawType &strEnding, ::index iFind = 0, ::index iLast = -1) const;
    ::index find_first_contains_eat(Type& strFoundAndEaten, const RawType &strEnding, ::index iFind = 0, ::index iLast = -1) const;


    ::index prefix_find_first_ci(const RawType &strTopic, ::index iFind = 0, ::index iLast = -1) const;
    ::index prefix_find_first(const RawType &strTopic, ::index iFind = 0, ::index iLast = -1) const;

    inline bool prefixes_ci(const RawType &strTopic, ::index iFind = 0, ::index iLast = -1) const { return found(prefix_find_first_ci(strTopic, iFind, iLast)); }
    inline bool prefixes(const RawType &strTopic, ::index iFind = 0, ::index iLast = -1) const { return found(prefix_find_first(strTopic, iFind, iLast)); }

    ::index suffix_find_first_ci(const RawType &strTopic, ::index iFind = 0, ::index iLast = -1) const;
    ::index suffix_find_first(const RawType &strTopic, ::index iFind = 0, ::index iLast = -1) const;

    inline bool case_insensitive_suffixes(const RawType &strTopic, ::index iFind = 0, ::index iLast = -1) const { return found(suffix_find_first_ci(strTopic, iFind, iLast)); }
    inline bool suffixes(const RawType &strTopic, ::index iFind = 0, ::index iLast = -1) const { return found(suffix_find_first(strTopic, iFind, iLast)); }

    ::index substring_find_first_ci(const RawType &strTopic, ::index iFind = 0, ::index iLast = -1, const CHARACTER ** ppszBeg = nullptr, const CHARACTER ** ppszEnd = nullptr) const;
    ::index substring_find_first(const RawType &strTopic, ::index iFind = 0, ::index iLast = -1, const CHARACTER ** ppszBeg = nullptr, const CHARACTER ** ppszEnd = nullptr) const;

    inline bool is_part_of_ci(const RawType &strTopic, ::index iFind = 0, ::index iLast = -1) const { return found(substring_find_first_ci(strTopic, iFind, iLast)); }
    inline bool is_part_of(const RawType &strTopic, ::index iFind = 0, ::index iLast = -1) const { return found(substring_find_first(strTopic, iFind, iLast)); }



    bool _067ContainsCi(const RawType &strFind,::index iFind = 0,::index iLast = -1,::count countMin = 1,::count countMax = -1) const;
    bool _067Contains(const RawType &str,::index iFind = 0,::index iLast = -1,::count countMin = 1,::count countMax = -1) const;


    bool _067ContainsSubstringCi(const RawType &str,::index iFind = 0,::index iLast = -1,::count countMin = 1,::count countMax = -1) const;
    bool _067ContainsSubstring(const RawType &str,::index iFind = 0,::index iLast = -1,::count countMin = 1,::count countMax = -1) const;


    bool case_insensitive_contains(const RawType &strFind, ::index iFind = 0, ::index iLast = -1) const { return found(find_first_ci(strFind, iFind, iLast)); }
    bool contains(const RawType &strFind,::index iFind = 0,::index iLast = -1) const { return found(find_first_ci(strFind, iFind, iLast)); }


    bool theres_ci(const RawType &strSubstring,::index iFind = 0,::index iLast = -1, const CHARACTER ** ppszBeg = nullptr, const CHARACTER ** ppszEnd = nullptr) const { return found(substring_find_first_ci(strSubstring, iFind, iLast, ppszBeg, ppszEnd)); }
    bool theres(const RawType &strSubstring,::index iFind = 0,::index iLast = -1, const CHARACTER ** ppszBeg = nullptr, const CHARACTER ** ppszEnd = nullptr) const { return found(substring_find_first_ci(strSubstring, iFind, iLast, ppszBeg, ppszEnd)); }


    template < primitive_array INDEX_ARRAY >
    ::count case_insensitive_begins(INDEX_ARRAY & ia, const RawType &strPrefix, ::index first = 0, ::index iLast = -1);

    template < primitive_array INDEX_ARRAY >
    ::count begins(INDEX_ARRAY & ia, const RawType &strPrefix, ::index first = 0, ::index iLast = -1);


    template < primitive_array STRING_ARRAY >
    ::count case_insensitive_ends(STRING_ARRAY & stra, const RawType &strSuffix, ::index first = 0, ::index iLast = -1);

    template < primitive_array STRING_ARRAY >
    ::count ends(STRING_ARRAY & stra, const RawType &strSuffix, ::index first = 0, ::index iLast = -1);


    template < primitive_array STRING_ARRAY >
    ::count search_ci(STRING_ARRAY & stra, const RawType &strSubstring, ::index first = 0, ::index iLast = -1);

    template < primitive_array STRING_ARRAY >
    ::count search(STRING_ARRAY & stra, const RawType &strSubstring, ::index first = 0, ::index iLast = -1);


//::count case_insensitive_begins(string_array_base & straPrefixed,const RawType &strPrefix,::index first = 0,::index iLast = -1);
//::count begins(string_array_base& straPrefixed, const RawType &strPrefix, ::index first = 0, ::index iLast = -1);


//::count case_insensitive_ends(string_array_base& straSuffixed, const RawType &strPrefix, ::index first = 0, ::index iLast = -1);
//::count ends(string_array_base& straSuffixed, const RawType &strPrefix, ::index first = 0, ::index iLast = -1);


//::count search_ci(string_array_base& straResult, const RawType &strSubstring, ::index first = 0, ::index iLast = -1);
//::count search(string_array_base& straResult, const RawType &strSubstring, ::index first = 0, ::index iLast = -1);


    ::count filter_begins_ci(const RawType &strPrefix,::index first = 0,::index iLast = -1);
    ::count filter_begins(const RawType &strPrefix, ::index first = 0, ::index iLast = -1);


    template < typename Pred >
    ::count filter(Pred pred,::index first = 0,::index iLast = -1);

    template < typename Pred >
    ::count filter_out(Pred pred,::index first = 0,::index iLast = -1);

    template < typename Pred, typename ArrayOut >
    ::count filter_out(Pred pred, ArrayOut & a, ::index first = 0,::index iLast = -1);

    ::count erase_first_ci(const RawType &str,::index iFind = 0,::index iLast = -1);

    ::count erase_first(const RawType &str,::index iFind = 0,::index iLast = -1);


    ::count erase_last_ci(const RawType &str, ::index iFind = 0, ::index iLast = -1);

    using BASE_ARRAY::erase_last;
    ::count erase_last(const RawType &str, ::index iFind = 0, ::index iLast = -1);

    ::count _067RemoveCi(const RawType &str, ::index iFind = 0, ::index iLast = -1, ::count countMin = 0, ::count countMax = -1);

    ::count _067Remove(const RawType &str, ::index iFind = 0, ::index iLast = -1, ::count countMin = 0, ::count countMax = -1);

    ::count erase_ci(const RawType &str,::index iFind = 0,::index iLast = -1);

    ::count erase(const RawType &str,::index iFind = 0,::index iLast = -1);


    ::count erase_ci(const string_array_base & stra);
    ::count erase(const string_array_base & stra);

    string_array_base & explode(const RawType &strSeparator, const RawType &str, bool bAddEmpty = true);

    string_array_base & _001Explode(const RawType &str);

// csstidy: Same as explode, but not within a Type
//string_array_base & csstidy_explode_ws(char sep,const RawType &str);


//template < typename PRED >
//void predicate_implode(Type & rwstr,PRED pred, const RawType &strSeparator = nullptr,::index iStart = 0,::count iCount = -1) const;


    template < typename PRED >
    Type predicate_implode(PRED pred, const RawType &strSeparator = nullptr,::index iStart = 0,::count iCount = -1) const;


//void implode(Type & rwstr,const RawType &strSeparator = nullptr,::index iStart = 0,::count iCount = -1) const;

    Type implode(const RawType &strSeparator = nullptr,::index iStart = 0,::count iCount = -1) const;

///void reverse_implode(Type & rwstr,const RawType &strSeparator = nullptr,::index iStart = 0,::count iCount = -1) const;

    Type reverse_implode(const RawType &strSeparator = nullptr,::index iStart = 0,::count iCount = -1) const;


//void _008Implode(Type & rwstr, const RawType &strSeparator = nullptr, const RawType &strLastSeparator = nullptr, ::index iStart = 0, ::count iCount = -1) const;

    Type _008Implode(const RawType &strSeparator = nullptr, const RawType &strLastSeparator = nullptr, ::index iStart = 0, ::count iCount = -1) const;


//void _008IfImplode(Type & rwstr, const RawType &strIfHasElementPrefix = nullptr, const RawType &strSeparator = nullptr, const RawType &strLastSeparator = nullptr, bool bUseLast = true, ::index iStart = 0, ::count iCount = -1) const;

    Type _008IfImplode(const RawType &strIfHasElementPrefix = nullptr, const RawType &strSeparator = nullptr, const RawType &strLastSeparator = nullptr, bool bUseLast = true, ::index iStart = 0, ::count iCount = -1) const;


    void surround(const RawType &strPrefix = nullptr,const RawType &strSuffix = nullptr,::index iStart = 0,::count iCount = -1);
    Type surround_and_implode(const RawType &strSeparator = nullptr,const RawType &strPrefix = nullptr,const RawType &strSuffix = nullptr,::index iStart = 0,::count iCount = -1);


//comparable_array < atom > get_comparable_ida() const;

//::count explode_command_line(const RawType &str, address_array < char * > * argv = nullptr);



//   void XFV001Expand();

//string_array_base & operator =(const ::payload & payload);
//   string_array_base & operator =(const string_array_base & stra);
//string_array_base & operator =(const i64_array & ia);
//   string_array_base & operator =(const string_array_base & stra);
//string_array_base & operator -=(const string_array_base & stra);
//string_array_base & operator +=(const string_array_base & stra);

    using BASE_ARRAY::operator +=;
    using BASE_ARRAY::operator -=;


//string_array_base operator -(const string_array_base & stra) const;
//string_array_base operator +(const string_array_base & stra) const;
//   string_array_base operator -(const string_array_base & stra) const;
//   string_array_base operator +(const string_array_base & stra) const;


    bool operator == (const RawStringArray & a) const;
    bool operator != (const RawStringArray & a) const;


    void replace_with(const RawType &strNew, const RawType &strOld);


//void write(stream & ostream) const;
//void read(stream & istream);


    void get_format_string(Type & str,const RawType &strSeparator) const;

    void add_tokens(const RawType &str, const RawType &strSeparator,bool bAddEmpty = true);

    void add_smallest_tokens(const RawType &str, const RawStringArray & straSeparator,bool bAddEmpty = true,bool bWithSeparator = false);

    template < bool bAddEmpty >
    typename Type::const_iterator _____add_lines_rn(const SCOPED_STRING & scopedstr);
//template < CHARACTER chSeparator, bool bAddEmpty >
//typename Type::const_iterator _____add_lines(const SCOPED_STRING & scopedstr);
    template < bool bAddEmpty >
    void __add_lines_suffix(Type::const_iterator start, Type::const_iterator end)
    {

       if (start < end)
       {

          this->add_item({ start, end});

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
    void _add_lines(const SCOPED_STRING & scopedstr);
    void add_lines(const SCOPED_STRING & scopedstr, bool bAddEmpty = true)
    {
       if(bAddEmpty)_add_lines<true>(scopedstr); else _add_lines<false>(scopedstr);
    }


    template < CHARACTER chSeparator, bool bAddEmpty >
    typename Type::const_iterator  _____add_lines(const SCOPED_STRING & scopedstr)
    {

       auto range = scopedstr();

       while (true)
       {

          auto p = range.find(chSeparator);

          if (::is_null(p))
          {

             return range.begin();

          }

          __add_lines_suffix<bAddEmpty>(range.begin(), p);

          range.begin(p + 1);

       }

    }



    void _001AddTokens(const RawType &str);



    bool is_empty(::count countMinimum = 1) const;
    bool has_elements(::count countMinimum = 1) const;

    Type encode_v16();


    void decode_v16(const RawType &str);

    ::count count_except(const RawType &str);
    ::count count_except(const string_array_base & stra);

    ::count count_except_ci(const RawType &str);
    ::count count_except_ci(const string_array_base & stra);

    Type & get_network_payload(Type & str, bool bNewLine = true) const;



// c_get
    ::array < const ::ansi_character * > c_ansi_get(bool bMemoryAlloc = false) const;
//::array < const ::wide_character * > c_wide_get(bool bMemoryAlloc = false) const;
    void c_add(char ** ppsz, ::count iCount, bool bMemoryAlloc = false);
    void c_add(char ** ppsz, bool bMemoryAlloc = false);
    void c_add(wchar_t ** ppsz, ::count iCount, bool bMemoryAlloc = false);
    void c_add(wchar_t ** ppsz, bool bMemoryAlloc = false);

    string_array_base & intersect(const string_array_base & a)
    {

       for (::index i = 0; i < get_size(); )
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

    string_array_base & intersect_ci(const string_array_base & a)
    {

       for (::index i = 0; i < get_size(); )
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

    string_array_base & operator &=(const string_array_base & a)
    {

       return intersect(a);

    }


    ::std::strong_ordering case_insensitive_order(const THIS_RAW_RANGE & rawrange) const
    {

       return BASE_ARRAY::order(rawrange, ::comparison::case_insensitive < Type >());

    }


};


//typedef CLASS_DECL_ACME string_array_base < string > string_array;
typedef CLASS_DECL_ACME string_array_base < wstring > wstring_array;


class CLASS_DECL_ACME string2a:
        public array < string_array >
{
public:


    void add_csv(string str);


};


CLASS_DECL_ACME bool next_csv(string & str, const string_array & stra);
CLASS_DECL_ACME void add_csv(string_array & stra, const ::string &str);







