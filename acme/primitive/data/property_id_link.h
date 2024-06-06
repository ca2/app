#pragma once



#include "property_container.h"

class property_link
{
public:


   ::property_container *         m_ppropertycontainer;


   //property_link(::property_container * ppropertycontainer = nullptr, const ::atom & atom = {});
   //property_link(const property_link & propertylink);
   //~property_link() override;


   //bool set_property(const ::payload & payload, const ::action_context & context = {});
   //::payload get_property() const;


   /*   void notify_property_changed(const ::action_context & actioncontext) const;

      property* operator ->() { return ::is_null(m_ppropertyobject) ? nullptr : m_pproperty; }
      property* operator ->() const { return ::is_null(m_ppropertyobject) ? nullptr : m_pproperty; }

      property& operator *() { return *this->operator->(); }
      property& operator *() const { return *this->operator->(); }

      operator int() const { return ::is_set(m_pproperty) && ::is_set(m_ppropertyobject); }

      linked_property& operator=(const linked_property& linkedproperty)
      {

         m_pproperty = linkedproperty.m_pproperty;
         m_ppropertyobject = linkedproperty.m_ppropertyobject;

         return *this;
      }
   */
   property_link(::property_container * ppropertycontainer):
      m_ppropertycontainer(ppropertycontainer)
   {


   }


   property_link(const property_link & propertylink) :
   m_ppropertycontainer(propertylink.m_ppropertycontainer)
   {

   }


   ~property_link()
   {


   }

   bool set_property(const ::atom & atom, const ::payload & payload, const ::action_context & actioncontext)
   {

      return m_ppropertycontainer->set_property(atom, payload, actioncontext);

   }


   ::payload get_property(const ::atom & atom) const
   {

      return m_ppropertycontainer->get_property(atom);

   }


};



template < enum_id t_eid >
class property_id_link :
   public property_link
{
public:


   //::property_container *         m_ppropertycontainer;


   //property_link(::property_container * ppropertycontainer = nullptr, const ::atom & atom = {});
   //property_link(const property_link & propertylink);
   //~property_link() override;


   //bool set_property(const ::payload & payload, const ::action_context & context = {});
   //::payload get_property() const;


/*   void notify_property_changed(const ::action_context & actioncontext) const;

   property* operator ->() { return ::is_null(m_ppropertyobject) ? nullptr : m_pproperty; }
   property* operator ->() const { return ::is_null(m_ppropertyobject) ? nullptr : m_pproperty; }

   property& operator *() { return *this->operator->(); }
   property& operator *() const { return *this->operator->(); }

   operator int() const { return ::is_set(m_pproperty) && ::is_set(m_ppropertyobject); }

   linked_property& operator=(const linked_property& linkedproperty)
   {

      m_pproperty = linkedproperty.m_pproperty;
      m_ppropertyobject = linkedproperty.m_ppropertyobject;

      return *this;
   }
*/
   property_id_link(::property_container * ppropertycontainer):
      property_link(ppropertycontainer)
   {


   }


   property_id_link(const property_link & propertylink) :
   property_link(propertylink.m_ppropertycontainer)
   {

   }


   ~property_id_link()
   {


   }

   bool set_property(const ::payload & payload, const ::action_context & actioncontext)
   {

      return property_link::set_property(t_eid, payload, actioncontext);

   }


   ::payload get_property() const
   {

      return property_link::get_property(t_eid);

   }


};
