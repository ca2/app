#pragma once


//#include "acme/primitive/primitive/payload.h"
////#include "acme/primitive/primitive/object.h"


namespace user
{


   class CLASS_DECL_ACME check :
      virtual public ::object
   {
   public:


      linked_property   m_linkedpropertyCheck;
      ::function < void(::user::check *) >     m_callbackOnCheck;



      check();
      ~check() override;

      inline ::e_check get_echeck() const { return !m_linkedpropertyCheck ? (::e_check) enum_check::e_check_undefined : m_linkedpropertyCheck->echeck(); }
      inline bool get_bcheck() const { return !m_linkedpropertyCheck ? false : m_linkedpropertyCheck->get_bool(); }
      inline ::e_check echeck() const { return m_linkedpropertyCheck->echeck(); }
      inline ::e_check & echeck() { return m_linkedpropertyCheck->e_check_reference(); }
      inline bool bcheck() const { return m_linkedpropertyCheck->get_bool(); }
      inline bool is_checked() const { return bcheck(); }
      virtual void _001SetCheck(const ::e_check & check, const ::action_context & action_context);
      virtual void _001ToggleCheck(const ::action_context & action_context);

      
      virtual void on_check_change();


   };


} // namespace user



