#pragma once


class CLASS_DECL_ACME linked_property
{
public:


   mutable property *                 m_pproperty;
   mutable property_object *          m_ppropertyobject;


   linked_property() :
      m_pproperty(nullptr),
      m_ppropertyobject(nullptr)
   {

   }

   linked_property(nullptr_t) :
      m_pproperty(nullptr),
      m_ppropertyobject(nullptr)
   {

   }

   linked_property(const linked_property & linkedproperty) :
      m_pproperty(linkedproperty.m_pproperty),
      m_ppropertyobject(linkedproperty.m_ppropertyobject)
   {

   }

   linked_property(property * pproperty, property_object * pobject) :
      m_pproperty(pproperty),
      m_ppropertyobject(pobject)
   {

   }


   void notify_property_changed(const ::action_context & actioncontext) const;

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

};
