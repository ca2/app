#pragma once


#include "acme/primitive/geometry2d/_geometry2d.h"
//#include "acme/primitive/primitive/object.h"


namespace user
{


   class CLASS_DECL_BASE split_pane :
      virtual public ::object
   {
   public:


      atom                                  m_atom;
      ::rectangle_i32                              m_rectangle;
      ::rectangle_i32                              m_rectangleClient;
      ::size_i32                              m_sizeFixed;
      bool                                m_bFixedSize;
      ::pointer<::user::place_holder>    m_pplaceholder;
      ::pointer<::user::impact_data>     m_pimpactdata;


      split_pane();


   };


} // namespace split_pane



