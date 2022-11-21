// Created by camilo on 2021-08-24 23:40 <3ThomasBS_!!
#pragma once


#include "acme/primitive/primitive/particle.h"
//#include "acme/primitive/primitive/payload.h"


class CLASS_DECL_AURA load_image :
   virtual public ::particle
{
public:


   ::payload                        m_payload;
   ::image_pointer                  m_pimage;
   ::pointer<context_image>         m_pcontextimage;


   load_image(context_image * pcontextimage);
   ~load_image() override;


   void run() override;


};



