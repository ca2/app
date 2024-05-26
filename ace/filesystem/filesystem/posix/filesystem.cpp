//
// Created by camilo on 2024-05-22 05:55 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "ace/filesystem/filesystem/filesystem.h"

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


namespace ace
{


    bool touch_file(const char *filename)
    {
        int fd = open(filename, O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);

        if (fd == -1) {
            perror("Unable to touch file");
            return false;
        }

        close(fd);
        return true;
    }


    void create_directory(const char * psz)
    {

        mkdir(psz, 0777);

    }


    ::ace::string FILE_as_string(FILE * f)
    {

        if (!f)
        {

            return nullptr;

        }

        char * buffer = nullptr;

        long length;

        fseek (f, 0, SEEK_END);

        length = ftell (f);

        fseek (f, 0, SEEK_SET);

        buffer = (char *) malloc (length);

        if (buffer)
        {

            fread (buffer, 1, length, f);

        }

        return {transfer_t{}, buffer};

    }


    ::ace::string file_as_string(const char * pszFilename)
    {

        ::ace::string str;

        FILE * f = fopen (pszFilename, "rb");

        if (f)
        {

            str = FILE_as_string(f);

            fclose (f);

        }

        return str;

    }


    ::ace::string get_current_directory()
    {

        //getcwd(strCurDir, sizeof(szCurDir));
        return {transfer_t{}, getcwd(nullptr, 0)};

    }


    ::ace::string get_temporary_file_name()
    {

        ::ace::string str;

        ::ace::string strCurDir = ::ace::get_current_directory();

        auto ptmpname = tempnam(strCurDir, "tmpfl");

        return {transfer_t{}, ptmpname};

    }



} // namespace ace