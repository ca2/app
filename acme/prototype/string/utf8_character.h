// Created by camilo on 2022-11-10 22:40 <3ThomasBorregaardSorensen!!
#pragma once


#include "inline_string.h"


using utf8_character = inline_string < ::ansi_character, 8 >;
//{
//
//   //char m_sz[8];
//   //int m_iLength;
//
//   using inline_string::inline_string;
//   //utf8_character()
//   //{
//
//   //   ::memory_set(this, 0, sizeof(utf8_character));
//   //   m_iLength = 0;
//
//   //}
//
//   //utf8_character(const ::scoped_string & scopedstr)
//   //{
//
//   //   auto len = string_safe_length(scopedstr, 7);
//
//   //   int i = 0;
//
//   //   for (; i < len; i++)
//   //   {
//
//   //      m_sz[i] = psz[i];
//
//   //   }
//
//   //   m_sz[i] = '\0';
//
//   //   m_iLength = i;
//
//   //}
//
//
//   //utf8_character(const utf8_character& utf8character)
//   //{
//
//   //   m_sz[0] = utf8character.m_sz[0];
//   //   m_sz[1] = utf8character.m_sz[1];
//   //   m_sz[2] = utf8character.m_sz[2];
//   //   m_sz[3] = utf8character.m_sz[3];
//   //   m_sz[4] = utf8character.m_sz[4];
//   //   m_sz[5] = utf8character.m_sz[5];
//   //   m_sz[6] = utf8character.m_sz[6];
//   //   m_sz[7] = utf8character.m_sz[7];
//
//   //   m_iLength = utf8character.m_iLength;
//
//   //}
//
////   operator const_char_pointer () const { return m_sz; }
//
//};
//
//
//
//
