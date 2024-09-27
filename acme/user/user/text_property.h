// Changed by camilo with 
// property* system on 2024-06-06 21:19 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/user/user/property.h"
#include "acme/prototype/prototype/action_context.h"
#include "acme/prototype/data/text_property.h"
#include "acme/prototype/data/property_listener.h"

//#include "acme/prototype/prototype/payload.h"
////#include "acme/prototype/prototype/object.h"


namespace user
{
   
   //struct text_change
   //{
   //   ::data::text_property & m_textproperty;
   //   ::data::property_change & m_propertychange;
   //   auto & payload() {
   //      return m_propertychange.m_payload;
   //   }
   //   auto & action_context() {
   //      return m_propertychange.m_actioncontext;
   //   }
   //};
   //using text_will_change = ::function < bool(text_change & textchange) >;

   //using text_changed = ::function < void(text_change & textchange) >;

   ////using insert_text = ::function< void(::data::text_property & textproperty, const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context & context) >;

   class CLASS_DECL_ACME text_property :
      public ::user::property,
      public ::data::text_property
   {
   protected:


      //::data::property_will_change                          m_propertywillchange;
      //::data::property_changed                              m_propertychanged;


      //::comparable_array < ::user::text_will_change >       m_textwillchangea;
      //::comparable_array < ::user::text_changed >           m_textchangeda;
      ////::comparable_array < insert_text >          m_inserttexta;


      //void unhook_callbacks();
      //void hook_callbacks();


   public:


      //property *     m_ppropertyText;


      text_property(::user::control * pusercontrol, ::data::property_container * ppropertycontainer = nullptr, const ::atom & atom = {});
      ~text_property();

      //void set_text_property(const ::data::text_property & textproperty);


      //::text_property & text() { return m_textproperty; }

      //virtual void get_text(string & str);


      //virtual strsize get_text_length();
      //virtual void get_text(char * psz, strsize len);
      //virtual void get_text(string & str, ::collection::index iBeg, ::collection::index iEnd);


      //virtual void set_text(const ::string & str, const ::action_context & action_context);
      //virtual void set_text(const ::string & psz, strsize len, const ::action_context & action_context);



      //virtual void _001GetSel(strsize & iBeg, strsize & iEnd);
      //virtual void set_text_selection(strsize iBeg, strsize iEnd, const ::action_context & action_context = ::e_source_user);
      //virtual void _001SetSelEnd(strsize iSelEnd, const ::action_context & action_context = ::e_source_user);


      //virtual void get_selection_text(string & str);
      //virtual void set_selection_text(const ::string & psz, const ::action_context & action_context);


      //virtual void get_text_selection(strsize &iSelStart, strsize &iSelEnd);


      //virtual void MacroBegin();
      //virtual void MacroEnd();


      void insert_text(const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context& context);


      //string as_string() const override;
      //virtual string& string_reference();
      ////inline string as_string() const { return m_propertyText->get_string(); }

      
      //virtual bool edit_undo();


      //virtual void get_text_composition_area(::rectangle_i32& rectangle);

      //::comparable_array < ::user::text_will_change > & text_will_change();
      //::comparable_array < ::user::text_changed > & text_changed();

      /*virtual bool on_property_will_change(property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext);
      virtual void on_property_changed(property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext);
      */

      
      
      //bool on_text_will_change(text_change & textchange);
      //void on_text_changed(text_change & textchange);


      bool operator == (const ::data::text_property & textproperty) const;
      bool operator == (const ::data::text_change & change) const;


   };


} // namespace user



