// Created by camilo on 2022-11-10 22:40 <3ThomasBorregaardSorensen!!
#pragma once


#include "inline_string.h"


using utf8_character = inline_string < ansichar, 8 >;
//{
//
//   //char m_sz[8];
//   //::i32 m_iLength;
//
//   using inline_string::inline_string;
//   //utf8_character()
//   //{
//
//   //   memset(this, 0, sizeof(utf8_character));
//   //   m_iLength = 0;
//
//   //}
//
//   //utf8_character(const char* psz)
//   //{
//
//   //   auto len = string_safe_length(psz, 7);
//
//   //   ::i32 i = 0;
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
////   operator const char* () const { return m_sz; }
//
//};
//
//
//
//
