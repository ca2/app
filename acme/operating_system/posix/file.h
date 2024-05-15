//
// Created by camilo on 2024-05-14 21:42 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace unistd
{


class file
{
public:

    int m_iFile;


    file();
    file(const file & file);
    file(int iFile);
    ~file();

    int create_tmpfile_cloexec(char * tmpname);
    int create_anonymous_file(memsize s);
    int set_cloexec_or_close();

    int close();

    bool is_opened() const {return m_iFile>=0;}

    memsize read(void * p, memsize s);
    int write(const void * p, memsize s);

};


}//namespace unistd