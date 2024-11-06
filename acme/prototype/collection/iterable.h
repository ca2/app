#pragma once


#include "collection_map_association.h"
#include "collection_sort.h"




namespace iter
{

   template < typename ITERABLE, typename ITYPE >
   bool icontains(const ITERABLE & iterable, const ITYPE & t, index first = 0, ::collection::count count = -1);

   template < typename ITERABLE, typename ITYPE >
   bool contains(const ITERABLE & iterable, const ITYPE & t, typename ITERABLE::const_iterator pos, typename ITERABLE::const_iterator posLast = nullptr, ::collection::count countMin = 0, ::collection::count countMax = -1);

   template < typename ITERABLE, typename ITYPE >
   bool contains(ITERABLE & iterable, const ITYPE & t, typename ITERABLE::iterator pos, typename ITERABLE::iterator posLast = nullptr, ::collection::count countMin = 0, ::collection::count countMax = -1);

   template < typename ITERABLE, typename ITERABLE2 >
   void copy(ITERABLE & iterable, const ITERABLE2 & iterable2);


   template < typename ITERABLE, typename ITYPE >
   ITERABLE & add_lines(ITERABLE & iterable, const ITYPE & str, bool bAddEmpty = true);

   template < typename ITERABLE, typename ITYPE >
   bool add_unique(ITERABLE & iterable, const ITYPE & pcsz);

   template < typename ITERABLE, typename ITYPE >
   bool case_insensitive_add_unique(ITERABLE & iterable, const ITYPE & pcsz);

   template < typename ITERABLE, typename ITERABLE2, typename ITYPE >
   typename ::collection::count add_unique_iter(ITERABLE & iterable, const ITERABLE & stra);

   template < typename ITERABLE, typename ITERABLE2, typename ITYPE >
   typename ::collection::count case_insensitive_add_unique_iter(ITERABLE & iterable, const ITERABLE & stra);

   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE & add(ITERABLE & iterable, const ITERABLE2 & iterable2);

   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE & copy_iter(ITERABLE & iterable, const ITERABLE2 & iterable2);

   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE & insert_iter_at(ITERABLE & iterable, typename ITERABLE::iterator nStartIndex, const ITERABLE2 & iterable2);

   template < typename ITERABLE >
   ::collection::count erase_empty(ITERABLE & iterable);

   template < typename ITERABLE, typename ITYPE, typename ITYPE2 >
   ITERABLE & replace(ITERABLE & iterable, const ITYPE & lpszSearch, const ITYPE2 & lpszReplace);

   // if ITYPE is found, transfer it to specified position
   template < typename ITERABLE, typename ITYPE, typename ITERABLE2 >
   bool case_insensitive_move(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator iIndex);

   template < typename ITERABLE >
   ITERABLE & copy(ITERABLE & iterable, const ::payload payload);

   template < typename ITERABLE, typename ITYPE, typename ITERABLE2 >
   ITERABLE & add_shortest_tokens(ITERABLE & iterable, const ITYPE & pcsz, const ITERABLE2 & iterableSeparator, bool bAddEmpty = true, bool bWithSeparator = false);

   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE2 & slice(ITERABLE & iterable, ITERABLE2 & iterable2, typename ITERABLE::iterator first, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE2 & islice(ITERABLE & iterable, ITERABLE2 & iterable2, index first, ::collection::count count = -1);

   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE & add_iter(ITERABLE & iterable, const ITERABLE2 & iterable2);

   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE diff(const ITERABLE & iterable, const ITERABLE2 & iterable2);

   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE sum(const ITERABLE & iterable, const ITERABLE2 & iterable2);

   template < typename ITERABLE >
   void make_lower(ITERABLE & iterable);

   template < typename ITERABLE >
   void make_upper(ITERABLE & iterable);

   template < typename ITERABLE >
   void erase(ITERABLE & iterable, typename ITERABLE::iterator typename first = nullptr, typename ITERABLE::iterator typename last = nullptr);

   template < typename ITERABLE, typename ITYPE, typename ITYPE2 >
   void implode(const ITERABLE & iterable, ITYPE & rwstr, const ITYPE2 & lpcszSeparator = "", typename ITERABLE::const_iterator iStart = 0, typename ITERABLE::const_iterator iEnd = nullptr);

   template < typename ITERABLE, typename ITYPE, typename ITYPE2 >
   void reverse_implode(const ITERABLE & iterable, ITYPE & rwstr, const ITYPE & lpcszSeparator = "", typename ITERABLE::const_iterator iStart = 0, typename ITERABLE::const_iterator iEnd = nullptr);

   template < typename ITERABLE, typename ITYPE, typename ITYPE2, typename ITYPE3 >
   void implode_ex(const ITERABLE & iterable, ITYPE & rwstr, const ITYPE2 & lpcszSeparator = "", const ITYPE3 & lpcszLastSeparator = nullptr, typename ITERABLE::const_iterator iStart = 0, typename ITERABLE::const_iterator iEnd = nullptr);

   template < typename ITERABLE, typename ITYPE >
   void if_prefix_implode_ex(const ITERABLE & iterable, ITYPE & rwstr, const ITYPE & lpcszIfHasElementPrefix = nullptr, const ITYPE & lpcszSeparator = nullptr, const ITYPE & lpcszLastSeparator = nullptr, bool bUseLast = true, typename ITERABLE::iterator iStart = 0, typename ITERABLE::const_iterator iEnd = nullptr);

   template < typename ITERABLE, typename ITERABLE2, typename ITYPE >
   void prefix(ITERABLE & iterable, const ITERABLE2 & iterable2, const ITYPE & pszPrefix, typename ITERABLE2::const_iterator first = nullptr, typename ITERABLE2::const_iterator last = nullptr);

   template < typename ITERABLE, typename ITERABLE2, typename ITYPE >
   void suffix(ITERABLE & iterable, const ITERABLE2 & iterable2, const ITYPE & pszSuffix, typename ITERABLE2::const_iterator first = nullptr, typename ITERABLE2::const_iterator last = nullptr);

   template < typename ITERABLE, typename ITERABLE2, typename ITYPE, typename ITYPE2 >
   void surround(ITERABLE & iterable, const ITERABLE2 & iterable2, const ITYPE & pszPrefix = "", const ITYPE2 & pszSuffix = "", typename ITERABLE2::const_iterator first = nullptr, typename ITERABLE2::const_iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   void prefix(ITERABLE & iterable, const ITYPE & pszPrefix, typename ITERABLE::iterator first = nullptr, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   void suffix(ITERABLE & iterable, const ITYPE & pszSuffix, typename ITERABLE::iterator first = nullptr, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE, typename ITYPE2 >
   void surround(ITERABLE & iterable, const ITYPE & pszPrefix = "", const ITYPE2 & pszSuffix = "", typename ITERABLE::iterator first = nullptr, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE, typename ITYPE2, typename ITYPE3, typename ITYPE4 >
   void surround_and_implode(const ITERABLE & iterable, ITYPE & str, const ITYPE2 & lpcszSeparator = "", const ITYPE3 & pszPrefix = "", const ITYPE4 & pszSuffix = "", typename ITERABLE::iterator first = nullptr, typename ITERABLE::iterator last = nullptr);

   //template < typename ITERABLE, typename ITERABLE2>
   //void get_comparable_ida(const ITERABLE & iterable, ITERABLE2 & iterable2);

   template < typename ITERABLE, typename ITYPE >
   ::collection::count explode_command_line(const ITERABLE & iterable, const ITYPE & str, char ** argv = nullptr);

   template < typename ITERABLE, typename ITERABLE2 >
   bool operator == (const ITERABLE & iterable, const ITERABLE & iterable2);

   template < typename ITERABLE, typename ITERABLE2 >
   bool operator != (const ITERABLE & iterable, const ITERABLE & iterable2);

   template < typename ITERABLE, typename ITERABLE2 >
   ::collection::count case_insensitive_erase_iter(ITERABLE & iterable, const ITERABLE & iterableRemove);

   template < typename ITERABLE, typename ITERABLE2 >
   ::collection::count erase_iter(ITERABLE & iterable, const ITERABLE2 & iterableRemove);

   template < typename ITERABLE, typename ITYPE >
   ITERABLE & trim_right(ITERABLE & iterable, const ITYPE & pszChars);

   template < typename ITERABLE, typename ITYPE >
   ITERABLE & trim_left(ITERABLE & iterable, const ITYPE & pszChars);

   template < typename ITERABLE, typename ITYPE >
   ITERABLE & trim(ITERABLE & iterable, const ITYPE & pszChars);

   template < typename ITERABLE >
   ITERABLE & trim_right(ITERABLE & iterable);

   template < typename ITERABLE >
   ITERABLE & trim_left(ITERABLE & iterable);

   template < typename ITERABLE >
   ITERABLE & trim(ITERABLE & iterable);

   // transfer preferred in order
   template < typename ITERABLE, typename ITYPE >
   ITERABLE & preferred(ITERABLE & iterable, const ITYPE & pcsz);

   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE & preferred_iter(ITERABLE & iterable, const ITERABLE2 & iterable2);

   template < typename ITERABLE, typename PRED >
   bool predicate_erase_first(ITERABLE & iterable, PRED pred);

   template < typename ITERABLE, typename PRED >
   typename ITERABLE::const_iterator predicate_find_first(const ITERABLE & iterable, PRED pred, typename ITERABLE::const_iterator = nullptr, typename ITERABLE::const_iterator last = nullptr);

   template < typename ITERABLE, typename PRED >
   typename ITERABLE::iterator predicate_find_first(ITERABLE & iterable, PRED pred, typename ITERABLE::iterator = nullptr, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename index case_insensitive_ifind_first(const ITERABLE & iterable, const ITYPE & pcsz, index first, ::collection::count count = -1);

   template < typename ITERABLE, typename ITYPE >
   typename index ifind_first_begins(const ITERABLE & iterable, const ITYPE & pcsz, ::collection::index find, ::collection::count count = -1);

   template < typename ITERABLE, typename ITYPE >
   typename index case_insensitive_ifind_first_begins(const ITERABLE & iterable, const ITYPE & pcsz, ::collection::index find = 0, ::collection::count count = -1);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator case_insensitive_find_first(const ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::const_iterator find = nullptr, typename ITERABLE::const_iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator find_first(const ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::const_iterator find = nullptr, typename ITERABLE::const_iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator case_insensitive_find_last(const ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::const_iterator find = nullptr, typename ITERABLE::const_iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator find_last(const ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::const_iterator find = nullptr, typename ITERABLE::const_iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator case_insensitive_reverse_find(const ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::const_iterator find = -1, typename ITERABLE::const_iterator last = 0);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator rear_find(const ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::const_iterator find = -1, typename ITERABLE::const_iterator last = 0);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator any_suffixes(const ITERABLE & iterable, const ITYPE & lpcszIsSuffixed, typename ITERABLE::const_iterator find = nullptr, typename ITERABLE::const_iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator any_case_insensitive_suffixes(const ITERABLE & iterable, const ITYPE & lpcszIdSuffixed, typename ITERABLE::const_iterator find = nullptr, typename ITERABLE::const_iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator any_prefixes(const ITERABLE & iterable, const ITYPE & lpcszIsPrefixed, typename ITERABLE::const_iterator find = nullptr, typename ITERABLE::const_iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator case_insensitive_any_prefixes(const ITERABLE & iterable, const ITYPE & lpcszIsPrefixed, typename ITERABLE::const_iterator find = nullptr, typename ITERABLE::const_iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator find_first_ends(const ITERABLE & iterable, const ITYPE & lpcszSuffix, typename ITERABLE::const_iterator find = nullptr, typename ITERABLE::const_iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator case_insensitive_find_first_ends(const ITERABLE & iterable, const ITYPE & lpcszSuffix, typename ITERABLE::const_iterator find = nullptr, typename ITERABLE::const_iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator find_first_ends_eat(const ITERABLE & iterable, ITYPE & str, const ITYPE & pcsz, typename ITERABLE::const_iterator find = nullptr, typename ITERABLE::const_iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator case_insensitive_find_first_ends_eat(const ITERABLE & iterable, ITYPE & str, const ITYPE & pcsz, typename ITERABLE::const_iterator find = nullptr, typename ITERABLE::const_iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator find_first_begins(const ITERABLE & iterable, const ITYPE & lpcszPrefix, typename ITERABLE::const_iterator find = nullptr, typename ITERABLE::const_iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator case_insensitive_find_first_begins(const ITERABLE & iterable, const ITYPE & lpcszPrefix, typename ITERABLE::const_iterator find = 0, typename ITERABLE::const_iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator find_first_begins_eat(const ITERABLE & iterable, ITYPE & str, const ITYPE & pcsz, typename ITERABLE::const_iterator find = 0, typename ITERABLE::const_iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator case_insensitive_find_first_begins_eat(const ITERABLE & iterable, ITYPE & str, const ITYPE & pcsz, typename ITERABLE::const_iterator find = 0, typename ITERABLE::const_iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator case_insensitive_find_first(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator find_first(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator case_insensitive_find_last(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator find_last(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator case_insensitive_reverse_find(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find = -1, typename ITERABLE::iterator last = 0);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator rear_find(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find = -1, typename ITERABLE::iterator last = 0);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator any_suffixes(ITERABLE & iterable, const ITYPE & lpcszIsSuffixed, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator any_case_insensitive_suffixes(ITERABLE & iterable, const ITYPE & lpcszIdSuffixed, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator any_prefixes(ITERABLE & iterable, const ITYPE & lpcszIsPrefixed, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator case_insensitive_any_prefixes(ITERABLE & iterable, const ITYPE & lpcszIsPrefixed, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator find_first_ends(ITERABLE & iterable, const ITYPE & lpcszSuffix, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator case_insensitive_find_first_ends(ITERABLE & iterable, const ITYPE & lpcszSuffix, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator find_first_ends_eat(ITERABLE & iterable, ITYPE & str, const ITYPE & pcsz, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator case_insensitive_find_first_ends_eat(ITERABLE & iterable, ITYPE & str, const ITYPE & pcsz, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator find_first_begins(ITERABLE & iterable, const ITYPE & lpcszPrefix, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator case_insensitive_find_first_begins(ITERABLE & iterable, const ITYPE & lpcszPrefix, typename ITERABLE::iterator find = 0, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator find_first_begins_eat(ITERABLE & iterable, ITYPE & str, const ITYPE & pcsz, typename ITERABLE::iterator find = 0, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator case_insensitive_find_first_begins_eat(ITERABLE & iterable, ITYPE & str, const ITYPE & pcsz, typename ITERABLE::iterator find = 0, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   bool case_insensitive_contains(const ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last = nullptr, ::collection::count countMin = 1, ::collection::count countMax = -1);

   template < typename ITERABLE, typename ITYPE >
   bool case_insensitive_icontains(const ITERABLE & iterable, const ITYPE & pcsz, index first, ::collection::count count = -1, ::collection::count countMin = 1, ::collection::count countMax = -1);

   template < typename ITERABLE, typename STRITERABLE, typename ITYPE >
   ::collection::count case_insensitive_get_begins(ITERABLE & iterable, STRITERABLE & stra, const ITYPE & pcsz, typename ITERABLE::iterator first = 0, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   ::collection::count case_insensitive_filter_begins(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator first = 0, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename PRED >
   ::collection::count filter(ITERABLE & iterable, PRED pred, typename ITERABLE::iterator first = 0, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename PRED >
   ::collection::count filter_out(ITERABLE & iterable, PRED pred, typename ITERABLE::iterator first = 0, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename PRED, typename ArrayOut >
   ::collection::count filter_out(ITERABLE & iterable, PRED pred, ArrayOut & a, typename ITERABLE::iterator first = 0, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   bool case_insensitive_erase_first(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   bool erase_first(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE >
   void erase_first(ITERABLE & iterable);

   template < typename ITERABLE, typename ITYPE >
   bool case_insensitive_erase_last(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   bool erase_last(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE >
   void erase_last(ITERABLE & iterable);

   template < typename ITERABLE, typename ITYPE >
   ::collection::count case_insensitive_erase(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last, ::collection::count countMin, ::collection::count countMax = -1);

   template < typename ITERABLE, typename ITYPE >
   ::collection::count erase(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last, ::collection::count countMin, ::collection::count countMax = -1);

   template < typename ITERABLE, typename ITYPE >
   ::collection::count case_insensitive_erase(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   ::collection::count erase(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last = nullptr);

   template < typename ITERABLE, typename ITYPE >
   ::collection::count case_insensitive_erase(ITERABLE & iterable, const ITYPE & pcsz);

   template < typename ITERABLE, typename ITYPE >
   ::collection::count erase(ITERABLE & iterable, const ITYPE & pcsz);

   template < typename ITERABLE, typename ITYPE >
   ::collection::count case_insensitive_ierase(ITERABLE & iterable, const ITYPE & pcsz, index first = 0, ::collection::count count = -1);

   template < typename ITERABLE, typename ITYPE >
   ::collection::count ierase(ITERABLE & iterable, const ITYPE & pcsz, index first = 0, ::collection::count count = -1);

   template < typename ITERABLE, typename ITYPE, typename ITYPE2 >
   ITERABLE & explode(ITERABLE & iterable, const ITYPE & strSeparator, const ITYPE2 & str);

   // csstidy: Same as explode, but not within a ITYPE
   template < typename ITERABLE, typename ITYPE >
   ITERABLE & csstidy_explode_ws(const ITERABLE & iterable, char sep, const ITYPE & psz);

   template < typename ITERABLE, typename ITYPE >
   void get_format_string(const ITERABLE & iterable, ITYPE & str, const ITYPE & lpcszSeparator);

   template < typename ITERABLE, typename ITYPE, typename ITYPE2 >
   ITERABLE & add_tokens(ITERABLE & iterable, const ITYPE & pcsz, const ITYPE2 & lpcszSeparator, bool bAddEmpty = true);

   template < typename ITERABLE, typename ITYPE >
   ITYPE encode_v16(const ITERABLE & iterable);

   template < typename ITERABLE, typename ITYPE >
   void decode_v16(ITERABLE & iterable, const ITYPE & psz);

   template < typename ITERABLE, typename ITYPE >
   ::collection::count get_count_except(const ITERABLE & iterable, const ITYPE & psz);

   template < typename ITERABLE, typename ITYPE >
   ::collection::count get_count_except(const ITERABLE & iterable, const ITYPE & str);

   template < typename ITERABLE, typename ITERABLE2 >
   ::collection::count get_count_except_iter(const ITERABLE & iterable, const ITERABLE & iterable2);

   template < typename ITERABLE, typename ITYPE >
   ::collection::count case_insensitive_get_count_except(const ITERABLE & iterable, const ITYPE & psz);

   template < typename ITERABLE, typename ITYPE >
   ::collection::count case_insensitive_get_count_except(const ITERABLE & iterable, const ITYPE & str);

   template < typename ITERABLE, typename ITERABLE2 >
   ::collection::count case_insensitive_get_count_except_iter(const ITERABLE & iterable, const ITERABLE & set);

   template < typename ITERABLE, typename ITYPE >
   ITYPE & get_network_payload(const ITERABLE & iterable, ITYPE & str, bool bNewLine = true);

   template < typename ITERABLE, typename ITYPE >
   void c_add(ITERABLE & iterable, char ** ppsz, ::collection::count iCount);

   template < typename ITERABLE, typename ITYPE >
   void c_add(ITERABLE & iterable, char ** ppsz);

   template < typename ITERABLE, typename ITYPE >
   void c_add(ITERABLE & iterable, wchar_t ** ppsz, ::collection::count iCount);

   template < typename ITERABLE, typename ITYPE >
   void c_add(ITERABLE & iterable, wchar_t ** ppsz);

   template < typename ITERABLE, typename ITYPE >
   bool contains(const ITERABLE & iterable, const ITYPE & value);

   template < typename ITERABLE, typename ITYPE >
   bool case_insensitive_contains(const ITERABLE & iterable, const ITYPE & value);




   template < typename ITERABLE, typename ITYPE >
   bool contains(const ITERABLE & iterable, const ITYPE & value)
   {

      for (auto & item : iterable)
      {

         if (item == value)
         {

            return true;

         }

      }

      return false;

   }


   template < typename ITERABLE, typename ITYPE >
   bool case_insensitive_contains(const ITERABLE & iterable, const ITYPE & value)
   {

      for (auto & item : iterable)
      {

         if (case_insensitive_ansi_compare(item, value) == 0)
         {

            return true;

         }

      }

      return false;

   }


   template < typename ITERABLE, typename PAIR >
   bool contains(ITERABLE & iterable, const set_node < PAIR > & assoc)
   {

      for (auto item : iterable1)
      {

         if (item == assoc.element1())
         {

            return true;

         }

      }

      return false;

   }


   template < typename ITERABLE, typename ITERABLE2, typename PRED >
   ITERABLE & intersect(ITERABLE & iterable, const ITERABLE2 & iterable2, PRED pred)
   {

      for (auto it = iterable.begin(); it != iterable.end();)
      {

         if (contains(iterable2, *it, pred))
         {

            iterable.erase_at(it);

         }
         else
         {

            it++;

         }

      }

      return iterable;

   }


   template < typename ITERABLE1, typename ITERABLE2 >
   ITERABLE1 & intersect(ITERABLE1 & iterable, const ITERABLE2 & iterable2)
   {

      for (auto it = iterable.begin(); it != iterable.end();)
      {

         if (contains(iterable2, *it))
         {

            iterable.erase(it);

         }
         else
         {

            it++;

         }

      }

      return iterable;

   }


   template < typename ITERABLE, typename ITYPE >
   typename ITYPE maximum(const ITERABLE & iterable, ITYPE maximum)
   {

      for (auto & item : iterable)
      {

         if (item > maximum)
         {

            maximum = item;

         }

      }

      return maximum;

   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator find_first_value(ITERABLE & iterable, const ITYPE & value)
   {

      auto it = iterable.begin();

      for (; it != iterable.end(); it++)
      {

         if (it->element2() == value)
         {

            break;

         }

      }

      return it;

   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator find_first_value(const ITERABLE & iterable, const ITYPE & value)
   {

      auto it = iterable.begin();

      for (; it != iterable.end(); it++)
      {

         if (it->element2() == value)
         {

            break;

         }

      }

      return it;

   }


   template < typename ITERABLE >
   typename ITERABLE::const_iterator find_first_value(const ITERABLE & iterable, const typename ITERABLE::PAYLOAD & value)
   {

      for (auto & item : iterable)
      {

         if (item.element2() == value)
         {

            return item;

         }

      }

      return iterable.end();

   }

   template < typename ITERABLE, typename ITYPE >
   bool contains_key(const ITERABLE & iterable, const ITYPE & value)
   {

      return iterable.find_first_key(value) != iterable.end();

   }

   template < typename ITERABLE, typename ITYPE >
   bool contains_payload(const ITERABLE & iterable, const ITYPE & value)
   {

      return find_first_value(iterable, value) != iterable.end();

   }


   template < typename ITERABLE >
   bool erase_first(ITERABLE & iterable, const typename ITERABLE::ITYPE & t)
   {

      auto find = find_first(iterable, t);

      if (find != iterable.end())
      {

         iterable.erase(find);

         return true;

      }

      return false;

   }


   template < typename ITERABLE >
   bool erase_last(ITERABLE & iterable, const typename ITERABLE::ITYPE & t)
   {

      auto find = find_last(iterable, t);

      if (find != iterable.end())
      {

         iterable.erase(find);

         return true;

      }

      return false;
   }


   template < typename ITERABLE, typename ITYPE >
   bool erase_first(ITERABLE & iterable, const ITYPE & t, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {

      if ((first = find_first(iterable, t, first, last)) != iterable.end())
      {

         iterable.erase(first);

         return true;

      }

      return false;

   }


   template < typename ITERABLE, typename ITYPE >
   bool erase_last(ITERABLE & iterable, const ITYPE & t, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {

      if ((first = find_last(iterable, t, first, last)) != iterable.end())
      {

         iterable.erase(first);

         return true;

      }

      return false;

   }


   template < typename ITERABLE >
   void erase_first(ITERABLE & iterable)
   {

      iterable.erase(iterable.begin());

   }


   template < typename ITERABLE >
   void erase_last(ITERABLE & iterable)
   {

      iterable.erase(iterable.upper_bound());

   }


   template < typename ITERABLE, typename ITYPE >
   bool case_insensitive_icontains(const ITERABLE & iterable, const ITYPE & t, index first, ::collection::count count, ::collection::count countMin, ::collection::count countMax)
   {
      ::collection::count c = 0;
      while ((c < countMin || (countMax >= 0 && c <= countMax))
             && (first = case_insensitive_ifind_first(iterable, t, first, count)) >= 0)
      {
         c++;
         first++;
      }
      return c >= countMin && conditional(countMax >= 0, c <= countMax);
   }


   template < typename ITERABLE, typename ITYPE >
   ::collection::index ifind_first(const ITERABLE & iterable, const ITYPE & t, index first, ::collection::count count)
   {

      iterable.iprepare_first_count(first, count);

      for (; first < count; first++)
      {

         if (iterable.element_at(first) == t)
         {

            return first;

         }

      }

      return -1;

   }


   template < typename ITERABLE, typename ITYPE >
   bool icontains(const ITERABLE & iterable, const ITYPE & t, index first, ::collection::count count)
   {

      return ifind_first(iterable, t, first, count) >= 0;

   }


   template < typename ITERABLE, typename ITYPE >
   bool contains(const ITERABLE & iterable, const ITYPE & t, typename ITERABLE::const_iterator find, typename ITERABLE::const_iterator last, ::collection::count countMin, ::collection::count countMax)
   {
      ::collection::count count = 0;
      while ((count < countMin || (countMax >= 0 && count <= countMax))
             && (find = find_first(iterable, t, find, last)) != iterable.end())
         count++;
      return count >= countMin && conditional(countMax >= 0, count <= countMax);
   }



   template < typename ITERABLE, typename ITYPE >
   bool contains(ITERABLE & iterable, const ITYPE & t, typename ITERABLE::iterator find, typename ITERABLE::iterator last, ::collection::count countMin, ::collection::count countMax)
   {
      ::collection::count count = 0;
      while ((count < countMin || (countMax >= 0 && count <= countMax))
             && (find = find_first(iterable, t, find, last)) != iterable.end())
         count++;
      return count >= countMin && conditional(countMax >= 0, count <= countMax);
   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator find_first(const ITERABLE & iterable, const ITYPE & t, typename ITERABLE::const_iterator find, typename ITERABLE::const_iterator last)
   {

      iterable.prepare_first_last(find, last);

      for (; iterable.valid_iter(find, last); find++)
      {

         if (*find == t)
         {

            return find;

         }

      }

      return iterable.end();

   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator find_first(ITERABLE & iterable, const ITYPE & t, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {

      iterable.prepare_first_last(first, last);

      for (; iterable.valid_iter(first, last); find++)
      {

         if (*first == t)
         {

            return first;

         }

      }

      return iterable.end();

   }


   template < typename ITERABLE, class ITYPE >
   ::collection::count erase(ITERABLE & iterable, const ITYPE & t, typename ITERABLE::iterator first, typename ITERABLE::iterator last, ::collection::count countMin, ::collection::count countMax)
   {
      ::collection::count count = 0;
      if (contains(iterable, t, first, last, countMin, countMax))
         while (conditional(countMax >= 0, count < countMax) && erase_first(iterable, t, first, last))
            count++;
      return count;
   }


   template < typename ITERABLE, class ITYPE >
   ::collection::count case_insensitive_erase(ITERABLE & iterable, const ITYPE & t, typename ITERABLE::iterator first, typename ITERABLE::iterator last, ::collection::count countMin, ::collection::count countMax)
   {
      ::collection::count count = 0;
      if (case_insensitive_contains(iterable, t, first, last, countMin, countMax))
         while (conditional(countMax >= 0, count < countMax) && case_insensitive_erase_first(iterable, t, first, last))
            count++;
      return count;
   }


   //template < typename ITERABLE, class ITYPE >
   //::collection::count case_insensitive_erase(ITERABLE & iterable, const ITYPE & t, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   //{

   //   ::collection::count c = 0;

   //   prepare_first_count(first, last);

   //   decltype(first) itRemove;

   //   for (; iterable.valid_iter(first, last);)
   //   {

   //      if (case_insensitive_ansi_compare(*first, t) == 0)
   //      {

   //         itRemove = first;

   //         first++;

   //         iterable.erase_at(itRemove);

   //         c++;

   //      }
   //      else
   //      {

   //         first++;

   //      }

   //   }

   //   return c;

   //}


   template < typename ITERABLE, class ITYPE >
   ::collection::count erase(ITERABLE & iterable, const ITYPE & t, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {

      ::collection::count c = 0;

      prepare_first_count(first, last);

      decltype(first) itRemove;

      for (; iterable.valid_iter(first, last);)
      {

         if (*first == t)
         {

            itRemove = first;

            first++;

            iterable.erase_at(itRemove);

            c++;

         }
         else
         {

            first++;

         }

      }

      return c;

   }


   template < typename ITERABLE, class ITYPE >
   ::collection::count case_insensitive_erase(ITERABLE & iterable, const ITYPE & t, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {

      ::collection::count c = 0;

      prepare_first_count(first, last);

      decltype(first) itRemove;

      for (; iterable.valid_iter(first, last);)
      {

         if (case_insensitive_ansi_compare(*first, t) == 0)
         {

            itRemove = first;

            first++;

            iterable.erase_at(itRemove);

            c++;

         }
         else
         {

            first++;

         }

      }

      return c;

   }

   template < typename ITERABLE, class ITYPE >
   ::collection::count erase(ITERABLE & iterable, const ITYPE & t)
   {

      ::collection::count c = 0;

      auto first = iterable.begin();

      for (; iterable.valid_iter(first, iterable.end());)
      {

         if (*first == t)
         {

            iterable.erase(first);

            c++;

         }
         else
         {

            first++;

         }

      }

      return c;

   }


   template < typename ITERABLE, class ITYPE >
   ::collection::count case_insensitive_erase(ITERABLE & iterable, const ITYPE & t)
   {

      ::collection::count c = 0;

      auto first = iterable.begin();

      for (; iterable.valid_iter(first, iterable.end());)
      {

         if (case_insensitive_ansi_compare(*first, t) == 0)
         {

            itRemove = first;

            first++;

            iterable.erase_at(itRemove);

            c++;

         }
         else
         {

            first++;

         }

      }

      return c;

   }



   template < typename ITERABLE, class ITYPE >
   ::collection::count rerase(ITERABLE & iterable, const ITYPE & t, typename ITERABLE::iterator first, typename ITERABLE::iterator last, ::collection::count countMin, ::collection::count countMax)
   {
      ::collection::count count = 0;
      if (contains(iterable, t, first, last, countMin, countMax))
         while (conditional(countMax >= 0, count < countMax) && erase_last(iterable, t, first, last))
            count++;
      return count;
   }


   template < typename ITERABLE, typename ITERABLE2 >
   void copy(ITERABLE & iterable, const ITERABLE2 & iterable2)
   {

      iterable.erase_all();

      for (auto & item : iterable2)
      {

         iterable.add(item);

      }

   }


   //template < typename ITERABLE, typename ITYPE >
   //bool contains_payload(const ITERABLE & map, const ITYPE & value)
   //{


   //   auto it = map.begin();

   //   for (; it != map.end(); it++)
   //   {

   //      if (it->element2() == value)
   //      {

   //         return true;

   //      }

   //   }

   //   return false;

   //}



   //template < typename ITERABLE, typename ITYPE >
   //ITERABLE()
   //{
   //
   //
   //}

   //template < typename ITERABLE, typename ITYPE >
   //ITERABLE(const ITERABLE & iterable)
   //{
   //
   //   copy(iterable);
   //
   //}


   //template < typename ITERABLE, typename ITYPE >
   //template < typename ITERABLE >
   //ITERABLE(const ITERABLE & iterable)
   //{
   //
   //   copy_iter(iterable);
   //
   //}
   //


   template < typename ITERABLE, typename ITYPE, typename ITYPE2 >
   void reverse_implode(const ITERABLE & iterable, ITYPE & str, const ITYPE2 & lpcszSeparator, typename ITERABLE::iterator first, ::collection::count last)
   {

      str.empty();

      string strSeparator(lpcszSeparator);

      if (first == nullptr)
      {

         first = begin();

      }

      if (last == nullptr)
      {

         last = upper_bound();

      }

      if (last == )

         for (auto i = last; i >= start; i--)
         {

            if (i < last)
            {
               str += strSeparator;
            }

            str += get_at(pos);

            get_previous(pos);

         }

   }



   template < typename ITERABLE, typename ITERABLE2 >
   ::collection::count case_insensitive_erase_iter(ITERABLE & iterable, const ITERABLE2 & iterable2)
   {

      ::collection::count count = 0;

      for (auto & item : iterable2)
      {

         count += case_insensitive_erase(iterable, item);

      }

      return count;

   }


   template < typename ITERABLE, typename ITERABLE2 >
   ::collection::count erase_iter(ITERABLE & iterable, const ITERABLE2 & iterable2)
   {

      ::collection::count count = 0;

      for (auto & item : iterable)
      {

         count += erase(iterable, item);

      }

      return count;

   }



   template < typename ITERABLE, typename ITYPE, typename ITYPE2 >
   void implode(const ITERABLE & iterable, ITYPE & str, const ITYPE2 & lpcszSeparator, typename ITERABLE::const_iterator first, typename ITERABLE::const_iterator last)
   {

      iterable.prepare_first_last(first, last);

      str.empty();

      ITYPE strSeparator(lpcszSeparator);

      if (iterable.valid_iter(first, last))
      {

         str = *first;

         first++;

      }

      for (; iterable.valid_iter(first, last); first++)
      {

         str += strSeparator;

         str += *first;

      }

   }



   //template < typename ITERABLE, typename ITYPE >
   //void reverse_implode(ITYPE & str, const ITYPE & lpcszSeparator, typename ITERABLE::iterator start, ::collection::count count)
   //{
   //   str.empty();
   //   ITYPE strSeparator(lpcszSeparator);
   //   if (start < 0)
   //   {
   //      start += iterable.get_size();
   //   }
   //   typename ITERABLE::iterator last;
   //   if (count < 0)
   //   {
   //      last = iterable.get_size() + count;
   //   }
   //   else
   //   {
   //      last = start + count - 1;
   //   }
   //   for (typename ITERABLE::iterator i = last; i >= start; i--)
   //   {
   //      if (i < last)
   //      {
   //         str += strSeparator;
   //      }
   //      str += iterable.element_at(i);
   //   }
   //}


   //template < typename ITERABLE, typename ITYPE >
   //ITYPE reverse_implode(const ITYPE & lpcszSeparator, typename ITERABLE::iterator iStart, typename ITERABLE::iterator iEnd)
   //{
   //   ITYPE str;
   //   reverse_implode(str, lpcszSeparator, iStart, iEnd);
   //   return str;
   //}
   //



   //template < typename ITERABLE, typename ITERABLE >
   //bool is_equal (const ITERABLE & iterable, const ITERABLE2 & iterable2)
   //{

   //   if (iterable.get_count() != get_count())
   //   {

   //      return false;

   //   }

   //   for (auto i = iterable.begin(), auto j = iterable.begin(); i < iterable.end(); i++, j++)
   //   {

   //      if (*i != *j)
   //      {

   //         return false;

   //      }

   //   }

   //   return true;

   //}


   //template < typename ITERABLE, typename ITYPE >
   //template < typename ITERABLE >
   //bool operator != (const ITERABLE & iterable, const ITERABLE & iterable)
   //{

   //   return !operator == (iterable);

   //}



   template < typename ITERABLE, typename ITYPE >
   ::collection::count explode_command_line(ITERABLE & iterable, const ITYPE & str, char ** argv)
   {

      ITYPE strParse(str);

      while (strParse.has_character())
      {

         iterable.add((ITYPE)::str::consume_command_line_argument(strParse));

      }

      if (argv != nullptr)
      {

         for (typename ITERABLE::iterator i = 0; i < get_count(); i++)
         {

            char * pch = (char *)(const ITYPE &)element_at(i);

            argv->add(pch);

         }

         argv->add(nullptr);

      }

      return get_count();


   }




   template < typename ITERABLE, typename ITYPE, typename ITERABLE2 >
   ITERABLE & add_shortest_tokens(ITERABLE & iterable, const ITYPE & pcsz, const ITERABLE2 & iterableSeparator, bool bAddEmpty, bool bWithSeparator)
   {

      ::tokenizer strTokenizer(pcsz);

      ITYPE strToken;

      if (bAddEmpty)
      {

         while (strTokenizer.next_shortest_token(strToken, iterableSeparator, bWithSeparator))
         {

            iterable.add(strToken);

         }

      }
      else
      {

         while (strTokenizer.next_shortest_token(strToken, iterableSeparator, bWithSeparator))
         {

            if (!strToken.is_empty())
            {

               iterable.add(strToken);

            }

         }

      }

      return iterable;

   }



   template < typename ITERABLE, typename ITYPE >
   ITERABLE & add_lines(ITERABLE & iterable, const ITYPE & strFindParam, bool bAddEmpty)
   {

      typedef typename ITERABLE::BASE_TYPE STRING_TYPE;

      STRING_TYPE str(strFindParam);

      character_count iPos = 0;

      character_count iFindA;

      character_count iFindB;

      character_count iFind1;

      character_count iFind2;

      do
      {

         iFindA = str.find('\n', iPos);

         if (iFindA < 0)
            goto r_only;

         iFindB = str.find('\r', iPos);

         if (iFindB < 0)
            goto n_only;

         iFind1 = minimum(iFindA, iFindB);

         iFind2 = maximum(iFindA, iFindB);

         if (iFind1 > iPos)
         {

            iterable.add((STRING_TYPE)STRING_TYPE(&str[iPos], iFind1 - iPos));

         }
         else if (bAddEmpty)
         {

            iterable.add(STRING_TYPE());

         }

         if (iFind2 - iFind1 == 1)
         {

            iPos = iFind2 + 1;

         }
         else
         {

            iPos = iFind1 + 1;

         }

      }
      while (true);

      goto end;

n_only:

      do
      {

         iFindA = str.find('\n', iPos);

         if (iFindA < 0)
            goto end;

         if (iFindA > iPos)
         {

            iterable.add((STRING_TYPE)STRING_TYPE(&str[iPos], iFindA - iPos));

         }
         else if (bAddEmpty)
         {

            iterable.add(STRING_TYPE());

         }

         iPos = iFindA + 1;


      }
      while (true);
      goto end;
r_only:
      do
      {

         iFindB = str.find('\r', iPos);

         if (iFindB < 0)
            goto end;

         if (iFindB > iPos)
         {

            iterable.add((STRING_TYPE)STRING_TYPE(&str[iPos], iFindB - iPos));

         }
         else if (bAddEmpty)
         {

            iterable.add(STRING_TYPE());

         }

         iPos = iFindB + 1;


      }
      while (true);

end:

      if (str.length() > iPos)
      {

         iterable.add((STRING_TYPE)STRING_TYPE(&str[iPos], str.length() - iPos));

      }
      else if (bAddEmpty)
      {

         iterable.add(STRING_TYPE());

      }

      return iterable;

   }





   template < typename ITERABLE, typename ITYPE >
   void get_format_string(const ITERABLE & iterable, ITYPE & str, const ITYPE & lpcszSeparator)
   {
      str.empty();
      if (iterable.m_nSize > 0)
      {
         str = get_at(0);
      }
      for (int i = 1; i < iterable.m_nSize; i++)
      {
         str += lpcszSeparator + get_at(i);
      }
   }






   /*void XFV001Expand()
   {
   ITERABLE  strArray;
   unsigned_int_array dwa;
   for(int i = 0; i < iterable.m_nSize; i++)
   {
   strArray.add_tokens(get_at(i), "/", false);
   if(strArray.get_size() > 1)
   {
   for(int j = 0; j < strArray.get_size(); j++)
   {
   add_unique(strArray.get_at(j));
   }
   if(strArray.get_size() > 1)
   {
   dwa.add(i);
   }
   }
   strArray.erase_all();
   }
   for(i = dwa.get_size(); --i >= 0 ;)
   {
   erase_at(dwa.get_at(i));
   }
   Sort(Compare);

   }*/


   template < typename ITERABLE, typename ITYPE >
   bool add_unique(ITERABLE & iterable, const ITYPE & str)
   {

      if (::iter::contains(iterable, str))
      {

         return false;

      }

      iterable.add((const ITYPE &)str);

      return true;

   }

   template < typename ITERABLE, typename ITYPE >
   bool case_insensitive_add_unique(ITERABLE & iterable, const ITYPE & str)
   {

      if (::iter::case_insensitive_contains(iterable, str))
      {

         return false;

      }

      iterable.add((const ITYPE &)str);

      return true;

   }



   template < typename ITERABLE, typename ITERABLE2 >
   ::collection::count add_unique_iter(ITERABLE & iterable, const typename ITERABLE2 & stra)
   {

      ::collection::count count = 0;

      for (auto & str : stra)
      {

         if (iterable.add_unique(str))
         {

            count++;

         }

      }

      return count;

   }


   template < typename ITERABLE, typename ITERABLE2 >
   ::collection::count case_insensitive_add_unique_iter(ITERABLE & iterable, const typename ITERABLE2 & iterable2)
   {

      ::collection::count count = 0;

      for (auto & str : iterable2)
      {

         if (iterable.case_insensitive_add_unique(str) != iterable.end())
         {

            count++;

         }

      }

      return count;

   }

   template < typename ITERABLE, typename PRED>
   bool predicate_erase_first(ITERABLE & iterable, PRED pred)
   {

      auto it = predicate_find_first(iterable, pred);

      if (it == iterable.end())
      {

         return false;

      }

      iterable.erase(it);

      return true;

   }

   template < typename ITERABLE, typename PRED >
   typename ITERABLE::const_iterator predicate_find_first(const ITERABLE & iterable, PRED pred, typename ITERABLE::const_iterator first, typename ITERABLE::const_iterator last)
   {

      iterable.prepare_first_last(first, last);

      for (; iterable.valid_iter(first, last); first++)
      {

         if (pred(*first))
         {

            break;

         }

      }

      return first;

   }


   template < typename ITERABLE, typename PRED >
   typename ITERABLE::iterator predicate_find_first(ITERABLE & iterable, PRED pred, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {

      iterable.prepare_first_last(first, last);

      for (; iterable.valid_iter(first, last); first++)
      {

         if (pred(*first))
         {

            break;

         }

      }

      return first;

   }


   //template<class ITYPE, class ARG_ITYPE>
   //void list<ITYPE, ARG_ITYPE>::erase(iterator & it)
   //{
   //
   //   this->erase_at(it);

   //}


   template < typename ITERABLE, typename ITYPE >
   typename index case_insensitive_ifind_first(const ITERABLE & iterable, const ITYPE & pcsz, index first, ::collection::count count)
   {

      iterable.iprepare_first_count(first, count);

      for (; first < count; first++)
      {

         if (case_insensitive_ansi_compare(iterable.element_at(first), pcsz) == 0)
         {

            return first;

         }

      }

      return -1;

   }


   template < typename ITERABLE, typename ITYPE >
   typename index ifind_first_begins(const ITERABLE & iterable, const ITYPE & pcsz, index first, ::collection::count count)
   {

      iterable.iprepare_first_count(first, count);

      for (; first < count; find++)
      {

         if (string_begins(iterable.element_at(first), pcsz))
         {

            return first;

         }

      }

      return -1;

   }

   template < typename ITERABLE, typename ITYPE >
   typename index case_insensitive_ifind_first_begins(const ITERABLE & iterable, const ITYPE & pcsz, index first, ::collection::count count)
   {

      iterable.iprepare_first_count(first, count);

      for (; first < count; find++)
      {

         if (case_insensitive_string_begins(iterable.element_at(first), pcsz))
         {

            return first;

         }

      }

      return -1;

   }



   //template < typename ITERABLE, typename ITYPE >
   //index case_insensitive_ifind_first(const ITERABLE & iterable, const ITYPE & pcsz, ::collection::index find, ::collection::count count)
   //{
   //   if (find < 0)
   //      find += iterable.get_count();
   //   if (last < 0)
   //      last += iterable.get_count();
   //   for (; find <= last; find++)
   //   {
   //      if (iterable.element_at(find).CompareNoCase(pcsz) == 0)
   //         return find;
   //   }
   //   return -1;
   //}


   //template < typename ITERABLE, typename ITYPE >
   //typename ITERABLE::const_iterator find_first(const ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::const_iterator find, typename ITERABLE::const_iterator last)
   //{
   //   return ::iter::find_first(iterable, pcsz, find, last);
   //}

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator case_insensitive_find_last(const ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::const_iterator first, typename ITERABLE::const_iterator last)
   {

      return case_insensitive_reverse_find(pcsz, first, last);

   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator find_last(const ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::const_iterator first, typename ITERABLE::const_iterator last)
   {

      return rear_find(pcsz, first, last);

   }



   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator case_insensitive_reverse_find(const ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::const_iterator first, typename ITERABLE::const_iterator last)
   {

      iterable.rprepare_first_last(first, last);

      for (; iterable.rvalid_iter(first, last); first--)
      {

         if (case_insensitive_ansi_compare(*first, pcsz) == 0)
         {

            return find;

         }

      }

      return iterable.end();

   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator rear_find(const ITERABLE & iterable, const ITYPE & value, typename ITERABLE::const_iterator first, typename ITERABLE::const_iterator last)
   {

      iterable.rprepare_first_last(first, last);

      for (; iterable.rvalid_iter(first, last); first--)
      {

         if (*first == value)
         {

            return first;

         }

      }

      return iterable.end();
   }




   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator find_first_ends(const ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::const_iterator first, typename ITERABLE::const_iterator last)
   {

      iterable.prepare_first_last(first, last);

      for (; iterable.valid_iter(first, last); first++)
      {

         if (string_ends(*first, pcsz))
         {

            return first;

         }

      }

      return iterable.end();

   }

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator case_insensitive_find_first_ends(const ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::const_iterator find, typename ITERABLE::const_iterator last)
   {

      iterable.prepare_first_last(first, last);

      for (; iterable.valid_iter(first, last); first++)
      {

         if (case_insensitive_string_ends(*first, pcsz))
         {

            return first;

         }

      }

      return iterable.end();

   }



   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator find_first_ends_eat(ITERABLE & iterable, string & str, const ITYPE & pcsz, typename ITERABLE::const_iterator first, typename ITERABLE::const_iterator last)
   {

      first = find_first_ends(pcsz, first, last);

      if (first == iterable.end())
         return first;

      str = first->Left(first->length() - ansi_length(pcsz));

      return find;

   }



   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator case_insensitive_find_first_ends_eat(ITERABLE & iterable, string & str, const ITYPE & pcsz, typename ITERABLE::const_iterator find, typename ITERABLE::const_iterator last)
   {

      find = case_insensitive_find_first_ends(pcsz, find, last);

      if (find < 0)
         return find;

      str = element_at(find).left(element_at(find).length() - strlen(pcsz));

      return find;

   }



   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator find_first_begins(const ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::const_iterator find, typename ITERABLE::const_iterator last)
   {
      if (find < 0)
         find += iterable.get_count();
      if (last < 0)
         last += iterable.get_count();
      for (; find < iterable.get_count(); find++)
      {
         if (string_begins(iterable.element_at(find), pcsz))
            return find;
      }
      return -1;
   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator case_insensitive_find_first_begins(const ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::const_iterator first, typename ITERABLE::const_iterator last)
   {

      iterable.prepare_first_last(first, last);

      for(; iterable.valid_iter(first, last); first++)
      {

         if (case_insensitive_string_begins(*first, pcsz))
            return first;

      }

      return iterable.end();

   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator find_first_begins_eat(ITERABLE & iterable, string & str, const ITYPE & pcsz, typename ITERABLE::const_iterator find, typename ITERABLE::const_iterator last)
   {

      find = find_first_begins(pcsz, find, last);

      if (find < 0)
         return find;

      str = element_at(find).substr(strlen(pcsz));

      return find;

   }



   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator case_insensitive_find_first_begins_eat(ITERABLE & iterable, string & str, const ITYPE & pcsz, typename ITERABLE::const_iterator find, typename ITERABLE::const_iterator last)
   {

      find = case_insensitive_find_first_begins(pcsz, find, last);

      if (find < 0)
         return find;

      str = element_at(find).substr(strlen(pcsz));

      return find;

   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator any_suffixes(const ITERABLE & iterable, const ITYPE & lpcszIdSuffixed, typename ITERABLE::const_iterator find, typename ITERABLE::const_iterator last)
   {

      if (find < 0)
         find += iterable.get_count();
      if (last < 0)
         last += iterable.get_count();
      for (; find < iterable.get_count(); find++)
      {
         if (string_ends(lpcszIdSuffixed, iterable.element_at(find)))
            return find;
      }
      return -1;
   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator any_case_insensitive_suffixes(const ITERABLE & iterable, const ITYPE & lpcszIdSuffixed, typename ITERABLE::const_iterator find, typename ITERABLE::const_iterator last)
   {

      iterable.prepare_first_last(first, last);

      for (; iterable.valid_iter(find, last); find++)
      {

         if (case_insensitive_string_ends(lpcszIdSuffixed, *find))
         {

            return find;

         }

      }

      return find;

   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator any_prefixes(const ITERABLE & iterable, const ITYPE & lpcszIdPrefixed, typename ITERABLE::const_iterator find, typename ITERABLE::const_iterator last)
   {

      if (find < 0)
         find += iterable.get_count();
      if (last < 0)
         last += iterable.get_count();
      for (; find < iterable.get_count(); find++)
      {
         if (string_begins(lpcszIdPrefixed, iterable.element_at(find)))
            return find;
      }
      return -1;
   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::const_iterator case_insensitive_any_prefixes(const ITERABLE & iterable, const ITYPE & lpcszIdPrefixed, typename ITERABLE::const_iterator find, typename ITERABLE::const_iterator last)
   {

      if (find < 0)
         find += iterable.get_count();
      if (last < 0)
         last += iterable.get_count();
      for (; find < iterable.get_count(); find++)
      {
         if (case_insensitive_string_begins(lpcszIdPrefixed, iterable.element_at(find)))
            return find;
      }
      return -1;
   }


   template < typename ITERABLE, typename ITYPE >
   typename index find_first_begins(ITERABLE & iterable, const ITYPE & pcsz, ::collection::index find, ::collection::count count)
   {

      iterable.iprepare_first_count(find, count);

      for (; find < count; find++)
      {

         if (string_begins(iterable.element_at(find), pcsz))
         {

            return find;

         }

      }

      return -1;

   }

   template < typename ITERABLE, typename ITYPE >
   typename index case_insensitive_find_first_begins(ITERABLE & iterable, const ITYPE & pcsz, ::collection::index find, ::collection::count count)
   {

      iterable.iprepare_first_count(find, count);

      for (; find < count; find++)
      {

         if (case_insensitive_string_begins(iterable.element_at(find), pcsz))
         {

            return find;

         }

      }

      return -1;

   }



   template < typename ITERABLE, typename ITYPE >
   ::collection::index case_insensitive_find_first(ITERABLE & iterable, const ITYPE & pcsz, ::collection::index find, ::collection::count count)
   {
      if (find < 0)
         find += iterable.get_count();
      if (last < 0)
         last += iterable.get_count();
      for (; find <= last; find++)
      {
         if (iterable.element_at(find).CompareNoCase(pcsz) == 0)
            return find;
      }
      return -1;
   }


   //template < typename ITERABLE, typename ITYPE >
   //typename ITERABLE::iterator find_first(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   //{
   //   return ::iter::find_first(iterable, pcsz, find, last);
   //}

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator case_insensitive_find_last(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {
      return case_insensitive_reverse_find(pcsz, find, last);
   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator find_last(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {
      return rear_find(pcsz, find, last);
   }



   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator case_insensitive_reverse_find(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {
      if (find < 0)
         find += iterable.get_count();
      if (last < 0)
         last += iterable.get_count();
      for (; find >= last; find--)
      {
         if (iterable.element_at(find).CompareNoCase(pcsz) == 0)
            return find;
      }
      return -1;
   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator rear_find(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {
      if (find < 0)
         find += iterable.get_count();
      if (last < 0)
         last += iterable.get_count();
      for (; find >= last; find--)
      {
         if (iterable.element_at(find).Compare(pcsz) == 0)
            return find;
      }
      return -1;
   }




   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator find_first_ends(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {
      if (find < 0)
         find += iterable.get_count();
      if (last < 0)
         last += iterable.get_count();
      for (; find < iterable.get_count(); find++)
      {
         if (string_ends(iterable.element_at(find), pcsz))
            return find;
      }
      return -1;
   }

   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator case_insensitive_find_first_ends(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {
      if (find < 0)
         find += iterable.get_count();
      if (last < 0)
         last += iterable.get_count();
      for (; find < iterable.get_count(); find++)
      {
         if (case_insensitive_string_ends(iterable.element_at(find), pcsz))
            return find;
      }
      return -1;
   }



   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator find_first_ends_eat(ITERABLE & iterable, string & str, const ITYPE & pcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {

      find = find_first_ends(pcsz, find, last);

      if (find < 0)
         return find;

      str = element_at(find).left(element_at(find).length() - strlen(pcsz));

      return find;

   }



   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator case_insensitive_find_first_ends_eat(ITERABLE & iterable, string & str, const ITYPE & pcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {

      find = case_insensitive_find_first_ends(pcsz, find, last);

      if (find < 0)
         return find;

      str = element_at(find).left(element_at(find).length() - strlen(pcsz));

      return find;

   }



   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator find_first_begins(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {
      if (find < 0)
         find += iterable.get_count();
      if (last < 0)
         last += iterable.get_count();
      for (; find < iterable.get_count(); find++)
      {
         if (string_begins(iterable.element_at(find), pcsz))
            return find;
      }
      return -1;
   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator case_insensitive_find_first_begins(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {

      iterable.prepare_first_last(first, last);

      for (; iterable.valid_iter(first, last); first++)
      {

         if (case_insensitive_string_begins(*first, pcsz))
            return first;

      }

      return iterable.end();

   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator find_first_begins_eat(ITERABLE & iterable, string & str, const ITYPE & pcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {

      find = find_first_begins(pcsz, find, last);

      if (find < 0)
         return find;

      str = element_at(find).substr(strlen(pcsz));

      return find;

   }



   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator case_insensitive_find_first_begins_eat(ITERABLE & iterable, string & str, const ITYPE & pcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {

      find = case_insensitive_find_first_begins(pcsz, find, last);

      if (find < 0)
         return find;

      str = element_at(find).substr(strlen(pcsz));

      return find;

   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator any_suffixes(ITERABLE & iterable, const ITYPE & lpcszIsSuffixed, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {

      iterable.prepare_first_last(first, last);

      for (; iterable.valid_iter(first, last); first++)
      {

         if (string_ends(lpcszIsSuffixed, *first))
         {

            return first;

         }

      }

      return iterable.end();

   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator any_case_insensitive_suffixes(ITERABLE & iterable, const ITYPE & lpcszIsSuffixed, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {

      iterable.prepare_first_last(first, last);

      for (; iterable.valid_iter(first, last); first++)
      {

         if (case_insensitive_string_ends(lpcszIsSuffixed, *first))
         {

            return first;

         }

      }

      return iterable.end();

   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator any_prefixes(ITERABLE & iterable, const ITYPE & lpcszIsPrefixed, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {

      iterable.prepare_first_last(first, last);

      for (; iterable.valid_iter(first, last); first++)
      {

         if (string_begins(lpcszIsPrefixed, *first))
         {

            return first;

         }

      }

      return iterable.end();

   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator case_insensitive_any_prefixes(ITERABLE & iterable, const ITYPE & lpcszIsPrefixed, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {

      iterable.prepare_first_last(first, last);

      for (; iterable.valid_iter(first, last); first++)
      {

         if (case_insensitive_string_begins(lpcszIsPrefixed, *first))
         {

            return first;

         }

      }

      return iterable.end();

   }



   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator case_insensitive_erase_first(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {

      if ((first = case_insensitive_find_first(pcsz, first, last)) == iterable.end())
      {

         return false;

      }

      iterable.erase(first);

      return true;

   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator case_insensitive_erase_last(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {

      if ((first = case_insensitive_find_last(pcsz, first, last)) == iterable.end())
      {

         return false;

      }

      iterable.erase(first);

      return true;

   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::iterator erase_last(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator find, typename ITERABLE::iterator last)
   {

      if ((find = find_last(pcsz, find, last)) == iterable.end())
      {

         return false;

      }

      iterable.erase_at(find);

      return true;

   }


   template < typename ITERABLE, typename ITYPE >
   ITERABLE & trim_left(ITERABLE & iterable, const ITYPE & pszChars)
   {

      for (auto & item : iterable)
      {

         item.trim_left(pszChars);

      }

      return iterable;

   }


   template < typename ITERABLE, typename ITYPE >
   ITERABLE & trim_right(ITERABLE & iterable, const ITYPE & pszChars)
   {

      for (auto & item : iterable)
      {

         item.trim_right(pszChars);

      }

      return iterable;

   }


   template < typename ITERABLE, typename ITYPE >
   ITERABLE & trim(ITERABLE & iterable, const ITYPE & pszChars)
   {

      for (auto & item : iterable)
      {

         item.trim(pszChars);

      }

      return iterable;

   }



   template < typename ITERABLE >
   ITERABLE & trim_left(ITERABLE & iterable)
   {

      for (auto & item : iterable)
      {

         item.trim_left();

      }

      return iterable;

   }


   template < typename ITERABLE >
   ITERABLE & trim_right(ITERABLE & iterable)
   {

      for (auto & item : iterable)
      {

         item.trim_right();

      }

      return iterable;

   }


   template < typename ITERABLE >
   ITERABLE & trim(ITERABLE & iterable)
   {

      for (auto & item : iterable)
      {

         item.trim();

      }

      return iterable;

   }


   //template < typename ITERABLE, typename ITYPE >
   //typename ITERABLE::iterator add_normal(const ITYPE & pcsz)
   //{

   //   return ITERABLE::add(pcsz);

   //}


   template < typename ITERABLE >
   ::collection::count erase_empty(ITERABLE & iterable)
   {

      ::collection::count count = 0;

      for (auto it = iterable.begin(); iterable.valid_iter(it, iterable.end());)
      {

         if (it->is_empty())
         {

            iterable.erase(it);

            count++;
         }
         else
         {

            it++;

         }

      }

      return count;

   }


















   template < typename ITERABLE, typename ITYPESEP, typename ITYPE2 >
   ITERABLE  & explode(ITERABLE & iterable, const ITYPESEP & strSeparator, const ITYPE2 & str)
   {

      iterable.erase_all();

      return add_tokens(iterable, str, strSeparator, true);

   }

   template < typename ITERABLE, typename ITYPE, typename ITYPESEP >
   ITERABLE & add_tokens(ITERABLE & iterable, const ITYPE & pcsz, const ITYPESEP & lpcszSeparator, bool bAddEmpty)
   {

      ::tokenizer strTokenizer(pcsz);

      string strToken;

      if (bAddEmpty)
      {

         while (strTokenizer.next_token(strToken, lpcszSeparator, false))
         {

            iterable.add(strToken);

         }

      }
      else
      {

         while (strTokenizer.next_token(strToken, lpcszSeparator, false))
         {

            if (!strToken.is_empty())
            {

               iterable.add(strToken);

            }

         }

      }

      return iterable;

   }



   template < typename ITERABLE, typename ITYPE >
   ITERABLE  & csstidy_explode_ws(ITERABLE & iterable, char sep, const ITYPE & psz)
   {

      ITYPE istring(psz);

      // 1 = st // 2 = str
      int status = 1;
      char to = '\0';

      add("");
      character_count num = 0;
      character_count len = istring.length();
      for (character_count i = 0; i < len; i++)
      {

         switch (status)
         {
         case 1:
            if (istring[i] == sep && !::str::simple_escaped(istring, i))
            {
               ++num;
               add("");
            }
            else if ((istring[i] == '"' || istring[i] == '\'' || istring[i] == '(') && !::str::simple_escaped(istring, i))
            {
               status = 2;
               to = (istring[i] == '(') ? ')' : istring[i];
               element_at(num) += (ITYPE)ITYPE(istring[i]);
            }
            else
            {
               element_at(num) += (ITYPE)ITYPE(istring[i]);
            }
            break;

         case 2:
            if (istring[i] == to && !::str::simple_escaped(istring, i))
            {
               status = 1;
            }
            element_at(num) += (ITYPE)ITYPE(istring[i]);
            break;
         }

      }

      return iterable;

   }




   template < typename ITERABLE, typename ITYPE >
   void replace(ITERABLE & iterable, const ITYPE & lpszSearch, const ITYPE & lpszReplace)
   {

      for (int i = 0; i < iterable.get_size(); i++)
      {

         iterable.element_at(i).replace(lpszSearch, lpszReplace);

      }

   }

   template < typename ITERABLE, typename ITERABLE2, typename ITYPE >
   void prefix(ITERABLE & iterable, const ITERABLE2 & iterable2, const ITYPE & pszPrefix, typename ITERABLE2::const_iterator first, typename ITERABLE2::const_iterator last)
   {

      typedef ITERABLE::BASE_TYPE STRING_TYPE;

      STRING_TYPE strPrefix(pszPrefix);

      iterable2.prepare_first_last(first, last);

      for (; iterable2.valid_iter(first, last); first++)
      {

         iterable.add(strPrefix + *first);

      }

   }

   template < typename ITERABLE, typename ITERABLE2, typename ITYPE >
   void suffix(ITERABLE & iterable, const ITERABLE2 & iterable2, const ITYPE & pszSuffix, typename ITERABLE2::const_iterator first, typename ITERABLE2::const_iterator last)
   {

      typedef ITERABLE::BASE_TYPE STRING_TYPE;

      STRING_TYPE strSuffix(pszSuffix);

      iterable2.prepare_first_last(first, last);

      for (; iterable2.valid_iter(first, last); first++)
      {

         iterable.add(*first + strSuffix);

      }

   }

   template < typename ITERABLE, typename ITERABLE2, typename ITYPE, typename ITYPE2 >
   void surround(ITERABLE & iterable, const ITERABLE2 & iterable2, const ITYPE & pszPrefix, const ITYPE2 & pszSuffix, typename ITERABLE2::const_iterator first, typename ITERABLE2::const_iterator last)
   {

      typedef ITERABLE::BASE_TYPE STRING_TYPE;

      STRING_TYPE strPrefix(pszPrefix);

      STRING_TYPE strSuffix(pszSuffix);

      iterable2.prepare_first_last(first, last);

      for (; iterable2.valid_iter(first, last); first++)
      {

         iterable.add(strPrefix + *first + strSuffix);

      }

   }


   template < typename ITERABLE, typename ITYPE >
   void prefix(ITERABLE & iterable, const ITYPE & pszPrefix, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {

      typedef ITERABLE::BASE_TYPE STRING_TYPE;

      STRING_TYPE strPrefix(pszPrefix);

      iterable.prepare_first_last(first, last);

      for (; iterable.valid_iter(first, last); first++)
      {

         *first = strPrefix + *first;

      }

   }

   template < typename ITERABLE, typename ITYPE >
   void suffix(ITERABLE & iterable, const ITYPE & pszSuffix, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {

      typedef ITERABLE::BASE_TYPE STRING_TYPE;

      STRING_TYPE strSuffix(pszSuffix);

      iterable.prepare_first_last(first, last);

      for (; iterable.valid_iter(first, last); first++)
      {

         *first = *first + strSuffix;

      }

   }


   template < typename ITERABLE, typename ITYPE, typename ITYPE2 >
   void surround(ITERABLE & iterable, const ITYPE & pszPrefix, const ITYPE2 & pszSuffix, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {

      typedef ITERABLE::BASE_TYPE STRING_TYPE;

      STRING_TYPE strPrefix(pszPrefix);

      STRING_TYPE strSuffix(pszSuffix);

      iterable.prepare_first_last(first, last);

      for (; iterable.valid_iter(first, last); first++)
      {

         *first = strPrefix + *first + strSuffix;

      }

   }


   template < typename ITERABLE, typename ITYPE, typename ITYPE2, typename ITYPE3, typename ITYPE4 >
   void surround_and_implode(const ITERABLE & iterable, ITYPE & str, const ITYPE2 & lpcszSeparator, const ITYPE3 & pszPrefix, const ITYPE4 & pszSuffix, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {

      str.empty();

      typedef ITERABLE::BASE_TYPE STRING_TYPE;

      STRING_TYPE strPrefix(pszPrefix);

      STRING_TYPE strSuffix(pszSuffix);

      iterable.prepare_first_last(first, last);

      if (iterable.valid_iter(first, last))
      {

         str = strPrefix + *first + strSuffix;

         first++;

      }

      for (; iterable.valid_iter(first, last); first++)
      {

         str += lpcszSeparator;

         str += strPrefix + *first + strSuffix;

      }

   }






   template < typename ITERABLE, typename ITYPE >
   void prefix(const ITERABLE & stra, const ITYPE & pszPrefix, typename ITERABLE::iterator iStart, ::collection::count iCount)
   {

      ITYPE strPrefix(pszPrefix);

      character_count iEnd;

      if (iStart < 0)
         iStart = stra.get_size() + iStart;

      if (iCount < 0)
         iEnd = stra.get_size() + iCount;
      else
         iEnd = iStart + iCount - 1;

      for (auto & str : stra)
      {

         add(strPrefix + str);

      }

   }


   template < typename ITERABLE, typename ITYPE >
   void suffix(const ITERABLE & stra, const ITYPE & pszSuffix, typename ITERABLE::iterator iStart, ::collection::count iCount)
   {

      ITYPE strSuffix(pszSuffix);

      character_count iEnd;

      if (iStart < 0)
         iStart = stra.get_size() + iStart;

      if (iCount < 0)
         iEnd = stra.get_size() + iCount;
      else
         iEnd = iStart + iCount - 1;

      for (typename ITERABLE::iterator i = iStart; i <= iEnd; i++)
      {

         add(stra.element_at(i) + strSuffix);

      }

   }


   template < typename ITERABLE, typename ITYPE >
   void surround(const ITERABLE & stra, const ITYPE & pszPrefix, const ITYPE & pszSuffix, typename ITERABLE::iterator iStart, ::collection::count iCount)
   {

      ITYPE strPrefix(pszPrefix);

      ITYPE strSuffix(pszSuffix);

      character_count iEnd;

      if (iStart < 0)
         iStart = stra.get_size() + iStart;

      if (iCount < 0)
         iEnd = stra.get_size() + iCount;
      else
         iEnd = iStart + iCount - 1;

      for (typename ITERABLE::iterator i = iStart; i <= iEnd; i++)
      {

         add(strPrefix + stra.element_at(i) + strSuffix);

      }

   }


   template < typename ITERABLE, typename ITYPE >
   void surround(ITERABLE & iterable, const ITYPE & pszPrefix, const ITYPE & pszSuffix, typename ITERABLE::iterator iStart, ::collection::count iCount)
   {

      ITYPE strPrefix(pszPrefix);

      ITYPE strSuffix(pszSuffix);

      character_count iEnd;

      if (iStart < 0)
         iStart = iterable.get_size() + iStart;

      if (iCount < 0)
         iEnd = iterable.get_size() + iCount;
      else
         iEnd = iStart + iCount - 1;

      for (typename ITERABLE::iterator i = iStart; i <= iEnd; i++)
      {

         iterable.element_at(i) = strPrefix + iterable.element_at(i);

      }

   }


   template < typename ITERABLE, typename ITYPE >
   void suffix(ITERABLE & iterable, const ITYPE & pszSuffix, typename ITERABLE::iterator iStart, ::collection::count iCount)
   {

      ITYPE strSuffix(pszSuffix);

      character_count iEnd;

      if (iStart < 0)
         iStart = iterable.get_size() + iStart;

      if (iCount < 0)
         iEnd = iterable.get_size() + iCount;
      else
         iEnd = iStart + iCount - 1;

      for (typename ITERABLE::iterator i = iStart; i <= iEnd; i++)
      {

         iterable.element_at(i) = iterable.element_at(i) + strSuffix;

      }

   }





   template < typename ITERABLE, typename ITYPE, typename ITYPE2, typename ITYPE3 >
   void surround_and_implode(const ITERABLE & iterable, ITYPE & str, const ITYPE2 & pszSeparator, const ITYPE3 & pszPrefix, const ITYPE & pszSuffix, typename ITERABLE::iterator iStart, ::collection::count iCount)
   {
      ITYPE str;
      ITYPE strSeparator(pszSeparator);
      ITYPE strPrefix(pszPrefix);
      ITYPE strSuffix(pszSuffix);

      typename ITERABLE::iterator iEnd;

      if (iStart < 0)
         iStart = iterable.get_size() + iStart;

      if (iCount < 0)
         iEnd = iterable.get_size() + iCount;
      else
         iEnd = iStart + iCount - 1;

      if (iStart <= iEnd)
      {

         str = strPrefix + iterable.element_at(iStart) + strSuffix;

         iStart++;

         for (typename ITERABLE::iterator i = iStart; i <= iEnd; i++)
         {

            str += strSeparator + strPrefix + iterable.element_at(i) + strSuffix;

         }

      }

      return str;

   }

   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE & add_iter(ITERABLE & iterable, const ITERABLE2 & iterable2)
   {

      for (auto & item : iterable2)
      {

         iterable.add(item);

      }

      return iterable;

   }


   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE diff(const ITERABLE & iterable, const ITERABLE2 & iterable2)
   {

      ITERABLE contanerSubtracted(iterable);

      contanerSubtracted.erase_iter(iterable2);

      return contanerSubtracted;

   }


   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE sum(const ITERABLE & iterable, const ITERABLE2 & iterable2)
   {

      ITERABLE contanerAdded(iterable);

      contanerAdded += iterable2;

      return contanerAdded;

   }


   template < typename ITERABLE, typename ITYPE >
   bool case_insensitive_move(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator iIndex)
   {
      typename ITERABLE::iterator i = case_insensitive_find_first(pcsz);
      if (i < 0)
         return false;
      iterable.erase_at(i);
      insert_at(iIndex, pcsz);
      return true;
   }


   template < typename ITERABLE, typename ITYPE >
   bool preferred(ITERABLE & iterable, const ITYPE & pcsz)
   {

      return case_insensitive_move(pcsz, 0);

   }


   template < typename ITERABLE, typename ITERABLE2 >
   ::collection::count preferred_iter(ITERABLE & iterable, const ITERABLE2 & iterable2)
   {

      ::collection::count count = 0;

      for (auto i = upper_bound(); i >= begin(); i--)
      {

         if (preferred(*i))
            count++;

      }

      return count;

   }




   //template < typename ITERABLE, typename ITYPE >
   //template < typename ITERABLE >
   //void slice(ITERABLE & stra, const_iterator iOffset, ::collection::count count)
   //{
   //
   //   typename ITERABLE::iterator iEnd;
   //
   //   if (count < 0)
   //      iEnd = get_upper_bound(count);
   //   else
   //      iEnd = iOffset + count - 1;
   //
   //   for (typename ITERABLE::iterator i = iOffset; i <= iEnd; i++)
   //   {
   //      stra.add(iterable.element_at(i));
   //   }
   //
   //}
   //

   template < typename ITERABLE, typename ITYPE >
   void erase(ITERABLE & iterable, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {

      while(iterable.valid_iter(first, last))
      {

         iterable.erase_at(first);

      }

   }





   //template < typename ITERABLE, typename ITYPE >
   //bool is_empty(::collection::count countMinimum)
   //{
   //   return iterable.get_size() < countMinimum;
   //}


   //template < typename ITERABLE, typename ITYPE >
   //bool has_elements(::collection::count countMinimum)
   //{
   //   return iterable.get_count() >= countMinimum;
   //}



   template < typename ITERABLE, typename STRITERABLE, typename ITYPE >
   ::collection::count case_insensitive_get_begins(const ITERABLE & iterable, STRITERABLE & stra, const ITYPE & pcsz, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {
      if (last < 0)
         last = iterable.get_size() + last;
      if (last >= iterable.get_size())
         last = get_upper_bound();
      if (first < 0)
         first = 0;
      typename ITERABLE::iterator i = first;
      typename ITERABLE::iterator iFind;
      ::collection::count count = 0;
      while (true)
      {
         iFind = case_insensitive_find_first_begins(pcsz, i, last);
         if (::is_null(pFind))
            return count;
         stra.add(iterable.element_at(iFind));
         i = iFind + 1;
         count++;
      }
   }


   template < typename ITERABLE, typename ITYPE >
   ::collection::count case_insensitive_filter_begins(ITERABLE & iterable, const ITYPE & pcsz, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {

      iterable.prepare_first_last(first, last);

      typename ITERABLE::iterator it = first;

      typename ITERABLE::iterator itFind;

      ::collection::count count = 0;

      while (true)
      {

         itFind = case_insensitive_find_first_begins(iterable, pcsz, it, last);

         if (itFind < 0)
         {

            iterable.erase(it, last);

            return count;

         }

         iterable.erase_count(it, itFind - it);

         count++;

         it++;

      }

   }

   template < typename ITERABLE, typename ITYPE, typename PRED >
   ::collection::count filter(ITERABLE & iterable, PRED pred, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {
      if (last < 0)
         last = iterable.get_size() + last;
      if (last >= iterable.get_size())
         last = get_upper_bound();
      if (first < 0)
         first = 0;
      //   typename ITERABLE::iterator i = first;
      ::collection::count count = 0;
      for (typename ITERABLE::iterator i = first; i <= last;)
      {
         if (pred(element_at(i)))
         {
            i++;
         }
         else
         {
            iterable.erase_at(i);
            count++;
            last--;
         }

      }
      return count;
   }


   template < typename ITERABLE, typename ITYPE, typename PRED >
   ::collection::count filter_out(ITERABLE & iterable, PRED pred, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {
      if (last < 0)
         last = iterable.get_size() + last;
      if (last >= iterable.get_size())
         last = get_upper_bound();
      if (first < 0)
         first = 0;
      //   typename ITERABLE::iterator i = first;
      ::collection::count count = 0;
      for (typename ITERABLE::iterator i = first; i <= last;)
      {
         if (!pred(element_at(i)))
         {
            i++;
         }
         else
         {
            iterable.erase_at(i);
            count++;
            last--;
         }

      }
      return count;
   }

   template < typename ITERABLE, typename ITYPE, typename PRED, typename ArrayOut >
   ::collection::count filter_out(ITERABLE & iterable, PRED pred, ArrayOut & a, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {
      if (last < 0)
         last = iterable.get_size() + last;
      if (last >= iterable.get_size())
         last = get_upper_bound();
      if (first < 0)
         first = 0;
      //   typename ITERABLE::iterator i = first;
      ::collection::count count = 0;
      for (typename ITERABLE::iterator i = first; i <= last;)
      {
         if (!pred(element_at(i)))
         {
            i++;
         }
         else
         {
            a.add(iterable.element_at(i));
            iterable.erase_at(i);
            count++;
            last--;
         }

      }
      return count;
   }






   template < typename ITERABLE >
   void make_lower(ITERABLE & iterable)
   {
      for (typename ITERABLE::iterator i = 0; i < iterable.get_count(); i++)
      {
         iterable.element_at(i).make_lower();
      }
   }


   template < typename ITERABLE >
   void make_upper(ITERABLE & iterable)
   {
      for (typename ITERABLE::iterator i = 0; i < iterable.get_count(); i++)
      {
         iterable.element_at(i).make_upper();
      }
   }



   //template < typename ITERABLE, typename ITERABLE2 >
   //void get_comparable_ida(const ITERABLE & iterable, ITERABLE2 & iterable2)
   //{

   //   array < atom > ida;

   //   for (int i = 0; i < get_count(); i++)
   //   {
   //      iterable2.add(element_at(i));
   //   }

   //   return ida;

   //}




   template < typename ITERABLE, typename ITYPE >
   ITYPE encode_v16(const ITERABLE & iterable)
   {
      ITYPE strEncode;
      for (int u = 0; u < iterable.get_count(); u++)
      {
         ITYPE & str = iterable.element_at(u);
         strEncode += hex::lower_from((const char*)str);
         strEncode += "00";
         /*      for(int uj = 0; uj < str.length(); uj++)
         {
         char sz[32];
         ansi_from_huge_integer(sz, str[uj], 16);
         if(ansi_length(sz) == 0)
         {
         strEncode += "00";
         }
         else if(ansi_length(sz) == 1)
         {
         strEncode += "0";
         strEncode += sz;
         }
         else if(ansi_length(sz) == 2)
         {
         strEncode += sz;
         }
         }*/

      }
      return strEncode;
   }




   template < typename ITERABLE, typename ITYPE >
   void decode_v16(const ITERABLE & iterable, const ITYPE & psz)
   {
      int iSize = 1024;
      char * str = nullptr;
      if (psz == nullptr)
         return;
      while (*psz != '\0')
      {
         psz++;
         if (*psz == '\0')
            break;
         char sz[3];
         sz[0] = psz[-1];
         sz[1] = psz[0];
         sz[2] = '\0';
         const ITYPE & pszEnd;
         int iConversion = ::ansi_to_int(sz, &pszEnd, 16);
         char ch = static_cast <char> (iConversion);
         if (ch == '\0')
         {
            add(str);
            str = nullptr;
            iSize = 1024;
         }
         else
         {
            if (str == nullptr)
            {
               str = (char *)::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(iSize);
            }
            else if (iSize < (ansi_length(str) + 1))
            {
               char * strOld = str;
               iSize += 1024;
               char * strNew = (char *)::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(iSize);
               ansi_copy(strNew, strOld);
               str = strNew;
            }
            sz[0] = ch;
            sz[1] = '\0';
            ansi_copy(str, sz);
         }
         psz++;
      }

   }



   template < typename ITERABLE, typename ITYPE >
   ::collection::count get_count_except(const ITERABLE & iterable, const ITYPE & str)
   {

      ::collection::count c = get_count();

      for (typename ITERABLE::iterator i = 0; i < get_count(); i++)
      {

         if (element_at(i) == str)
            c--;

      }

      return c;

   }


   template < typename ITERABLE, typename ITERABLE2 >
   ::collection::count get_count_except_iter(const ITERABLE & iterable, const ITERABLE2 & iterable2)
   {

      ::collection::count c = get_count();

      for (auto & item : iterable)
      {

         if (stra.contains(item))
            c--;

      }

      return c;

   }



   template < typename ITERABLE, typename ITYPE >
   ::collection::count case_insensitive_get_count_except(const ITERABLE & iterable, const ITYPE & str)
   {

      ::collection::count c = get_count();

      for (typename ITERABLE::iterator i = 0; i < get_count(); i++)
      {

         if (element_at(i).CompareNoCase(str) == 0)
            c--;

      }

      return c;

   }


   template < typename ITERABLE, typename ITERABLE2 >
   ::collection::count case_insensitive_get_count_except_iter(const ITERABLE & iterable, const ITERABLE2 & iterable2)
   {

      ::collection::count c = get_count();

      for (auto & item : iterable)
      {

         if (stra.case_insensitive_contains(item))
            c--;

      }

      return c;

   }



   template < typename ITERABLE, typename ITYPE >
   ITYPE & get_network_payload(const ITERABLE & iterable, ITYPE & str, bool bNewLine)
   {

      str += "[";

      auto it = iterable.begin();

      if (iterable.get_count() > 0)
      {

         str += "\"";

         str += *it;

         str += "\"";

         it++;

      }

      for (; iterable.valid_iter(it, iterable.end()); it++)
      {

         if (bNewLine)
         {

            str += ", \r\n";

         }
         else
         {

            str += ", ";

         }

         str += "\"";

         str += *it;

         str += "\"";

      }

      if (bNewLine)
      {

         str += "\r\n";

      }

      str += "]";

      return str;

   }





   template < typename ITERABLE, typename ITYPE, typename ITYPE2, typename ITYPE3 >
   void implode_ex(const ITERABLE & iterable, ITYPE & str, const ITYPE2 & lpcszSeparator, const ITYPE3 & lpcszLastSeparator, typename ITERABLE::const_iterator start, typename ITERABLE::const_iterator end)
   {

      str.empty();

      ITYPE strSeparator(lpcszSeparator);

      if (start == nullptr)
      {

         start = iterable.upper_bound();

      }

      typename ITERABLE::iterator last;

      if (end == nullptr)
      {

         start = iterable.upper_bound();

      }

      auto i = start;

      if (i != last)
      {

         str = *i;

         i++;

         if (i != iterable.end())
         {

            for (; i != last; i++)
            {

               str += strSeparator;

               str += *i;

            }

            str += lpcszLastSeparator;

            str += *i;

         }

      }

   }




   template < typename ITERABLE, typename ITYPE >
   void if_prefix_implode_ex(const ITERABLE & iterable, ITYPE & str, const ITYPE & lpcszIfHasElementPrefix, const ITYPE & lpcszSeparator, const ITYPE & lpcszLastSeparator, bool bUseLast, typename ITERABLE::iterator start, ::collection::count count)
   {

      str.empty();

      ITYPE strSeparator(lpcszSeparator);

      if (start < 0)
      {
         start += iterable.get_size();
      }
      typename ITERABLE::iterator last;
      if (count < 0)
      {
         last = iterable.get_size() + count;
      }
      else
      {
         last = start + count - 1;
      }
      if (last >= start)
      {
         str += lpcszIfHasElementPrefix;
      }
      for (typename ITERABLE::iterator i = start; i <= last; i++)
      {
         if (i > start)
         {
            if (i == last && bUseLast)
            {
               str += lpcszLastSeparator;
            }
            else
            {
               str += strSeparator;
            }
         }
         str += iterable.element_at(i);
      }
   }


   template < typename ITERABLE, typename ITYPE >
   typename ITERABLE::ITYPE if_prefix_implode_ex(const ITERABLE & iterable, const ITYPE & lpcszIfHasElementPrefix, const ITYPE & lpcszSeparator, const ITYPE & lpcszLastSeparator, bool bUseLast, typename ITERABLE::iterator iStart, typename ITERABLE::iterator iEnd)
   {
      ITYPE str;
      if_prefix_implode_ex(str, lpcszIfHasElementPrefix, lpcszSeparator, lpcszLastSeparator, bUseLast, iStart, iEnd);
      return str;
   }


   /// expect strings allocated with malloc (sic, not ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate) or strdup and array allocated with malloc (sic, not ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate)
   template < typename ITERABLE >
   void c_add(ITERABLE & iterable, char ** ppsz, ::collection::count c)
   {

      for (typename ITERABLE::iterator i = 0; i < c; i++)
      {

         iterable.add(ppsz[i]);

         free((void *)ppsz[i]);

      }

      free((void *)ppsz);

   }

   /// expect strings allocated with malloc (sic, not ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate) or strdup and array allocated with malloc (sic, not ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate)
   template < typename ITERABLE >
   void c_add(ITERABLE & iterable, char ** ppszParam)
   {

      char ** ppsz = ppszParam;

      while (ppsz != nullptr)
      {

         char * psz = *ppsz;

         iterable.add(psz);

         free((void *)psz);

         ppsz++;

      }

      free((void *)ppsz);

   }

   /// expect strings allocated with malloc (sic, not ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate) or wcsdup and array allocated with malloc (sic, not ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate)
   template < typename ITERABLE >
   void c_add(ITERABLE & iterable, wchar_t ** ppsz, ::collection::count c)
   {

      for (typename ITERABLE::iterator i = 0; i < c; i++)
      {

         iterable.add(ppsz[i]);

         free((void *)ppsz[i]);

      }

      free((void *)ppsz);

   }

   /// expect strings allocated with malloc (sic, not ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate) or wcsdup and array allocated with malloc (sic, not ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate)
   template < typename ITERABLE >
   void c_add(ITERABLE & iterable, wchar_t ** ppszParam)
   {

      wchar_t ** ppsz = ppszParam;

      while (ppsz != nullptr)
      {

         wchar_t * psz = *ppsz;

         iterable.add(psz);

         free((void *)psz);

         ppsz++;

      }

      free((void *)ppsz);

   }


   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE & copy_iter(ITERABLE & iterable, const ITERABLE2 & iterable2)
   {

      for (auto & item : iterable2)
      {

         iterable.add(item);

      }

      return iterable;

   }



   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE & copy_from(ITERABLE & iterable, const ITERABLE2 & iterable2)
   {

      return copy_iter(iterable, iterable2.begin(), iterable2.end());

   }


   template < typename ITERABLE, typename ITERATOR >
   ITERABLE & copy_from(ITERABLE & iterable, ITERATOR & iterator, ITERATOR & limit)
   {

      ASSERT_VALID(this);

      iterable.provision(iterator, limit);

      for (; iterator != limit; iterator++)
      {

         iterable.add(as_string(*iterator));

      }

      return *iterable;

   }


   template < typename ITERABLE >
   ITERABLE  & copy(ITERABLE & iterable, ::payload varSrc)
   {

      iterable.erase_all();

      if (varSrc.get_type() == ::e_type_string_array)
      {

         varSrc.get_array(iterable);

      }
      else
      {
         if (varSrc.get_count() == 1)
         {

            add((ITYPE)varSrc.get_string());

         }
         else if (varSrc.get_count() > 1)
         {

            varSrc.get_array(iterable);

         }

      }

      return iterable;

   }


   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE2 & slice(ITERABLE & iterable, ITERABLE2 & iterable2, typename ITERABLE::iterator first, typename ITERABLE::iterator last)
   {

      iterable.prepare_first_last(first, last);

      for (; iterable.valid_iter(first, last); first++)
      {

         iterable2.add(*first);

      }

      iterable.erase(first, last);

      return iterable2;

   }


   template < typename ITERABLE, typename ITERABLE2 >
   ITERABLE2 & islice(ITERABLE & iterable, ITERABLE2 & iterable2, index first, ::collection::count count)
   {

      iterable.iprepare_first_count(first, count);

      for (; first < count; first++)
      {

         iterable2.add(iterable.element_at(first));

      }

      iterable.erase_at(first, count-first);

      return iterable2;

   }

   template < typename ITERABLE, typename ITYPE >
   ITERABLE & add_data(ITERABLE & iterable, const ITYPE * pdata, ::collection::count count)
   {

      for (::collection::index i = 0; i < count; i++)
      {

         iterable.add(pdata[i]);

      }

      return iterable;

   }


   template < typename ITERABLE, typename ITYPE >
   ITERABLE & add_item(ITERABLE & iterable, const ITYPE & t, ::collection::count n)
   {

      while (n > 0)
      {

         iterable.add(t);

         n--;

      }

      return iterable;

   }


} // namespace iter



template < typename ITERABLE >
class iterable :
   public ITERABLE
{
public:

   typedef typename ITERABLE::iterator          iterator;
   typedef typename ITERABLE::const_iterator    const_iterator;
   typedef typename ITERABLE                    Iterable;
   typedef typename Iterable::BASE_TYPE         Type;
   typedef iterable                             Container;


   template < typename ITYPE >
   bool add_unique(const ITYPE & str)
   {

      return ::iter::add_unique(*this, str);

   }


   template < typename ITYPE >
   bool case_insensitive_add_unique(const ITYPE & str)
   {

      return ::iter::case_insensitive_add_unique(*this, str);

   }


   template < typename ITYPE >
   bool case_insensitive_contains_iter(const ITYPE & str, typename ITERABLE::iterator find = 0, typename ITERABLE::iterator last = nullptr, ::collection::count countMin = 1, ::collection::count countMax = -1) const
   {

      return ::iter::case_insensitive_contains(*this, str, find, last, countMin, countMax);

   }


   template < typename ITYPE >
   bool contains_iter(const ITYPE & str, typename ITERABLE::iterator find = 0, typename ITERABLE::iterator last = nullptr, ::collection::count countMin = 1, ::collection::count countMax = -1) const
   {

      return ::iter::contains(*this, str, find, last, countMin, countMax);

   }


   template < typename ITYPE >
   bool case_insensitive_icontains(const ITYPE & str, ::collection::index find, ::collection::count count, ::collection::count countMin /*= 1*/, ::collection::count countMax = -1) const
   {

      return ::iter::case_insensitive_icontains(*this, str, find, last, countMin, countMax);

   }


   template < typename ITYPE >
   bool icontains(const ITYPE & str, ::collection::index find, ::collection::count count, ::collection::count countMin /*= 1*/, ::collection::count countMax = -1) const
   {

      return ::iter::icontains(*this, str, find, last, countMin, countMax);

   }

   template < typename ITYPE >
   Type implode(const ITYPE & lpcszSeparator = "", typename ITERABLE::const_iterator iStart = 0, typename ITERABLE::const_iterator iEnd = nullptr) const
   {

      Type value;

      ::iter::implode(*this, value, lpcszSeparator, iStart, iEnd);

      return value;

   }

   template < typename ITYPE, typename ITYPE2 >
   Type implode_ex(const ITYPE & lpcszSeparator = "", const ITYPE2 & lpcszLastSeparator = "", typename ITERABLE::const_iterator iStart = 0, typename ITERABLE::const_iterator iEnd = nullptr) const
   {

      Type value;

      ::iter::implode_ex(*this, value, lpcszSeparator, lpcszLastSeparator, iStart, iEnd);

      return value;

   }


   template < typename ITERABLE2, typename ITYPE >
   void prefix(const ITERABLE2 & iterable2, const ITYPE & pszPrefix, typename ITERABLE2::const_iterator first = nullptr, typename ITERABLE2::const_iterator last = nullptr)
   {

      ::iter::prefix(*this, iterable2, pszPrefix, first, last);

   }

   template < typename ITERABLE2, typename ITYPE >
   void suffix(const ITERABLE2 & iterable2, const ITYPE & pszSuffix, typename ITERABLE2::const_iterator first = nullptr, typename ITERABLE2::const_iterator last = nullptr)
   {

      ::iter::suffix(*this, iterable2, pszSuffix, first, last);

   }

   template < typename ITERABLE2, typename ITYPE, typename ITYPE2 >
   void surround(const ITERABLE2 & iterable2, const ITYPE & pszPrefix = "", const ITYPE2 & pszSuffix = "", typename ITERABLE2::iterator first = nullptr, typename ITERABLE2::const_iterator last = nullptr)
   {

      ::iter::surround(*this, iterable2, pszPrefix, pszSuffix, first, last);

   }

   template < typename ITYPE >
   void prefix(const ITYPE & pszPrefix, typename ITERABLE::iterator first = nullptr, typename ITERABLE::iterator last = nullptr)
   {

      ::iter::surround(*this, pszPrefix, first, last);

   }

   template < typename ITYPE >
   void suffix(const ITYPE & pszSuffix, typename ITERABLE::iterator first = nullptr, typename ITERABLE::iterator last = nullptr)
   {

      ::iter::surround(*this, pszSuffix, first, last);

   }


   template < typename ITYPE, typename ITYPE2 >
   void surround(const ITYPE & pszPrefix = "", const ITYPE & pszSuffix = "", typename ITERABLE::iterator first = 0, typename ITERABLE::iterator last = nullptr)
   {

      ::iter::surround(*this, pszPrefix, pszSuffix, first, last);

   }


   template < typename ITYPE, typename ITYPE2, typename ITYPE3 >
   void surround_and_implode(const ITYPE & str, const ITYPE2 & lpcszSeparator = "", const ITYPE3 & pszPrefix = "", const ITYPE2 & pszSuffix = nullptr, typename ITERABLE::iterator first = nullptr, typename ITERABLE::iterator last = nullptr)
   {

      ::iter::surround(*this, lpcszSeparator, pszPrefix, lpszSuffix, first, last);

   }




   template < typename ITYPE, typename ITYPESEP >
   Container & add_tokens(const ITYPE & pcsz, const ITYPESEP & lpcszSeparator, bool bAddEmpty = true)
   {

      return ::iter::add_tokens(*this, pcsz, lpcszSeparator, bAddEmpty);

   }

   template < typename ITYPE >
   Container & add_lines(const ITYPE & str, bool bAddEmpty = true)
   {

      return ::iter::add_lines(*this, str, bAddEmpty);

   }

   template < typename ITYPE, typename ITERABLE2 >
   Container & add_shortest_tokens(const ITYPE & pcsz, const ITERABLE2 & iterableSeparator, bool bAddEmpty = true, bool bWithSeparator = false)
   {

      return ::iter::add_shortest_tokens(*this, pcsz, iterableSeparator, bAddEmpty, bWithSeparator);

   }

   template < typename ITYPE >
   Container & trim_right(const ITYPE & pszChars)
   {

      return ::iter::trim_right(*this, pszChars);

   }

   template < typename ITYPE >
   Container & trim_left(const ITYPE & pszChars)
   {

      return ::iter::trim_left(*this, pszChars);

   }

   template < typename ITYPE >
   Container & trim(const ITYPE & pszChars)
   {

      return ::iter::trim(*this, pszChars);

   }




   // transfer preferred in order
   template < typename ITYPE >
   Container & preferred(const ITYPE & pcsz)
   {

      return ::iter::preferred(*this, pcsz);

   }


   template < typename ITERABLE2 >
   Container & preferred_iter(const ITERABLE2 & iterable2)
   {

      return ::iter::preferred_iter(*this, iterable2);

   }

   template < typename ITERABLE2 >
   ::collection::count erase_iter(const ITERABLE2 & iterable2)
   {

      return ::iter::erase_iter(*this, iterable2);

   }


   template < typename ITERABLE2 >
   Container & add_iter(const ITERABLE2 & iterable2)
   {

      return ::iter::add_iter(*this, iterable2);

   }


   template < typename ITERABLE2 >
   Container diff(const ITERABLE2 & iterable2) const
   {

      return ::iter::diff(*this, iterable2);

   }


   template < typename ITERABLE2 >
   Container sum(const ITERABLE2 & iterable2) const
   {

      return ::iter::sum(*this, iterable2);

   }

   template < typename ITYPE >
   ::collection::count case_insensitive_erase_element_iter(const ITYPE & pcsz, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr, ::collection::count countMin = 0, ::collection::count countMax = -1)
   {

      return ::iter::case_insensitive_erase(pcsz, find, last, countMin, countMax);

   }

   template < typename ITYPE >
   ::collection::count erase_element_iter(const ITYPE & pcsz, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr, ::collection::count countMin = 0, ::collection::count countMax = -1)
   {

      return ::iter::case_insensitive_erase(pcsz, find, last, countMin, countMax);

   }


   template < typename ITYPE >
   typename ITERABLE::iterator case_insensitive_reverse_find(const ITYPE & pcsz, typename ITERABLE::iterator find = -1, typename ITERABLE::iterator last = 0)
   {

      return ::iter::case_insensitive_reverse_find(*this, pcsz, find, last);

   }

   template < typename ITYPE >
   typename ITERABLE::iterator rear_find(const ITYPE & pcsz, typename ITERABLE::iterator find = -1, typename ITERABLE::iterator last = 0)
   {

      return ::iter::rear_find(*this, pcsz, find, last);

   }

   template < typename ITYPE >
   typename ITERABLE::iterator any_suffixes(const ITYPE & lpcszIsSuffixed, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr)
   {

      return ::iter::any_suffixes(*this, lpcszIsSuffixed, find, last);

   }

   template < typename ITYPE >
   bool any_case_insensitive_suffixes(const ITYPE & lpcszIsSuffixed, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr)
   {

      return ::iter::any_case_insensitive_suffixes(*this, lpcszIsSuffixed, find, last) != end();

   }

   template < typename ITYPE >
   typename ITERABLE::iterator any_prefixes(const ITYPE & lpcszIsPrefixed, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr)
   {

      return ::iter::any_prefixes(*this, lpcszIsPrefixed, find, last);

   }

   template < typename ITYPE >
   typename ITERABLE::iterator case_insensitive_any_prefixes(const ITYPE & lpcszIsPrefixed, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr)
   {

      return ::iter::case_insensitive_any_prefixes(*this, lpcszIsPrefixed, find, last);

   }

   template < typename ITYPE >
   typename ITERABLE::iterator find_first_ends(const ITYPE & lpcszSuffix, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr)
   {

      return ::iter::find_first_ends(*this, lpcszSuffix, find, last);

   }

   template < typename ITYPE >
   typename ITERABLE::iterator case_insensitive_find_first_ends(const ITYPE & lpcszSuffix, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr)
   {

      return ::iter::case_insensitive_find_first_ends(*this, lpcszSuffix, find, last);

   }

   template < typename ITYPE >
   typename ITERABLE::iterator find_first_ends_eat(ITYPE & str, const ITYPE & pcsz, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr)
   {

      return ::iter::find_first_ends_eat(*this, str, pcsz, find, last);

   }

   template < typename ITYPE >
   typename ITERABLE::iterator case_insensitive_find_first_ends_eat(ITYPE & str, const ITYPE & pcsz, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr)
   {

      return ::iter::case_insensitive_find_first_ends_eat(*this, str, pcsz, find, last);

   }

   template < typename ITYPE >
   typename ITERABLE::iterator find_first_begins(const ITYPE & lpcszPrefix, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr)
   {

      return ::iter::find_first_begins(*this, lpclpcszPrefixsz, find, last);

   }

   template < typename ITYPE >
   typename ITERABLE::iterator case_insensitive_find_first_begins(const ITYPE & lpcszPrefix, typename ITERABLE::iterator find = 0, typename ITERABLE::iterator last = nullptr)
   {

      return ::iter::case_insensitive_find_first_begins(*this, lpcszPrefix, find, last);

   }

   template < typename ITYPE >
   typename ITERABLE::iterator find_first_begins_eat(ITYPE & str, const ITYPE & pcsz, typename ITERABLE::iterator find = 0, typename ITERABLE::iterator last = nullptr)
   {

      return ::iter::find_first_begins_eat(*this, str, pcsz, find, last);

   }

   template < typename ITYPE >
   typename ITERABLE::iterator case_insensitive_find_first_begins_eat(ITYPE & str, const ITYPE & pcsz, typename ITERABLE::iterator find = 0, typename ITERABLE::iterator last = nullptr)
   {

      return ::iter::case_insensitive_find_first_begins_eat(*this, str, pcsz, find, last);

   }

   template < typename STRITERABLE, typename ITYPE >
   ::collection::count case_insensitive_get_begins(STRITERABLE & stra, const ITYPE & pcsz, typename ITERABLE::iterator first = 0, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr)
   {

      return ::iter::case_insensitive_get_begins(*this, stra, pcsz, first, last);

   }


   template < typename ITYPE >
   ::collection::count case_insensitive_filter_begins(const ITYPE & pcsz, typename ITERABLE::iterator first = 0, typename ITERABLE::iterator last = nullptr)
   {

      return ::iter::case_insensitive_filter_begins(*this, pcsz, first, last);

   }


   template < typename PRED >
   ::collection::count filter(PRED pred, typename ITERABLE::iterator first = 0, typename ITERABLE::iterator last = nullptr)
   {

      return ::iter::filter(*this, pred, first, last);

   }

   template < typename PRED >
   ::collection::count filter_out(PRED pred, typename ITERABLE::iterator first = 0, typename ITERABLE::iterator last = nullptr)
   {

      return ::iter::filter_out(*this, pred, first, last);

   }

   template < typename PRED, typename ArrayOut >
   ::collection::count filter_out(PRED pred, ArrayOut & a, typename ITERABLE::iterator first = 0, typename ITERABLE::iterator last = nullptr)
   {

      return ::iter::filter_out(*this, pred, a, first, last);

   }

   template < typename ITYPE >
   ::collection::count case_insensitive_erase_first(const ITYPE & pcsz, typename ITERABLE::iterator find = nullptr, typename ITERABLE::iterator last = nullptr)
   {

      return ::iter::case_insensitive_erase_first(*this, pcsz, first, last);

   }

   using ITERABLE::erase_first;
   template < typename ITYPE >
   ::collection::count erase_first(const ITYPE & pcsz, typename ITERABLE::iterator first = nullptr, typename ITERABLE::iterator last = nullptr)
   {

      return ::iter::erase_first(*this, pcsz, first, last);

   }

   template < typename ITYPE >
   ::collection::count case_insensitive_erase_last(const ITYPE & pcsz, typename ITERABLE::iterator first = nullptr, typename ITERABLE::iterator last = nullptr)
   {

      return ::iter::case_insensitive_erase_last(*this, pcsz, first, last);

   }


   using ITERABLE::erase_last;
   template < typename ITYPE >
   ::collection::count erase_last(const ITYPE & pcsz, typename ITERABLE::iterator first = nullptr, typename ITERABLE::iterator last = nullptr)
   {

      return ::iter::erase_last(*this, pcsz, first, last);

   }





   template < typename ITYPESEP, typename ITYPE2 >
   Container & explode(const ITYPESEP & strSeparator, const ITYPE2 & str)
   {

      return ::iter::explode(*this, strSeparator, str);

   }

   // csstidy: Same as explode, but not within a ITYPE
   template < typename ITYPE >
   Container & csstidy_explode_ws(const char sep, const ITYPE & psz)
   {

      return ::iter::csstidy_explode_ws(*this, sep, psz);

   }

   template < typename ITYPE >
   void get_format_string(const ITYPE & str, const ITYPE & lpcszSeparator) const
   {

      return ::iter::get_format_string(*this, str, lpcszSeparator);

   }

   template < typename ITYPE >
   ITYPE & get_network_payload(ITYPE & str, bool bNewLine = true) const
   {

      return ::iter::get_network_payload(*this, str, bNewLine);

   }

   template < typename ITYPE >
   void c_add(char ** ppsz, ::collection::count iCount)
   {

      return ::iter::c_add(*this, ppsz, iCount);

   }

   template < typename ITYPE >
   void c_add(char ** ppsz)
   {

      return ::iter::c_add(*this, ppsz);

   }

   template < typename ITYPE >
   void c_add(wchar_t ** ppsz, ::collection::count iCount)
   {

      return ::iter::c_add(*this, ppsz, iCount);

   }

   template < typename ITYPE >
   void c_add(wchar_t ** ppsz)
   {

      return ::iter::c_add(ppsz);

   }


   template < typename ITYPE >
   bool contains_key(const ITYPE & key) const
   {

      return ::iter::contains_key(*this, key);

   }


   template < typename ITYPE >
   bool contains_payload(const ITYPE & value) const
   {

      return ::iter::contains_payload(*this, value);

   }


   template < typename ITYPE >
   bool contains(const ITYPE & value) const
   {

      return ::iter::contains(*this, value);

   }


   template < typename ITYPE >
   bool contains(const ITYPE & value, const_iterator first, const_iterator last = nullptr) const
   {

      return ::iter::contains(*this, value, first, last);

   }

   template < typename ITYPE >
   bool case_insensitive_icontains(const ITYPE & value, index first = 0, ::collection::count count = -1) const
   {

      return ::iter::case_insensitive_icontains(*this, value, first, count);

   }


   template < typename ITYPE >
   bool icontains(const ITYPE & value, index first = 0, ::collection::count count = -1) const
   {

      return ::iter::icontains(*this, value, first, count);

   }

   template < typename ITYPE >
   ::collection::count erase(const ITYPE & value)
   {

      return ::iter::erase(*this, value);

   }


   template < typename ITERABLE2 >
   ITERABLE & intersect(const ITERABLE2 & iterable2)
   {

      return ::iter::intersect(*this, iterable2);

   }

   template < typename ITERABLE2 >
   typename ::collection::count add_unique_iter(const ITERABLE2 & stra)
   {

      return ::iter::add_unique_iter(*this, stra);

   }

   template < typename ITERABLE2 >
   typename ::collection::count case_insensitive_add_unique_iter(const ITERABLE2 & stra)
   {

      return ::iter::case_insensitive_add_unique_iter(*this, stra);

   }

   template < typename PRED >
   bool predicate_erase_first(PRED pred)
   {

      return ::iter::predicate_erase_first(*this, pred);

   }

   template < typename PRED >
   typename ITERABLE::const_iterator predicate_find_first(PRED pred, typename ITERABLE::const_iterator first = nullptr, typename ITERABLE::const_iterator last = nullptr) const
   {

      return ::iter::predicate_find_first(*this, pred, first, last);

   }

   template < typename PRED >
   typename ITERABLE::iterator predicate_find_first(PRED pred, typename ITERABLE::iterator first = nullptr, typename ITERABLE::iterator last = nullptr)
   {

      return ::iter::predicate_find_first(*this, pred, first, last);

   }

   template < typename ITERATOR >
   Container slice(ITERATOR first, ITERATOR last = nullptr)
   {

      Container iterableSlice;

      ::iter::slice(*this, iterableSlice, first, last);

      return iterableSlice;


   }

   template < typename int, typename INT2 >
   Container islice(int first, INT2 count = -1)
   {

      Container iterableSlice;

      ::iter::islice(*this, iterableSlice, first, count);

      return iterableSlice;


   }


   template < typename ITYPE >
   typename index ifind_first_begins(const ITYPE & lpcszPrefix, typename ITERABLE::const_iterator find = nullptr, typename ITERABLE::const_iterator last = nullptr) const
   {

      return ::iter::ifind_first_begins(*this, lpcszPrefix, find, last);

   }


   template < typename ITYPE >
   typename index ifind_first_begins(const ITYPE & lpcszPrefix, index first = 0, ::collection::count count = -1)
   {

      return ::iter::ifind_first_begins(*this, lpcszPrefix, first, count);

   }


   template < typename ITYPE >
   typename index ifind_first(const ITYPE & lpcszPrefix, ::collection::index find = 0, ::collection::count count = -1) const
   {

      return ::iter::ifind_first(*this, lpcszPrefix, find, count);

   }


   template < typename ITYPE >
   typename index ifind_first(const ITYPE & lpcszPrefix, ::collection::index find = 0, ::collection::count count = -1)
   {

      return ::iter::ifind_first(*this, lpcszPrefix, find, count);

   }


   template < typename ITYPE >
   typename index case_insensitive_ifind_first(const ITYPE & lpcszPrefix, ::collection::index find = 0, ::collection::count count = -1) const
   {

      return ::iter::case_insensitive_ifind_first(*this, lpcszPrefix, find, count);

   }

   template < typename ITYPE >
   typename index case_insensitive_ifind_first(const ITYPE & lpcszPrefix, ::collection::index find = 0, ::collection::count count = -1)
   {

      return ::iter::case_insensitive_ifind_first(*this, lpcszPrefix, find, count);

   }






   template < typename SWAP >
   void swap_quick_sort(SWAP __swap, bool bAscending)
   {

      ::sort::swap_quick_sort(*this, __swap, bAscending);

   }

   template < typename SWAP >
   void swap_quick_sort(SWAP __swap)
   {

      ::sort::swap_quick_sort(*this, __swap);

   }

   template < typename SWAP >
   void swap_quick_sort_descending(SWAP __swap)
   {

      ::sort::swap_quick_sort_desceding(*this, __swap);

   }

   template < typename SWAP >
   void case_insensitive_swap_quick_sort(SWAP __swap, bool bAscending)
   {

      ::sort::swap_quick_sort(*this, __swap, bAscending);

   }

   template < typename SWAP >
   void case_insensitive_swap_quick_sort(SWAP __swap)
   {

      ::sort::swap_quick_sort(*this, __swap);

   }

   template < typename SWAP >
   void swap_quick_sort_ci_descending(SWAP __swap)
   {

      ::sort::swap_quick_sort_desceding(*this, __swap);

   }







   template < typename PRED >
   void predicate_quick_sort(PRED pred, bool bAscending)
   {

      ::sort::predicate_quick_sort(*this, pred, bAscending);

   }


   template < typename PRED >
   void predicate_quick_sort(PRED pred)
   {

      ::sort::predicate_quick_sort(*this, pred);

   }


   template < typename PRED >
   void predicate_quick_sort_descending(PRED pred)
   {

      ::sort::predicate_quick_sort_descending(*this, pred);

   }






   template < typename PRED, typename SWAP >
   void predicate_swap_quick_sort(PRED pred, SWAP __swap, bool bAscending)
   {

      ::sort::predicate_swap_quick_sort(*this, pred, bAscending);

   }


   template < typename PRED, typename SWAP >
   void predicate_swap_quick_sort(PRED pred, SWAP __swap)
   {

      ::sort::predicate_swap_quick_sort(*this, pred);

   }

   template < typename PRED, typename SWAP >
   void predicate_swap_quick_sort_descending(PRED pred, SWAP __swap)
   {

      ::sort::predicate_swap_quick_sort_descending(*this, pred, bAscending);

   }






   template < typename INDEX_ARRAY >
   void get_quick_sort(const INDEX_ARRAY & ia)
   {

      ::sort::get_quick_sort(*this, ia);

   }

   template < typename INDEX_ARRAY  >
   void case_insensitive_get_quick_sort(const INDEX_ARRAY & ia)
   {

      ::sort::case_insensitive_get_quick_sort(*this, ia);

   }


   template < typename ITERABLE2 >
   bool is_equal(const ITERABLE2 & iterable2) const
   {

      if (iterable2.get_count() != get_count())
      {

         return false;

      }

      auto a = begin();

      auto b = iterable2.begin();

      for (; valid_iter(a, end()) && iterable2.valid_iter(b, iterable2.end()); a++, b++)
      {

         if (!(*a == *b))
         {

            return false;

         }

      }

      return a == end() && b == iterable2.end();

   }


};




