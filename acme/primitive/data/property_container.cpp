//
// Created by camilo on 2024-06-05 19:22 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "property_container.h"
#include "property_listener.h"


bool property_container::set_property(const ::atom & atom, const ::payload & payload, const ::action_context & actioncontext)
{

    if(!on_property_will_change(atom, payload, actioncontext))
    {

        return false;

    }

    m_propertyset[atom] = payload;

    on_property_changed(atom, payload, actioncontext);

    return true;

}


::payload property_container::get_property(const ::atom & atom) const
{

    return m_propertyset[atom];

}


bool property_container::on_property_will_change(const ::atom & atom, const ::payload & payload, const ::action_context & actioncontext)
{

    for(auto & propertywillchange : m_propertywillchangea)
    {

        if(!propertywillchange(this, atom, payload, actioncontext))
        {

            return false;

        }

    }

    for(auto & plistener : m_propertylistenera)
    {

        if(!plistener->on_property_will_change(this, atom, payload, actioncontext))
        {

            return false;

        }

    }

    return true;

}


void property_container::on_property_changed(const ::atom & atom, const ::payload & payload, const ::action_context & actioncontext)
{

    for(auto & propertychanged : m_propertychangeda)
    {

        propertychanged(this, atom, payload, actioncontext);

    }

    for(auto & plistener : m_propertylistenera)
    {

        plistener->on_property_changed(this, atom, payload, actioncontext);

    }

}





