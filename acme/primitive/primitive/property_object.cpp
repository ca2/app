#include "framework.h"


property_object::~property_object()
{

}


//void property_object::assert_valid() const
//{
//
//}


//void property_object::dump(dump_context& context) const
//{
//
//}


//::e_status     property_object::initialize(::object * pobject)
//{
//
//   set_object(pobject);
//
//   return ::success;
//
//}


::e_status property_object::destroy()
{

   auto estatus = ::material_object::destroy();

   m_pmapPropertyRoutine.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

   m_pia.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

   m_ppropertyset.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

   return ::success;

}


void property_object::notify_on_destroy(::property_object * pcontextobjectFinish)
{

   if (has(e_matter_destroying))
   {

      //finish(nullptr);
      destroy();

   }

}


::object * property_object::source_channel()
{

   return nullptr;

}


::e_status property_object::run()
{

   return ::success;

}


class debug_test_reference :
   public property_set
{
public:


   bool & m_bTest1;
   ::string & m_strText1;


   debug_test_reference() :
      m_bTest1(payload_reference(topic("bTest1"))),
      m_strText1(payload_reference(topic("strTest1")))
   {

   }

};

string get_message_text(const ::id & id, bool bWithNumbers);

CLASS_DECL_ACME void debug_debug_reference()
{
   auto message = e_message_create;
#if OSBIT == 64
   wparam wparam = 0x12345678901234;
   lparam lparam = 0x56781234567890;
#else
   wparam wparam = 0x1234567;
   lparam lparam = 0x5678123;
#endif


   {

      string strTitle1 = "Hello ";

      string strTitle2 = "ountries";

      auto xxx = 'C' + strTitle2;

      strTitle1 += xxx;

      printf("%s\n\n", strTitle1.c_str());

   }

   {

      string strTitle1 = "Hello ";

      string strTitle2 = "ountries";

      strTitle1 += 'C' + strTitle2;

      printf("%s\n\n", strTitle1.c_str());

   }

//   {
//
//      string str;
//
//      str.Format("%s wparam=0x%" PRIxPTR " lparam=0x%" PRIxPTR, get_message_text(message, true).c_str(), wparam, lparam);
//
//      output_debug_string(str);
//
//      output_debug_string("-");
//
//   }

//   {
//
//      string str;
//
//      string strMessageText = get_message_text(message, true);
//
//      const char * pszMessageText = strMessageText;
//
//      str.Format("%s %" PRIxPTR " %" PRIxPTR, strMessageText.c_str(), wparam, lparam);
//
//      output_debug_string(str);
//
//      output_debug_string("-");
//
//   }

   debug_test_reference ref;

   ref.m_bTest1 = true;
   ref.m_strText1 = "Text1";

   auto json1 = ref.get_json();

   output_debug_string(json1);

   ref.m_bTest1 = false;
   ref.m_strText1 = ref.get_json();

   auto json2 = ref.get_json();

   output_debug_string(json2);

   output_debug_string("debug_debug_reference end");

   output_debug_string("-");

}
//void property_object::add_trait(::i64 i)
//{
//
//   if (!m_ptraits)
//   {
//
//      m_ptraits = __new(traits);
//
//   }
//
//   m_ptraits->add(i);
//
//}

void property_object::keep_alive()
{

   try
   {

      on_keep_alive();

   }
   catch (...)
   {

   }

}


void property_object::on_keep_alive()
{

}


bool property_object::is_alive()
{

   return true;

}


::e_status property_object::operator()()
{

   ::e_status estatus;

   try
   {

      estatus = run();

   }
   catch (...)
   {

      estatus = ::error_exception;

   }

   return estatus;

}


//::e_status property_object::call(::trait & trait)
//{
//
//   //auto estatus = ::property_object::call(trait);
//
//   //m_cRun++;
//
//   return error_exception;
//
//}


//void property_object::notify(::u64 uId)
//{
//
//   m_uid |= uId;
//
//}


//void property_object::io(stream & s)
//{
//
//
//}
//
//
//stream & property_object::do_property_exchange(stream & stream) const
//{
//
//   ASSERT(stream.is_storing());
//
//   property_set set;
//
//   set += object_storing;
//
//   ((property_object *)this)->exchange(set);
//
//   stream << set;
//
//   return stream;
//
//}
//
//


void property_object::exchange(::stream & stream)
{

   throw ::interface_only_exception();

}


::e_status property_object::handle_exception(const ::exception& e)
{

   return ::success;

}



void property_object::add_exception(const ::exception & e)
{

   m_estatus = error_exception;

   set_fail();

}


void property_object::on_catch_all_exception()
{

   m_estatus = error_catch_all_exception;

   set_fail();

}


stream & property_object::write(::stream & stream) const
{

   ((property_object*)this)->exchange(stream);

   return stream;

}


stream & property_object::read(::stream & stream)
{

   exchange(stream);
   //property_object::read(stream);

   //if (has_flag(object_default_property_exchange))
   //{

   //   do_property_exchange(stream);

   //}

   return stream;

}


routine_array * property_object::routine_array(const ::id & id, bool bCreate)
{

   if (!bCreate)
   {

      auto passociation = m_pmapPropertyRoutine->plookup(id);

      if (::is_null(passociation))
      {

         return nullptr;

      }

      return &passociation->m_element2;

   }

   m_psystem->__defer_construct_new(m_pmapPropertyRoutine);

   return &m_pmapPropertyRoutine->operator[](id);

}


::e_status property_object::add_routine(const ::id & id, const ::routine & routine)
{

   if (!routine)
   {

      return error_invalid_argument;

   }

   auto proutinea = routine_array(id, true);
   
   if (!proutinea)
   {

      return error_resource;

   }
   
   proutinea->add(routine);

   return ::success;

}


//void debug_trait()
//{
//
//
//   auto pimage = __create_image();
//
//
//   //get_system()->imaging().start_traits(get_system()->imaging(), pimage);
//
//}





::property_object * property_object::parent_property_set_holder() const
{

   return nullptr;

}


linked_property property_object::parent_lookup_property(const id & id) const
{

   auto pobject = parent_property_set_holder();

   if (!pobject)
   {

      return nullptr;

   }

   return pobject->on_fetch_property(id);

}


::linked_property property_object::on_fetch_property(const ::id & id) const
{

   auto pproperty = find_property(id);

   if (pproperty)
   {

      return { (property *) pproperty, (property_object *) this };

   }

   //auto ppropertyArray = find_property("property_set_array");

   //__pointer(__pointer_array(property_set)) parray;

   //if (ppropertyArray)
   //{

   //   ppropertyArray->defer_get(parray);

   //   if (parray)
   //   {

   //      for (auto & pset : parray->ptra())
   //      {

   //         pproperty = pset->find(id); // first-level find

   //         if (pproperty)
   //         {

   //            return pproperty;

   //         }

   //      }

   //   }

   //}

   return parent_lookup_property(id);

}


id property_object::translate_property_id(const ::id & id)
{

   auto pparent = parent_property_set_holder();

   if (!pparent)
   {

      return id;

   }

   return pparent->translate_property_id(id);

}

//void property_object::add_property_set(property_set * pset)
//{
//
//   auto * pproperty = find_property("property_set_array");
//
//   auto parray = pproperty->cast < __pointer_array(property_set) >();
//
//   if (!parray)
//   {
//
//      parray = __new(__pointer_array(property_set)());
//
//      *pproperty = parray;
//
//   }
//
//   parray->add(pset);
//
//}


string property_object::property_set_evaluate(const ::string & str) const
{

   return ::papaya::property_set::evaluate(*this, str);

}


string property_object::property_set_get_evaluation(const ::string & str) const
{

   return property_set_get_string(str.c_str() + 1);

}


bool property_object::property_set_get_evaluation(string & strResult, const string& str) const
{

   return property_set_get_string(strResult, str.c_str() + 1);

}

string property_object::property_set_get_string(const ::string & str) const
{

   auto pproperty = on_fetch_property(str);

   if (is_null(pproperty))
   {

      return "";

   }

   return pproperty->string();

}

bool property_object::property_set_get_string(string & strResult, const string& str) const
{

   auto pproperty = on_fetch_property(str);

   if (is_null(pproperty))
   {

      return false;

   }

   strResult = pproperty->string();

   return true;

}


void property_object::property_set_replace(string & str) const
{

   str = property_set_evaluate(str);

}


void property_object::notify_property_changed(property* pproperty, const ::action_context & actioncontext)
{

   on_property_changed(pproperty, actioncontext);

}


void property_object::on_property_changed(property* pproperty, const action_context & actioncontext)
{


}


::linked_property property_object::fetch_property(const ::id & idParam, bool bCreate)
{

   auto id = translate_property_id(idParam);

   if(!id.is_empty())
   {

      auto linkedproperty = on_fetch_property(id);

      if(linkedproperty)
      {

         return linkedproperty;

      }

   }

   if (bCreate)
   {

      return { &get_property_set().get_property(id), this };

   }

   return nullptr;

}

//
//string property_object::property_set_get_evaluation(const ::string & str) const
//{
//
//   return property_set_get_string(str.c_str() + 1);
//
//}
//
//
//string property_object::property_set_evaluate(const ::string & strParam) const
//{
//
//   return ::lemon::property_set::evaluate(*this, strParam);
//
//}
//
//
//
//string property_object::property_set_get_string(const ::string & str) const
//{
//
//   auto pproperty = on_fetch_property(str);
//
//   if (is_null(pproperty))
//   {
//
//      return "";
//
//   }
//
//   return pproperty->string();
//
//}


string property_object::get_text(const ::payload & payload, const ::id & id)
{

   if (payload.has_property(id) && payload[id].has_char())
   {

      return payload[id];

   }

   return payload.string();

}


::extended::status property_object::run_property(const ::id& id)
{

   auto pproperty = find_property(id);

   if (!pproperty)
   {

      return error_not_found;

   }

   return pproperty->run();

}


//void property_object::to_string(const class string_exchange & str) const
//{
//
//   str = typeid(*this).name();
//
//}


//strsize property_object::sz_len() const
//{
//
//   string str;
//
//   to_string(str);
//
//   return str.get_length();
//
//}
//
//
//void property_object::to_sz(char * sz, strsize len) const
//{
//
//   string str;
//
//   to_string(str);
//
//   strncpy(sz, str, len);
//
//}



