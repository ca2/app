// 2020-01-11 - Curitiba, ca2

// "pluggable" non-member non-virtual global serializers

// Use cases:
// - Entry int_point convenience syntax sugar
// - syntax sugar
template < typename TYPE >
inline stream & operator >> (stream & stream, TYPE & t) { stream.defer_set_loading(); stream.exchange(t); return stream; }

template < typename TYPE >
inline stream & operator << (stream & stream, const TYPE & t) { stream.defer_set_storing(); stream.exchange((TYPE &) t); return stream; }

int file_procedure()
{

   ::file pfile = file()->get_file("C:\\window.window");

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

   virtual void read(char & i) {}
   virtual void read(string & i) {}

   virtual void write(const char & i) {}
   virtual void write(const ::scoped_string & scopedstr) {}

   template < typename TYPE >
   void default_exchange(TYPE & t) { is_loading() ? read(t) : write(t); }

   virtual void exchange(const ::atom & atom, char & i) { default_exchange(i); }
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
      auto pparticle = øcreate_by_id<::matter>(idFactory);
      exchange("", pparticle);
      return pparticle;
   }


};


class payload_stream
{
public:

   ::payload & payload();

   virtual void read(char & i) {}
   virtual void read(string & i) {}

   virtual void write(const char & i) {}
   virtual void write(const ::scoped_string & scopedstr) {}

   template < typename TYPE >
   void default_exchange(const ::atom & atom, TYPE & t) { is_loading() ? t = operator[atom] : operator[atom] = t; }

   virtual void exchange(const ::atom & atom, char & i) { default_exchange(atom, i); }
   virtual void exchange(const ::atom & atom, string & str) { default_exchange(atom, str); }






   virtual void write_object(const ::atom & atom, const ::atom & idFactory, ::particle * pparticle) override
   {
      payload_stream stream(øallocate< ::payload(&payload()[atom].propset >()));
      stream.exchange("id", idFactory);
      stream.exchange("", pparticle);
   }

   virtual ::pointer<::contex_object>read_object(const ::atom & atom) override
   {
      payload_stream stream(øallocate< ::payload(&payload()[atom].propset >()));
      ::atom idFactory;
      stream.exchange("id", idFactory);
      auto pparticle = øcreate_by_id<::matter>(idFactory);
      stream.exchange("", pparticle);
      return pparticle;
   }

};
//void __exchange(stream & stream, char & i) { __exchange_blt(stream, i); }
//void __exchange(stream & stream, string & str) { __exchange_string(stream, str); }
//void __exchange(stream & stream, in_addr & addr) { __exchange_stringable(stream, addr); }
//
//
//void __exchange(stream & stream, const ::atom & atom, char & i) { __exchange_blt(stream, i); }
//void __exchange(stream & stream, const ::atom & atom, string & str) { __exchange_string(stream, str); }
//void __exchange(stream & stream, const ::atom & atom, in_addr & addr) { __exchange_stringable(stream, addr); }
//
//
//void __exchange(payload_stream & stream, char & i) { __exchange_blt(stream, i); }
//void __exchange(payload_stream & stream, string & str) { __exchange_string(stream, str); }
//void __exchange(payload_stream & stream, in_addr & addr) { __exchange_stringable(stream, addr); }


class window :
   virtual public matter
{
public:

   char                   m_iVisible;
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


           read(atom, char) throw not_implemented;
           read(atom, short) throw not_implemented;
           read(atom, int) throw not_implemented;
           read(atom, long long) throw not_implemented;
           read(atom, unsigned char) throw not_implemented;
           read(atom, unsigned short) throw not_implemented;
           read(atom, unsigned int) throw not_implemented;
           read(atom, unsigned long long) throw not_implemented;

           read(char) throw not_implemented;
           read(short) throw not_implemented;
           read(int) throw not_implemented;
           read(long long) throw not_implemented;
           read(unsigned char) throw not_implemented;
           read(unsigned short) throw not_implemented;
           read(unsigned int) throw not_implemented;
           read(unsigned long long) throw not_implemented;

           write(atom, char) throw not_implemented;
           write(atom, short) throw not_implemented;
           write(atom, int) throw not_implemented;
           write(atom, long long) throw not_implemented;
           write(atom, unsigned char) throw not_implemented;
           write(atom, unsigned short) throw not_implemented;
           write(atom, unsigned int) throw not_implemented;
           write(atom, unsigned long long) throw not_implemented;

           write(char) throw not_implemented;
           write(short) throw not_implemented;
           write(int) throw not_implemented;
           write(long long) throw not_implemented;
           write(unsigned char) throw not_implemented;
           write(unsigned short) throw not_implemented;
           write(unsigned int) throw not_implemented;
           write(unsigned long long) throw not_implemented;


           }


              binary_stream
           {


           read(atom, char) read(char)
           read(atom, short) read(short)
           read(atom, int) read(int)
           read(atom, long long) read(long long)
           read(atom, unsigned char) read(unsigned char)
           read(atom, unsigned short) read(unsigned short)
           read(atom, unsigned int) read(unsigned int)
           read(atom, unsigned long long) read(unsigned long long)

           read(char) m_pfile->read(char)
           read(short) m_pfile->read(short)
           read(int) m_pfile->read(int)
           read(long long) m_pfile->read(long long)
           read(unsigned char) m_pfile->read(unsigned char)
           read(unsigned short) m_pfile->read(unsigned short)
           read(unsigned int) m_pfile->read(unsigned int)
           read(unsigned long long) m_pfile->read(unsigned long long)

           write(atom, char) write(char)
           write(atom, short) write(short)
           write(atom, int) write(int)
           write(atom, long long) write(long long)
           write(atom, unsigned char) write(unsigned char)
           write(atom, unsigned short) write(unsigned short)
           write(atom, unsigned int) write(unsigned int)
           write(atom, unsigned long long) write(unsigned long long)

           write(char) m_pfile->write(char)
           write(short) m_pfile->write(short)
           write(int) m_pfile->write(int)
           write(long long) m_pfile->write(long long)
           write(unsigned char) m_pfile->write(unsigned char)
           write(unsigned short) m_pfile->write(unsigned short)
           write(unsigned int) m_pfile->write(unsigned int)
           write(unsigned long long) m_pfile->write(unsigned long long)


           }

              text_stream
           {


           write(atom, char) write(char)
           write(atom, short) write(short)
           write(atom, int) write(int)
           write(atom, long long) write(long long)
           write(atom, unsigned char) write(unsigned char)
           write(atom, unsigned short) write(unsigned short)
           write(atom, unsigned int) write(unsigned int)
           write(atom, unsigned long long) write(unsigned long long)

           write(char) m_pfile->write(char)
           write(short) m_pfile->write(short)
           write(int) m_pfile->write(int)
           write(long long) m_pfile->write(long long)
           write(unsigned char) m_pfile->write(unsigned char)
           write(unsigned short) m_pfile->write(unsigned short)
           write(unsigned int) m_pfile->write(unsigned int)
           write(unsigned long long) m_pfile->write(unsigned long long)


           }


              template < typename CONTAINER >
           id_stream :
           stream
           {

           read(atom, char)char = m_ppayload->operator[](atom);
           read(atom, short) short = m_ppayload->operator[](atom);
           read(atom, int) int = m_ppayload->operator[](atom);
           read(atom, long long) long long = m_ppayload->operator[](atom);
           read(atom, unsigned char) unsigned char = m_ppayload->operator[](atom);
           read(atom, unsigned short) unsigned short = m_ppayload->operator[](atom);
           read(atom, unsigned int) unsigned int = m_ppayload->operator[](atom);
           read(atom, unsigned long long) unsigned long long = m_ppayload->operator[](atom);

           read(char) char = *m_ppayload
           read(short) short = *m_ppayload
           read(int) int = *m_ppayload
           read(long long) long long = *m_ppayload
           read(unsigned char) uch = *m_ppayload
           read(unsigned short) unsigned short = *m_ppayload
           read(unsigned int) unsigned int = *m_ppayload
           read(unsigned long long) unsigned long long = *m_ppayload

           write(atom, char) write(char)
           write(atom, short) write(short)
           write(atom, int) write(int)
           write(atom, long long) write(long long)
           write(atom, unsigned char) write(unsigned char)
           write(atom, unsigned short) write(unsigned short)
           write(atom, unsigned int) write(unsigned int)
           write(atom, unsigned long long) write(unsigned long long)

           write(char) m_pfile->write(char)
           write(short) m_pfile->write(short)
           write(int) m_pfile->write(int)
           write(long long) m_pfile->write(long long)
           write(unsigned char) m_pfile->write(unsigned char)
           write(unsigned short) m_pfile->write(unsigned short)
           write(unsigned int) m_pfile->write(unsigned int)
           write(unsigned long long) m_pfile->write(unsigned long long)

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
              return øallocate frame_window();
           }
