#include "framework.h"


generic::~generic()
{

}


void generic::assert_valid() const
{

}


void generic::dump(dump_context& context) const
{

}


::estatus     generic::initialize(::generic * pobjectContext)
{

   return ::success;

}


void generic::finalize()
{

}


::generic * generic::source_channel()
{

   return nullptr;

}


void generic::set_mutex(sync* psync)
{

   if (m_pmutex)
   {

      m_pmutex.release();

   }

   m_pmutex = psync;

}


void generic::defer_create_mutex()
{

   if (!m_pmutex)
   {

      m_pmutex = __new(::mutex);

   }

}


::estatus generic::run()
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

   {

      string str;

      str.Format("%s wparam=0x%" PRIxPTR " lparam=0x%" PRIxPTR, get_message_text(message, true).c_str(), wparam, lparam);

      output_debug_string(str);

      output_debug_string("-");

   }

   {

      string str;

      string strMessageText = get_message_text(message, true);

      const char * pszMessageText = strMessageText;

      str.Format("%s %" PRIxPTR " %" PRIxPTR, strMessageText.c_str(), wparam, lparam);

      output_debug_string(str);

      output_debug_string("-");

   }

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
//void generic::add_trait(::i64 i)
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

void generic::keep_alive()
{

   try
   {

      on_keep_alive();

   }
   catch (...)
   {

   }

}


void generic::on_keep_alive()
{

}


bool generic::is_alive()
{

   return true;

}


::estatus generic::call()
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


//::estatus generic::call(::trait & trait)
//{
//
//   //auto estatus = ::generic::call(trait);
//
//   //m_cRun++;
//
//   return error_exception;
//
//}


//void generic::notify(::u64 uId)
//{
//
//   m_uid |= uId;
//
//}


//void generic::io(stream & s)
//{
//
//
//}
//
//
//stream & generic::do_property_exchange(stream & stream) const
//{
//
//   ASSERT(stream.is_storing());
//
//   property_set set;
//
//   set += object_storing;
//
//   ((generic *)this)->exchange(set);
//
//   stream << set;
//
//   return stream;
//
//}
//
//


void generic::exchange(::stream & stream)
{

   __throw(interface_only_exception());

}


void generic::add_exception(::exception::exception * pexception)
{

   m_estatus = error_exception;

   set_fail();

}


void generic::on_catch_all_exception()
{

   m_estatus = error_catch_all_exception;

   set_fail();

}


stream & generic::write(::stream & stream) const
{

   ((generic*)this)->exchange(stream);

   return stream;

}


stream & generic::read(::stream & stream)
{

   exchange(stream);
   //generic::read(stream);

   //if (has_flag(object_default_property_exchange))
   //{

   //   do_property_exchange(stream);

   //}

   return stream;

}



void debug_trait()
{


   auto pimage = __create_image();


   //System.imaging().start_traits(System.imaging(), pimage);

}





::generic * generic::parent_property_set_holder() const
{

   return get_context_application();

}


property * generic::parent_lookup_property(const id & id) const
{

   auto pobject = parent_property_set_holder();

   if (!pobject)
   {

      return nullptr;

   }

   return pobject->on_fetch_property(id);

}


property * generic::on_fetch_property(const ::id & id) const
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


id generic::translate_property_id(const ::id & id)
{

   auto pparent = parent_property_set_holder();

   if (!pparent)
   {

      return id;

   }

   return pparent->translate_property_id(id);

}

void generic::add_property_set(property_set * pset)
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


string generic::property_set_evaluate(const string & str) const
{

   return ::papaya::property_set::evaluate(*this, str);

}


string generic::property_set_get_evaluation(const string & str) const
{

   return property_set_get_string(str.c_str() + 1);

}


bool generic::property_set_get_evaluation(string & strResult, const string& str) const
{

   return property_set_get_string(strResult, str.c_str() + 1);

}

string generic::property_set_get_string(const string & str) const
{

   auto pproperty = on_fetch_property(str);

   if (is_null(pproperty))
   {

      return "";

   }

   return pproperty->get_string();

}

bool generic::property_set_get_string(string & strResult, const string& str) const
{

   auto pproperty = on_fetch_property(str);

   if (is_null(pproperty))
   {

      return false;

   }

   strResult = pproperty->get_string();

   return true;

}


void generic::property_set_replace(string & str) const
{

   str = property_set_evaluate(str);

}


property * generic::fetch_property(const ::id & idParam, bool bCreate)
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
//string generic::property_set_get_evaluation(const string & str) const
//{
//
//   return property_set_get_string(str.c_str() + 1);
//
//}
//
//
//string generic::property_set_evaluate(const string & strParam) const
//{
//
//   return ::lemon::property_set::evaluate(*this, strParam);
//
//}
//
//
//
//string generic::property_set_get_string(const string & str) const
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


string generic::get_text(const var & var, const ::id & id)
{

   if (var.has_property(id) && var[id].has_char())
   {

      return var[id];

   }

   return var.get_string();

}


::status::result generic::run_property(const ::id& id)
{

   auto pproperty = find_property(id);

   if (!pproperty)
   {

      return error_not_found;

   }

   return pproperty->run();

}


void generic::to_string(string & str) const
{
   
   str = typeid(*this).name();
   
}


strsize generic::sz_len() const
{

   string str;
   
   to_string(str);
   
   return str.get_length();
   
}


void generic::to_sz(char * sz, strsize len) const
{

   string str;
   
   to_string(str);
   
   strncpy(sz, str, len);

}



