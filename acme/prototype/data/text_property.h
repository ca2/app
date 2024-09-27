// Creating by camilo with 
// property* system on 2024-06-06 21:20 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
//#include "acme_context.h
#include "acme/prototype/data/property.h"
#include "acme/prototype/prototype/action_context.h"
////#include "acme/prototype/prototype/object.h"

struct payload_action_context
{

   ::payload            m_payload;
   ::action_context     m_actioncontext;

};


namespace data
{
   
   class text_property;

   struct text_change
   {
      ::data::text_property & m_textproperty;
      ::data::property_change & m_propertychange;
      auto & payload() {
         return m_propertychange.m_payload;
      }
      auto & action_context() {
         return m_propertychange.m_actioncontext;
      }
   };
   using text_will_change = ::function < bool(text_change & textchange) >;

   using text_changed = ::function < void(text_change & textchange) >;

   ////using insert_text = ::function< void(::data::text_property & textproperty, const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context & context) >;

   class CLASS_DECL_ACME text_property :
      public ::data::property
   {


   protected:


      ::data::property_will_change                          m_propertywillchange;
      ::data::property_changed                              m_propertychanged;


      ::comparable_array < ::data::text_will_change >       m_textwillchangea;
      ::comparable_array < ::data::text_changed >           m_textchangeda;
      //::comparable_array < insert_text >          m_inserttexta;


      void unhook_callbacks();
      void hook_callbacks();


   public:


      text_property(::data::property_container * ppropertycontainer = nullptr, const ::atom & atom = {});
      text_property(const ::data::property & property);
      ~text_property();
      //property *     m_ppropertyText;


      //text_prophandler(::data::property_container * ppropertycontainer = nullptr, const ::atom & atom = {});
      //~text_handler();


      void set_text_property(const ::data::text_property & textproperty);


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


      void insert_text(const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context & actioncontext);


      //string as_string() const override;
      //virtual string& string_reference();
      ////inline string as_string() const { return m_propertyText->get_string(); }


      //virtual bool edit_undo();


      //virtual void get_text_composition_area(::rectangle_i32& rectangle);

      ::comparable_array < ::data::text_will_change > & text_will_change();
      ::comparable_array < ::data::text_changed > & text_changed();

      /*virtual bool on_property_will_change(property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext);
      virtual void on_property_changed(property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext);
      */



      bool on_text_will_change(text_change & textchange);
      void on_text_changed(text_change & textchange);

   //public:


      //linked_property   m_linkedpropertyCheck;
      //::function < void(::user::check *) >     m_callbackOnCheck;
      //virtual public ::property_container


      /*
            virtual void get_text(string & str);


            virtual strsize get_text_length();
            virtual void get_text(char * psz, strsize len);
            virtual void get_text(string & str, ::collection::index iBeg, ::collection::index iEnd);


            virtual void set_text(const ::string & str, const ::action_context & action_context);
            virtual void set_text(const ::string & psz, strsize len, const ::action_context & action_context);



            virtual void _001GetSel(strsize & iBeg, strsize & iEnd);
            virtual void set_text_selection(strsize iBeg, strsize iEnd, const ::action_context & action_context = ::e_source_user);
            virtual void _001SetSelEnd(strsize iSelEnd, const ::action_context & action_context = ::e_source_user);


            virtual void get_selection_text(string & str);
            virtual void set_selection_text(const ::string & psz, const ::action_context & action_context);


            virtual void get_text_selection(strsize &iSelStart, strsize &iSelEnd);


            virtual void MacroBegin();
            virtual void MacroEnd();


            virtual void insert_text(string str, bool bForceNewStep, const ::action_context& context);


            string as_string() const override;
            //virtual string& string_reference();
            //inline string as_string() const { return m_propertyText->get_string(); }


            virtual bool edit_undo();


            //virtual void get_text_composition_area(::rectangle_i32& rectangle);
      */

      ::string as_text() const;
      ::strsize selection_begin() const;
      ::strsize selection_end() const;


      bool set_selection_text(const ::scoped_string & scopedstrNewSelectionText, const ::action_context & actioncontext);

      bool set_text(const ::scoped_string & scopedstrText, const ::action_context & actioncontext);

      strsize get_size() const;

      void get_text(char * psz, strsize len);


      void get_text(::string & str) const;

      void get_text(::string & str, strsize iBeg, strsize iEnd = -1) const;


      void set_text(const ::scoped_string & scopedstrText, strsize iLen, const ::action_context & actioncontext);

      text_property & operator = (const payload_action_context & payloadactioncontext);

      void get_selection(strsize & iBegin, strsize & iEnd) const;


      // strsize selection_begin() const
      // {
      //
      //    ::strsize iBegin;
      //
      //    ::strsize iEnd;
      //
      //    get_selection(iBegin, iEnd);
      //
      //    return iBegin;
      //
      // }


      // strsize selection_end() const
      // {
      //
      //    ::strsize iBegin;
      //
      //    ::strsize iEnd;
      //
      //    get_selection(iBegin, iEnd);
      //
      //    return iEnd;
      //
      // }


      void set_selection(strsize iBegin, strsize iEnd, const ::action_context & actioncontext);

      /*
         void set_text_selection(strsize iBeg, strsize iEnd, const ::action_context & action_context)
         {

            __UNREFERENCED_PARAMETER(iBeg);
            __UNREFERENCED_PARAMETER(iEnd);
            __UNREFERENCED_PARAMETER(action_context);

         }


         void text::get_text_selection(strsize & iBeg, strsize & iEnd)
         {

            __UNREFERENCED_PARAMETER(iBeg);
            __UNREFERENCED_PARAMETER(iEnd);

         }
      */

      void set_selection_begin(strsize iBegin, const ::action_context & actioncontext);

      void set_selection_end(strsize iEnd, const ::action_context & actioncontext);
      ::string get_selection_text() const;

      /*
         void text::MacroBegin()
         {

         }


         void text::MacroEnd()
         {

         }


         void text::insert_text(string str, bool bForceNewStep, const ::action_context& context)
         {


         }
      */
      /*
         string as_string() const
         {

            return get_property().as_string();

         }
      */
      /*
         string& text::string_reference()
         {

            return m_linkedpropertyText->string_reference();

         }



         bool text::edit_undo()
         {

            return false;

         }


         void text::get_text_composition_area(::rectangle_i32& rectangle)
         {


         }

      */

      bool operator == (const text_property & textproperty) const;
      bool operator == (const text_change & change) const;


   };


} // namespace data



