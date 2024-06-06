//
// Created by camilo on 2024-06-05 19:18 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/primitive/primitive/action_context.h"


class CLASS_DECL_ACME property_listener :
    virtual public ::particle
{
public:


    virtual bool on_property_will_change(property_container * pcontainer, const ::atom & atom, const ::payload & payload, const ::action_context & actioncontext);
    virtual void on_property_changed(property_container * pcontainer, const ::atom & atom, const ::payload & payload, const ::action_context & actioncontext);


};



