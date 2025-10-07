//
//  callstack.hpp
//  acme
//
//  Created by Camilo Sasuke <3 Thomas Borregaard Soerensen on 14/02/22.
//  15:33
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once

#if !defined(ANDROID)
CLASS_DECL_ACME string _ansi_stack_trace(::particle * pparticle, void * const * ppui, int frames, const_char_pointer pszFormat, int iSkip = -1);
#endif


