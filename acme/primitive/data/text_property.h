#pragma once


//#include "acme/primitive/geometry2d/_geometry2d.h"
//#include "acme_context.h
#include "property_link.h"
//#include "acme/primitive/primitive/payload.h"
////#include "acme/primitive/primitive/object.h"


//namespace user
//{


class text_property :
   public ::property_link
{
public:


   //linked_property   m_linkedpropertyCheck;
   //::function < void(::user::check *) >     m_callbackOnCheck;
   //virtual public ::property_container


   text_property(::property_container * ppropertycontainer, const ::atom & atom) :
      property_link(ppropertycontainer, atom)
   {
   }
   text_property(const text_property & checkproperty) :
         property_link(checkproperty)
   {


   }
   ~text_property()
   {

   }

/*
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
      //virtual string& string_reference();
      //inline string as_string() const { return m_propertyText->get_string(); }


      virtual bool edit_undo();


      //virtual void get_text_composition_area(::rectangle_i32& rectangle);
*/
   ::string text() const { return this->get_property({ID_TEXT}).as_string(); }
   ::strsize selection_begin() const { return this->get_property({ID_TEXT_SELECTION_BEGIN}).as_iptr(); }
   ::strsize selection_end() const { return this->get_property({ID_TEXT_SELECTION_END}).as_iptr(); }


   void    get_text(string & str)
   {


         str = this->text();

   }


   bool set_selection_text(const ::scoped_string & scopedstrNewSelectionText, const ::action_context & actioncontext)
   {

      auto strText = this->text();

      strsize iBegin;

      strsize iEnd;

      this->get_selection(iBegin, iEnd);

      auto strLeft = strText(0, iBegin);

      auto strRight = strText(iEnd);

      if(!set_text(strLeft + scopedstrNewSelectionText + strRight, actioncontext))
      {

         return false;

      }

      set_selection_end(iBegin + scopedstrNewSelectionText.size(), actioncontext);

   }


   bool set_text(const ::scoped_string & scopedstrText, const ::action_context & actioncontext)
   {

      return set_property({ID_TEXT}, scopedstrText, actioncontext);

   }


   strsize get_size() const
   {

      return this->text().size();

   }


   void get_text(char * psz, strsize len)
   {

      auto strText = this->text();

      ansi_count_copy(psz,strText,len);

   }


   void get_text(string & str, strsize iBeg, strsize iEnd) const
   {

      auto strText = this->text();

      __sort(iBeg, iEnd);

      str = strText(iBeg, iEnd - iBeg);

   }


   void set_text(const ::scoped_string & scopedstrText, strsize iLen, const ::action_context & actioncontext)
   {

      set_text(scopedstrText(0, iLen),actioncontext);

   }


   void get_selection(strsize & iBegin, strsize & iEnd) const
   {

      iBegin = selection_begin();

      iEnd = selection_end();

   }


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


   void set_selection(strsize iBegin, strsize iEnd, const ::action_context & actioncontext)
   {

      set_selection_begin(iBegin, actioncontext);

      set_selection_end(iEnd, actioncontext);

   }

/*
   void _001SetSel(strsize iBeg, strsize iEnd, const ::action_context & action_context)
   {

      __UNREFERENCED_PARAMETER(iBeg);
      __UNREFERENCED_PARAMETER(iEnd);
      __UNREFERENCED_PARAMETER(action_context);

   }


   void text::_001GetImpactSel(strsize & iBeg, strsize & iEnd)
   {

      __UNREFERENCED_PARAMETER(iBeg);
      __UNREFERENCED_PARAMETER(iEnd);

   }
*/

   void set_selection_begin(strsize iBegin, const ::action_context & actioncontext)
   {

      set_property({ID_TEXT_SELECTION_BEGIN}, iBegin, actioncontext);

   }


   void set_selection_end(strsize iEnd, const ::action_context & actioncontext)
   {

      set_property({ID_TEXT_SELECTION_END}, iEnd, actioncontext);

   }


   void get_selection_text(::string & str) const
   {

      ::strsize iBegin;

      ::strsize iEnd;

      get_selection(iBegin, iEnd);

      get_text(str, iBegin, iEnd);

   }

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
   };


//} // namespace user



