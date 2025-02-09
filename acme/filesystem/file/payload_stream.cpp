#include "framework.h"

//payload_stream::~payload_stream()
//{
//
//   //if (m_bOwn) ::acme::del(m_ppayload);
//   ::acme::del(m_ppayload);
//
//}
//
////namespace discrete
////{
////
////
////   payload_stream::payload_stream(::particle * pparticle, bool bStoring) :
////      ::matter(pparticle),
////      stream(pparticle)
////   {
////
////   }
////
////
////   payload_stream::~payload_stream()
////   {
////
////   }
////
////
////   memsize payload_stream::read(void *pdata, memsize nCount)
//
////   {
////      auto pm = cast < memory > ();
////      if (::is_null(pm))
////      {
////         return 0;
////      }
////      memsize uRead = minimum(pm->get_length(), nCount);
////      ::memory_copy(pdata, pm->get_data(), uRead);
//
////      return uRead;
////   }
////
////   void payload_stream::write(const void *pdata, memsize nCount)
//
////   {
////      auto pm = __allocate memory();
////      pm->assign(pdata, nCount);
//
////      m_var = pm;
////   }
////
////   void payload_stream::write(char ch)
////   {
////      m_var = ch;
////   }
////
////   void payload_stream::write(uchar uch)
////   {
////      m_var = uch;
////   }
////
////   void payload_stream::write(short sh)
////   {
////      m_var = sh;
////   }
////
////   void payload_stream::write(unsigned short u)
////   {
////      m_var = u;
////   }
////#ifdef WINDOWS
////   void payload_stream::write(unichar wch)
////   {
////      m_var = wch;
////
////   }
////#endif
////   void payload_stream::write(bool b)
////   {
////      m_var = b;
////   }
////   void payload_stream::write(int i)
////   {
////      m_var = i;
////   }
////   void payload_stream::write(unsigned int u)
////   {
////
////      m_var = u;
////   }
////   void payload_stream::write(long long i)
////   {
////
////      m_var = i;
////   }
////   void payload_stream::write(unsigned long long u)
////   {
////
////      m_var = u;
////
////   }
////#if defined(__APPLE__)
////   void payload_stream::write(unsigned long u)
////   {
////
////      m_var = u;
////
////   }
////   //void write (long long hi);
////#endif
////   void payload_stream::write(float f)
////   {
////
////      m_var = f;
////
////   }
////   void payload_stream::write(double d)
////   {
////
////      m_var = d;
////
////   }
////   void payload_stream::write(const int_rectangle & & rectangle)
////   {
////
////      oblt(rectangle);
////
////   }
////   void payload_stream::write(::int_rectangle * pcrect)
//
////   {
////
////      oblt(*pcrect);
//
////
////   }
////   void payload_stream::write(const int_size & & size)
////   {
////      oblt(size);
////
////   }
////   void payload_stream::write(const ::scoped_string & scopedstr)
////   {
////
////      m_var = psz;
////   }
////#ifdef WINDOWS
////   void payload_stream::write(const unichar * wch)
////   {
////      m_var = wch;
////   }
////#endif
////   void payload_stream::write(atom & atom)
////   {
////      m_var = atom;
////   }
////   void payload_stream::write(::payload & payload)
////   {
////      m_var = payload;
////   }
////   void payload_stream::write(property & property)
////   {
////      m_
////   }
////   void payload_stream::write(string & str);
////   void payload_stream::write(::particle * pparticle);
////   void payload_stream::write(matter & matter);
////
////
////
////   //      virtual void read(int & i);
////   //      virtual void read(unsigned int & u);
////   //      virtual void read(long long & i);
////   //      virtual void read(unsigned long long & u);
////
////
////   void payload_stream::read(bool & b);
////   void payload_stream::read(char & ch);
////   void payload_stream::read(uchar & uch);
////#ifdef WINDOWS
////   void payload_stream::read(unichar & wch);
////#endif
////   void payload_stream::read(short & sh);
////   void payload_stream::read(unsigned short & u);
////   void payload_stream::read(int & i);
////   void payload_stream::read(unsigned int & u);
////   void payload_stream::read(long long & i);
////   void payload_stream::read(unsigned long long & u);
////#ifdef __APPLE__
////   void payload_stream::read(unsigned long & u);
////   //virtual void read (long long & u);
////#endif
////   void payload_stream::read(float & f);
////   void payload_stream::read(double & d);
////   void payload_stream::read(::int_rectangle * prectangle);
//
////   void payload_stream::read(const int_size & & size);
////   void payload_stream::read(atom & atom);
////   void payload_stream::read(::payload & payload);
////   void payload_stream::read(property & property);
////   void payload_stream::read(string & str);
////   void payload_stream::read(::particle * pparticle);
////   void payload_stream::read(matter & matter);
////
////
////   bool is_storing()
////   {
////
////      return m_bStoring;
////
////   }
////
////
////
////   output_var_stream(::particle * pparticle);
////   virtual ~output_var_stream();
////
////
////} // namespace discrete
////
////
////
//
//
////void payload_stream::write_object(const ::atom & atom, ::particle * pparticle)
////{
////
////   payload_stream stream(__allocate< ::payload(&payload()[atom].propset >()));
////
////   ::atom idType = ::type(pparticle).name();
////
////   string strId = stream.factory_id_to_text(idType);
////
////   stream.var_exchange(e_property_id, strId);
////
////   stream.set_storing();
////
////   pparticle->exchange(stream);
////
////}
////
////
////::pointer<::matter>payload_stream::read_object(const ::atom & atom)
////{
////
////   payload_stream stream(__allocate< ::payload(&payload()[atom].propset >()));
////
////   string strId;
////
////   stream.var_exchange(e_property_id, strId);
////
////   auto pparticle = stream.create_object_from_text(strId);
////
////   pparticle->exchange(stream);
////
////   return pparticle;
////
////}
//
//
//
//void payload_stream::read(block & block)
//{
//
//   if (block.get_size() <= 0)
//   {
//
//      return;
//
//   }
//
//   if (m_ppayload->m_etype != e_type_memory || ::is_null(m_ppayload->m_pmemory))
//   {
//
//      throw ::exception(error_io);
//
//      return;
//
//   }
//
//   if (block.get_size() != m_ppayload->m_pmemory->get_size()
//      || block.get_data() == nullptr
//      || m_ppayload->m_pmemory->get_data() == nullptr)
//   {
//
//      throw ::exception(error_io);
//
//      return;
//
//   }
//
//   ::memory_copy(block.get_data(), m_ppayload->m_pmemory->get_data(), block.get_size());
//
//}
//
//
//void payload_stream::write(const block & block)
//{
//
//   *m_ppayload = block;
//
//}
//
//
//void payload_stream::exchange(const ::atom & atom, double & d)
//{
//
//   var_exchange(atom, d);
//
//}
//
//void payload_stream::exchange(const ::atom& atom, long long& i)
//{
//
//   var_exchange(atom, i);
//
//}
//
//
