//
//  registry.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 04/04/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#pragma once


#include "acme/subsystem/particle.h"


namespace platform
{


   class registry_key_interface;


   /* --------------------------------------------------------------------------
      Types
      -------------------------------------------------------------------------- */

   enum enum_registry 
   {
      e_registry_none   = 0,
      e_registry_string     = 1,
      e_registry_dword = 2,
      e_registry_qword = 3,
      e_registry_binary = 4
   };

   /* --------------------------------------------------------------------------
      Root key strings
      -------------------------------------------------------------------------- */

#define REGX_HKCU "HKCU"
#define REGX_HKLM "HKLM"
#define REGX_HKCR "HKCR"
#define REGX_HKU  "HKU"



   class registry :
      virtual public ::particle
   {
   public:

      ::file::path   m_path;


      virtual void open_from_file(const ::file::path & path) = 0;

      virtual void flush() = 0;

      virtual void close() = 0;

      virtual ::pointer < registry_key_interface > open_key(const ::file::path & path) = 0;

      virtual ::pointer < registry_key_interface > create_key(const ::file::path & path) = 0;

      virtual void delete_key(const ::file::path & path) = 0;


   };

   class CLASS_DECL_ACME registry_key_interface :
      virtual public ::particle
   {
   public:

      ::pointer < registry > m_pregistry;
      ::file::path m_path;


      virtual void close() =0;


      virtual void set_string(const ::scoped_string &scopedstrName, const ::scoped_string &scopedstr) = 0;
      virtual void set_dword(const ::scoped_string &scopedstrName, unsigned int value) = 0;
      virtual void set_qword(const ::scoped_string &scopedstrName, unsigned long long value) = 0;
      virtual void set_binary(const ::scoped_string &scopedstrName, const ::block &block) = 0;


      virtual ::e_status _get_string(const ::scoped_string &scopedstrName, ::string &str) = 0;
      virtual ::e_status _get_dword(const ::scoped_string &scopedstrName, unsigned int &u) = 0;
      virtual ::e_status _get_qword(const ::scoped_string &scopedstrName, unsigned long long & ull) = 0;
      virtual ::e_status _get_binary(const ::scoped_string &scopedstrName, ::memory & memory) = 0;


      virtual void erase_payload(const ::scoped_string &scopedstrName) = 0;
      virtual bool has_payload(const ::scoped_string &scopedstrName) = 0;
      virtual enum_registry payload_type(const ::scoped_string &scopedstrName) = 0;


      ::string get_string(const ::scoped_string &scopedstrName)
      {
         ::string str;
         auto estatus = _get_string(scopedstrName, str);
         if (!estatus)
            throw estatus;
         return ::transfer(str);
      }

      inline unsigned int long get_dword(const ::scoped_string &scopedstrName)
      {
         unsigned int u = 0;
         auto estatus = _get_qword(scopedstrName, u);
         if (!estatus)
            throw estatus;
         return u;
      }

      inline unsigned long long get_qword(const ::scoped_string &scopedstrName)
      {
         unsigned long long ull = 0;
         auto estatus = _get_qword(scopedstrName, ull);
         if (!estatus)
            throw estatus;
         return ull;
      }

      /*
          Gets a binary value.

          Usage pattern:
              size_t size = 0;
              RegXGetBinary(key, "Blob", NULL, &size);
              void *buf = malloc(size);
              RegXGetBinary(key, "Blob", buf, &size);
      */
      inline ::memory get_binary(const ::scoped_string &scopedstrName)
      {
         ::memory memory;
         auto estatus = _get_binary(scopedstrName, memory);
         if (!estatus)
            throw estatus;
         return ::transfer(memory);
      }

   };


   class CLASS_DECL_ACME registry_key : 
      virtual public registry_key_interface
   {
   public:

      ::pointer<registry_key_interface> m_pregistrykey;

      registry_key();
      ~registry_key() override;

      void close() override;

      void set_string(const ::scoped_string &scopedstrName, const ::scoped_string &scopedstr) override;
      void set_dword(const ::scoped_string &scopedstrName, unsigned int value) override;
      void set_qword(const ::scoped_string &scopedstrName, unsigned long long value) override;
      void set_binary(const ::scoped_string &scopedstrName, const ::block &block) override;

      ::e_status _get_string(const ::scoped_string &scopedstrName, ::string &str) override;
      ::e_status _get_dword(const ::scoped_string &scopedstrName, unsigned int &u) override;
      ::e_status _get_qword(const ::scoped_string &scopedstrName, unsigned long long &ull) override;
      ::e_status _get_binary(const ::scoped_string &scopedstrName, ::memory &memory) override;


      void erase_payload(const ::scoped_string &scopedstrName) override;
      bool has_payload(const ::scoped_string &scopedstrName) override;
      enum_registry payload_type(const ::scoped_string &scopedstrName) override;

   };

   // /* --------------------------------------------------------------------------
//    Opaque handles
//    -------------------------------------------------------------------------- */
//
//    struct registry {
//       std::string filename;
//       Document doc;
//    };
//
//    struct registry_key {
//       registry *owner;
//       std::string path;
//    };

/* --------------------------------------------------------------------------
   Registry lifecycle
   -------------------------------------------------------------------------- */

/*
    Opens or creates a registry database backed by a JSON file.

    Example:
        registry *reg = NULL;
        RegXOpen("registry.json", &reg);
*/
//::pointer < registry > RegXOpen(const ::file::path & path);

/*
    Writes the in-memory registry to disk.
*/
//int RegXFlush(registry *reg);

/*
    Flushes and destroys the registry object.
*/
//void RegXClose(registry *reg);

/* --------------------------------------------------------------------------
   Key lifetime
   -------------------------------------------------------------------------- */

/*
    Frees a key handle created by RegXOpenKey / RegXCreateKey.
*/
//void RegXCloseKey(registry_key *key);

/* --------------------------------------------------------------------------
   Key operations
   -------------------------------------------------------------------------- */

/*
    Opens an existing key.

    Example:
        registry_key *key = NULL;
        RegXOpenKey(reg, "HKCU\\Software\\MyApp", &key);
*/
//int RegXOpenKey(registry *reg, const char *path, registry_key **out_key);

/*
    Creates a key and any missing parents.

    Example:
        RegXCreateKey(reg, "HKCU\\Software\\MyApp", &key);
*/
//int RegXCreateKey(registry *reg, const char *path, registry_key **out_key);

/*
    Deletes a key and all descendants.
*/
//int RegXDeleteKey(registry *reg, const char *path);

/* --------------------------------------------------------------------------
   Value set operations
   -------------------------------------------------------------------------- */

// int RegXSetString(registry_key *key, const char *name, const char *value);
// int RegXSetDword (registry_key *key, const char *name, uint32_t value);
// int RegXSetBinary(registry_key *key, const char *name, const void *data, size_t size);

/* --------------------------------------------------------------------------
   Value get operations
   -------------------------------------------------------------------------- */

/*
    Gets a string value.

    Usage pattern:
        size_t len = 0;
        RegXGetString(key, "UserName", NULL, &len);   // query required size
        char *buf = malloc(len);
        RegXGetString(key, "UserName", buf, &len);
*/
//int RegXGetString(registry_key *key, const char *name, char *buf, size_t *inout_len);

//int RegXGetDword(registry_key *key, const char *name, uint32_t *out_value);

/*
    Gets a binary value.

    Usage pattern:
        size_t size = 0;
        RegXGetBinary(key, "Blob", NULL, &size);
        void *buf = malloc(size);
        RegXGetBinary(key, "Blob", buf, &size);
*/
//int RegXGetBinary(registry_key *key, const char *name, void *buf, size_t *inout_len);

/* --------------------------------------------------------------------------
   Value utility
   -------------------------------------------------------------------------- */

//int RegXDeleteValue(registry_key *key, const char *name);
//int RegXValueExists(registry_key *key, const char *name);
//int RegXGetValueType(registry_key *key, const char *name, RegXType *out_type);

/* --------------------------------------------------------------------------
   Error strings
   -------------------------------------------------------------------------- */

   //const char * registry_error(int status);


} // namespace platform



