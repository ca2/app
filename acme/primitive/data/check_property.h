#pragma once


#include "property_link.h"


//#include "acme/primitive/primitive/payload.h"
////#include "acme/primitive/primitive/object.h"


//namespace user
//{


//template < enum_id t_eid = (enum_id) ID_CHECK>
class check_property :
   public ::property_link
{
public:


      //linked_property   m_linkedpropertyCheck;
      //::function < void(::user::check *) >     m_callbackOnCheck;
      //virtual public ::property_container


      check_property(::property_container * ppropertycontainer, const ::atom & atom) :
         property_link(ppropertycontainer, atom)
      {
      }
      check_property(const check_property & checkproperty) :
         property_link(checkproperty)
      {


      }
      ~check_property()
      {

      }


      // ::e_check get_echeck() const;
      // virtual bool get_bcheck() const;
      ::e_check echeck() const
      {

         return this->get_property().as_echeck();

      }

      bool bcheck() const
      {
         return this->get_property().as_bool();

      }

      bool is_checked() const
      {

         return this->bcheck();

      }

      bool set_check(::e_check echeck, const ::action_context & actioncontext)
      {

         return this->set_property(echeck, actioncontext);

      }
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

   bool toggle_check(const ::action_context & context)
   {

      if(bcheck())
      {

         return set_check(::e_check_unchecked, context);

      }
      else
      {

         return set_check(::e_check_checked, context);

      }

   }

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


//} // namespace user



