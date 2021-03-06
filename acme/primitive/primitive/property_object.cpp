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


::e_status property_object::finalize()
{

   ::material_object::finalize();

   //m_pobject.release(OBJ_REF_DBG_THIS);

   m_pia.release(OBJ_REF_DBG_THIS);

   m_pset.release(OBJ_REF_DBG_THIS);

   return ::success;

}


//::property_object * property_object::_get_context_object()
//{
//
//   return this;
//
//}


void property_object::notify_on_finish(::property_object * pcontextobjectFinish)
{

   if (m_bFinishing)
   {

      //finish(nullptr);
      finish();

   }

}


//void property_object::set_object(::object * pobject  OBJ_REF_DBG_COMMA_PARAMS_DEF)
//{
//
//   m_pobject.reset(pobject OBJ_REF_DBG_COMMA_ARGS);
//
//}


//::e_status property_object::finish(::property_object * pcontextobjectFinish)
::e_status property_object::finish()
{

   //return ::matter::finish(pcontextobjectFinish);

   auto estatus = ::material_object::finish();

   return estatus;

}


::e_status property_object::on_finish()
{

   auto estatus = material_object::on_finish();

   return estatus;

   //synchronous_lock synchronouslock(mutex());

   //if (m_pnotifya)
   //{

   //   auto pnotifya = m_pnotifya;

   //   restart_notifya_loop:

   //   for (auto pmatter : *pnotifya)
   //   {

   //      if (pmatter && pmatter->m_bFinishing)
   //      {

   //         synchronouslock.unlock();

   //         sleep(10_ms);

   //         auto estatus = pmatter->finish();

   //         if (estatus == ::success)
   //         {

   //            synchronouslock.lock();

   //            pnotifya->erase(pmatter);

   //            goto restart_notifya_loop;

   //         }

   //         synchronouslock.lock();

   //      }

   //   }

   //}
   
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
      m_bTest1(topic("bTest1")),
      m_strText1(topic("strTest1"))
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

   __throw(error_interface_only);

}


::e_status property_object::handle_exception(const ::exception::exception& e)
{

   return ::success;

}



void property_object::add_exception(const ::exception::exception & e)
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


string property_object::property_set_evaluate(const string & str) const
{

   return ::papaya::property_set::evaluate(*this, str);

}


string property_object::property_set_get_evaluation(const string & str) const
{

   return property_set_get_string(str.c_str() + 1);

}


bool property_object::property_set_get_evaluation(string & strResult, const string& str) const
{

   return property_set_get_string(strResult, str.c_str() + 1);

}

string property_object::property_set_get_string(const string & str) const
{

   auto pproperty = on_fetch_property(str);

   if (is_null(pproperty))
   {

      return "";

   }

   return pproperty->get_string();

}

bool property_object::property_set_get_string(string & strResult, const string& str) const
{

   auto pproperty = on_fetch_property(str);

   if (is_null(pproperty))
   {

      return false;

   }

   strResult = pproperty->get_string();

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
//string property_object::property_set_get_evaluation(const string & str) const
//{
//
//   return property_set_get_string(str.c_str() + 1);
//
//}
//
//
//string property_object::property_set_evaluate(const string & strParam) const
//{
//
//   return ::lemon::property_set::evaluate(*this, strParam);
//
//}
//
//
//
//string property_object::property_set_get_string(const string & str) const
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
//   return pproperty->get_string();
//
//}


string property_object::get_text(const ::payload & payload, const ::id & id)
{

   if (payload.has_property(id) && payload[id].has_char())
   {

      return payload[id];

   }

   return payload.get_string();

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



