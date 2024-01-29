//
//  simple_allocate.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 07/12/23.
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


CLASS_DECL_ACME void * simple_memory_allocate(size_t s, const char * pszAnnotation = nullptr);
CLASS_DECL_ACME void * simple_memory_reallocate(void * p, size_t s, const char * pszAnnotation = nullptr);
CLASS_DECL_ACME void simple_memory_free(void * p);
CLASS_DECL_ACME memsize simple_memory_size(void * p);



