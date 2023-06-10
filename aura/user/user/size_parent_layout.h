//
//  _user.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 2023-06-06 19:50
//
#pragma once


//#include "acme/primitive/geometry2d/_geometry2d.h"


//#include "acme/primitive/geometry2d/_collection.h"


//#include "acme/primitive/mathematics/c_number.h"


struct size_parent_layout
{

   ::rectangle_i32      m_rectangle;     // parent client rectangle (trim as appropriate)
   ::size_i32           m_sizeTotal;     // total size on each side as on_layout proceeds
   bool                 m_bStretch;      // should stretch to fill all space

};



