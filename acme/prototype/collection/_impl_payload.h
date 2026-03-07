//
// Created by camilo on 23/12/22 <3ThomasBorregaardSørensen!!
//
#pragma once




inline payload::payload(const ::inline_number_string& a) :
    payload(e_type_new)
{

    //m_etype = e_type_new;
    operator = (a);

}



inline property & property::operator = (const property& property)
{

    if (this != &property)
    {

        m_atomName = property.m_atomName;

        payload::operator=((const ::payload&)property);

    }

    return *this;

}



inline ::property& property_set_base::set_at(const ::atom& atom, const ::payload& payload)
{

    auto& property = this->property(atom);

    property = payload;

    return property;

}


inline ::payload property_object::payload(const ::atom& atom) const
{
    
    return this->property(atom); 

}



