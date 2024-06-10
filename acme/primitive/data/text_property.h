// Creating by camilo with 
// property* system on 2024-06-06 21:20 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/primitive/geometry2d/_geometry2d.h"
//#include "acme_context.h
#include "acme/primitive/data/property.h"
#include "acme/primitive/primitive/action_context.h"
////#include "acme/primitive/primitive/object.h"

struct payload_action_context
{


   ::payload            m_payload;
   ::action_context     m_actioncontext;

};

namespace data
{


   class CLASS_DECL_ACME text_property :
      public ::data::property
   {
   public:


      //linked_property   m_linkedpropertyCheck;
      //::function < void(::user::check *) >     m_callbackOnCheck;
      //virtual public ::property_container


      text_property(::data::property_container * ppropertycontainer = nullptr, const ::atom & atom = {});
      text_property(const text_property & textproperty);
      ~text_property();
      /*
            virtual void get_text(string & str);


            virtual strsize _001GetTextLength();
            virtual void get_text(char * psz, strsize len);
            virtual void get_text(string & str, ::collection::index iBeg, ::collection::index iEnd);


            virtual void set_text(const ::string & str, const ::action_context & action_context);
            virtual void set_text(const ::string & psz, strsize len, const ::action_context & action_context);



            virtual void _001GetSel(strsize & iBeg, strsize & iEnd);
            virtual void set_text_selection(strsize iBeg, strsize iEnd, const ::action_context & action_context = ::e_source_user);
            virtual void _001SetSelEnd(strsize iSelEnd, const ::action_context & action_context = ::e_source_user);


            virtual void get_selection_text(string & str);
            virtual void _001SetSelText(const ::string & psz, const ::action_context & action_context);


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


   };


} // namespace data



