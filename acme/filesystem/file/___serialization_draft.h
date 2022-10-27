// 2020-01-11 - Curitiba, ca2

// "pluggable" non-member non-virtual global serializers

// Use cases:
// - Entry point_i32 convenience syntax sugar
// - syntax sugar
template < typename TYPE >
inline stream & operator >> (stream & stream, TYPE & t) { stream.defer_set_loading(); stream.exchange(t); return stream; }

template < typename TYPE >
inline stream & operator << (stream & stream, const TYPE & t) { stream.defer_set_storing(); stream.exchange((TYPE &) t); return stream; }

int file_procedure()
{

   ::file pfile = m_pcontext->m_papexcontext->file().get_file("C:\\window.window");

   in_addr addr;

   ::stream stream(pfile);

   stream >> addr;

}


int var_procedure()
{

   ::payload payload;

   in_addr addr;

   ::payload_stream stream(payload);

   stream >> addr;

}

class stream
{
public:

   virtual void read(i8 & i) {}
   virtual void read(string & i) {}

   virtual void write(const i8 & i) {}
   virtual void write(const ::string & str) {}

   template < typename TYPE >
   void default_exchange(TYPE & t) { is_loading() ? read(t) : write(t); }

   virtual void exchange(const ::atom & atom, i8 & i) { default_exchange(i); }
   virtual void exchange(const ::atom & atom, string & str) { default_exchange(str); }

   

   template < typename OBJECT >
   inline void exchange(const ::atom & atom, ::pointer<OBJECT>& pparticle)
   {
      if (is_storing())
      {
         write_object(atom, pparticle.m_p);
      }
      else
      {
         pparticle = read_object(atom);
      }
   }


   virtual void write_object(const ::atom & atom, const ::atom & idFactory, ::particle * pparticle)
   {
      exchange("id", idFactory);
      exchange("", pparticle);
   }

   virtual ::pointer<::matter>read_object(const ::atom & atom)
   {
      ::atom idFactory;
      exchange("id", idFactory);
      auto pparticle = __id_create<::matter>(idFactory);
      exchange("", pparticle);
      return pparticle;
   }


};


class payload_stream
{
public:

   ::payload & payload();

   virtual void read(i8 & i) {}
   virtual void read(string & i) {}

   virtual void write(const i8 & i) {}
   virtual void write(const ::string & str) {}

   template < typename TYPE >
   void default_exchange(const ::atom & atom, TYPE & t) { is_loading() ? t = operator[atom] : operator[atom] = t; }

   virtual void exchange(const ::atom & atom, i8 & i) { default_exchange(atom, i); }
   virtual void exchange(const ::atom & atom, string & str) { default_exchange(atom, str); }






   virtual void write_object(const ::atom & atom, const ::atom & idFactory, ::particle * pparticle) override
   {
      payload_stream stream(memory_new ::payload(&payload()[atom].propset()));
      stream.exchange("id", idFactory);
      stream.exchange("", pparticle);
   }

   virtual ::pointer<::contex_object>read_object(const ::atom & atom) override
   {
      payload_stream stream(memory_new ::payload(&payload()[atom].propset()));
      ::atom idFactory;
      stream.exchange("id", idFactory);
      auto pparticle = __id_create<::matter>(idFactory);
      stream.exchange("", pparticle);
      return pparticle;
   }

};
//void __exchange(stream & stream, i8 & i) { __exchange_blt(stream, i); }
//void __exchange(stream & stream, string & str) { __exchange_string(stream, str); }
//void __exchange(stream & stream, in_addr & addr) { __exchange_stringable(stream, addr); }
//
//
//void __exchange(stream & stream, const ::atom & atom, i8 & i) { __exchange_blt(stream, i); }
//void __exchange(stream & stream, const ::atom & atom, string & str) { __exchange_string(stream, str); }
//void __exchange(stream & stream, const ::atom & atom, in_addr & addr) { __exchange_stringable(stream, addr); }
//
//
//void __exchange(payload_stream & stream, i8 & i) { __exchange_blt(stream, i); }
//void __exchange(payload_stream & stream, string & str) { __exchange_string(stream, str); }
//void __exchange(payload_stream & stream, in_addr & addr) { __exchange_stringable(stream, addr); }


class window :
   virtual public matter
{
public:

   i8                   m_iVisible;
   string               m_strTitle;
   in_addr              m_addr;
   ::pointer<::matter> m_pobject;

   virtual void exchange(stream & s);

};

#define __EXCHANGE(xxx) stream.exchange(__STRING(xxx), m_##xxx)
#define __TYPE_EXCHANGE(xxx) stream.exchange(__STRING(xxx), t.m_##xxx)


void window::exchange(stream & stream)
{

   __EXCHANGE(iVisible); // expands... to: stream.exchange("iVisible", m_iVisible);
   __EXCHANGE(strTitle); // expands... to: stream.exchange("strTitle", m_strTitle);
   __EXCHANGE(addr);     // expands... to: stream.exchange("addr", m_addr);
   __EXCHANGE(pparticle);  // expands... to: stream.exchange("pparticle", m_pobject);

}


class exchanger
{

   stream * m_pstream;

   template
      exchange(atom, value) read / write value
   {
       if (is_storing)
       m_pstream->write(atom value)
       else
       m_pstream->read(atom, value)

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


           read(atom, i8) throw not_implemented;
           read(atom, i16) throw not_implemented;
           read(atom, i32) throw not_implemented;
           read(atom, i64) throw not_implemented;
           read(atom, u8) throw not_implemented;
           read(atom, u16) throw not_implemented;
           read(atom, u32) throw not_implemented;
           read(atom, u64) throw not_implemented;

           read(i8) throw not_implemented;
           read(i16) throw not_implemented;
           read(i32) throw not_implemented;
           read(i64) throw not_implemented;
           read(u8) throw not_implemented;
           read(u16) throw not_implemented;
           read(u32) throw not_implemented;
           read(u64) throw not_implemented;

           write(atom, i8) throw not_implemented;
           write(atom, i16) throw not_implemented;
           write(atom, i32) throw not_implemented;
           write(atom, i64) throw not_implemented;
           write(atom, u8) throw not_implemented;
           write(atom, u16) throw not_implemented;
           write(atom, u32) throw not_implemented;
           write(atom, u64) throw not_implemented;

           write(i8) throw not_implemented;
           write(i16) throw not_implemented;
           write(i32) throw not_implemented;
           write(i64) throw not_implemented;
           write(u8) throw not_implemented;
           write(u16) throw not_implemented;
           write(u32) throw not_implemented;
           write(u64) throw not_implemented;


           }


              binary_stream < FILE >
           {


           read(atom, i8) read(i8)
           read(atom, i16) read(i16)
           read(atom, i32) read(i32)
           read(atom, i64) read(i64)
           read(atom, u8) read(u8)
           read(atom, u16) read(u16)
           read(atom, u32) read(u32)
           read(atom, u64) read(u64)

           read(i8) m_pfile->read(i8)
           read(i16) m_pfile->read(i16)
           read(i32) m_pfile->read(i32)
           read(i64) m_pfile->read(i64)
           read(u8) m_pfile->read(u8)
           read(u16) m_pfile->read(u16)
           read(u32) m_pfile->read(u32)
           read(u64) m_pfile->read(u64)

           write(atom, i8) write(i8)
           write(atom, i16) write(i16)
           write(atom, i32) write(i32)
           write(atom, i64) write(i64)
           write(atom, u8) write(u8)
           write(atom, u16) write(u16)
           write(atom, u32) write(u32)
           write(atom, u64) write(u64)

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


           write(atom, i8) write(i8)
           write(atom, i16) write(i16)
           write(atom, i32) write(i32)
           write(atom, i64) write(i64)
           write(atom, u8) write(u8)
           write(atom, u16) write(u16)
           write(atom, u32) write(u32)
           write(atom, u64) write(u64)

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

           read(atom, i8)i8 = m_ppayload->operator[](atom);
           read(atom, i16) i16 = m_ppayload->operator[](atom);
           read(atom, i32) i32 = m_ppayload->operator[](atom);
           read(atom, i64) i64 = m_ppayload->operator[](atom);
           read(atom, u8) u8 = m_ppayload->operator[](atom);
           read(atom, u16) u16 = m_ppayload->operator[](atom);
           read(atom, u32) u32 = m_ppayload->operator[](atom);
           read(atom, u64) u64 = m_ppayload->operator[](atom);

           read(i8) i8 = *m_ppayload
           read(i16) i16 = *m_ppayload
           read(i32) i32 = *m_ppayload
           read(i64) i64 = *m_ppayload
           read(u8) u8 = *m_ppayload
           read(u16) u16 = *m_ppayload
           read(u32) u32 = *m_ppayload
           read(u64) u64 = *m_ppayload

           write(atom, i8) write(i8)
           write(atom, i16) write(i16)
           write(atom, i32) write(i32)
           write(atom, i64) write(i64)
           write(atom, u8) write(u8)
           write(atom, u16) write(u16)
           write(atom, u32) write(u32)
           write(atom, u64) write(u64)

           write(i8) m_pfile->write(i8)
           write(i16) m_pfile->write(i16)
           write(i32) m_pfile->write(i32)
           write(i64) m_pfile->write(i64)
           write(u8) m_pfile->write(u8)
           write(u16) m_pfile->write(u16)
           write(u32) m_pfile->write(u32)
           write(u64) m_pfile->write(u64)

           }




              stream & operator >> (stream & stream, matter & o)
           {

              exchange e(stream);

              e.defer_set_loading();

              e.exchange(s);

           }

           stream & operator >> (stream & s, matter & o)
           {

              o.exchange(stream);

           }


           window new_frame_window()
           {
              return memory_new frame_window();
           }
