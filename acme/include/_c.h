//
//  _c.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 24/04/20.
//
#pragma once


#ifdef _WIN32


#define LONG_IS_32BIT TRUE
#define LONG_IS_64BIT FALSE


#else


#if OSBIT == 64


#define LONG_IS_32BIT FALSE
#define LONG_IS_64BIT TRUE


#else


#define LONG_IS_32BIT TRUE
#define LONG_IS_64BIT FALSE


#endif


#endif



