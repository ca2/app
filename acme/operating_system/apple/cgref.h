//
//  cgref.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 18/06/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#pragma once


#include "acme/operating_system/apple/cfref.h"


using cgcolorref = cfref<CGColorRef, ::CGColorRelease >;

using cgcolorspaceref = cfref<CGColorSpaceRef, CGColorSpaceRelease >;

