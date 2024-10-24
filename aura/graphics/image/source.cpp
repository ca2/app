//
// Created by camilo on 31/12/2021. 10:42 BRT <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "source.h"
#include "context.h"
#include "image.h"
#include "icon.h"
#include "acme/platform/application.h"


namespace image
{


   image_payload::image_payload(::particle * pparticle, const ::payload & payload) :
      ::image::image_source(pparticle->image()->get_image(payload))
   {


   }



   icon_payload::icon_payload(::particle * pparticle, const ::payload & payload) :
      ::image::image_source(pparticle->image()->get_icon(payload))
   {


   }



} // namespace image



