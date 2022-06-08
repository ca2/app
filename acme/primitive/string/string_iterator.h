//
//  string_iterator.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 08/06/22.
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once

template < typename CHAR_TYPE >
class string_iterator
{
public:

   const CHAR_TYPE *         m_psz;

   string_iterator(const CHAR_TYPE * psz) : m_psz(psz) { }
   string_iterator(const CHAR_TYPE * psz, strsize size) : m_psz(psz + size) { }

   ::i32 operator *();
   string_iterator & operator ++();
   string_iterator operator ++(int);

   bool operator == (const string_iterator & it) const { return m_psz == it.m_psz;}

   bool operator != (const string_iterator & it) const { return !operator==(it);}

};
