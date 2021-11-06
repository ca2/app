#pragma once


namespace user
{


   class CLASS_DECL_BASE split_pane :
      virtual public object
   {
   public:


      id                                  m_id;
      ::rectangle_i32                              m_rectangle;
      ::rectangle_i32                              m_rectangleClient;
      ::size_i32                              m_sizeFixed;
      bool                                m_bFixedSize;
      __pointer(::user::place_holder)     m_pplaceholder;
      __pointer(::user::impact_data)      m_pimpactdata;


      split_pane();


   };


} // namespace split_pane



