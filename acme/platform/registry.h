//
//  registry.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 04/04/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#pragma once


#include "acme/subsystem/particle.h"


namespace subsystem
{


   class registry_key_interface;


   class CLASS_DECL_ACME registry_interface :
      virtual public ::subsystem::particle_interface
   {
   public:

      ::file::path   m_path;


      virtual void open_from_file(const ::file::path & path) = 0;

      virtual void flush() = 0;

      virtual void close() = 0;

      virtual ::pointer < registry_key_interface > open_key(const ::file::path & path) = 0;

      virtual ::pointer < registry_key_interface > create_key(const ::file::path & path) = 0;

      virtual bool delete_key(const ::file::path & path) = 0;


   };

   class CLASS_DECL_ACME registry_key_interface :
   virtual public ::particle
   {
   public:

      ::pointer < registry_interface > m_pregistry;
      ::file::path m_path;


      virtual void close() =0;

      virtual void set_string(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrPayload) = 0;
      virtual void set_dword(const ::scoped_string & scopedstr, unsigned int value) = 0;
      virtual void set_binary(const ::scoped_string & scopedstr, const ::block & block) = 0;

      ::string get_string(const ::scoped_string & scopedstr);

      unsigned get_dword(const ::scoped_string & scopedstr);

      /*
          Gets a binary value.

          Usage pattern:
              size_t size = 0;
              RegXGetBinary(key, "Blob", NULL, &size);
              void *buf = malloc(size);
              RegXGetBinary(key, "Blob", buf, &size);
      */
      ::memory get_binary(const ::scoped_string & scopedstr) = 0;

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
   Types
   -------------------------------------------------------------------------- */

typedef enum RegXType {
    REGX_NONE   = 0,
    REGX_SZ     = 1,
    REGX_DWORD  = 2,
    REGX_BINARY = 3
} RegXType;

typedef enum RegXStatus {
    REGX_OK = 0,
    REGX_ERR_INVALID_ARG = -1,
    REGX_ERR_NOT_FOUND   = -2,
    REGX_ERR_EXISTS      = -3,
    REGX_ERR_IO          = -4,
    REGX_ERR_NOMEM       = -5,
    REGX_ERR_TYPE        = -6,
    REGX_ERR_BUFFER      = -7
} RegXStatus;

/* --------------------------------------------------------------------------
   Root key strings
   -------------------------------------------------------------------------- */

#define REGX_HKCU "HKCU"
#define REGX_HKLM "HKLM"
#define REGX_HKCR "HKCR"
#define REGX_HKU  "HKU"

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
int RegXGetString(registry_key *key, const char *name, char *buf, size_t *inout_len);

int RegXGetDword(registry_key *key, const char *name, uint32_t *out_value);

/*
    Gets a binary value.

    Usage pattern:
        size_t size = 0;
        RegXGetBinary(key, "Blob", NULL, &size);
        void *buf = malloc(size);
        RegXGetBinary(key, "Blob", buf, &size);
*/
int RegXGetBinary(registry_key *key, const char *name, void *buf, size_t *inout_len);

/* --------------------------------------------------------------------------
   Value utility
   -------------------------------------------------------------------------- */

int RegXDeleteValue(registry_key *key, const char *name);
int RegXValueExists(registry_key *key, const char *name);
int RegXGetValueType(registry_key *key, const char *name, RegXType *out_type);

/* --------------------------------------------------------------------------
   Error strings
   -------------------------------------------------------------------------- */

const char *RegXStrError(int status);

} // namespace subsystem



