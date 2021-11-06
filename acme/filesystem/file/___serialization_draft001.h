// 2020-01-11 - Curitiba, ca2

// "pluggable" non-member non-virtual global serializers


int main2()
{

   ::file pfile = pcontext->m_papexcontext->file().get_file("C:\\window.window");

   in_addr addr;

   ::stream stream(pfile);

   stream >> addr;

   window::in_addr();

}


stream & operator __exchange (stream & stream, in_addr & o)
{

   string str = to_string(o);

   stream.exchange(id, s);

}


void window::exchange(stream & stream)
{
   e.exchange("a", m_a);
   e.exchange("c", m_b);
   e.exchange("b", m_c);
   e.exchange("b", m_inaddr);

}

void __exchange(stream & s, const ::id & id,)


int main()
{

    ::file pfile = pcontext->m_papexcontext->file().get_file("C:\\window.window");

    auto pinteraction = new window();

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

void __exchange(var_stream & stream, i8 & i) { __exchange_blt(stream, i); }
void __exchange(var_stream & stream, string & str) { __exchange_string(stream, str); }
void __exchange(var_stream & stream, in_addr & addr) { __exchange_stringable(stream, addr); }

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
exchange(id, value) read/write value
{
    if(is_storing)
    m_pstream->write(id value)
    else 
    m_pstream->read(id, value)

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

read(id, i8)i8 = m_ppayload->operator[](id);
read(id, i16) i16= m_ppayload->operator[](id);
read(id, i32) i32= m_ppayload->operator[](id);
read(id, i64) i64= m_ppayload->operator[](id);
read(id, u8) u8= m_ppayload->operator[](id);
read(id, u16) u16= m_ppayload->operator[](id);
read(id, u32) u32= m_ppayload->operator[](id);
read(id, u64) u64= m_ppayload->operator[](id);

read(i8) i8 = *m_ppayload
read(i16) i16 = *m_ppayload
read(i32) i32 = *m_ppayload
read(i64) i64 = *m_ppayload
read(u8) u8 = *m_ppayload
read(u16) u16 = *m_ppayload
read(u32) u32 = *m_ppayload
read(u64) u64 = *m_ppayload

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
    return new frame_window();
}
