// Created by camilo on 2021-08-24 23:40 <3ThomasBS_!!
#pragma once


class CLASS_DECL_AURA load_image :
   virtual public ::object
{
public:


   ::payload                        m_payload;
   ::image_pointer                  m_pimage;
   __pointer(context_image)         m_pcontextimage;


   load_image(context_image * pcontextimage);
   ~load_image() override;


   ::e_status run() override;


};



