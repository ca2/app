#pragma once


namespace user
{


   class CLASS_DECL_AURA text :
      virtual public object
   {
   public:


      property *     m_ppropertyText;


      text();
      virtual ~text();


      virtual void _001GetText(string & str) const;


      virtual strsize _001GetTextLength() const;
      virtual void _001GetText(char * psz, strsize len) const;
      virtual void _001GetText(string & str, index iBeg, index iEnd) const;


      virtual void _001SetText(const ::string & str, const ::action_context & action_context);
      virtual void _001SetText(const ::string & psz, strsize len, const ::action_context & action_context);



      virtual void _001GetSel(strsize & iBeg, strsize & iEnd) const;
      virtual void _001SetSel(strsize iBeg, strsize iEnd);
      virtual void _001SetSelEnd(strsize iSelEnd);


      virtual void _001GetSelText(string & str) const;
      virtual void _001SetSelText(const ::string & psz, const ::action_context & action_context);


      virtual void _001GetViewSel(strsize &iSelStart, strsize &iSelEnd) const;


      virtual void MacroBegin();
      virtual void MacroEnd();


      inline auto strtext() const { return m_ppropertyText->m_str; }
      inline auto & strtext() { return m_ppropertyText->m_str; }
      inline string as_string() const { return m_ppropertyText->get_string(); }



   };


} // namespace user



