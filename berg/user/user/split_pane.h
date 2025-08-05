#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
////#include "acme/prototype/prototype/object.h"
#include "acme/prototype/geometry2d/rectangle.h"


namespace user
{


   class CLASS_DECL_BERG split_pane :
      virtual public ::object
   {
   public:


      atom                                   m_atomSplitPane;
      ::int_rectangle                        m_rectanglePane;
      ::int_rectangle                        m_rectangleHosting;
      ::int_size                             m_sizeFixed;
      bool                                   m_bFixedSize;
      ::pointer<::user::place_holder>        m_pplaceholder;
      ::pointer<::user::impact_data>         m_pimpactdata;


      split_pane();


   };


} // namespace split_pane



