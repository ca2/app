// 2020-01-11 - Curitiba, ca2

// "pluggable" non-member non-virtual global serializers


int main2()
{

   ::file pfile = pcontext->m_papexcontext->file()->get_file("C:\\window.window");

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

    ::file pfile = pcontext->m_papexcontext->file()->get_file("C:\\window.window");

    auto pinteraction = memory_new window();

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


void __exchange(stream & stream, i8 & i) { __exchange_blt(stream, i); }
void __exchange(stream & stream, string & str) { __exchange_string(stream, str); }
void __exchange(stream & stream, in_addr & addr) { __exchange_stringable(stream, addr); }

void __exchange(payload_stream & stream, i8 & i) { __exchange_blt(stream, i); }
void __exchange(payload_stream & stream, string & str) { __exchange_string(stream, str); }
void __exchange(payload_stream & stream, in_addr & addr) { __exchange_stringable(stream, addr); }

class window
{
public:

   i8          m_iVisible;
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
read(atom, i16) i16= m_ppayload->operator[](atom);
read(atom, i32) i32= m_ppayload->operator[](atom);
read(atom, i64) i64= m_ppayload->operator[](atom);
read(atom, u8) u8= m_ppayload->operator[](atom);
read(atom, u16) u16= m_ppayload->operator[](atom);
read(atom, u32) u32= m_ppayload->operator[](atom);
read(atom, u64) u64= m_ppayload->operator[](atom);

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
