// Changed by camilo with 
// property* system on 2024-06-06 21:19 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/primitive/geometry2d/_geometry2d.h"
#include "acme/user/user/property.h"
#include "acme/primitive/primitive/action_context.h"
#include "acme/primitive/data/text_property.h"
#include "acme/primitive/data/property_listener.h"

//#include "acme/primitive/primitive/payload.h"
////#include "acme/primitive/primitive/object.h"


namespace user
{
   
   using text_will_change = ::function < bool(::data::text_property & textproperty, const ::payload &, const ::action_context &) >;

   using text_changed = ::function < void(::data::text_property & textproperty, const ::payload &, const ::action_context &) >;

   //using insert_text = ::function< void(::data::text_property & textproperty, const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context & context) >;

   class CLASS_DECL_ACME text_property :
      public ::user::property,
      public ::data::text_property
   {
   protected:


      ::data::property_will_change                          m_propertywillchange;
      ::data::property_changed                              m_propertychanged;


      ::comparable_array < ::user::text_will_change >       m_textwillchangea;
      ::comparable_array < ::user::text_changed >           m_textchangeda;
      //::comparable_array < insert_text >          m_inserttexta;


      void unhook_callbacks();
      void hook_callbacks();


   public:


      //property *     m_ppropertyText;


      text_property(::user::control * pusercontrol, ::data::property_container * ppropertycontainer = nullptr, const ::atom & atom = {});
      ~text_property();

      void set_text_property(const ::data::text_property & textproperty);


      //::text_property & text() { return m_textproperty; }

      //virtual void get_text(string & str);


      //virtual strsize _001GetTextLength();
      //virtual void get_text(char * psz, strsize len);
      //virtual void get_text(string & str, ::collection::index iBeg, ::collection::index iEnd);


      //virtual void set_text(const ::string & str, const ::action_context & action_context);
      //virtual void set_text(const ::string & psz, strsize len, const ::action_context & action_context);



      //virtual void _001GetSel(strsize & iBeg, strsize & iEnd);
      //virtual void _001SetSel(strsize iBeg, strsize iEnd, const ::action_context & action_context = ::e_source_user);
      //virtual void _001SetSelEnd(strsize iSelEnd, const ::action_context & action_context = ::e_source_user);


      //virtual void get_selection_text(string & str);
      //virtual void _001SetSelText(const ::string & psz, const ::action_context & action_context);


      //virtual void get_text_selection(strsize &iSelStart, strsize &iSelEnd);


      //virtual void MacroBegin();
      //virtual void MacroEnd();


      void insert_text(const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context& context);


      //string as_string() const override;
      //virtual string& string_reference();
      ////inline string as_string() const { return m_propertyText->get_string(); }

      
      //virtual bool edit_undo();


      //virtual void get_text_composition_area(::rectangle_i32& rectangle);

      ::comparable_array < ::user::text_will_change > & text_will_change();
      ::comparable_array < ::user::text_changed > & text_changed();

      /*virtual bool on_property_will_change(property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext);
      virtual void on_property_changed(property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext);
      */

      
      
      bool on_text_will_change(::data::text_property & textproperty, const ::payload & payload, const ::action_context & actioncontext);
      void on_text_changed(::data::text_property & textproperty, const ::payload & payload, const ::action_context & actioncontext);


   };


} // namespace user



