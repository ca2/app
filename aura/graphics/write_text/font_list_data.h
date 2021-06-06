// Created by camilo 2021-06-06 04:25 <3ThomasBS_!!
#pragma once


namespace write_text
{


   class CLASS_DECL_AURA font_list_data :
      virtual public __pointer_array(font_list_item)
   {
   public:


      index             m_iSerial;
      index             m_iUpdateId;
      int               m_iBaseSize;
      int_array         m_iaSize;
      ::rectangle_i32   m_rectClient;
      int               m_iUpdatedCount;
      bool              m_bLayoutStillIntersect;


   };


} // namespace write_text



