#pragma once


class CLASS_DECL_ACME linked_property
{
public:


   mutable property *                 m_pproperty;
   mutable context_object *           m_pobjectPropertyHolder;


   linked_property() :
      m_pproperty(nullptr),
      m_pobjectPropertyHolder(nullptr)
   {

   }

   linked_property(nullptr_t) :
      m_pproperty(nullptr),
      m_pobjectPropertyHolder(nullptr)
   {

   }

   linked_property(const linked_property & linkedproperty) :
      m_pproperty(linkedproperty.m_pproperty),
      m_pobjectPropertyHolder(linkedproperty.m_pobjectPropertyHolder)
   {

   }

   linked_property(property * pproperty, context_object * pobject) :
      m_pproperty(pproperty),
      m_pobjectPropertyHolder(pobject)
   {

   }


   void notify_property_changed(const ::action_context & actioncontext) const;

   property* operator ->() { return ::is_null(m_pobjectPropertyHolder) ? nullptr : m_pproperty; }
   property* operator ->() const { return ::is_null(m_pobjectPropertyHolder) ? nullptr : m_pproperty; }

   property& operator *() { return *this->operator->(); }
   property& operator *() const { return *this->operator->(); }

   operator int() const { return ::is_set(m_pproperty) && ::is_set(m_pobjectPropertyHolder); }

   linked_property& operator=(const linked_property& linkedproperty)
   {

      m_pproperty = linkedproperty.m_pproperty;
      m_pobjectPropertyHolder = linkedproperty.m_pobjectPropertyHolder;

      return *this;
   }

};