//
//  registry.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 04/04/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#include "framework.h"
#include "registry.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/platform/application.h"


#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

//using namespace rapidjson;

namespace platform
{

   static bool ensure_object(::rapidjson::Value &v, ::rapidjson::Document::AllocatorType &a)
   {
      if (!v.IsObject())
      {
         v.SetObject();
      }
      return true;
   }

   static void set_type_and_data(::rapidjson::Value &entry, const char *type, ::rapidjson::Value &data,
                                 ::rapidjson::Document::AllocatorType &alloc)
   {
      entry.SetObject();

      ::rapidjson::Value t(type, alloc);
      entry.AddMember("type", t, alloc);
      entry.AddMember("data", data, alloc);
   }


   void registry_key::close()
   {
      
      m_pregistrykey->close();
      
   }

   
   ::e_status registry_key::_set_string(const ::scoped_string &scopedstrName, const ::scoped_string &scopedstr)
   {
      
      return m_pregistrykey->_set_string(scopedstrName, scopedstr);
      
   }

   
   ::e_status registry_key::_set_dword(const ::scoped_string &scopedstrName, unsigned int u)
   {
      
      return m_pregistrykey->_set_dword(scopedstrName, u);
      
   }

   
   ::e_status registry_key::_set_qword(const ::scoped_string &scopedstrName, unsigned long long ull)
   {
      
      return m_pregistrykey->_set_qword(scopedstrName, ull);
      
   }

   
   ::e_status registry_key::_set_binary(const ::scoped_string &scopedstrName, const ::block &block)
   {
      
      return m_pregistrykey->_set_binary(scopedstrName, block);
      
   }

   

   ::e_status registry_key::_get_string(const ::scoped_string &scopedstrName, ::string &str)
   {
      
      return m_pregistrykey->_get_string(scopedstrName, str);
      
   }

   
   ::e_status registry_key::_get_dword(const ::scoped_string &scopedstrName, unsigned int &u)
   {
      
      return m_pregistrykey->_get_dword(scopedstrName, u);
      
   }

   
   ::e_status registry_key::_get_qword(const ::scoped_string &scopedstrName, unsigned long long &ull)
   {
      
      return m_pregistrykey->_get_qword(scopedstrName, ull);
      
   }

   
   ::e_status registry_key::_get_binary(const ::scoped_string &scopedstrName, ::memory &memory)
   {
      
      return m_pregistrykey->_get_binary(scopedstrName, memory);
      
   }

   


   ::e_status registry_key::_erase_payload(const ::scoped_string &scopedstrName)
   {
      
      return m_pregistrykey->_erase_payload(scopedstrName);
      
   }

   
   ::e_status registry_key::_has_payload(const ::scoped_string &scopedstrName, bool & bOk)
   {
      
      return m_pregistrykey->_has_payload(scopedstrName, bOk);
      
   }

   
   ::e_status registry_key::_payload_type(const ::scoped_string &scopedstrName, enum_registry & eregistry)
   {
      
      return m_pregistrykey->_payload_type(scopedstrName, eregistry);
      
   }

   

   class CLASS_DECL_ACME registry_implementation :
      virtual public registry
   {
   public:

      ::file::path m_pathFileSystem;
      ::rapidjson::Document m_rapidjsondocument;

      registry_implementation();
      ~registry_implementation();

      void open_from_file(const ::file::path &path)override;
      void flush() override;
      void close() override;
      ::pointer<registry_key_interface> open_key(const ::file::path &path) override;
      ::pointer<registry_key_interface> create_key(const ::file::path &path) override;
      void erase_key(const ::file::path &path) override;


      ::rapidjson::Value *_get_key_node(const ::file::path & path, bool create);

   
   };


   registry_implementation::registry_implementation()
   {


   }


   registry_implementation::~registry_implementation()
   {


   }

   
   struct CLASS_DECL_ACME registry_key_implementation : 
      virtual public registry_key
   {
   public:
      
      
      ::pointer<registry_implementation> m_pregistry;
      ::file::path m_path;


      registry_key_implementation();
      ~registry_key_implementation() override;



      
      //bool ensure_object(::rapidjson::Value &v, ::rapidjson::Document::AllocatorType &a);
      virtual ::rapidjson::Value * _get_payloads(bool create);
      virtual ::rapidjson::Value * _get_payload_entry(const ::scoped_string &scopedstrName, bool create);

      ::e_status _set_string(const ::scoped_string &scopedstrName, const ::scoped_string & scopedstr) override;
      ::e_status _set_dword(const ::scoped_string &scopedstrName, unsigned int value) override;
      ::e_status _set_qword(const ::scoped_string &scopedstrName, unsigned long long value) override;
      ::e_status _set_binary(const ::scoped_string &scopedstrName, const ::block & block) override;


      ::e_status _get_string(const ::scoped_string &scopedstrName, string &str) override;
      ::e_status _get_dword(const ::scoped_string &scopedstrName, unsigned int &u) override;
      ::e_status _get_qword(const ::scoped_string &scopedstrName, unsigned long long &ll) override;
      ::e_status _get_binary(const ::scoped_string &scopedstrName, memory &memory) override;

      ::e_status _erase_payload(const ::scoped_string &scopedstrName) override;
      ::e_status _has_payload(const ::scoped_string &scopedstrName, bool & bExists) override;
      ::e_status _payload_type(const ::scoped_string &scopedstrName, enum_registry & eregistry) override;


   };


   registry_key_implementation::registry_key_implementation()
   {

   }
   registry_key_implementation::~registry_key_implementation()
   {

   }

   // struct RegX {
   //     std::string filename;
   //     Document doc;
   // };
   //
   // struct registry_key {
   //     RegX *m_pregistry;
   //     std::string path;
   // };

   ///* ============================================================================
   //   Helpers
   //   ============================================================================ */

   //static std::vector<std::string> split_path(const ::file::path & path)
   //{
   //   std::vector<std::string> parts;
   //   if (!path) return parts;

   //   std::string cur;
   //   for (const char *p = path; *p; ++p) {
   //      if (*p == '\\' || *p == '/') {
   //         if (!cur.empty()) {
   //            parts.push_back(cur);
   //            cur.clear();
   //         }
   //      } else {
   //         cur.push_back(*p);
   //      }
   //   }
   //   if (!cur.empty()) parts.push_back(cur);
   //   return parts;
   //}

   static ::string bin_to_hex(const unsigned char *data, memsize size) 
   {
      static const char *hex = "0123456789ABCDEF";
      ::string out;
      auto p = out.get_buffer(size * 2);
      for (size_t i = 0; i < size; ++i)
      {
         unsigned char b = data[i];
         *p = hex[(b >> 4) & 0xF];
         p++;
         *p = hex[b & 0xF];
         p++;
      }
      out.release_buffer(size * 2);
      return ::transfer(out);
   }

   static int hex_val(char c) {
      if (c >= '0' && c <= '9') return c - '0';
      if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
      if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
      return -1;
   }

   static ::e_status hex_to_bin(const char *hex, memory & memory) {
      if (!hex) return error_bad_argument;
      size_t n = std::strlen(hex);
      if (n % 2 != 0) return error_io;

      size_t needed = n / 2;

      memory.set_size(needed);

      auto buf = memory.data();

      for (size_t i = 0; i < needed; ++i) {
         int hi = hex_val(hex[i * 2]);
         int lo = hex_val(hex[i * 2 + 1]);
         if (hi < 0 || lo < 0) return error_io;
         *buf = (unsigned char)((hi << 4) | lo);
         buf++;
      }

      return ::success;
      
   }

   


   ::rapidjson::Value *registry_implementation::_get_key_node(const ::file::path & path, bool create)
   {
      if (!path) return nullptr;

      auto parts = path.parts();
      if (parts.is_empty()) return nullptr;

      ::rapidjson::Value *cur = &m_rapidjsondocument;
      auto &alloc = m_rapidjsondocument.GetAllocator();

      for (const auto &part : parts) {
         ensure_object(*cur, alloc);

         if (!cur->HasMember(part.c_str())) {
            if (!create) return nullptr;

            ::rapidjson::Value k(part.c_str(), alloc);
            ::rapidjson::Value obj(::rapidjson::kObjectType);
            cur->AddMember(k, obj, alloc);
         }

         ::rapidjson::Value &next = (*cur)[part.c_str()];
         if (!next.IsObject()) {
            if (!create) return nullptr;
            next.SetObject();
         }

         cur = &next;
      }

      return cur;

   }


   ::rapidjson::Value *registry_key_implementation::_get_payloads(bool create)
   {

      
      if (::is_null(this) || ::is_null(m_pregistry)) return nullptr;

      ::rapidjson::Value *node = m_pregistry->_get_key_node(m_path.c_str(), create);
      if (!node) return nullptr;

      auto &alloc = m_pregistry->m_rapidjsondocument.GetAllocator();

      if (!node->HasMember("__values__"))
      {
         if (!create) return nullptr;
         ::rapidjson::Value k("__values__", alloc);
         ::rapidjson::Value obj(::rapidjson::kObjectType);
         node->AddMember(k, obj, alloc);
      }

      ::rapidjson::Value &vals = (*node)["__values__"];
      if (!vals.IsObject()) 
      {
         if (!create) return nullptr;
         vals.SetObject();
      }

      return &vals;
   }

   ::rapidjson::Value *registry_key_implementation::_get_payload_entry(const ::scoped_string & scopedstrName, bool create) 
   {

      if (::is_null(this) || scopedstrName.is_empty()) return nullptr;
      auto ppayloads = _get_payloads(create);
      if (!ppayloads) return nullptr;

      auto &alloc = m_pregistry->m_rapidjsondocument.GetAllocator();

      ::string strName(scopedstrName);

      if (!ppayloads->HasMember(strName)) {
         if (!create) return nullptr;
         ::rapidjson::Value k(strName, alloc);
         ::rapidjson::Value obj(::rapidjson::kObjectType);
         ppayloads->AddMember(k, obj, alloc);
      }

      auto &entry = (*ppayloads)[strName.c_str()];
      if (!entry.IsObject()) {
         if (!create) return nullptr;
         entry.SetObject();
      }

      return &entry;
   }

   
   /* ============================================================================
      Lifecycle
      ============================================================================ */

   void registry_implementation::open_from_file(const ::file::path &path) 
   {
      if (path.is_empty())
      {

         throw ::exception(error_bad_argument);
      }

      ////RegX *reg = new (std::nothrow) RegX();
      auto reg = this;
      //if (!reg) throw ::exception(error_no_memory);

      reg->m_pathFileSystem = path;
      m_rapidjsondocument.SetObject();

      auto content = file()->as_string(path);

      //std::ifstream ifs(filename, std::ios::binary);
      //if (ifs.good()) {
      //   std::stringstream ss;
      //   ss << ifs.rdbuf();
      //   std::string content = ss.str();

         if (content.has_character()) 
         {
            m_rapidjsondocument.Parse(content.c_str());
            if (m_rapidjsondocument.HasParseError() || !m_rapidjsondocument.IsObject()) {
               m_rapidjsondocument.SetObject();
            }
         }
      //}

      //*out_reg = reg;
      //return ::success;
   }



   void registry_implementation::flush()
   {
      if (::is_null(this))
      {

         throw ::exception(error_bad_argument);
      }

      ::rapidjson::StringBuffer buffer;
      ::rapidjson::PrettyWriter<::rapidjson::StringBuffer> writer(buffer);
      m_rapidjsondocument.Accept(writer);

      file()->put_memory(m_pathFileSystem, {buffer.GetString(), buffer.GetSize()});

   }

   void registry_implementation::close()
   {
      flush();
      //if (!reg) return;
      //RegXFlush(reg);
      //delete reg;
   }

   /* ============================================================================
      Key operations
      ============================================================================ */

   ::pointer<registry_key_interface>registry_implementation::open_key(const ::file::path &path)
   {
      if (::is_null(this) || path.is_empty()) throw ::exception(error_bad_argument);

      auto pnode = _get_key_node(path, false);
      if (!pnode) throw ::exception(error_not_found);

      auto pkey = create_newø<registry_key_implementation>();
      if (!pkey) throw ::exception(error_no_memory);

      pkey->m_pregistry = this;
      pkey->m_path = path;
      //*out_key = key;
      //return ::success;
      return pkey;
   }

   
   ::pointer<registry_key_interface> registry_implementation::create_key(const ::file::path &path)
   {
      if (::is_null(this) || path.is_empty()) throw ::exception(error_bad_argument);

      rapidjson::Value *pnode = _get_key_node(path, true);
      if (!pnode) throw ::exception(error_io);

      auto pkey = create_newø<registry_key_implementation>();
      if (!pkey)
         throw ::exception(error_no_memory);
      pkey->m_pregistry = this;
      pkey->m_path = path;
      return pkey;
   }


   void registry_implementation::erase_key(const ::file::path &path)
   {
      if (::is_null(this) || path.is_empty())
         throw ::exception(error_bad_argument);

      auto parts = path.parts();
      if (parts.is_empty()) throw ::exception(error_bad_argument);
      if (parts.size() == 1) throw ::exception(error_io); /* don't delete top root directly */

      rapidjson::Value *cur = &m_rapidjsondocument;
      for (size_t i = 0; i + 1 < parts.size(); ++i) {
         if (!cur->IsObject() || !cur->HasMember(parts[i].c_str())) {
            throw ::exception(error_not_found);
         }
         cur = &(*cur)[parts[i].c_str()];
      }

      if (!cur->IsObject() || !cur->HasMember(parts.last().c_str())) {
         throw ::exception(error_not_found);
      }

      cur->RemoveMember(parts.last().c_str());
      
   }

   /* ============================================================================
      Set values
      ============================================================================ */

   ::e_status registry_key_implementation::_set_string(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstr)
   {
      auto key = this;
      if (!key || scopedstrName.is_empty()) return error_bad_argument;

      auto pentry = _get_payload_entry(scopedstrName, true);
      if (!pentry) return error_io;

      auto &alloc = m_pregistry->m_rapidjsondocument.GetAllocator();
      ::rapidjson::Value data(::string(scopedstr), alloc);
      set_type_and_data(*pentry, "sz", data, alloc);
      return ::success;
   }


   ::e_status registry_key_implementation::_set_dword(const ::scoped_string & scopedstrName, unsigned int u)
   {
      if (::is_null(this) || scopedstrName.is_empty()) return error_bad_argument;

      auto pentry = _get_payload_entry(scopedstrName, true);
      if (!pentry) return error_io;

      auto &alloc = m_pregistry->m_rapidjsondocument.GetAllocator();
      ::rapidjson::Value data(u);
      set_type_and_data(*pentry, "dword", data, alloc);
      return ::success;
   }


   ::e_status registry_key_implementation::_set_qword(const ::scoped_string &scopedstrName, unsigned long long ull)
   {
      if (::is_null(this) || scopedstrName.is_empty())
         return error_bad_argument;

      auto pentry = _get_payload_entry(scopedstrName, true);
      if (!pentry)
         return error_io;

      auto &alloc = m_pregistry->m_rapidjsondocument.GetAllocator();
      ::rapidjson::Value data(ull);
      set_type_and_data(*pentry, "dword", data, alloc);
      return ::success;
   }


   ::e_status registry_key_implementation::_set_binary(const ::scoped_string &scopedstrName, const ::block &block) 
   {
      if (::is_null(this) || scopedstrName.is_empty() || (!block.data()&& block.size() != 0)) return error_bad_argument;

      auto pentry = _get_payload_entry(scopedstrName, true);
      if (!pentry) return error_io;

      auto hex = bin_to_hex((const unsigned char *)block.data(), block.size());
      auto &alloc = m_pregistry->m_rapidjsondocument.GetAllocator();
      ::rapidjson::Value val(hex.c_str(), alloc);
      set_type_and_data(*pentry, "binary", val, alloc);
      return ::success;
   }

   /* ============================================================================
      Get values
      ============================================================================ */

   ::e_status registry_key_implementation::_get_string(const ::scoped_string & scopedstrName, string & str) 
   {
      if (::is_null(this) || scopedstrName.is_empty())
         return error_bad_argument;

      auto pentry = _get_payload_entry(scopedstrName, false);
      if (!pentry)
         return error_not_found;

      if (!pentry->HasMember("type") || !pentry->HasMember("data"))
         return error_wrong_type;
      if (!(*pentry)["type"].IsString() || std::strcmp((*pentry)["type"].GetString(), "sz") != 0)
         return error_wrong_type;
      if (!(*pentry)["data"].IsString())
         return error_wrong_type;

      str = (*pentry)["data"].GetString();

      return ::success;

   }

   ::e_status registry_key_implementation::_get_dword(const ::scoped_string & scopedstrName, unsigned int &u)
   {
      if (::is_null(this) || scopedstrName.is_empty())
         return error_bad_argument;


      auto pentry = _get_payload_entry(scopedstrName, false);
      if (!pentry) return error_not_found;

      if (!pentry->HasMember("type") || !pentry->HasMember("data")) return error_wrong_type;
      if (!(*pentry)["type"].IsString() || std::strcmp((*pentry)["type"].GetString(), "dword") != 0) return error_wrong_type;
      if (!(*pentry)["data"].IsUint()) return error_wrong_type;

      u = (*pentry)["data"].GetUint();
      return ::success;
   }


      ::e_status registry_key_implementation::_get_qword(const ::scoped_string &scopedstrName, unsigned long long &ull)
   {
      if (::is_null(this) || scopedstrName.is_empty())
         return error_bad_argument;


      auto pentry = _get_payload_entry(scopedstrName, false);
      if (!pentry)
         return error_not_found;

      if (!pentry->HasMember("type") || !pentry->HasMember("data"))
         return error_wrong_type;
      if (!(*pentry)["type"].IsString() || std::strcmp((*pentry)["type"].GetString(), "qword") != 0)
         return error_wrong_type;
      if (!(*pentry)["data"].IsUint())
         return error_wrong_type;

      ull = (*pentry)["data"].GetUint64();
      return ::success;
   }


   ::e_status registry_key_implementation::_get_binary(const ::scoped_string &scopedstrName, memory & memory)
   {
      if (::is_null(this) || scopedstrName.is_empty())
         return error_bad_argument;

      auto pentry = _get_payload_entry(scopedstrName, false);
      if (!pentry)
         return error_not_found;

      if (!pentry->HasMember("type") || !pentry->HasMember("data")) return error_not_found;
      if (!(*pentry)["type"].IsString() || std::strcmp((*pentry)["type"].GetString(), "binary") != 0) return error_not_found;
      if (!(*pentry)["data"].IsString()) return error_not_found;

      return hex_to_bin((*pentry)["data"].GetString(), memory);

   }

   /* ============================================================================
      Misc
      ============================================================================ */

   ::e_status registry_key_implementation::_erase_payload(const ::scoped_string &scopedstrName)
   {
      if (::is_null(this) || scopedstrName.is_empty())
         return error_bad_argument;

      auto ppayloads = _get_payloads(false);
      if (!ppayloads) return error_not_found;

      if (!ppayloads->HasMember(scopedstrName)) return error_not_found;
      ppayloads->RemoveMember(scopedstrName);
      return ::success;
   }


   ::e_status registry_key_implementation::_has_payload(const ::scoped_string & scopedstrName, bool & bExists)
   {
      if (::is_null(this) || scopedstrName.is_empty()) return error_bad_argument;
      auto ppayloads = _get_payloads(false);
      if (!ppayloads) return error_not_found;
      bExists = ppayloads->HasMember(scopedstrName) ? true : false;
      return ::success;
   }


   ::e_status registry_key_implementation::_payload_type(const ::scoped_string & scopedstrName, enum_registry & eregistry)
   {
      if (::is_null(this) || scopedstrName.is_empty())
         return error_bad_argument;

      auto pentry = _get_payload_entry(scopedstrName, false);
      if (!pentry) return error_not_found;
      if (!pentry->HasMember("type") || !(*pentry)["type"].IsString()) return error_wrong_type;

      const char *t = (*pentry)["type"].GetString();
      if (std::strcmp(t, "sz") == 0) eregistry = e_registry_string;
      else if (std::strcmp(t, "dword") == 0) eregistry = e_registry_dword;
      else if (std::strcmp(t, "qword") == 0) eregistry = e_registry_qword;
      else if (std::strcmp(t, "binary") == 0) eregistry = e_registry_binary;
      else eregistry = e_registry_none;

      return ::success;
   }

   //const char *RegXStrError(int status) {
   //   switch (status) {
   //      case ::success: return "ok";
   //      case error_bad_argument: return "invalid argument";
   //      case error_not_found: return "not found";
   //      case REGX_ERR_EXISTS: return "already exists";
   //      case error_io: return "i/o error";
   //      case REGX_ERR_NOMEM: return "out of memory";
   //      case REGX_ERR_TYPE: return "type mismatch";
   //      case error_insufficient_buffer: return "buffer too small";
   //      default: return "unknown error";
   //   }
   //}


   registry_key::registry_key()
   {

      m_pregistrykey = ::system()->m_papplication->create_newø < registry_key_implementation >();

   }


   registry_key::~registry_key()
   {


   }


   pointer<registry> registry::create_from_file(const file::path &pathRegistry)
   {

      auto pregistryImplementation = ::system()->m_papplication->create_newø<registry_implementation>();

      pregistryImplementation->open_from_file(pathRegistry);

      return pregistryImplementation;

   }

} // namespace subsystem

