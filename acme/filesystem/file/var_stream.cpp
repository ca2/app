#include "framework.h"

var_stream::~var_stream()
{

   //if (m_bOwn) ::acme::del(m_ppayload);
   ::acme::del(m_ppayload);

}

//namespace discrete
//{
//
//
//   var_stream::var_stream(::matter * pobject, bool bStoring) :
//      ::matter(pobject),
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
//      memsize uRead = minimum(pm->get_length(), nCount);
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
//   void var_stream::write(u16 u)
//   {
//      m_var = u;
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
//   void var_stream::write(u32 u)
//   {
//
//      m_var = u;
//   }
//   void var_stream::write(i64 i)
//   {
//
//      m_var = i;
//   }
//   void var_stream::write(u64 u)
//   {
//
//      m_var = u;
//
//   }
//#if defined(__APPLE__)
//   void var_stream::write(unsigned long u)
//   {
//
//      m_var = u;
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
//   void var_stream::write(const rectangle_i32 & & rectangle)
//   {
//
//      oblt(rectangle);
//
//   }
//   void var_stream::write(RECTANGLE_I32 * pcrect)

//   {
//
//      oblt(*pcrect);

//
//   }
//   void var_stream::write(const size_i32 & & size)
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
//   void var_stream::write(::payload & payload)
//   {
//      m_var = payload;
//   }
//   void var_stream::write(property & property)
//   {
//      m_
//   }
//   void var_stream::write(string & str);
//   void var_stream::write(matter * pobject);
//   void var_stream::write(matter & matter);
//
//
//
//   //      virtual void read(i32 & i);
//   //      virtual void read(u32 & u);
//   //      virtual void read(i64 & i);
//   //      virtual void read(u64 & u);
//
//
//   void var_stream::read(bool & b);
//   void var_stream::read(char & ch);
//   void var_stream::read(uchar & uch);
//#ifdef WINDOWS
//   void var_stream::read(unichar & wch);
//#endif
//   void var_stream::read(i16 & sh);
//   void var_stream::read(u16 & u);
//   void var_stream::read(i32 & i);
//   void var_stream::read(u32 & u);
//   void var_stream::read(i64 & i);
//   void var_stream::read(u64 & u);
//#ifdef __APPLE__
//   void var_stream::read(unsigned long & u);
//   //virtual void read (long long & u);
//#endif
//   void var_stream::read(float & f);
//   void var_stream::read(double & d);
//   void var_stream::read(RECTANGLE_I32 * prectangle);

//   void var_stream::read(const size_i32 & & size);
//   void var_stream::read(id & id);
//   void var_stream::read(::payload & payload);
//   void var_stream::read(property & property);
//   void var_stream::read(string & str);
//   void var_stream::read(matter * pobject);
//   void var_stream::read(matter & matter);
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
//   output_var_stream(::matter * pobject);
//   virtual ~output_var_stream();
//
//
//} // namespace discrete
//
//
//


//void var_stream::write_object(const ::id & id, ::matter * pobject)
//{
//
//   var_stream stream(new ::payload(&payload()[id].propset()));
//
//   ::id idType = __type_name(pobject);
//
//   string strId = stream.factory_id_to_text(idType);
//
//   stream.var_exchange(e_property_id, strId);
//
//   stream.set_storing();
//
//   pobject->exchange(stream);
//
//}
//
//
//__pointer(::matter) var_stream::read_object(const ::id & id)
//{
//
//   var_stream stream(new ::payload(&payload()[id].propset()));
//
//   string strId;
//
//   stream.var_exchange(e_property_id, strId);
//
//   auto pobject = stream.create_object_from_text(strId);
//
//   pobject->exchange(stream);
//
//   return pobject;
//
//}



void var_stream::read(block & block)
{

   if (block.get_size() <= 0)
   {

      return;

   }

   if (m_ppayload->m_etype != e_type_memory || ::is_null(m_ppayload->m_pmemory))
   {

      throw_status(error_io);

      return;

   }

   if (block.get_size() != m_ppayload->m_pmemory->get_size()
      || block.get_data() == nullptr
      || m_ppayload->m_pmemory->get_data() == nullptr)
   {

      throw_status(error_io);

      return;

   }

   ::memcpy(block.get_data(), m_ppayload->m_pmemory->get_data(), block.get_size());

}


void var_stream::write(const block & block)
{

   *m_ppayload = block;

}


void var_stream::exchange(const ::id & id, double & d)
{

   var_exchange(id, d);

}

void var_stream::exchange(const ::id& id, i64& i)
{

   var_exchange(id, i);

}


