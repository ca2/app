//
//  this_type.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 08/06/22.
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//


#pragma once


CLASS_DECL_ACME void this_type_init(const scoped_string & strThisType);


CLASS_DECL_ACME void this_type_term(const scoped_string & strThisType);


class this_type
{
public:
   
   
   const char * m_psz;
   
   
   this_type(const scoped_string & str) :
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



