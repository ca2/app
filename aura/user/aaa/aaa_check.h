#pragma once


namespace user
{


   class CLASS_DECL_AURA check :
      virtual public object
   {
   public:


      property *     m_ppropertyCheck;


      check();
      virtual ~check();

      inline ::enum_check get_echeck() const { return ::is_null(m_ppropertyCheck) ? enum_check::e_check_undefined : m_ppropertyCheck->m_echeck; }
      inline bool get_bcheck() const { return ::is_null(m_ppropertyCheck) ? false : m_ppropertyCheck->operator bool(); }
      inline ::enum_check echeck() const { return m_ppropertyCheck->m_echeck; }
      inline ::enum_check & echeck() { return m_ppropertyCheck->m_echeck; }
      inline bool bcheck() const { return m_ppropertyCheck->operator bool(); }
      inline bool is_checked() const { return bcheck(); }
      virtual void set_check(bool b, const ::action_context & action_context);
      virtual void set_check(::enum_check check, const ::action_context & action_context);
      virtual void toggle_check(const ::action_context & action_context);



   };


} // namespace user



