#pragma once


namespace user
{


   class CLASS_DECL_APEX check :
      virtual public object
   {
   public:


      linked_property   m_propertyCheck;


      check();
      virtual ~check();

      inline ::enum_check get_echeck() const { return !m_propertyCheck ? enum_check::check_undefined : m_propertyCheck->m_echeck; }
      inline bool get_bcheck() const { return !m_propertyCheck ? false : m_propertyCheck->get_bool(); }
      inline ::enum_check echeck() const { return m_propertyCheck->m_echeck; }
      inline ::enum_check & echeck() { return m_propertyCheck->m_echeck; }
      inline bool bcheck() const { return m_propertyCheck->get_bool(); }
      inline bool is_checked() const { return bcheck(); }
      virtual void _001SetCheck(bool b, const ::action_context & action_context);
      virtual void _001SetCheck(::enum_check check, const ::action_context & action_context);
      virtual void _001ToggleCheck(const ::action_context & action_context);



   };


} // namespace user



