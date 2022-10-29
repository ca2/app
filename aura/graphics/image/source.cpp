//
// Created by camilo on 31/12/2021. 10:42 BRT <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "source.h"
#include "context_image.h"
#include "image.h"
#include "icon.h"
#include "acme/platform/context.h"


image_payload::image_payload(::particle * pparticle, const ::payload & payload):
   image_source(pparticle->m_pcontext->context_image()->get_image(payload))
{


}



icon_payload::icon_payload(::particle * pparticle, const ::payload & payload) :
   image_source(pparticle->m_pcontext->context_image()->get_icon(payload))
{


}
