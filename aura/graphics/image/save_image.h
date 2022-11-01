//
// Created to host save_image by camilo on 30/12/2021 15:40 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/primitive/primitive/matter.h"


class CLASS_DECL_AURA save_image :
   virtual public ::matter
{
public:


   ::draw2d::enum_format      m_eformat;
   int                     m_iQuality;
   int                     m_iDpi;


   save_image();


};



