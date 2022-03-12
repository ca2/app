#pragma once


class image_frame_array;
class image_map;


class CLASS_DECL_AURA image_extension :
   virtual public ::object
{
public:


   ::image_pointer                     m_pimage;
   __pointer(image_frame_array)        m_pframea;
   __pointer(image_map)                m_pmap;
   double                              m_dSpeed;


   image_extension();
   ~image_extension() override;


};
