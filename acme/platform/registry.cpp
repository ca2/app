//
//  registry.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 04/04/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#include "framework.h"
#include "registry.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

//using namespace rapidjson;

namespace subsystem
{
   class CLASS_DECL_ACME registry_key_implementation :
   virtual public registry_key
   {
   public:
      ::rapidjson::Document m_rapidjsondocument;

   };

   // struct RegX {
   //     std::string filename;
   //     Document doc;
   // };
   //
   // struct registry_key {
   //     RegX *owner;
   //     std::string path;
   // };

   /* ============================================================================
      Helpers
      ============================================================================ */

   static std::vector<std::string> split_path(const char *path) {
      std::vector<std::string> parts;
      if (!path) return parts;

      std::string cur;
      for (const char *p = path; *p; ++p) {
         if (*p == '\\' || *p == '/') {
            if (!cur.empty()) {
               parts.push_back(cur);
               cur.clear();
            }
         } else {
            cur.push_back(*p);
         }
      }
      if (!cur.empty()) parts.push_back(cur);
      return parts;
   }

   static std::string bin_to_hex(const unsigned char *data, size_t size) {
      static const char *hex = "0123456789ABCDEF";
      std::string out;
      out.reserve(size * 2);
      for (size_t i = 0; i < size; ++i) {
         unsigned char b = data[i];
         out.push_back(hex[(b >> 4) & 0xF]);
         out.push_back(hex[b & 0xF]);
      }
      return out;
   }

   static int hex_val(char c) {
      if (c >= '0' && c <= '9') return c - '0';
      if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
      if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
      return -1;
   }

   static int hex_to_bin(const char *hex, unsigned char *buf, size_t *inout_len) {
      if (!hex || !inout_len) return REGX_ERR_INVALID_ARG;
      size_t n = std::strlen(hex);
      if (n % 2 != 0) return REGX_ERR_IO;

      size_t needed = n / 2;
      if (!buf || *inout_len < needed) {
         *inout_len = needed;
         return REGX_ERR_BUFFER;
      }

      for (size_t i = 0; i < needed; ++i) {
         int hi = hex_val(hex[i * 2]);
         int lo = hex_val(hex[i * 2 + 1]);
         if (hi < 0 || lo < 0) return REGX_ERR_IO;
         buf[i] = (unsigned char)((hi << 4) | lo);
      }

      *inout_len = needed;
      return REGX_OK;
   }

   static bool ensure_object(Value &v, Document::AllocatorType &a) {
      if (!v.IsObject()) {
         v.SetObject();
      }
      return true;
   }

   static Value *get_key_node(RegX *reg, const char *path, bool create) {
      if (!reg || !path) return nullptr;

      auto parts = split_path(path);
      if (parts.empty()) return nullptr;

      Value *cur = &reg->doc;
      auto &alloc = reg->doc.GetAllocator();

      for (const auto &part : parts) {
         ensure_object(*cur, alloc);

         if (!cur->HasMember(part.c_str())) {
            if (!create) return nullptr;

            Value k(part.c_str(), alloc);
            Value obj(kObjectType);
            cur->AddMember(k, obj, alloc);
         }

         Value &next = (*cur)[part.c_str()];
         if (!next.IsObject()) {
            if (!create) return nullptr;
            next.SetObject();
         }

         cur = &next;
      }

      return cur;
   }

   static Value *get_values_object(registry_key *key, bool create) {
      if (!key || !key->owner) return nullptr;

      Value *node = get_key_node(key->owner, key->path.c_str(), create);
      if (!node) return nullptr;

      auto &alloc = key->owner->doc.GetAllocator();

      if (!node->HasMember("__values__")) {
         if (!create) return nullptr;
         Value k("__values__", alloc);
         Value obj(kObjectType);
         node->AddMember(k, obj, alloc);
      }

      Value &vals = (*node)["__values__"];
      if (!vals.IsObject()) {
         if (!create) return nullptr;
         vals.SetObject();
      }

      return &vals;
   }

   static Value *get_value_entry(registry_key *key, const char *name, bool create) {
      if (!key || !name) return nullptr;
      Value *vals = get_values_object(key, create);
      if (!vals) return nullptr;

      auto &alloc = key->owner->doc.GetAllocator();

      if (!vals->HasMember(name)) {
         if (!create) return nullptr;
         Value k(name, alloc);
         Value obj(kObjectType);
         vals->AddMember(k, obj, alloc);
      }

      Value &entry = (*vals)[name];
      if (!entry.IsObject()) {
         if (!create) return nullptr;
         entry.SetObject();
      }

      return &entry;
   }

   static void set_type_and_data(Value &entry, const char *type, Value &data, Document::AllocatorType &alloc) {
      entry.SetObject();

      Value t(type, alloc);
      entry.AddMember("type", t, alloc);
      entry.AddMember("data", data, alloc);
   }

   /* ============================================================================
      Lifecycle
      ============================================================================ */

   int RegXOpen(const char *filename, RegX **out_reg) {
      if (!filename || !out_reg) return REGX_ERR_INVALID_ARG;

      RegX *reg = new (std::nothrow) RegX();
      if (!reg) return REGX_ERR_NOMEM;

      reg->filename = filename;
      reg->doc.SetObject();

      std::ifstream ifs(filename, std::ios::binary);
      if (ifs.good()) {
         std::stringstream ss;
         ss << ifs.rdbuf();
         std::string content = ss.str();

         if (!content.empty()) {
            reg->doc.Parse(content.c_str());
            if (reg->doc.HasParseError() || !reg->doc.IsObject()) {
               reg->doc.SetObject();
            }
         }
      }

      *out_reg = reg;
      return REGX_OK;
   }

   int RegXFlush(RegX *reg) {
      if (!reg) return REGX_ERR_INVALID_ARG;

      StringBuffer buffer;
      PrettyWriter<StringBuffer> writer(buffer);
      reg->doc.Accept(writer);

      std::ofstream ofs(reg->filename, std::ios::binary | std::ios::trunc);
      if (!ofs.good()) return REGX_ERR_IO;

      ofs.write(buffer.GetString(), (std::streamsize)buffer.GetSize());
      if (!ofs.good()) return REGX_ERR_IO;

      return REGX_OK;
   }

   void RegXClose(RegX *reg) {
      if (!reg) return;
      RegXFlush(reg);
      delete reg;
   }

   /* ============================================================================
      Key operations
      ============================================================================ */

   int RegXOpenKey(RegX *reg, const char *path, registry_key **out_key) {
      if (!reg || !path || !out_key) return REGX_ERR_INVALID_ARG;

      Value *node = get_key_node(reg, path, false);
      if (!node) return REGX_ERR_NOT_FOUND;

      registry_key *key = new (std::nothrow) registry_key();
      if (!key) return REGX_ERR_NOMEM;

      key->owner = reg;
      key->path = path;
      *out_key = key;
      return REGX_OK;
   }

   int RegXCreateKey(RegX *reg, const char *path, registry_key **out_key) {
      if (!reg || !path) return REGX_ERR_INVALID_ARG;

      Value *node = get_key_node(reg, path, true);
      if (!node) return REGX_ERR_IO;

      if (out_key) {
         registry_key *key = new (std::nothrow) registry_key();
         if (!key) return REGX_ERR_NOMEM;
         key->owner = reg;
         key->path = path;
         *out_key = key;
      }

      return REGX_OK;
   }

   int RegXDeleteKey(RegX *reg, const char *path) {
      if (!reg || !path) return REGX_ERR_INVALID_ARG;

      auto parts = split_path(path);
      if (parts.empty()) return REGX_ERR_INVALID_ARG;
      if (parts.size() == 1) return REGX_ERR_IO; /* don't delete top root directly */

      Value *cur = &reg->doc;
      for (size_t i = 0; i + 1 < parts.size(); ++i) {
         if (!cur->IsObject() || !cur->HasMember(parts[i].c_str())) {
            return REGX_ERR_NOT_FOUND;
         }
         cur = &(*cur)[parts[i].c_str()];
      }

      if (!cur->IsObject() || !cur->HasMember(parts.back().c_str())) {
         return REGX_ERR_NOT_FOUND;
      }

      cur->RemoveMember(parts.back().c_str());
      return REGX_OK;
   }

   /* ============================================================================
      Set values
      ============================================================================ */

   int RegXSetString(registry_key *key, const char *name, const char *value) {
      if (!key || !name || !value) return REGX_ERR_INVALID_ARG;

      Value *entry = get_value_entry(key, name, true);
      if (!entry) return REGX_ERR_IO;

      auto &alloc = key->owner->doc.GetAllocator();
      Value data(value, alloc);
      set_type_and_data(*entry, "sz", data, alloc);
      return REGX_OK;
   }

   int RegXSetDword(registry_key *key, const char *name, uint32_t value) {
      if (!key || !name) return REGX_ERR_INVALID_ARG;

      Value *entry = get_value_entry(key, name, true);
      if (!entry) return REGX_ERR_IO;

      auto &alloc = key->owner->doc.GetAllocator();
      Value data(value);
      set_type_and_data(*entry, "dword", data, alloc);
      return REGX_OK;
   }

   int RegXSetBinary(registry_key *key, const char *name, const void *data, size_t size) {
      if (!key || !name || (!data && size != 0)) return REGX_ERR_INVALID_ARG;

      Value *entry = get_value_entry(key, name, true);
      if (!entry) return REGX_ERR_IO;

      std::string hex = bin_to_hex((const unsigned char *)data, size);
      auto &alloc = key->owner->doc.GetAllocator();
      Value val(hex.c_str(), alloc);
      set_type_and_data(*entry, "binary", val, alloc);
      return REGX_OK;
   }

   /* ============================================================================
      Get values
      ============================================================================ */

   int RegXGetString(registry_key *key, const char *name, char *buf, size_t *inout_len) {
      if (!key || !name || !inout_len) return REGX_ERR_INVALID_ARG;

      Value *entry = get_value_entry(key, name, false);
      if (!entry) return REGX_ERR_NOT_FOUND;

      if (!entry->HasMember("type") || !entry->HasMember("data")) return REGX_ERR_TYPE;
      if (!(*entry)["type"].IsString() || std::strcmp((*entry)["type"].GetString(), "sz") != 0) return REGX_ERR_TYPE;
      if (!(*entry)["data"].IsString()) return REGX_ERR_TYPE;

      const char *s = (*entry)["data"].GetString();
      size_t needed = std::strlen(s) + 1;

      if (!buf || *inout_len < needed) {
         *inout_len = needed;
         return REGX_ERR_BUFFER;
      }

      std::memcpy(buf, s, needed);
      *inout_len = needed;
      return REGX_OK;
   }

   int RegXGetDword(registry_key *key, const char *name, uint32_t *out_value) {
      if (!key || !name || !out_value) return REGX_ERR_INVALID_ARG;

      Value *entry = get_value_entry(key, name, false);
      if (!entry) return REGX_ERR_NOT_FOUND;

      if (!entry->HasMember("type") || !entry->HasMember("data")) return REGX_ERR_TYPE;
      if (!(*entry)["type"].IsString() || std::strcmp((*entry)["type"].GetString(), "dword") != 0) return REGX_ERR_TYPE;
      if (!(*entry)["data"].IsUint()) return REGX_ERR_TYPE;

      *out_value = (*entry)["data"].GetUint();
      return REGX_OK;
   }

   int RegXGetBinary(registry_key *key, const char *name, void *buf, size_t *inout_len) {
      if (!key || !name || !inout_len) return REGX_ERR_INVALID_ARG;

      Value *entry = get_value_entry(key, name, false);
      if (!entry) return REGX_ERR_NOT_FOUND;

      if (!entry->HasMember("type") || !entry->HasMember("data")) return REGX_ERR_TYPE;
      if (!(*entry)["type"].IsString() || std::strcmp((*entry)["type"].GetString(), "binary") != 0) return REGX_ERR_TYPE;
      if (!(*entry)["data"].IsString()) return REGX_ERR_TYPE;

      return hex_to_bin((*entry)["data"].GetString(), (unsigned char *)buf, inout_len);
   }

   /* ============================================================================
      Misc
      ============================================================================ */

   int RegXDeleteValue(registry_key *key, const char *name) {
      if (!key || !name) return REGX_ERR_INVALID_ARG;

      Value *vals = get_values_object(key, false);
      if (!vals) return REGX_ERR_NOT_FOUND;

      if (!vals->HasMember(name)) return REGX_ERR_NOT_FOUND;
      vals->RemoveMember(name);
      return REGX_OK;
   }

   int RegXValueExists(registry_key *key, const char *name) {
      if (!key || !name) return 0;
      Value *vals = get_values_object(key, false);
      if (!vals) return 0;
      return vals->HasMember(name) ? 1 : 0;
   }

   int RegXGetValueType(registry_key *key, const char *name, RegXType *out_type) {
      if (!key || !name || !out_type) return REGX_ERR_INVALID_ARG;

      Value *entry = get_value_entry(key, name, false);
      if (!entry) return REGX_ERR_NOT_FOUND;
      if (!entry->HasMember("type") || !(*entry)["type"].IsString()) return REGX_ERR_TYPE;

      const char *t = (*entry)["type"].GetString();
      if (std::strcmp(t, "sz") == 0) *out_type = REGX_SZ;
      else if (std::strcmp(t, "dword") == 0) *out_type = REGX_DWORD;
      else if (std::strcmp(t, "binary") == 0) *out_type = REGX_BINARY;
      else *out_type = REGX_NONE;

      return REGX_OK;
   }

   const char *RegXStrError(int status) {
      switch (status) {
         case REGX_OK: return "ok";
         case REGX_ERR_INVALID_ARG: return "invalid argument";
         case REGX_ERR_NOT_FOUND: return "not found";
         case REGX_ERR_EXISTS: return "already exists";
         case REGX_ERR_IO: return "i/o error";
         case REGX_ERR_NOMEM: return "out of memory";
         case REGX_ERR_TYPE: return "type mismatch";
         case REGX_ERR_BUFFER: return "buffer too small";
         default: return "unknown error";
      }
   }
} // namespace subsystem

