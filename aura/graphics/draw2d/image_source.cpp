//
// Created by camilo on 31/12/2021. 10:42 BRT <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "image_source.h"
#include "context_image.h"
#include "image.h"
#include "icon.h"



image_payload::image_payload(::object * pobject, const ::payload & payload):
   image_source(pobject->m_pcontext->context_image()->get_image(payload))
{


}



icon_payload::icon_payload(::object * pobject, const ::payload & payload) :
   image_source(pobject->m_pcontext->context_image()->get_icon(payload))
{


}
