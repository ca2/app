#include "framework.h"
//#include "property_object.h"
//#include "payload.h"
#include "acme/constant/message.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
//#include "acme/prototype/mathematics/c_number.h"


property_object::~property_object()
{

}


//void property_object::assert_ok() const
//{
//
//}


//void property_object::dump(dump_context& context) const
//{
//
//}


//void     property_object::initialize(::particle * pparticle)
//{
//
//   set_object(pparticle);
//
//   return ::success;
//
//}


void property_object::destroy()
{

   ::matter::destroy();

   m_ppropertyset.release();

}


void property_object::notify_on_destroy(::property_object * pcontextobjectFinish)
{

   if (has_flag(e_flag_destroying))
   {

      //finish(nullptr);
      destroy();

   }

}


::object * property_object::source_channel()
{

   return nullptr;

}


//void property_object::run()
//{
//
//   //return ::success;
//
//}


class debug_test_reference :
   public property_set
{
public:


   bool & m_bTest1;
   ::string & m_strText1;


   debug_test_reference() :
      m_bTest1(reference("bTest1")),
      m_strText1(reference("strTest1"))
   {

   }

};

string get_message_text(const ::atom & atom, bool bWithNumbers);

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

      output_debug_string_formatf("%s\n\n", strTitle1.c_str());

   }

   {

      string strTitle1 = "Hello ";

      string strTitle2 = "ountries";

      strTitle1 += 'C' + strTitle2;

       output_debug_string_formatf("%s\n\n", strTitle1.c_str());

   }

//   {
//
//      string str;
//
//      str.formatf("%s wparam=0x%" PRIxPTR " lparam=0x%" PRIxPTR, get_message_text(message, true).c_str(), wparam, lparam);
//
//      information(str);
//
//      informationf("-");
//
//   }

//   {
//
//      string str;
//
//      string strMessageText = get_message_text(message, true);
//
//      const ::scoped_string & scopedstrMessageText = strMessageText;
//
//      str.formatf("%s %" PRIxPTR " %" PRIxPTR, strMessageText.c_str(), wparam, lparam);
//
//      information(str);
//
//      informationf("-");
//
//   }

   debug_test_reference ref;

   ref.m_bTest1 = true;
   ref.m_strText1 = "Text1";

   auto network_payload1 = ref.get_network_payload();

   informationf(network_payload1);

   ref.m_bTest1 = false;
   ref.m_strText1 = ref.get_network_payload();

   auto network_payload2 = ref.get_network_payload();

   informationf(network_payload2);

   informationf("debug_debug_reference end");

   informationf("-");

}
//void property_object::add_trait(long long i)
//{
//
//   if (!m_ptraits)
//   {
//
//      m_ptraits = __allocate traits();
//
//   }
//
//   m_ptraits->add(i);
//
//}

void property_object::ping()
{

   try
   {

      on_ping();

   }
   catch (...)
   {

   }

}


void property_object::on_ping()
{

}


bool property_object::is_pinging() const
{

   return true;

}


//void property_object::call()
//{
//
//   //::e_status estatus;
//
//   //try
//   //{
//
//   run();
//
//   //}
//   //catch (...)
//   //{
//
//   //   estatus = ::error_exception;
//
//   //}
//
//   //return estatus;
//
//}


//void property_object::call(::trait & trait)
//{
//
//   //auto estatus = ::property_object::call(trait);
//
//   //m_cRun++;
//
//   return error_exception;
//
//}


//void property_object::notify(unsigned long long uId)
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
//   ::property_set set;
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


//void property_object::exchange(::stream & stream)
//{
//
//   __exchange(stream, *m_ppropertyset);
//
//}
//
//
//void property_object::exchange(::payload_stream& stream)
//{
//
//   __exchange(stream, *m_ppropertyset);
//
//}


void property_object::handle_exception(const ::exception& e)
{

   //return ::success;

}



void property_object::add_exception(const ::exception & e)
{

   m_estatus = error_exception;

   set_fail_flag();

}


void property_object::on_catch_all_exception()
{

   m_estatus = error_catch_all_exception;

   set_fail_flag();

}


::string property_object::get_object_file_name()
{

   ::string str = ::type(*this).name();

   str.find_replace("::", "_");

   return str;

}


::file::path property_object::get_ini_configuration_path()
{

   ::file::path path;

   path = "dropbox-app://";

   if (include_hostname_in_configuration_path())
   {

      auto strComputerName = node()->get_computer_name();

      if (strComputerName.is_empty())
      {

         strComputerName = "localhost";

      }

      path /= strComputerName;

   }

   ::string strFileName;

   strFileName = get_object_file_name() + ".ini";

   path /= strFileName;

   return path;

}


bool property_object::include_hostname_in_configuration_path()
{

   return false;

}


void property_object::read_ini_configuration()
{

   auto pathIni = get_ini_configuration_path();

   read_configuration_from_ini(pathIni);

}


void property_object::write_ini_configuration()
{

   auto pathIni = get_ini_configuration_path();

   write_configuration_to_ini(pathIni);

}


void property_object::read_configuration_from_ini(const ::payload & payloadFile)
{

   auto strIni = file()->safe_get_string(payloadFile);

   property_set().parse_ini(strIni);

}


void property_object::write_configuration_to_ini(const ::payload & payloadFile)
{

   auto strIni = property_set().get_ini();

   file()->put_text(payloadFile, strIni);

}


//stream & property_object::write(::stream & stream) const
//{
//
//   ((property_object*)this)->exchange(stream);
//
//   return stream;
//
//}
//
//
//stream & property_object::read(::stream & stream)
//{
//
//   exchange(stream);
//   //property_object::read(stream);
//
//   //if (has_flag(object_default_property_exchange))
//   //{
//
//   //   do_property_exchange(stream);
//
//   //}
//
//   return stream;
//
//}



//void debug_trait()
//{
//
//
//   auto pimage = __create_image();
//
//
//   //system()->imaging().start_traits(system()->imaging(), pimage);
//
//}





::property_object * property_object::parent_property_set_holder() const
{

   return nullptr;

}


// linked_property property_object::parent_lookup_property(const atom & atom) const
// {
//
//    auto pparticle = parent_property_set_holder();
//
//    if (!pparticle)
//    {
//
//       return nullptr;
//
//    }
//
//    return pparticle->on_fetch_property(atom);
//
// }
//
//
// ::linked_property property_object::on_fetch_property(const ::atom & atom) const
// {
//
//    auto pproperty = find_property(atom);
//
//    if (pproperty)
//    {
//
//       return { (property *) pproperty, (property_object *) this };
//
//    }
//
//    //auto ppropertyArray = find_property("property_set_array");
//
//    //pointer< pointer_array < property_set > > parray;
//
//    //if (ppropertyArray)
//    //{
//
//    //   ppropertyArray->defer_get(parray);
//
//    //   if (parray)
//    //   {
//
//    //      for (auto & pset : parray->ptra())
//    //      {
//
//    //         pproperty = pset->find(atom); // first-level find
//
//    //         if (pproperty)
//    //         {
//
//    //            return pproperty;
//
//    //         }
//
//    //      }
//
//    //   }
//
//    //}
//
//    return parent_lookup_property(atom);
//
// }


//atom property_object::translate_property_id(const ::atom & atom)
//{
//
//   auto pparent = parent_property_set_holder();
//
//   if (!pparent)
//   {
//
//      return atom;
//
//   }
//
//   return pparent->translate_property_id(atom);
//
//}

//void property_object::add_property_set(property_set * pset)
//{
//
//   auto * pproperty = find_property("property_set_array");
//
//   auto parray = pproperty->cast < pointer_array < property_set > >();
//
//   if (!parray)
//   {
//
//      parray = __allocate pointer_array < property_set > ();
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

   return m_ppropertyset ? m_ppropertyset->evaluate(str) : str;

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

   // auto pproperty = on_fetch_property(str);
   //
   // if (is_reference_null(pproperty))
   // {
   //
   //    return "";
   //
   // }
   //
   // return *pproperty;

   return {};

}


bool property_object::property_set_get_string(string & strResult, const string& str) const
{

   // auto linkedproperty = on_fetch_property(str);
   //
   // if (!linkedproperty)
   // {
   //
   //    return false;
   //
   // }
   //
   // strResult = linkedproperty->as_string();

   return true;

}


void property_object::property_set_replace(string & str) const
{

   str = property_set_evaluate(str);

}


void property_object::notify_property_changed(::property* pproperty, const ::action_context & actioncontext)
{

   on_property_changed(pproperty, actioncontext);

}


void property_object::on_property_changed(::property* pproperty, const action_context & actioncontext)
{


}


// ::linked_property property_object::fetch_property(const ::atom & idParam, bool bCreate)
// {
//
//    auto atom = translate_property_id(idParam);
//
//    if(!atom.is_empty())
//    {
//
//       auto linkedproperty = on_fetch_property(atom);
//
//       if(linkedproperty)
//       {
//
//          return linkedproperty;
//
//       }
//
//    }
//
//    if (bCreate)
//    {
//
//       return { &get_property_set().get(atom), this };
//
//    }
//
//    return nullptr;
//
// }

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


//string property_object::get_text(const ::payload & payload, const ::atom & atom)
//{
//
//   if (payload.has_property(atom) && payload[atom].has_character())
//   {
//
//      return { payload[atom] };
//
//   }
//
//   return { payload };
//
//}


void property_object::defer_run_property(const ::atom& atom)
{

   auto pproperty = lookup_property(atom);

   if (!pproperty)
   {

      ///throw ::exception(error_not_found);

      return;

   }

   if (pproperty->get_type() != e_type_element)
   {

      //throw ::exception(error_not_found);

      return;

   }

   pproperty->defer_run_payload();

}


//void property_object::to_string(const class string_exchange & str) const
//{
//
//   str = ::type(this).name();
//
//}


//character_count property_object::sz_len() const
//{
//
//   string str;
//
//   to_string(str);
//
//   return str.length();
//
//}
//
//
//void property_object::to_sz(char * sz, character_count len) const
//{
//
//   string str;
//
//   to_string(str);
//
//   strncpy(sz, str, len);
//
//}





//property_object::property_object(const property_object & propertyobject) :
//   ::PARTICLE(propertyobject),
//   ::particle(propertyobject),
//   ::matter(propertyobject),
//   m_ppropertyset(propertyobject.m_ppropertyset)
//{
//
//}




bool property_object::has_property(const atom & atom) const { return m_ppropertyset && m_ppropertyset->has_property(atom); }
property * property_object::lookup_property(const atom& atom) const { return m_ppropertyset ? m_ppropertyset->lookup(atom) : nullptr; }
bool property_object::erase_key(const atom & atom) { return m_ppropertyset && m_ppropertyset->erase_by_name(atom); }
property_set & property_object::property_set() { defer_propset(); return *m_ppropertyset; }
bool property_object::has_property_set() const { return ::is_set(m_ppropertyset); }


bool property_object::contains(const ::property_set & set) const
{

   if (set.is_empty())
   {

      return true;

   }

   if (m_ppropertyset.is_null())
   {

      return false;

   }

   return m_ppropertyset->contains(set);

}


void property_object::defer_propset()
{

#if REFERENCING_DEBUGGING

   refdbg_top_track refdbgtoptrack(this);

#endif

   m_papplication->__defer_construct_new(m_ppropertyset);

}


::collection::index property_object::index_of_property(const atom & atom) const
{

   if (!m_ppropertyset)
   {

      return -1;

   }

   return m_ppropertyset->index_of(atom);

}


string property_object::get_string(const ::atom & atom, const ::scoped_string & scopedstrDefault) const
{

   if (!m_ppropertyset)
   {

      return scopedstrDefault;

   }

   return m_ppropertyset->get_string(atom, scopedstrDefault);

}


int property_object::get_int(const ::atom & atom, int iDefault) const
{

   if (!m_ppropertyset)
   {

      return iDefault;

   }

   return m_ppropertyset->get_int(atom, iDefault);

}


unsigned int property_object::get_unsigned_int(const ::atom & atom, unsigned int uDefault) const
{

   if (!m_ppropertyset)
   {

      return uDefault;

   }

   return m_ppropertyset->get_unsigned_int(atom, uDefault);

}


//template < primitive_subparticle TYPE >
//TYPE * property_object::cast(const ::atom & atom) const
//{
//
//   return payload(atom).cast <TYPE>();
//
//}


//template < typename TYPE > ::pointer<TYPE>property_object::cast(const ::atom & atom) const
//{
//
//   auto pproperty = find_property(atom);
//
//   if (!pproperty)
//   {
//
//      return nullptr;
//
//   }
//
//   return pproperty->cast < TYPE >();
//
//}


//::payload & property_object::payload(const atom & atom)
//{
//
//   return property(atom);
//
//}


::property & property_object::property(const atom & atom)
{

   return property_set()[atom];

}

bool property_object::is_true(const ::atom & atom) const
{

   return m_ppropertyset && m_ppropertyset->is_true(atom);

}


bool property_object::is_false(const ::atom& atom) const
{

   return !is_true(atom);

}


bool property_object::is_true_or_empty(const ::atom & atom) const
{

   return m_ppropertyset && m_ppropertyset->is_true_or_empty(atom);

}


//bool property_object::__is_true(const ::atom & atom, const ::payload & payloadDefault, bool bDefault = false) const
//{
//
//   return payload(atom).__is_true(payloadDefault, bDefault);
//
//}


// ::payload & property_object::operator[](const ::atom & atom) { return payload(atom); }
//
// ::payload property_object::operator[](const ::atom & atom) const
// {
//
//    auto pproperty = find_property(atom);
//
//    if (!pproperty)
//    {
//
//       return e_type_new;
//
//    }
//
//    return *pproperty;
//
// }


//::payload property_object::payload(const ::atom & atom) const 
//{
//   
//   auto pproperty = lookup_property(atom); 
//
//   if (::is_null(pproperty))
//   {
//
//      return e_type_new;
//
//   }
//
//   return *pproperty;
//
//}


//::property & property_object::property(const ::atom & atom)
//{
//
//   auto & property = this->property_set()[atom];
//
//   return property;
//
//}


//::payload property_object::payload(const ::atom & atom, const ::payload & payloadDefault) const
//{
//
//   return find_payload(atom, payloadDefault); 
//
//}
//
//
//::property property_object::property(const ::atom & atom, const ::payload & payloadDefault) const
//{
//
//   auto pproperty = find_property(atom);
//
//   if (!pproperty)
//   {
//
//      return { atom, payloadDefault };
//
//   }
//
//   return *pproperty;
//
//}
//




// ::payload property_object::operator()(const ::atom & atom) const { return find_payload(atom, ::error_not_found); }
//
// ::payload property_object::operator()(const ::atom & atom, const ::payload & payloadDefault) const { return find_payload(atom, payloadDefault); }

//::payload property_object::find_payload(const ::atom & atom) const { return find_payload(atom, ::error_not_found); }
//
//::payload property_object::find_payload(const ::atom & atom, const ::payload & payloadDefault) const
//{
//
//   auto pproperty = find_property(atom);
//
//   if (!pproperty)
//   {
//
//      return payloadDefault;
//
//   }
//
//   return *pproperty;
//
//}

//::property & property_object::attribute(const ::atom & atom) { return payload(atom); }
//
//::property * property_object::find_attribute(const ::atom & atom) { return find_property(atom); }
//
//template < typename TYPE >
//bool property_object::find_attribute(const ::atom & atom, TYPE & t)
//{
//
//   auto p = find_property(atom);
//
//   if (!p)
//   {
//
//      return false;
//
//   }
//
//   t = *p;
//
//   return true;
//
//}

//
//::payload & property_object::get_object(const ::atom & atom)
//{
//
//   auto pproperty = &payload(atom);
//
//   if (!pproperty)
//   {
//
//      throw ::exception(error_resource);
//
//   }
//
//   return *pproperty;
//
//}


//
//
//::payload & property_object::topic(const ::atom& atom)
//{
//
//   // auto property = fetch_property(atom);
//   //
//   // if (!property)
//   // {
//
//      throw ::exception(error_resource);
//   //
//   // }
//   //
//   // return *property.m_pproperty;
//
//   return *((::payload *)nullptr);
//
//}
//


