//
// Created by camilo on 2024-05-14 21:42 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace unistd
{


class file
{
public:

    ::i32 m_iFile;


    file();
    file(const file & file);
    file(::i32 iFile);
    ~file();

    ::i32 create_tmpfile_cloexec(char_pointer tmpname);
    ::i32 create_anonymous_file(memsize s);
    ::i32 set_cloexec_or_close();

    ::i32 close();

    bool is_opened() const {return m_iFile>=0;}

    memsize read(void * p, memsize s);
    long write(const void * p, memsize s);

};


}//namespace unistd
