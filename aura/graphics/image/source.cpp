//
// Created by camilo on 31/12/2021. 10:42 BRT <3ThomasBorregaardSorensen!!
//
#include "platform.h"
#include "source.h"
#include "context.h"
#include "image.h"
#include "icon.h"
#include "acme/platform/application.h"
#include "aura/graphics/draw2d/domain.h"


namespace image
{


   image_payload::image_payload(::draw2d::domain_container * pdomaincontainer, const ::payload & payload) :
::image::image_source(pdomaincontainer->image()->get_image(payload, {.draw2d_domain=pdomaincontainer->draw2d_domain()}))
   {


   }



   icon_payload::icon_payload(::particle * pparticle, const ::payload & payload) :
      ::image::image_source(pparticle->image()->get_icon(payload))
   {


   }



} // namespace image



