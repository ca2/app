#pragma once


#if !defined(WINDOWS)
#define _snprintf snprintf
#endif

#if defined(WINDOWS)
#define FILETIME_TO_USEC(ft) (((unsigned long long) ft.dwHighDateTime << 32 | ft.dwLowDateTime) / 10)
#endif


#define SEGMENT_RECORD_LENGTH 3
#define STANDARD_RECORD_LENGTH 3
#define ORG_RECORD_LENGTH 4
#define MAX_RECORD_LENGTH 4
#define NUM_DB_TYPES 20

/* 128 bit address in network order */
typedef struct in6_addr geoipv6_t;

#define GEOIP_CHKBIT_V6(bit,ptr) (ptr[((127UL - bit) >> 3)] & (1UL << (~(127 - bit) & 7)))

typedef struct GeoIPTag {
   FILE* GeoIPDataaxis;
   char* file_path;
   uchar* cache;
   uchar* index_cache;
   unsigned int* databaseSegments;
   char databaseType;
   posix_time mtime;
   int flags;
   off_t   size;
   char record_length;
   int charset; /* 0 iso-8859-1 1 utf8 */
   int record_iter; /* used in GeoIP_next_record */
   int netmask; /* netmask of last lookup - set using depth in _GeoIP_seek_record */
   posix_time last_mtime_check;
} GeoIP;


typedef enum {
   GEOIP_CHARSET_ISO_8859_1 = 0,
   GEOIP_CHARSET_UTF8 = 1
} GeoIPCharset;

typedef struct GeoIPRegionTag {
   char country_code[3];
   char region[3];
} GeoIPRegion;

typedef enum {
   GEOIP_STANDARD = 0,
   GEOIP_MEMORY_CACHE = 1,
   GEOIP_CHECK_CACHE = 2,
   GEOIP_INDEX_CACHE = 4,
   GEOIP_MMAP_CACHE = 8
} GeoIPOptions;

typedef enum {
   GEOIP_COUNTRY_EDITION = 1,
   GEOIP_REGION_EDITION_REV0 = 7,
   GEOIP_CITY_EDITION_REV0 = 6,
   GEOIP_ORG_EDITION = 5,
   GEOIP_ISP_EDITION = 4,
   GEOIP_CITY_EDITION_REV1 = 2,
   GEOIP_REGION_EDITION_REV1 = 3,
   GEOIP_PROXY_EDITION = 8,
   GEOIP_ASNUM_EDITION = 9,
   GEOIP_NETSPEED_EDITION = 10,
   GEOIP_DOMAIN_EDITION = 11,
   GEOIP_COUNTRY_EDITION_V6 = 12
} GeoIPDBTypes;

typedef enum {
   GEOIP_ANON_PROXY = 1,
   GEOIP_HTTP_X_FORWARDED_FOR_PROXY = 2,
   GEOIP_HTTP_CLIENT_IP_PROXY = 3
} GeoIPProxyTypes;

typedef enum {
   GEOIP_UNKNOWN_SPEED = 0,
   GEOIP_DIALUP_SPEED = 1,
   GEOIP_CABLEDSL_SPEED = 2,
   GEOIP_CORPORATE_SPEED = 3
} GeoIPNetspeedValues;

extern char** GeoIPDBFileName;
extern const_char_pointer  GeoIPDBDescription[NUM_DB_TYPES];
extern const_char_pointer  GeoIPCountryDBFileName;
extern const_char_pointer  GeoIPRegionDBFileName;
extern const_char_pointer  GeoIPCityDBFileName;
extern const_char_pointer  GeoIPOrgDBFileName;
extern const_char_pointer  GeoIPISPDBFileName;

/* Warning: do not use those arrays as doing so may break your
 * program with newer GeoIP versions */
extern const char GeoIP_country_code[253][3];
extern const char GeoIP_country_code3[253][4];
extern const_char_pointer  GeoIP_country_name[253];
extern const char GeoIP_country_continent[253][3];

#define GEOIP_API CLASS_DECL_AXIS

GEOIP_API void GeoIP_setup_custom_directory(char* dir);
GEOIP_API GeoIP* GeoIP_open_type(int type, int flags);
GEOIP_API GeoIP* GeoIP_new(int flags);
GEOIP_API GeoIP* GeoIP_open(const_char_pointer  filename, int flags);
GEOIP_API int GeoIP_db_avail(int type);
GEOIP_API void GeoIP_delete(GeoIP* gi);
GEOIP_API const_char_pointer  GeoIP_country_code_by_addr(GeoIP* gi, const_char_pointer  addr);
GEOIP_API const_char_pointer  GeoIP_country_code_by_name(GeoIP* gi, const_char_pointer  host);
GEOIP_API const_char_pointer  GeoIP_country_code3_by_addr(GeoIP* gi, const_char_pointer  addr);
GEOIP_API const_char_pointer  GeoIP_country_code3_by_name(GeoIP* gi, const_char_pointer  host);
GEOIP_API const_char_pointer  GeoIP_country_name_by_addr(GeoIP* gi, const_char_pointer  addr);
GEOIP_API const_char_pointer  GeoIP_country_name_by_name(GeoIP* gi, const_char_pointer  host);
GEOIP_API const_char_pointer  GeoIP_country_name_by_ipnum(GeoIP* gi, unsigned int ipnum);
GEOIP_API const_char_pointer  GeoIP_country_code_by_ipnum(GeoIP* gi, unsigned int ipnum);
GEOIP_API const_char_pointer  GeoIP_country_code3_by_ipnum(GeoIP* gi, unsigned int ipnum);

/* */
GEOIP_API const_char_pointer  GeoIP_country_name_by_ipnum_v6(GeoIP* gi, geoipv6_t ipnum);
GEOIP_API const_char_pointer  GeoIP_country_code_by_ipnum_v6(GeoIP* gi, geoipv6_t ipnum);
GEOIP_API const_char_pointer  GeoIP_country_code3_by_ipnum_v6(GeoIP* gi, geoipv6_t ipnum);

/* Deprecated - for backwards compatibility only */
GEOIP_API int GeoIP_country_id_by_addr(GeoIP* gi, const_char_pointer  addr);
GEOIP_API int GeoIP_country_id_by_name(GeoIP* gi, const_char_pointer  host);
GEOIP_API char* GeoIP_org_by_addr(GeoIP* gi, const_char_pointer  addr);
GEOIP_API char* GeoIP_org_by_name(GeoIP* gi, const_char_pointer  host);
GEOIP_API char* GeoIP_org_by_ipnum(GeoIP* gi, unsigned int ipnum);

GEOIP_API char* GeoIP_org_by_ipnum_v6(GeoIP* gi, geoipv6_t ipnum);
GEOIP_API char* GeoIP_org_by_addr_v6(GeoIP* gi, const_char_pointer  addr);
GEOIP_API char* GeoIP_org_by_name_v6(GeoIP* gi, const_char_pointer  name);

/* End deprecated */

GEOIP_API int GeoIP_id_by_addr(GeoIP* gi, const_char_pointer  addr);
GEOIP_API int GeoIP_id_by_name(GeoIP* gi, const_char_pointer  host);
GEOIP_API int GeoIP_id_by_ipnum(GeoIP* gi, unsigned int ipnum);

GEOIP_API int GeoIP_id_by_addr_v6(GeoIP* gi, const_char_pointer  addr);
GEOIP_API int GeoIP_id_by_name_v6(GeoIP* gi, const_char_pointer  host);
GEOIP_API int GeoIP_id_by_ipnum_v6(GeoIP* gi, geoipv6_t ipnum);

GEOIP_API GeoIPRegion* GeoIP_region_by_addr(GeoIP* gi, const_char_pointer  addr);
GEOIP_API GeoIPRegion* GeoIP_region_by_name(GeoIP* gi, const_char_pointer  host);
GEOIP_API GeoIPRegion* GeoIP_region_by_ipnum(GeoIP* gi, unsigned int ipnum);

GEOIP_API GeoIPRegion* GeoIP_region_by_addr_v6(GeoIP* gi, const_char_pointer  addr);
GEOIP_API GeoIPRegion* GeoIP_region_by_name_v6(GeoIP* gi, const_char_pointer  host);
GEOIP_API GeoIPRegion* GeoIP_region_by_ipnum_v6(GeoIP* gi, geoipv6_t ipnum);

/* Warning - don't call this after GeoIP_assign_region_by_inetaddr calls */
GEOIP_API void GeoIPRegion_delete(GeoIPRegion* gir);

GEOIP_API void GeoIP_assign_region_by_inetaddr(GeoIP* gi, unsigned int inetaddr, GeoIPRegion* gir);

GEOIP_API void GeoIP_assign_region_by_inetaddr_v6(GeoIP* gi, geoipv6_t inetaddr, GeoIPRegion* gir);

/* Used to query GeoIP Organization, ISP and AS Number databases */
GEOIP_API char* GeoIP_name_by_ipnum(GeoIP* gi, unsigned int ipnum);
GEOIP_API char* GeoIP_name_by_addr(GeoIP* gi, const_char_pointer  addr);
GEOIP_API char* GeoIP_name_by_name(GeoIP* gi, const_char_pointer  host);

GEOIP_API char* GeoIP_name_by_ipnum_v6(GeoIP* gi, geoipv6_t ipnum);
GEOIP_API char* GeoIP_name_by_addr_v6(GeoIP* gi, const_char_pointer  addr);
GEOIP_API char* GeoIP_name_by_name_v6(GeoIP* gi, const_char_pointer  name);

/** return two letter country code */
GEOIP_API const_char_pointer  GeoIP_code_by_id(int atom);

/** return three letter country code */
GEOIP_API const_char_pointer  GeoIP_code3_by_id(int atom);

/** return full name of country */
GEOIP_API const_char_pointer  GeoIP_name_by_id(int atom);

/** return continent of country */
GEOIP_API const_char_pointer  GeoIP_continent_by_id(int atom);

/** return atom by country code **/
GEOIP_API int GeoIP_id_by_code(const_char_pointer  country);

/** return return number of known countries */
GEOIP_API unsigned int GeoIP_num_countries();

GEOIP_API char* GeoIP_database_info(GeoIP* gi);
GEOIP_API uchar GeoIP_database_edition(GeoIP* gi);

GEOIP_API int GeoIP_charset(GeoIP* gi);
GEOIP_API int GeoIP_set_charset(GeoIP* gi, int charset);

GEOIP_API int GeoIP_last_netmask(GeoIP* gi);
GEOIP_API char** GeoIP_range_by_ip(GeoIP* gi, const_char_pointer  addr);
GEOIP_API void GeoIP_range_by_ip_delete(char** ptr);

/* Convert region code to region name */
GEOIP_API const_char_pointer  GeoIP_region_name_by_code(const_char_pointer  country_code, const_char_pointer  region_code);

/* get timezone from country and region code */
GEOIP_API const_char_pointer  GeoIP_time_zone_by_country_and_region(const_char_pointer  country_code, const_char_pointer  region_code);

//#ifdef BSD
//#define ::memory_copy(dest, src, n) bcopy(src, dest, n)
//#endif

#include "global.h"
#include "city.h"
#include "update.h"
#include "internal.h"



