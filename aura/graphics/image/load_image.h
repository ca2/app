// Created by camilo on 2021-08-24 23:40 <3ThomasBS_!!
#pragma once



//#include "acme/primitive/primitive/payload.h"


namespace image
{


class CLASS_DECL_AURA load_image :
   virtual public ::particle
{
public:


   ::payload                        m_payload;
   ::image::image_pointer                  m_pimage;
   ::pointer<::image::image_context>       m_pimagecontext;
   ::function < void(::image::image *) >     m_functionLoaded;


   load_image(::image::image_context * pimagecontext);
   ~load_image() override;


   void run() override;


};





} // namespace image


