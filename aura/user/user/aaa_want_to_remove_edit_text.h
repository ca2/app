#pragma once


namespace user
{


   class CLASS_DECL_AURA get_text :
      virtual public object
   {
   public:

      virtual void _001GetText(string & str) const;

      virtual strsize _001GetTextLength() const;
      virtual void _001GetText(char * psz, strsize len) const;
      virtual void _001GetText(string & str, index iBeg, index iEnd) const;

   };

   class CLASS_DECL_AURA set_text :
      virtual public object
   {
   public:

      virtual void _001SetText(const string & str, const ::action_context & action_context);

      virtual void _001SetText(const char * psz, strsize len, const ::action_context & action_context);


   };


   class CLASS_DECL_AURA edit_text :
      virtual public get_text,
      virtual public set_text
   {
   public:


      virtual void _001GetSel(strsize & iBeg, strsize & iEnd) const;
      virtual void _001SetSel(strsize iBeg, strsize iEnd);
      virtual void _001SetSelEnd(strsize iSelEnd);


      virtual void _001GetSelText(string & str) const;
      virtual void _001SetSelText(const char * psz, const ::action_context & action_context);


      virtual void _001GetViewSel(strsize &iSelStart, strsize &iSelEnd) const;


      virtual void MacroBegin();
      virtual void MacroEnd();


   };


} // namespace user




