//
// Created by camilo on 2024-06-05 18:57 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/primitive/primitive/action_context.h"
#include "acme/primitive/collection/atom_array.h"
#include "property_listener.h"

namespace data
{


   class CLASS_DECL_ACME property_container :
      virtual public ::particle
   {
   public:


      ::property_set                                  m_propertyset;
      ::pointer_array < ::data::property_listener >   m_propertylistenera;
      ::comparable_array < property_will_change >     m_propertywillchangea;
      ::comparable_array < property_changed >         m_propertychangeda;



      bool set_property(const ::atom_array & atoma, const ::payload & payload, const ::action_context & context = {});
      ::payload get_property(const ::atom_array & atoma) const;

      virtual bool on_property_will_change(const ::atom_array & atoma, const ::payload & payload, const ::action_context & context = {});
      virtual void on_property_changed(const ::atom_array & atoma, const ::payload & payload, const ::action_context & context = {});


      ::comparable_array < property_will_change > & property_will_change();
      ::comparable_array < property_changed > & property_changed();


   };


} // namespace data

