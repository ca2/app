#pragma once


//#include "acme/primitive/geometry2d/_geometry2d.h"
////#include "acme/primitive/primitive/object.h"
#include "acme/primitive/geometry2d/rectangle.h"



class CLASS_DECL_AURA image_frame :
   virtual public particle
{
public:


   ::rectangle_i32               m_rectangle;
   ::image_pointer               m_pimage;
   class ::time                    m_time;
   ::collection::index                         m_iFrame;
   ::draw2d::enum_disposal          m_edisposal;
   ::color::color                m_colorTransparent;
   bool                          m_bTransparent;
   bool                          m_bLocalPalette;


   image_frame();
   ~image_frame() override;

   
   virtual void gif_set_disposal(int iDisposal);


   virtual void _001Process(::image * pimageCompose, ::image * pimageFrame, image_frame_array * pframea);
   virtual void create(image_frame * pframeSource, const ::image_drawing & imagedrawing, ::image_frame_array * pframea);


};


