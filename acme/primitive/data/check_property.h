// Creating by camilo with 
// property* system on 2024-06-06 21:20 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/data/property.h"
#include "acme/primitive/data/signal.h"


//#include "acme/primitive/primitive/payload.h"
////#include "acme/primitive/primitive/object.h"


namespace data
{
   class check_property;

   struct check_change
   {
      ::data::check_property & m_checkproperty;
      ::data::property_change & m_propertychange;
      auto & payload() {
         return m_propertychange.m_payload;
      }
      auto & action_context() {
         return m_propertychange.m_actioncontext;
      }

   };

   using check_will_change = ::function < bool(check_change &) >;

   using check_changed = ::function < void(check_change &) >;

   //template < enum_id t_eid = (enum_id) ID_CHECK>
   class CLASS_DECL_ACME check_property :
      public ::data::property
   {
   protected:


      ::data::property_will_change                    m_propertywillchange;
      ::data::property_changed                        m_propertychanged;
      ::data::signal < ::data::check_will_change >    m_checkwillchangesignal;
      ::data::signal < ::data::check_changed >        m_checkchangedsignal;


      void unhook_callbacks();
      void hook_callbacks();

   public:

      check_property(::data::property_container * ppropertycontainer = nullptr, const ::atom & atom = {});
      check_property(const check_property & checkproperty);
      ~check_property();



      // ::e_check get_echeck() const;
      // virtual bool get_bcheck() const;
      ::e_check echeck() const;

      bool is_checked() const;

      //bool is_checked() const;
      bool operator ==(::e_check echeck) const { return this->echeck() == echeck; }
      
      bool set(::e_check echeck, const ::action_context & actioncontext);
      //       bool toggle_check(const ::action_context & action_context)
      //       {
      //
      //
      //       }
      //
      //
      //       virtual bool on_check_will_change(::e_check echeck, const action_context & actioncontext);
      //       virtual void on_check_changed(::e_check echeck, const action_context & actioncontext);
      //
      //       bool on_property_will_change(const ::atom & atom, const ::payload & payload, const ::action_context & context = {}) override;
      //       void on_property_changed(const ::atom & atom, const ::payload & payload, const ::action_context & context = {}) override;
      //
      // check_property::check_property(::property_container * ppropertycontainer, const ::atom & atom) :
      // property_link(ppropertycontainer, atom)
      // {
      //
      // }
      //
      //
      // check_property::check_property(const check_property & checkproperty) :
      // check_property(checkproperty.m_ppropertycontainer, checkproperty.m_atom)
      // {
      //
      //
      //    }
      //
      //
      //
      // check_property::~check_property()
      // {
      //
      //
      // }
      //
      //
      //  /*  void check::set_check(bool bChecked, const ::action_context & context)
      //    {
      //
      //       set_check((::enum_check) (bChecked ? ::e_check_checked : ::e_check_unchecked),context);
      //
      //    }*/
      //
      //
      //    ::e_check check_property::get_echeck() const
      //    {
      //
      //       return this->echeck();
      //
      //    }
      //
      //
      //    bool check_property::get_bcheck() const
      //    {
      //
      //       return this->bcheck();
      //
      //    }
      //
      //
      //    ::e_check check_property::echeck() const
      //    {
      //
      //       return get_property().as_echeck();
      //
      //    }
      //
      //
      //    bool check_property::bcheck() const
      //    {
      //
      //       return this->echeck() != e_check_unchecked;
      //
      //    }
      //
      //
      //    bool check_property::is_checked() const
      //    {
      //
      //       return this->bcheck();
      //
      //    }
      //
      //
      //    bool check_property::set_check(::e_check echeck, const ::action_context & actioncontext)
      //    {
      //
      //       return set_property(echeck, actioncontext);
      //
      //       // if (!m_linkedpropertyCheck)
      //       // {
      //       //
      //       //    return;
      //       //
      //       // }
      //       //
      //       // if(echeck != this->get_echeck())
      //       // {
      //       //
      //       //    *m_linkedpropertyCheck = echeck;
      //       //
      //       //    if (context.is_user_source())
      //       //    {
      //       //
      //       //       if (m_callbackOnCheck)
      //       //       {
      //       //
      //       //          m_callbackOnCheck(this);
      //       //
      //       //       }
      //       //
      //       //    }
      //       //
      //       //    m_linkedpropertyCheck.notify_property_changed(context);
      //       //
      //       // }
      //
      //    }
      //

      bool toggle(const ::action_context & context);

      //
      // bool check_property::on_check_will_change(::e_check echeck, const action_context & actioncontext)
      // {
      //
      //    return true;
      //
      // }
      //
      //
      // void check_property::on_check_changed(::e_check echeck, const action_context & actioncontext)
      // {
      //
      //
      //
      // }
      //
      //
      // bool check_property::on_property_will_change(const ::atom & atom, const ::payload & payload, const ::action_context & actioncontext)
      // {
      //
      //    if(atom == m_atom)
      //    {
      //
      //       if(!on_check_will_change(atom, payload.as_echeck(), actioncontext))
      //       {
      //
      //          return false;
      //
      //       }
      //
      //    }
      //
      //    return true;
      //
      // }
      //
      //
      // void check_property::on_property_changed(const ::atom & atom, const ::payload & payload, const ::action_context & actioncontext)
      // {
      //
      //    if(atom == m_atom)
      //    {
      //
      //       on_check_changed(payload.as_echeck(), actioncontext);
      //
      //    }
      //
      // }

      void set_check_property(const ::data::check_property & checkproperty);

      //check_property & check() { return m_checkproperty; }

      /*
      //virtual bool on_property_will_change(property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext);
      //virtual void on_property_changed(property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext);
      */

      bool on_check_will_change(::data::check_change & checkchange);
      void on_check_changed(::data::check_change & checkchange);

      add_signal_function_to_holder < ::data::check_will_change > check_will_change(::matter * pmatterFunctionHolder);
      add_signal_function_to_holder < ::data::check_changed > check_changed(::matter * pmatterFunctionHolder);


      bool operator == (const ::data::check_property & checkproperty) const;
      bool operator == (const ::data::check_change & change) const;



      //bool operator == (const check_property & checkproperty) const;


   };


} // namespace data



