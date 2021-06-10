//
//  _c.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 24/04/20.
//
#pragma once


#ifdef _WIN32


#define LONG_IS_32BIT 1
#define LONG_IS_64BIT 0


#else


#if OSBIT == 64


#define LONG_IS_32BIT 0
#define LONG_IS_64BIT 1


#else


#define LONG_IS_32BIT 1
#define LONG_IS_64BIT 0


#endif


#endif



