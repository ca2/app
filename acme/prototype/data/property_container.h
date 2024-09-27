//
// Created by camilo on 2024-06-05 18:57 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/prototype/prototype/action_context.h"
#include "acme/prototype/collection/atom_array.h"
#include "property_listener.h"

namespace data
{


   class CLASS_DECL_ACME property_container :
      virtual public ::particle
   {
   public:


      ::property_set                                        m_propertyset;
      ::pointer_array < ::data::property_listener >         m_propertylistenera;
      ::comparable_array < ::data::property_will_change >   m_propertywillchangea;
      ::comparable_array < ::data::property_changed >       m_propertychangeda;


      property_container();
      ~property_container() override;


      virtual bool set_property(const ::atom_array & atoma, const ::payload & payload, const ::action_context & context = {});
      virtual ::payload get_property(const ::atom_array & atoma) const;

      virtual void on_set_property(::data::property_change & change);
      virtual ::payload on_get_property(const ::atom_array & atoma) const;

      virtual bool on_property_will_change(::data::property_change & change);
      virtual void on_property_changed(::data::property_change & change);


      ::comparable_array < ::data::property_will_change > & property_will_change();
      ::comparable_array < ::data::property_changed > & property_changed();


   };


} // namespace data

