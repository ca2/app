//
//  this_type.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 08/06/22.
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//


#pragma once


CLASS_DECL_ACME void this_type_init(const ::scoped_string & scopedstrThisType);


CLASS_DECL_ACME void this_type_term(const ::scoped_string & scopedstrThisType);


class this_type
{
public:
   
   
   const_char_pointer m_psz;
   
   
   this_type(const ::scoped_string & scopedstr) :
   m_psz(scopedstr)
   {
   
      this_type_init(m_psz);

   }
   
   
   ~this_type()
   {
      
      this_type_term(m_psz);
      
   }
   
   
};


#define IMPLEMENT_THIS_TYPE(type) static this_type g_type_ ## type(MAKE_STRING(type));



