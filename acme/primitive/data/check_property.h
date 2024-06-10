// Creating by camilo with 
// property* system on 2024-06-06 21:20 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/data/property.h"


//#include "acme/primitive/primitive/payload.h"
////#include "acme/primitive/primitive/object.h"


namespace data
{


   //template < enum_id t_eid = (enum_id) ID_CHECK>
   class CLASS_DECL_ACME check_property :
      public ::data::property
   {
   public:


      //linked_property   m_linkedpropertyCheck;
      //::function < void(::user::check *) >     m_callbackOnCheck;
      //virtual public ::property_container


      check_property(::data::property_container * ppropertycontainer = nullptr, const ::atom & atom = {});
      check_property(const check_property & checkproperty);
      ~check_property();

      // ::e_check get_echeck() const;
      // virtual bool get_bcheck() const;
      ::e_check echeck() const;

      bool is_checked() const;

      //bool is_checked() const;

      
      bool set(::e_check echeck, const ::action_context & actioncontext);
      //       bool _001ToggleCheck(const ::action_context & action_context)
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
      //  /*  void check::_001SetCheck(bool bChecked, const ::action_context & context)
      //    {
      //
      //       _001SetCheck((::enum_check) (bChecked ? ::e_check_checked : ::e_check_unchecked),context);
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
      //    bool check_property::_001SetCheck(::e_check echeck, const ::action_context & actioncontext)
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

   };


} // namespace data



