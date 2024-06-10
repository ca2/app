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


      virtual void get_text(string & str) const;


      virtual strsize _001GetTextLength() const;
      virtual void get_text(char * psz, strsize len) const;
      virtual void get_text(string & str, ::collection::index iBeg, ::collection::index iEnd) const;


      virtual void set_text(const ::string & str, const ::action_context & action_context);
      virtual void set_text(const ::string & psz, strsize len, const ::action_context & action_context);



      virtual void _001GetSel(strsize & iBeg, strsize & iEnd) const;
      virtual void _001SetSel(strsize iBeg, strsize iEnd);
      virtual void _001SetSelEnd(strsize iSelEnd);


      virtual void get_selection_text(string & str) const;
      virtual void _001SetSelText(const ::string & psz, const ::action_context & action_context);


      virtual void get_impact_selection(strsize &iSelStart, strsize &iSelEnd) const;


      virtual void MacroBegin();
      virtual void MacroEnd();


      inline auto strtext() const { return m_ppropertyText->m_str; }
      inline auto & strtext() { return m_ppropertyText->m_str; }
      inline string as_string() const { return m_ppropertyText->get_string(); }



   };


} // namespace user



