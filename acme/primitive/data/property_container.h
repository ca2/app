//
// Created by camilo on 2024-06-05 18:57 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/primitive/primitive/action_context.h"
#include "property_listener.h"


using property_will_change_function = ::function < bool(property_container *, const ::atom &, const ::payload & , const ::action_context &) >;

using property_changed_function = ::function < void(property_container *, const ::atom &, const ::payload &, const ::action_context & ) >;


class CLASS_DECL_ACME property_container :
    virtual public ::particle
{
public:


    ::property_set                                          m_propertyset;
    ::pointer_array < ::property_listener >                 m_propertylistenera;
    ::comparable_array < property_will_change_function >    m_propertywillchangea;
    ::comparable_array < property_changed_function >        m_propertychangeda;



    bool set_property(const ::atom & atom, const ::payload & payload, const ::action_context & context = {});
    ::payload get_property(const ::atom & atom) const;

    virtual bool on_property_will_change(const ::atom & atom, const ::payload & payload, const ::action_context & context = {});
    virtual void on_property_changed(const ::atom & atom, const ::payload & payload, const ::action_context & context = {});


};



