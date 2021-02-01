#pragma once

#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

typedef void * HPALETTE;

#endif

class image_palette
{
public:


   image_palette();


   void create(::image * pimage);


   //HPALETTE m_hpalette;

public:
   
   
   virtual ~image_palette();


};
