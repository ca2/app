//
// Created by camilo on 2024-06-05 19:20 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "property_listener.h"


bool property_listener::on_property_will_change(property_container * pcontainer, const ::atom & atom, const ::payload & payload, const ::action_context & actioncontext)
{

    return true;

}


void property_listener::on_property_changed(property_container * pcontainer, const ::atom & atom, const ::payload & payload, const ::action_context & actioncontext)
{


}



