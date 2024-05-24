//
//  locale.h
//  acid
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 29/11/2022.
//  22:18
//  Copyright (c) 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


#if defined(LINUX) || defined(OPENBSD)
#include <locale.h>
#elif !defined(WINDOWS)
#include <xlocale.h>
#endif


class CLASS_DECL_ACID locale :
virtual public ::particle
{
public:

   
#if defined(WINDOWS)
   _locale_t      m_locale;
#else
   locale_t       m_locale;
#endif   
   
};



