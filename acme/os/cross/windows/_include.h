//
//  _include.h
//  acme
//
//  Created by Camilo Sasuke on 2021-05-12 03:54 BRT <3ThomasBS_!!
//  Copyright © 2021 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once

#ifndef LODWORD
#define LODWORD(l)                                    ((::u32)(((::u64)(l)) & 0xffffffff))
#endif
#ifndef HIDWORD
#define HIDWORD(l)                                    ((::u32)((((::u64)(l)) >> 32) & 0xffffffff))
#endif


