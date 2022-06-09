//
//  this_type.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 08/06/22.
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//


#pragma once


void this_type_init(const char * pszThisType);


void this_type_term(const char * pszThisType);


class this_type
{
public:
   
   
   const char * m_psz;
   
   
   this_type(const char * psz) :
   m_psz(psz)
   {
   
      this_type_init(m_psz);

   }
   
   
   ~this_type()
   {
      
      this_type_term(m_psz);
      
   }
   
   
};


#define IMPLEMENT_THIS_TYPE(type) static this_type g_type_ ## type(STRINGFY(type));



