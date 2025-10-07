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


      virtual character_count get_text_length() const;
      virtual void get_text(char * psz, character_count len) const;
      virtual void get_text(string & str, ::collection::index iBeg, ::collection::index iEnd) const;


      virtual void set_text(const ::scoped_string & scopedstr, const ::action_context & action_context);
      virtual void set_text(const ::scoped_string & scopedstr, character_count len, const ::action_context & action_context);



      virtual void _001GetSel(character_count & iBeg, character_count & iEnd) const;
      virtual void set_text_selection(character_count iBeg, character_count iEnd);
      virtual void _001SetSelEnd(character_count iSelEnd);


      virtual void get_selection_text(string & str) const;
      virtual void set_selection_text(const ::scoped_string & scopedstr, const ::action_context & action_context);


      virtual void get_text_selection(character_count &iSelStart, character_count &iSelEnd) const;


      virtual void MacroBegin();
      virtual void MacroEnd();


      inline auto strtext() const { return m_ppropertyText->m_str; }
      inline auto & strtext() { return m_ppropertyText->m_str; }
      inline string as_string() const { return m_ppropertyText->get_string(); }



   };


} // namespace user



