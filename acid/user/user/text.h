#pragma once


//#include "acid/primitive/geometry2d/_geometry2d.h"
#include "acid/primitive/primitive/action_context.h"
//#include "acid/primitive/primitive/payload.h"
////#include "acid/primitive/primitive/object.h"


namespace user
{


   class CLASS_DECL_ACID text :
      virtual public ::object
   {
   public:


      //property *     m_ppropertyText;
      linked_property      m_linkedpropertyText;


      text();
      ~text() override;


      virtual void _001GetText(string & str);


      virtual strsize _001GetTextLength();
      virtual void _001GetText(char * psz, strsize len);
      virtual void _001GetText(string & str, ::collection::index iBeg, ::collection::index iEnd);


      virtual void _001SetText(const ::string & str, const ::action_context & action_context);
      virtual void _001SetText(const ::string & psz, strsize len, const ::action_context & action_context);



      virtual void _001GetSel(strsize & iBeg, strsize & iEnd);
      virtual void _001SetSel(strsize iBeg, strsize iEnd, const ::action_context & action_context = ::e_source_user);
      virtual void _001SetSelEnd(strsize iSelEnd, const ::action_context & action_context = ::e_source_user);


      virtual void _001GetSelText(string & str);
      virtual void _001SetSelText(const ::string & psz, const ::action_context & action_context);


      virtual void _001GetImpactSel(strsize &iSelStart, strsize &iSelEnd);


      virtual void MacroBegin();
      virtual void MacroEnd();


      virtual void insert_text(string str, bool bForceNewStep, const ::action_context& context);


      string as_string() const override;
      virtual string& string_reference();
      //inline string as_string() const { return m_propertyText->get_string(); }

      
      virtual bool edit_undo();


      virtual void get_text_composition_area(::rectangle_i32& rectangle);


   };


} // namespace user



