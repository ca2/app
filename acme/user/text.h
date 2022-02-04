#pragma once


namespace user
{


   class CLASS_DECL_ACME text :
      virtual public object
   {
   public:


      //property *     m_ppropertyText;
      linked_property      m_propertyText;


      text();
      ~text() override;


      virtual void _001GetText(string & str) const;


      virtual strsize _001GetTextLength() const;
      virtual void _001GetText(char * psz, strsize len) const;
      virtual void _001GetText(string & str, index iBeg, index iEnd) const;


      virtual void _001SetText(const ::string & str, const ::action_context & action_context);
      virtual void _001SetText(const ::string & psz, strsize len, const ::action_context & action_context);



      virtual void _001GetSel(strsize & iBeg, strsize & iEnd) const;
      virtual void _001SetSel(strsize iBeg, strsize iEnd, const ::action_context & action_context = ::e_source_user);
      virtual void _001SetSelEnd(strsize iSelEnd);


      virtual void _001GetSelText(string & str) const;
      virtual void _001SetSelText(const ::string & psz, const ::action_context & action_context);


      virtual void _001GetImpactSel(strsize &iSelStart, strsize &iSelEnd) const;


      virtual void MacroBegin();
      virtual void MacroEnd();


      virtual void insert_text(string str, bool bForceNewStep, const ::action_context& context);


      inline string strtext() const { return m_propertyText->string(); }
      inline string & as_strtext() { return m_propertyText->as_string(); }
      //inline string as_string() const { return m_propertyText->get_string(); }

      
      virtual bool edit_undo();


      virtual void get_text_composition_area(::rectangle_i32& rectangle);


   };


} // namespace user



