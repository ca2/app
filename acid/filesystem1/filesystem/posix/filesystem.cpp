//
// Created by camilo on 2024-05-22 05:55 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "acid/filesystem/filesystem/filesystem.h"

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


namespace filesystem
{


    bool touch(const string_pointer * psz)
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

    void change_directory(const char * psz)
    {

        chdir(psz);

    }

    ::acid::string FILE_as_string(FILE * f)
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


    ::acid::string as_string(const char * pszFilename)
    {

        ::acid::string str;

        FILE * f = fopen (pszFilename, "rb");

        if (f)
        {

            str = FILE_as_string(f);

            fclose (f);

        }

        return str;

    }


    ::acid::string current_directory()
    {

        //getcwd(strCurDir, sizeof(szCurDir));
        return {transfer_t{}, getcwd(nullptr, 0)};

    }


    ::acid::string get_temporary_file_name()
    {

        ::acid::string str;

        ::acid::string strCurDir = ::filesystem::current_directory();

        auto ptmpname = tempnam(strCurDir, "tmpfl");

        return {transfer_t{}, ptmpname};

    }


} // namespace filesystem



