// Changed by camilo with 
// property* system on 2024-06-06 21:19 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/primitive/geometry2d/_geometry2d.h"
#include "control.h"
#include "acme/primitive/primitive/action_context.h"
#include "acme/primitive/data/text_property.h"
#include "acme/primitive/data/property_listener.h"

//#include "acme/primitive/primitive/payload.h"
////#include "acme/primitive/primitive/object.h"


namespace user
{
   
   using text_will_change_function = ::function < bool(::text_property & checkproperty, const ::payload &, const ::action_context &) >;

   using text_changed_function = ::function < void(::text_property & checkproperty, const ::payload &, const ::action_context &) >;


   class CLASS_DECL_ACME text_control :
      virtual public ::user::control
   {
   protected:
      text_property      m_textproperty;

   public:
      ::comparable_array < text_will_change_function >     m_textwillchangea;
      ::comparable_array < text_changed_function >         m_textchangeda;


      //property *     m_ppropertyText;


      text_control();
      ~text_control() override;

      void set_text_property(const text_property & textproperty);


       ::text_property & text() { return m_textproperty; }

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


      //string as_string() const override;
      //virtual string& string_reference();
      ////inline string as_string() const { return m_propertyText->get_string(); }

      
      virtual bool edit_undo();


      virtual void get_text_composition_area(::rectangle_i32& rectangle);


   };


} // namespace user



