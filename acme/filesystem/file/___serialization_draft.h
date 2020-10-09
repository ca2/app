// 2020-01-11 - Curitiba, ca2

// "pluggable" non-member non-virtual global serializers

// Use cases:
// - Entry point convenience syntax sugar
// - syntax sugar
template < typename TYPE >
inline stream & operator >> (stream & stream, TYPE & t) { stream.defer_set_loading(); stream.exchange(t); return stream; }

template < typename TYPE >
inline stream & operator << (stream & stream, const TYPE & t) { stream.defer_set_storing(); stream.exchange((TYPE &) t); return stream; }

int file_procedure()
{

   ::file pfile = Context.file().get_file("C:\\window.window");

   in_addr addr;

   ::stream stream(pfile);

   stream >> addr;

}


int var_procedure()
{

   var var;

   in_addr addr;

   ::var_stream stream(var);

   stream >> addr;

}

class stream
{
public:

   virtual void read(i8 & i) {}
   virtual void read(string & i) {}

   virtual void write(const i8 & i) {}
   virtual void write(const string & str) {}

   template < typename TYPE >
   void default_exchange(TYPE & t) { is_loading() ? read(t) : write(t); }

   virtual void exchange(const ::id & id, i8 & i) { default_exchange(i); }
   virtual void exchange(const ::id & id, string & str) { default_exchange(str); }

   

   template < typename OBJECT >
   inline void exchange(const ::id & id, __pointer(OBJECT) & pobject)
   {
      if (is_storing())
      {
         write_object(id, pobject.m_p);
      }
      else
      {
         pobject = read_object(id);
      }
   }


   virtual void write_object(const ::id & id, const ::id & idFactory, ::element * pobject)
   {
      exchange("id", idFactory);
      exchange("", pobject);
   }

   virtual __pointer(::element) read_object(const ::id & id)
   {
      ::id idFactory;
      exchange("id", idFactory);
      auto pobject = __id_create<::element>(idFactory);
      exchange("", pobject);
      return pobject;
   }


};


class var_stream
{
public:

   var & var();

   virtual void read(i8 & i) {}
   virtual void read(string & i) {}

   virtual void write(const i8 & i) {}
   virtual void write(const string & str) {}

   template < typename TYPE >
   void default_exchange(const ::id & id, TYPE & t) { is_loading() ? t = operator[id] : operator[id] = t; }

   virtual void exchange(const ::id & id, i8 & i) { default_exchange(id, i); }
   virtual void exchange(const ::id & id, string & str) { default_exchange(id, str); }






   virtual void write_object(const ::id & id, const ::id & idFactory, ::element * pobject) override
   {
      var_stream stream(new var(&var()[id].propset()));
      stream.exchange("id", idFactory);
      stream.exchange("", pobject);
   }

   virtual __pointer(::contex_object) read_object(const ::id & id) override
   {
      var_stream stream(new var(&var()[id].propset()));
      ::id idFactory;
      stream.exchange("id", idFactory);
      auto pobject = __id_create<::element>(idFactory);
      stream.exchange("", pobject);
      return pobject;
   }

};
//void __exchange(stream & stream, i8 & i) { __exchange_blt(stream, i); }
//void __exchange(stream & stream, string & str) { __exchange_string(stream, str); }
//void __exchange(stream & stream, in_addr & addr) { __exchange_stringable(stream, addr); }
//
//
//void __exchange(stream & stream, const ::id & id, i8 & i) { __exchange_blt(stream, i); }
//void __exchange(stream & stream, const ::id & id, string & str) { __exchange_string(stream, str); }
//void __exchange(stream & stream, const ::id & id, in_addr & addr) { __exchange_stringable(stream, addr); }
//
//
//void __exchange(var_stream & stream, i8 & i) { __exchange_blt(stream, i); }
//void __exchange(var_stream & stream, string & str) { __exchange_string(stream, str); }
//void __exchange(var_stream & stream, in_addr & addr) { __exchange_stringable(stream, addr); }


class window :
   virtual public element
{
public:

   i8                   m_iVisible;
   string               m_strTitle;
   in_addr              m_addr;
   __pointer(::element)  m_pobject;

   virtual void exchange(stream & s);

};

#define __EXCHANGE(xxx) stream.exchange(__STRING(xxx), m_##xxx)
#define __TYPE_EXCHANGE(xxx) stream.exchange(__STRING(xxx), t.m_##xxx)


void window::exchange(stream & stream)
{

   __EXCHANGE(iVisible); // expands... to: stream.exchange("iVisible", m_iVisible);
   __EXCHANGE(strTitle); // expands... to: stream.exchange("strTitle", m_strTitle);
   __EXCHANGE(addr);     // expands... to: stream.exchange("addr", m_addr);
   __EXCHANGE(pobject);  // expands... to: stream.exchange("pobject", m_pobject);

}


class exchanger
{

   stream * m_pstream;

   template
      exchange(id, value) read / write value
   {
       if (is_storing)
       m_pstream->write(id value)
       else
       m_pstream->read(id, value)

   }
      template
          exchange(value) read / write value
       {
           if (is_storing)
           m_pstream->write(value)
           else
           m_pstream->read(value)

       }


          stream
           {


           read(id, i8) throw not_implemented;
           read(id, i16) throw not_implemented;
           read(id, i32) throw not_implemented;
           read(id, i64) throw not_implemented;
           read(id, u8) throw not_implemented;
           read(id, u16) throw not_implemented;
           read(id, u32) throw not_implemented;
           read(id, u64) throw not_implemented;

           read(i8) throw not_implemented;
           read(i16) throw not_implemented;
           read(i32) throw not_implemented;
           read(i64) throw not_implemented;
           read(u8) throw not_implemented;
           read(u16) throw not_implemented;
           read(u32) throw not_implemented;
           read(u64) throw not_implemented;

           write(id, i8) throw not_implemented;
           write(id, i16) throw not_implemented;
           write(id, i32) throw not_implemented;
           write(id, i64) throw not_implemented;
           write(id, u8) throw not_implemented;
           write(id, u16) throw not_implemented;
           write(id, u32) throw not_implemented;
           write(id, u64) throw not_implemented;

           write(i8) throw not_implemented;
           write(i16) throw not_implemented;
           write(i32) throw not_implemented;
           write(i64) throw not_implemented;
           write(u8) throw not_implemented;
           write(u16) throw not_implemented;
           write(u32) throw not_implemented;
           write(u64) throw not_implemented;


           }


              binary_stream
           {


           read(id, i8) read(i8)
           read(id, i16) read(i16)
           read(id, i32) read(i32)
           read(id, i64) read(i64)
           read(id, u8) read(u8)
           read(id, u16) read(u16)
           read(id, u32) read(u32)
           read(id, u64) read(u64)

           read(i8) m_pfile->read(i8)
           read(i16) m_pfile->read(i16)
           read(i32) m_pfile->read(i32)
           read(i64) m_pfile->read(i64)
           read(u8) m_pfile->read(u8)
           read(u16) m_pfile->read(u16)
           read(u32) m_pfile->read(u32)
           read(u64) m_pfile->read(u64)

           write(id, i8) write(i8)
           write(id, i16) write(i16)
           write(id, i32) write(i32)
           write(id, i64) write(i64)
           write(id, u8) write(u8)
           write(id, u16) write(u16)
           write(id, u32) write(u32)
           write(id, u64) write(u64)

           write(i8) m_pfile->write(i8)
           write(i16) m_pfile->write(i16)
           write(i32) m_pfile->write(i32)
           write(i64) m_pfile->write(i64)
           write(u8) m_pfile->write(u8)
           write(u16) m_pfile->write(u16)
           write(u32) m_pfile->write(u32)
           write(u64) m_pfile->write(u64)


           }

              text_stream
           {


           write(id, i8) write(i8)
           write(id, i16) write(i16)
           write(id, i32) write(i32)
           write(id, i64) write(i64)
           write(id, u8) write(u8)
           write(id, u16) write(u16)
           write(id, u32) write(u32)
           write(id, u64) write(u64)

           write(i8) m_pfile->write(i8)
           write(i16) m_pfile->write(i16)
           write(i32) m_pfile->write(i32)
           write(i64) m_pfile->write(i64)
           write(u8) m_pfile->write(u8)
           write(u16) m_pfile->write(u16)
           write(u32) m_pfile->write(u32)
           write(u64) m_pfile->write(u64)


           }


              template < typename CONTAINER >
           id_stream :
           stream
           {

           read(id, i8)i8 = m_pvar->operator[](id);
           read(id, i16) i16 = m_pvar->operator[](id);
           read(id, i32) i32 = m_pvar->operator[](id);
           read(id, i64) i64 = m_pvar->operator[](id);
           read(id, u8) u8 = m_pvar->operator[](id);
           read(id, u16) u16 = m_pvar->operator[](id);
           read(id, u32) u32 = m_pvar->operator[](id);
           read(id, u64) u64 = m_pvar->operator[](id);

           read(i8) i8 = *m_pvar
           read(i16) i16 = *m_pvar
           read(i32) i32 = *m_pvar
           read(i64) i64 = *m_pvar
           read(u8) u8 = *m_pvar
           read(u16) u16 = *m_pvar
           read(u32) u32 = *m_pvar
           read(u64) u64 = *m_pvar

           write(id, i8) write(i8)
           write(id, i16) write(i16)
           write(id, i32) write(i32)
           write(id, i64) write(i64)
           write(id, u8) write(u8)
           write(id, u16) write(u16)
           write(id, u32) write(u32)
           write(id, u64) write(u64)

           write(i8) m_pfile->write(i8)
           write(i16) m_pfile->write(i16)
           write(i32) m_pfile->write(i32)
           write(i64) m_pfile->write(i64)
           write(u8) m_pfile->write(u8)
           write(u16) m_pfile->write(u16)
           write(u32) m_pfile->write(u32)
           write(u64) m_pfile->write(u64)

           }




              stream & operator >> (stream & stream, element & o)
           {

              exchange e(stream);

              e.defer_set_loading();

              e.exchange(s);

           }

           stream & operator >> (stream & s, element & o)
           {

              o.exchange(stream);

           }


           window new_frame_window()
           {
              return new frame_window();
           }