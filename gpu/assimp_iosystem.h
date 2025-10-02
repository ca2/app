//
// Created by camilo on 2025-09-27.
//
#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/IOSystem.hpp>
#include <assimp/IOStream.hpp>
#include "acme/filesystem/filesystem/file_context.h"

#include "acme/constant/filesystem.h"



// Custom IOStream that reads from memory
class assimp_iostream : public Assimp::IOStream{
public:

::pointer < ::file::file > m_pfile;

    assimp_iostream(::file::file * pfile):m_pfile(pfile) {}
    ~assimp_iostream() override
    {


}

    size_t Read(void* pvBuffer, size_t pSize, size_t pCount) override {

       auto read = m_pfile->read(pvBuffer, pSize * pCount);

       return read / pSize;
    }

    size_t Write(const void*  p, size_t size, size_t  count) override {

       auto len = size * count;
       m_pfile->write(p, len);
        return len/size;
    }

    aiReturn Seek(size_t pOffset, aiOrigin pOrigin) override {

       try
       {
          if (pOrigin == aiOrigin_SET) m_pfile->translate(pOffset, ::enum_seek::e_seek_set);
          else if (pOrigin == aiOrigin_CUR)m_pfile->translate(pOffset, ::enum_seek::e_seek_current);
          else if (pOrigin == aiOrigin_END) m_pfile->translate(-(iptr)pOffset, ::enum_seek::e_seek_from_end);
       }
       catch (...)
       {

          return aiReturn_FAILURE;

       }
        return aiReturn_SUCCESS;
    }

    size_t Tell() const override { return m_pfile->get_position(); }
    size_t FileSize() const override { return m_pfile->size(); }
    void Flush() override {m_pfile->flush();}

};

// Custom IOSystem
class assimp_iosystem : public Assimp::IOSystem
{
public:

   ::particle * m_p;

   assimp_iosystem(::particle * pparticle) :m_p(pparticle){}
   ~assimp_iosystem() override
   {


   }

    bool Exists(const char* pFile) const override {
        return m_p->file()->exists(pFile);
    }

    char getOsSeparator() const override {
        return '/';
    }

    Assimp::IOStream* Open(const char* pFile, const char* pMode = "rb") override {
        // In real use, you'd open files from your source (zip, memory, etc.)
        // Here we simulate loading from memory
        //std::vector<char> fakeData;

       ::string strMode(pMode);

       ::pointer < ::file::file > pfile;

       if (strMode.case_insensitive_contains("w"))
       {

          pfile = m_p->file()->get_writer(pFile);

       }
       else
       {
          pfile = m_p->file()->get_reader(pFile);

       }

        // fill fakeData with file contents...
        auto piostream = øraw_new assimp_iostream (pfile);

       return piostream;

    }

    void Close(Assimp::IOStream* pFile) override
   {
        delete pFile;
    }
};

// int main() {
//     Assimp::Importer importer;
//
//     // Set our custom IO handler
//     importer.SetIOHandler(new MyIOSystem());
//
//     const aiScene* scene = importer.ReadFile("dummy.obj",
//         aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
//
//     if (!scene) {
//         std::cerr << importer.GetErrorString() << std::endl;
//         return 1;
//     }
//
//     std::cout << "Loaded scene with " << scene->mNumMeshes << " meshes." << std::endl;
//     return 0;
// }
