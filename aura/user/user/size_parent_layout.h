#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"


//#include "acme/prototype/geometry2d/_collection.h"


//#include "acme/prototype/mathematics/c_number.h"


struct size_parent_layout
{

   ::int_rectangle      m_rectangle;     // parent client rectangle (trim as appropriate)
   ::int_size           m_sizeTotal;     // total size on each side as on_layout proceeds
   bool                 m_bStretch;      // should stretch to fill all space

};



