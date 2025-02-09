// 2020-01-11 - Curitiba, ca2

// "pluggable" non-member non-virtual global serializers


int main2()
{

   ::file pfile = file()->get_file("C:\\window.window");

   in_addr addr;

   ::stream stream(pfile);

   stream >> addr;

   window::in_addr();

}


stream & operator __exchange (stream & stream, in_addr & o)
{

   string str = to_string(o);

   stream.exchange(atom, s);

}


void window::exchange(stream & stream)
{
   e.exchange("a", m_a);
   e.exchange("c", m_b);
   e.exchange("b", m_c);
   e.exchange("b", m_inaddr);

}

void __exchange(stream & s, const ::atom & atom,)


int main()
{

    ::file pfile = file()->get_file("C:\\window.window");

    auto pinteraction = __allocate window();

    ::stream stream(pfile);

    stream >> *pinteraction;

    pinteraction ->show();

    pui2 = new_frame_window();

    ::stream stream(pfile);

    stream >> *pinteraction;


    property_set set;


    id_stream idstream(set);

    idstream >> * pinteraction;

}


void __exchange(stream & stream, char & i) { __exchange_blt(stream, i); }
void __exchange(stream & stream, string & str) { __exchange_string(stream, str); }
void __exchange(stream & stream, in_addr & addr) { __exchange_stringable(stream, addr); }

void __exchange(payload_stream & stream, char & i) { __exchange_blt(stream, i); }
void __exchange(payload_stream & stream, string & str) { __exchange_string(stream, str); }
void __exchange(payload_stream & stream, in_addr & addr) { __exchange_stringable(stream, addr); }

class window
{
public:

   char          m_iVisible;
   string      m_strTitle;
   in_addr     m_addr;
   ::matter    m_pobject;

   void exchange(stream & s);

};
virtual void window::exchange(exchanger & e)
{
   e.exchange("a", m_a);
   e.exchange("c", m_b);
   e.exchange("b", m_c);

}



class exchanger
{

    stream * m_pstream;

template
exchange(atom, value) read/write value
{
    if(is_storing)
    m_pstream->write(atom value)
    else 
    m_pstream->read(atom, value)

}
template
exchange(value) read/write value
{
    if(is_storing)
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
read(atom, short) short= m_ppayload->operator[](atom);
read(atom, int) int= m_ppayload->operator[](atom);
read(atom, long long) long long= m_ppayload->operator[](atom);
read(atom, unsigned char) unsigned char= m_ppayload->operator[](atom);
read(atom, unsigned short) unsigned short= m_ppayload->operator[](atom);
read(atom, unsigned int) unsigned int= m_ppayload->operator[](atom);
read(atom, unsigned long long) unsigned long long= m_ppayload->operator[](atom);

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
    return __allocate frame_window();
}
