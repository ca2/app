#pragma once

typedef enum {
   GEOIP_NO_NEW_UPDATES          = 1,   /* Dataaxis up-to-date, no action taken */
  GEOIP_SUCCESS                 = 0,   /* Success */
  GEOIP_LICENSE_KEY_INVALID_ERR =   -1,  /* License Key Invalid */
  GEOIP_DNS_ERR                 = -11, /* Unable to resolve hostname */
  GEOIP_NON_IPV4_ERR            = -12, /* Non - IPv4 address */
  GEOIP_SOCKET_OPEN_ERR         = -13, /* Error opening socket */
   GEOIP_CONNECTION_ERR          = -14, /* Unable to connect */
   GEOIP_GZIP_IO_ERR             = -15, /* Unable to write GeoIP.dat.gz file */
  GEOIP_TEST_IO_ERR             = -16, /* Unable to write GeoIP.dat.test file */
   GEOIP_GZIP_READ_ERR           = -17, /* Unable to read gzip data */
   GEOIP_OUT_OF_MEMORY_ERR       = -18, /* Out of memory error */
   GEOIP_SOCKET_READ_ERR         = -19, /* Error reading from socket, see errno */
   GEOIP_SANITY_OPEN_ERR         = -20, /* Sanity check GeoIP_open error */
   GEOIP_SANITY_INFO_FAIL        = -21, /* Sanity check database_info string failed */
   GEOIP_SANITY_LOOKUP_FAIL      = -22, /* Sanity check ip address lookup failed */
   GEOIP_RENAME_ERR              = -23, /* Rename error while installing db, check errno */
   GEOIP_USER_ID_INVALID_ERR     = -24, /* Invalid userID */
   GEOIP_PRODUCT_ID_INVALID_ERR  = -25, /* Invalid product ID or subscription expired */
   GEOIP_INVALID_SERVER_RESPONSE = -26  /* Server returned invalid response */
} GeoIPUpdateCode;

const char * GeoIP_get_error_message(i32 i);

/* Original Update Function, just for MaxMind GeoIP Country database */
i16 GeoIP_update_database (char * license_key, i32 verbose, void (*f)( char *));

/* More generalized update function that works more databases */
i16 GeoIP_update_database_general (char * user_id, char * license_key,char * data_axis_type, i32 verbose,char ** client_ipaddr, void (*f)( char *));

   /* experimental export */
   i32  GeoIP_fprintf(i32 (*f)(FILE *, char *),FILE *fp, const char *fmt, ...);
   void GeoIP_printf(void (*f)(char *), const char *fmt, ...);

