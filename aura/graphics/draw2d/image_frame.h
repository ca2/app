#pragma once


class CLASS_DECL_AURA image_frame :
   virtual public context_object
{
public:


   ::rect                        m_rect;
   ::image_pointer               m_pimage;
   millis                          m_tick;
   index                         m_iFrame;
   ::draw2d::e_disposal          m_edisposal;
   color32_t                      m_colorTransparent;
   bool                          m_bTransparent;
   bool                          m_bLocalPalette;


   image_frame();
   virtual ~image_frame();


   //virtual bool to(::draw2d::graphics_pointer & pgraphics);

   
   virtual void gif_set_disposal(int iDisposal);


   virtual void _001Process(::image * pimageCompose, ::image * pimageFrame, image_frame_array * pframea);


};


