// Creating by camilo with 
// property* system on 2024-06-06 21:20 <3ThomasBorregaardSorensen!!
#pragma once


namespace user { class property; }


namespace data
{

   class property_container;


   class CLASS_DECL_ACME property
   {
   protected:
      ::data::property_container *     m_ppropertycontainer;
      ::atom                           m_atom;
      friend class ::user::property;
      void initialize_data_property(const ::data::property & propertySource);
   public:




      property(::data::property_container * ppropertycontainer = nullptr, const ::atom & atom = {});


      property(const property & property);

      ~property();


      ::atom atom() const { return m_atom; }

      ::comparable_array < ::data::property_will_change > & property_will_change() const;

      ::comparable_array < ::data::property_changed > & property_changed() const;

      //property_link(::property_container * ppropertycontainer = nullptr, const ::atom & atom = {});
      //property_link(const property_link & propertylink);
      //~property_link() override;


      //bool set_property(const ::payload & payload, const ::action_context & context = {});
      //::payload get_property() const;

      bool operator &&(::data::property_change & change) const;

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


      bool set_property(const ::payload & payload, const ::action_context & actioncontext) const;

      ::atom_array get_key(const ::atom_array & atomaSuffix) const;


      bool set_property(const ::atom_array & atomaSuffix, const ::payload & payload, const ::action_context & actioncontext) const;

      ::payload get_property(const ::atom_array & atomaSuffix = {}) const;

      
      bool operator == (const property & property) const;


   };



   ////template < enum_id t_eid >
   //class property_id_link :
   //   public property_link
   //{
   //public:
   //
   //
   //   //::property_container *         m_ppropertycontainer;
   //
   //
   //   //property_link(::property_container * ppropertycontainer = nullptr, const ::atom & atom = {});
   //   //property_link(const property_link & propertylink);
   //   //~property_link() override;
   //
   //
   //   //bool set_property(const ::payload & payload, const ::action_context & context = {});
   //   //::payload get_property() const;
   //
   //
   ///*   void notify_property_changed(const ::action_context & actioncontext) const;
   //
   //   property* operator ->() { return ::is_null(m_ppropertyobject) ? nullptr : m_pproperty; }
   //   property* operator ->() const { return ::is_null(m_ppropertyobject) ? nullptr : m_pproperty; }
   //
   //   property& operator *() { return *this->operator->(); }
   //   property& operator *() const { return *this->operator->(); }
   //
   //   operator int() const { return ::is_set(m_pproperty) && ::is_set(m_ppropertyobject); }
   //
   //   linked_property& operator=(const linked_property& linkedproperty)
   //   {
   //
   //      m_pproperty = linkedproperty.m_pproperty;
   //      m_ppropertyobject = linkedproperty.m_ppropertyobject;
   //
   //      return *this;
   //   }
   //*/
   //   property_id_link(::property_container * ppropertycontainer):
   //      property_link(ppropertycontainer)
   //   {
   //
   //
   //   }
   //
   //
   //   property_id_link(const property_link & propertylink) :
   //   property_link(propertylink.m_ppropertycontainer)
   //   {
   //
   //   }
   //
   //
   //   ~property_id_link()
   //   {
   //
   //
   //   }
   //
   //   bool set_property(const ::payload & payload, const ::action_context & actioncontext)
   //   {
   //
   //      return property_link::set_property(t_eid, payload, actioncontext);
   //
   //   }
   //
   //
   //   ::payload get_property() const
   //   {
   //
   //      return property_link::get_property(t_eid);
   //
   //   }
   //
   //
   //};


} // namespace data



