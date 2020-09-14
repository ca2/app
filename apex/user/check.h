#pragma once


namespace user
{


   class CLASS_DECL_APEX check :
      virtual public object
   {
   public:


      property *     m_ppropertyCheck;


      check();
      virtual ~check();

      inline ::enum_check get_echeck() const { return ::is_null(m_ppropertyCheck) ? enum_check::check_undefined : m_ppropertyCheck->m_echeck; }
      inline bool get_bcheck() const { return ::is_null(m_ppropertyCheck) ? false : m_ppropertyCheck->operator bool(); }
      inline ::enum_check echeck() const { return m_ppropertyCheck->m_echeck; }
      inline ::enum_check & echeck() { return m_ppropertyCheck->m_echeck; }
      inline bool bcheck() const { return m_ppropertyCheck->operator bool(); }
      inline bool is_checked() const { return bcheck(); }
      virtual void _001SetCheck(bool b, const ::action_context & action_context);
      virtual void _001SetCheck(::enum_check check, const ::action_context & action_context);
      virtual void _001ToggleCheck(const ::action_context & action_context);



   };


} // namespace user



