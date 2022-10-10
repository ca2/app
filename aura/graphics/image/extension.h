#pragma once


class image_frame_array;
class image_map;
class size_image;


class CLASS_DECL_AURA image_extension :
   virtual public ::object
{
public:


   ::image_pointer                     m_pimage;
   ::pointer<image_frame_array>        m_pframea;
   ::pointer<image_map>                m_pmap;
   ::pointer<size_image>               m_psizeimage;
   double                              m_dSpeed;


   image_extension();
   ~image_extension() override;


};
