#include "framework.h"


context_object::~context_object()
{

}


void context_object::assert_valid() const
{

}


void context_object::dump(dump_context& context) const
{

}


::estatus     context_object::initialize(::layered * pobjectContext)
{

   set_context_object(pobjectContext);

   return ::success;

}


void context_object::finalize()
{

   ::layered::finalize();

   m_pobjectContext.release(OBJ_REF_DBG_THIS);

   m_pia.release(OBJ_REF_DBG_THIS);

   m_pset.release(OBJ_REF_DBG_THIS);

}


void context_object::set_context_object(::layered * pobjectContext  OBJ_REF_DBG_COMMA_PARAMS_DEF)
{

   m_pobjectContext.reset(pobjectContext OBJ_REF_DBG_COMMA_ARGS);

}


void context_object::set_finish()
{

   finalize();

}


::object * context_object::source_channel()
{

   return nullptr;

}




::estatus context_object::run()
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

string get_message_text(UINT message, bool bWithNumbers);

CLASS_DECL_ACME void debug_debug_reference()
{
   auto message = WM_CREATE;
#if OSBIT == 64
   WPARAM wparam = 0x12345678901234;
   LPARAM lparam = 0x56781234567890;
#else
   WPARAM wparam = 0x1234567;
   LPARAM lparam = 0x5678123;
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
//void context_object::add_trait(::i64 i)
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

void context_object::keep_alive()
{

   try
   {

      on_keep_alive();

   }
   catch (...)
   {

   }

}


void context_object::on_keep_alive()
{

}


bool context_object::is_alive()
{

   return true;

}


::estatus context_object::call()
{

   ::estatus estatus;

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


//::estatus context_object::call(::trait & trait)
//{
//
//   //auto estatus = ::context_object::call(trait);
//
//   //m_cRun++;
//
//   return error_exception;
//
//}


//void context_object::notify(::u64 uId)
//{
//
//   m_uid |= uId;
//
//}


//void context_object::io(stream & s)
//{
//
//
//}
//
//
//stream & context_object::do_property_exchange(stream & stream) const
//{
//
//   ASSERT(stream.is_storing());
//
//   property_set set;
//
//   set += object_storing;
//
//   ((context_object *)this)->exchange(set);
//
//   stream << set;
//
//   return stream;
//
//}
//
//


void context_object::exchange(::stream & stream)
{

   __throw(interface_only_exception());

}


void context_object::add_exception(::exception::exception * pexception)
{

   m_estatus = error_exception;

   set_fail();

}


void context_object::on_catch_all_exception()
{

   m_estatus = error_catch_all_exception;

   set_fail();

}


stream & context_object::write(::stream & stream) const
{

   ((context_object*)this)->exchange(stream);

   return stream;

}


stream & context_object::read(::stream & stream)
{

   exchange(stream);
   //context_object::read(stream);

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
//   //System.imaging().start_traits(System.imaging(), pimage);
//
//}





::context_object * context_object::parent_property_set_holder() const
{

   return nullptr;

}


property * context_object::parent_lookup_property(const id & id) const
{

   auto pobject = parent_property_set_holder();

   if (!pobject)
   {

      return nullptr;

   }

   return pobject->on_fetch_property(id);

}


property * context_object::on_fetch_property(const ::id & id) const
{

   auto pproperty = find_property(id);

   if (pproperty)
   {

      return pproperty;

   }

   auto ppropertyArray = find_property("property_set_array");

   __pointer(__pointer_array(property_set)) parray;

   if (ppropertyArray)
   {

      ppropertyArray->defer_get(parray);

      if (parray)
      {

         for (auto & pset : parray->ptra())
         {

            pproperty = pset->find(id); // first-level find

            if (pproperty)
            {

               return pproperty;

            }

         }

      }

   }

   return parent_lookup_property(id);

}


id context_object::translate_property_id(const ::id & id)
{

   auto pparent = parent_property_set_holder();

   if (!pparent)
   {

      return id;

   }

   return pparent->translate_property_id(id);

}

void context_object::add_property_set(property_set * pset)
{

   auto * pproperty = find_property("property_set_array");

   auto parray = pproperty->cast < __pointer_array(property_set) >();

   if (!parray)
   {

      parray = __new(__pointer_array(property_set)());

      *pproperty = parray;

   }

   parray->add(pset);

}


string context_object::property_set_evaluate(const string & str) const
{

   return ::papaya::property_set::evaluate(*this, str);

}


string context_object::property_set_get_evaluation(const string & str) const
{

   return property_set_get_string(str.c_str() + 1);

}


bool context_object::property_set_get_evaluation(string & strResult, const string& str) const
{

   return property_set_get_string(strResult, str.c_str() + 1);

}

string context_object::property_set_get_string(const string & str) const
{

   auto pproperty = on_fetch_property(str);

   if (is_null(pproperty))
   {

      return "";

   }

   return pproperty->get_string();

}

bool context_object::property_set_get_string(string & strResult, const string& str) const
{

   auto pproperty = on_fetch_property(str);

   if (is_null(pproperty))
   {

      return false;

   }

   strResult = pproperty->get_string();

   return true;

}


void context_object::property_set_replace(string & str) const
{

   str = property_set_evaluate(str);

}


property * context_object::fetch_property(const ::id & idParam, bool bCreate)
{

   auto id = translate_property_id(idParam);

   if(!id.is_empty())
   {

      auto pproperty = on_fetch_property(id);

      if(pproperty)
      {

         return pproperty;

      }

   }

   if (bCreate)
   {

      return &get_property_set().get_property(id);

   }

   return nullptr;

}

//
//string context_object::property_set_get_evaluation(const string & str) const
//{
//
//   return property_set_get_string(str.c_str() + 1);
//
//}
//
//
//string context_object::property_set_evaluate(const string & strParam) const
//{
//
//   return ::lemon::property_set::evaluate(*this, strParam);
//
//}
//
//
//
//string context_object::property_set_get_string(const string & str) const
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


string context_object::get_text(const var & var, const ::id & id)
{

   if (var.has_property(id) && var[id].has_char())
   {

      return var[id];

   }

   return var.get_string();

}


::status::result context_object::run_property(const ::id& id)
{

   auto pproperty = find_property(id);

   if (!pproperty)
   {

      return error_not_found;

   }

   return pproperty->run();

}


void context_object::to_string(const class string_exchange & str) const
{

   str = typeid(*this).name();

}


strsize context_object::sz_len() const
{

   string str;

   to_string(str);

   return str.get_length();

}


void context_object::to_sz(char * sz, strsize len) const
{

   string str;

   to_string(str);

   strncpy(sz, str, len);

}



