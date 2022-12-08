//
//  locale.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 29/11/2022.
//  22:18
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


#if !defined(WINDOWS)
#include <xlocale.h>
#endif


class CLASS_DECL_ACME locale :
virtual public ::particle
{
public:

   
#if defined(WINDOWS)
   _locale_t      m_locale;
#else
   locale_t       m_locale;
#endif   
   
};



