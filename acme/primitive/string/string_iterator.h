//
//  string_iterator.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 08/06/22.
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#pragma once


template < primitive_character CHARACTER >
class string_iterator
{
public:

   const CHARACTER *         m_psz;

   string_iterator(const CHARACTER * psz) : m_psz(psz) { }
   string_iterator(const CHARACTER * psz, strsize size) : m_psz(psz + size) { }

   ::wd32char operator *();
   string_iterator & operator ++();
   string_iterator operator ++(int);

   bool operator == (const string_iterator & it) const { return m_psz == it.m_psz;}

   bool operator != (const string_iterator & it) const { return !operator==(it);}

};
