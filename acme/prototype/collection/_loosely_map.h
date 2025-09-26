// From ::papaya::weak to ::loosely by camilo on 2022-11-18 07:48 <3ThomasBorregaardSorensen!!
#pragma once


// #include "acme/prototype/collection/_loosely.h"
//
// // maybe use and enhance string_map_base::case_insensitive_find_key_containing
// // instead of this loosely::map_base
// namespace loosely
// {
//
//
//    namespace map_base
//    {
//
//
//       template < typename MAP >
//       typename MAP::BASE_NODE * get(MAP& m, typename MAP::ARG_PAYLOAD key)
//       {
//
//          for (auto& item : m)
//          {
//
//             if (contains(item.element1(), key))
//             {
//
//                return item.m_p;
//
//             }
//
//          }
//
//          return nullptr;
//
//       }
//
//
//       template < typename MAP >
//       typename MAP::iterator find(MAP& m, typename MAP::ARG_PAYLOAD item)
//       {
//
//          for (auto& item : m)
//          {
//
//             if (contains(item.element1(), item))
//             {
//
//                return item;
//
//             }
//
//          }
//
//          return nullptr;
//
//       }
//
//
//       template < typename MAP >
//       typename MAP::PAYLOAD defer_get(MAP& m, typename MAP::ARG_PAYLOAD item, typename MAP::PAYLOAD default_payload = ::loosely::default_payload < typename MAP::PAYLOAD >())
//       {
//
//          auto iterator = find(m, item);
//
//          if (!iterator)
//          {
//
//             return default_payload;
//
//          }
//
//          return iterator->payload();
//
//       }
//
//
//    } // namespace map_base
//
//
// } // namespace loosely
//
//
