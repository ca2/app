//
//  registry.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 04/04/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#pragma once


namespace acme
{



/* --------------------------------------------------------------------------
   Opaque handles
   -------------------------------------------------------------------------- */

typedef struct RegX RegX;
typedef struct RegXKey RegXKey;

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
        RegX *reg = NULL;
        RegXOpen("registry.json", &reg);
*/
int RegXOpen(const char *filename, RegX **out_reg);

/*
    Writes the in-memory registry to disk.
*/
int RegXFlush(RegX *reg);

/*
    Flushes and destroys the registry object.
*/
void RegXClose(RegX *reg);

/* --------------------------------------------------------------------------
   Key lifetime
   -------------------------------------------------------------------------- */

/*
    Frees a key handle created by RegXOpenKey / RegXCreateKey.
*/
void RegXCloseKey(RegXKey *key);

/* --------------------------------------------------------------------------
   Key operations
   -------------------------------------------------------------------------- */

/*
    Opens an existing key.

    Example:
        RegXKey *key = NULL;
        RegXOpenKey(reg, "HKCU\\Software\\MyApp", &key);
*/
int RegXOpenKey(RegX *reg, const char *path, RegXKey **out_key);

/*
    Creates a key and any missing parents.

    Example:
        RegXCreateKey(reg, "HKCU\\Software\\MyApp", &key);
*/
int RegXCreateKey(RegX *reg, const char *path, RegXKey **out_key);

/*
    Deletes a key and all descendants.
*/
int RegXDeleteKey(RegX *reg, const char *path);

/* --------------------------------------------------------------------------
   Value set operations
   -------------------------------------------------------------------------- */

int RegXSetString(RegXKey *key, const char *name, const char *value);
int RegXSetDword (RegXKey *key, const char *name, uint32_t value);
int RegXSetBinary(RegXKey *key, const char *name, const void *data, size_t size);

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
int RegXGetString(RegXKey *key, const char *name, char *buf, size_t *inout_len);

int RegXGetDword(RegXKey *key, const char *name, uint32_t *out_value);

/*
    Gets a binary value.

    Usage pattern:
        size_t size = 0;
        RegXGetBinary(key, "Blob", NULL, &size);
        void *buf = malloc(size);
        RegXGetBinary(key, "Blob", buf, &size);
*/
int RegXGetBinary(RegXKey *key, const char *name, void *buf, size_t *inout_len);

/* --------------------------------------------------------------------------
   Value utility
   -------------------------------------------------------------------------- */

int RegXDeleteValue(RegXKey *key, const char *name);
int RegXValueExists(RegXKey *key, const char *name);
int RegXGetValueType(RegXKey *key, const char *name, RegXType *out_type);

/* --------------------------------------------------------------------------
   Error strings
   -------------------------------------------------------------------------- */

const char *RegXStrError(int status);

} // namespace acme



