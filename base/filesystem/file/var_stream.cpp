#include "framework.h"

var_stream::~var_stream()
{

   //if (m_bOwn) ::aura::del(m_pvar);
   ::aura::del(m_pvar);

}

//namespace discrete
//{
//
//
//   var_stream::var_stream(::object * pobject, bool bStoring) :
//      ::object(pobject),
//      stream(pobject)
//   {
//
//   }
//
//
//   var_stream::~var_stream()
//   {
//
//   }
//
//
//   memsize var_stream::read(void *pdata, memsize nCount)

//   {
//      auto pm = cast < memory > ();
//      if (::is_null(pm))
//      {
//         return 0;
//      }
//      memsize uRead = MIN(pm->get_length(), nCount);
//      ::memcpy_dup(pdata, pm->get_data(), uRead);

//      return uRead;
//   }
//
//   void var_stream::write(const void *pdata, memsize nCount)

//   {
//      auto pm = __new(memory());
//      pm->assign(pdata, nCount);

//      m_var = pm;
//   }
//
//   void var_stream::write(char ch)
//   {
//      m_var = ch;
//   }
//
//   void var_stream::write(uchar uch)
//   {
//      m_var = uch;
//   }
//
//   void var_stream::write(i16 sh)
//   {
//      m_var = sh;
//   }
//
//   void var_stream::write(u16 ui)
//   {
//      m_var = ui;
//   }
//#ifdef WINDOWS
//   void var_stream::write(unichar wch)
//   {
//      m_var = wch;
//
//   }
//#endif
//   void var_stream::write(bool b)
//   {
//      m_var = b;
//   }
//   void var_stream::write(i32 i)
//   {
//      m_var = i;
//   }
//   void var_stream::write(u32 ui)
//   {
//
//      m_var = ui;
//   }
//   void var_stream::write(i64 i)
//   {
//
//      m_var = i;
//   }
//   void var_stream::write(u64 ui)
//   {
//
//      m_var = ui;
//
//   }
//#if defined(__APPLE__)
//   void var_stream::write(unsigned long ui)
//   {
//
//      m_var = ui;
//
//   }
//   //void write (long long ll);
//#endif
//   void var_stream::write(float f)
//   {
//
//      m_var = f;
//
//   }
//   void var_stream::write(double d)
//   {
//
//      m_var = d;
//
//   }
//   void var_stream::write(const rect & & rect)
//   {
//
//      oblt(rect);
//
//   }
//   void var_stream::write(RECT * pcrect)

//   {
//
//      oblt(*pcrect);

//
//   }
//   void var_stream::write(const size & & size)
//   {
//      oblt(size);
//
//   }
//   void var_stream::write(const char * psz)
//   {
//
//      m_var = psz;
//   }
//#ifdef WINDOWS
//   void var_stream::write(const unichar * wch)
//   {
//      m_var = wch;
//   }
//#endif
//   void var_stream::write(id & id)
//   {
//      m_var = id;
//   }
//   void var_stream::write(var & var)
//   {
//      m_var = var;
//   }
//   void var_stream::write(property & property)
//   {
//      m_
//   }
//   void var_stream::write(string & str);
//   void var_stream::write(generic_object * pobject);
//   void var_stream::write(generic_object & object);
//
//
//
//   //      virtual void read(i32 & i);
//   //      virtual void read(u32 & ui);
//   //      virtual void read(i64 & i);
//   //      virtual void read(u64 & ui);
//
//
//   void var_stream::read(bool & b);
//   void var_stream::read(char & ch);
//   void var_stream::read(uchar & uch);
//#ifdef WINDOWS
//   void var_stream::read(unichar & wch);
//#endif
//   void var_stream::read(i16 & sh);
//   void var_stream::read(u16 & ui);
//   void var_stream::read(i32 & i);
//   void var_stream::read(u32 & ui);
//   void var_stream::read(i64 & i);
//   void var_stream::read(u64 & ui);
//#ifdef __APPLE__
//   void var_stream::read(unsigned long & ui);
//   //virtual void read (long long & ui);
//#endif
//   void var_stream::read(float & f);
//   void var_stream::read(double & d);
//   void var_stream::read(RECT * prect);

//   void var_stream::read(const size & & size);
//   void var_stream::read(id & id);
//   void var_stream::read(var & var);
//   void var_stream::read(property & property);
//   void var_stream::read(string & str);
//   void var_stream::read(generic_object * pobject);
//   void var_stream::read(generic_object & object);
//
//
//   bool is_storing()
//   {
//
//      return m_bStoring;
//
//   }
//
//
//
//   output_var_stream(::object * pobject);
//   virtual ~output_var_stream();
//
//
//} // namespace discrete
//
//
//


void var_stream::write_object(const ::id & id, ::generic_object * pobject)
{

   var_stream stream(new ::var(&var()[id].propset()));

   ::id idType = pobject->type_name();

   string strId = stream.factory_id_to_text(idType);

   stream.var_exchange(property_id, strId);

   stream.set_storing();

   pobject->exchange(stream);

}


__pointer(::generic_object) var_stream::read_object(const ::id & id)
{

   var_stream stream(new ::var(&var()[id].propset()));

   string strId;

   stream.var_exchange(property_id, strId);

   auto pobject = stream.create_object_from_text(strId);

   pobject->exchange(stream);

   return pobject;

}



void var_stream::read(block & block)
{

   if (block.get_size() <= 0)
   {

      return;

   }

   if (m_pvar->m_etype != type_memory || ::is_null(m_pvar->m_pmemory))
   {

      set_fail_bit();

      return;

   }

   if (block.get_size() != m_pvar->m_pmemory->get_size()
      || block.get_data() == nullptr
      || m_pvar->m_pmemory->get_data() == nullptr)
   {

      set_fail_bit();

      return;

   }

   ::memcpy(block.get_data(), m_pvar->m_pmemory->get_data(), block.get_size());

}


void var_stream::write(const block & block)
{

   *m_pvar = block;

}


void var_stream::exchange(const ::id & id, double & d)
{

   var_exchange(id, d);

}



