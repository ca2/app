#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "axis/geoip/_.h"
#endif
#include <stdio.h>


#ifdef WINDOWS

//#include<Winsock2.h>

#endif

#if defined(APPLEOS) || defined(ANDROID) || defined(LINUX)

#include <netdb.h>

#endif

static geoipv6_t IPV6_NULL;


#define GEOIPDATADIR "/aura/geoip"

#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

#include<sys/stat.h>
#include<sys/mman.h>


#define _fileno fileno


#endif

#if defined(APPLEOS) || defined(LINUX) || defined(ANDROID)

#include<arpa/inet.h>
#include<sys/time.h>

#endif

i32 GeoIP_db_avail(::object * pobject, i32 type);
char *_get_name_v6 (GeoIP* gi, geoipv6_t ipnum);
char *_GeoIP_num_to_addr (GeoIP* gi, u32 ipnum);


#ifndef        INADDR_NONE
#define        INADDR_NONE     -1
#endif

#define COUNTRY_BEGIN 16776960
#define STATE_BEGIN_REV0 16700000
#define STATE_BEGIN_REV1 16000000
#define STRUCTURE_INFO_MAX_SIZE 20
#define DATAAXIS_INFO_MAX_SIZE 100
#define MAX_ORG_RECORD_LENGTH 300
#define US_OFFSET 1
#define CANADA_OFFSET 677
#define WORLD_OFFSET 1353
#define FIPS_RANGE 360

#define CHECK_ERR(err, msg) { \
   if (err != Z_OK) { \
   fprintf(stderr, "%s error: %d\n", msg, err); \
   exit(1); \
   } \
}

const char GeoIP_country_code[253][3] = { "--","AP","EU","AD","AE","AF","AG","AI","AL","AM","AN",
                                          "AO","AQ","AR","AS","AT","AU","AW","AZ","BA","BB",
                                          "BD","BE","BF","BG","BH","BI","BJ","BM","BN","BO",
                                          "BR","BS","BT","BV","BW","BY","BZ","CA","CC","CD",
                                          "CF","CG","CH","CI","CK","CL","CM","CN","CO","CR",
                                          "CU","CV","CX","CY","CZ","DE","DJ","DK","DM","DO",
                                          "DZ","EC","EE","EG","EH","ER","ES","ET","FI","FJ",
                                          "FK","FM","FO","FR","FX","GA","GB","GD","GE","GF",
                                          "GH","GI","GL","GM","GN","GP","GQ","GR","GS","GT",
                                          "GU","GW","GY","HK","HM","HN","HR","HT","HU","ID",
                                          "IE","IL","IN","IO","IQ","IR","IS","IT","JM","JO",
                                          "JP","KE","KG","KH","KI","KM","KN","KP","KR","KW",
                                          "KY","KZ","LA","LB","LC","LI","LK","LR","LS","LT",
                                          "LU","LV","LY","MA","MC","MD","MG","MH","MK","ML",
                                          "MM","MN","MO","MP","MQ","MR","MS","MT","MU","MV",
                                          "MW","MX","MY","MZ","NA","NC","NE","NF","NG","NI",
                                          "NL","NO","NP","NR","NU","NZ","OM","PA","PE","PF",
                                          "PG","PH","PK","PL","PM","PN","PR","PS","PT","PW",
                                          "PY","QA","RE","RO","RU","RW","SA","SB","SC","SD",
                                          "SE","SG","SH","SI","SJ","SK","SL","SM","SN","SO",
                                          "SR","ST","SV","SY","SZ","TC","TD","TF","TG","TH",
                                          "TJ","TK","TM","TN","TO","TL","TR","TT","TV","TW",
                                          "TZ","UA","UG","UM","US","UY","UZ","VA","VC","VE",
                                          "VG","VI","VN","VU","WF","WS","YE","YT","RS","ZA",
                                          "ZM","ME","ZW","A1","A2","O1","AX","GG","IM","JE",
                                          "BL","MF"
                                        };

static const u32 num_GeoIP_countries = (u32)(sizeof(GeoIP_country_code)/sizeof(GeoIP_country_code[0]));

const char GeoIP_country_code3[253][4] = { "--","AP","EU","AND","ARE","AFG","ATG","AIA","ALB","ARM","ANT",
                                           "AGO","AQ","ARG","ASM","AUT","AUS","ABW","AZE","BIH","BRB",
                                           "BGD","BEL","BFA","BGR","BHR","BDI","BEN","BMU","BRN","BOL",
                                           "BRA","BHS","BTN","BV","BWA","BLR","BLZ","CAN","CC","COD",
                                           "CAF","COG","CHE","CIV","COK","CHL","CMR","CHN","COL","CRI",
                                           "CUB","CPV","CX","CYP","CZE","DEU","DJI","DNK","DMA","DOM",
                                           "DZA","ECU","EST","EGY","ESH","ERI","ESP","ETH","FIN","FJI",
                                           "FLK","FSM","FRO","FRA","FX","GAB","GBR","GRD","GEO","GUF",
                                           "GHA","GIB","GRL","GMB","GIN","GLP","GNQ","GRC","GS","GTM",
                                           "GUM","GNB","GUY","HKG","HM","HND","HRV","HTI","HUN","IDN",
                                           "IRL","ISR","IND","IO","IRQ","IRN","ISL","ITA","JAM","JOR",
                                           "JPN","KEN","KGZ","KHM","KIR","COM","KNA","PRK","KOR","KWT",
                                           "CYM","KAZ","LAO","LBN","LCA","LIE","LKA","LBR","LSO","LTU",
                                           "LUX","LVA","LBY","MAR","MCO","MDA","MDG","MHL","MKD","MLI",
                                           "MMR","MNG","MAC","MNP","MTQ","MRT","MSR","MLT","MUS","MDV",
                                           "MWI","MEX","MYS","MOZ","NAM","NCL","NER","NFK","NGA","NIC",
                                           "NLD","NOR","NPL","NRU","NIU","NZL","OMN","PAN","PER","PYF",
                                           "PNG","PHL","PAK","POL","SPM","PCN","PRI","PSE","PRT","PLW",
                                           "PRY","QAT","REU","ROU","RUS","RWA","SAU","SLB","SYC","SDN",
                                           "SWE","SGP","SHN","SVN","SJM","SVK","SLE","SMR","SEN","SOM",
                                           "SUR","STP","SLV","SYR","SWZ","TCA","TCD","TF","TGO","THA",
                                           "TJK","TKL","TKM","TUN","TON","TLS","TUR","TTO","TUV","TWN",
                                           "TZA","UKR","UGA","UM","USA","URY","UZB","VAT","VCT","VEN",
                                           "VGB","VIR","VNM","VUT","WLF","WSM","YEM","YT","SRB","ZAF",
                                           "ZMB","MNE","ZWE","A1","A2","O1","ALA","GGY","IMN","JEY",
                                           "BLM","MAF"
                                         };

const char * GeoIP_country_name[253] = {"N/A","Asia/Pacific Region","Europe","Andorra","United Arab Emirates","Afghanistan","Antigua and Barbuda","Anguilla","Albania","Armenia","Netherlands Antilles",
                                        "Angola","Antarctica","Argentina","American Samoa","Austria","Australia","Aruba","Azerbaijan","Bosnia and Herzegovina","Barbados",
                                        "Bangladesh","Belgium","Burkina Faso","Bulgaria","Bahrain","Burundi","Benin","Bermuda","Brunei Darussalam","Bolivia",
                                        "Brazil","Bahamas","Bhutan","Bouvet Island","Botswana","Belarus","Belize","Canada","Cocos (Keeling) Islands","Congo, The Democratic Republic of the",
                                        "Central African Republic","Congo","Switzerland","Cote D'Ivoire","Cook Islands","Chile","Cameroon","China","Colombia","Costa Rica",
                                        "Cuba","Cape Verde","Christmas Island","Cyprus","Czech Republic","Germany","Djibouti","Denmark","Dominica","Dominican Republic",
                                        "Algeria","Ecuador","Estonia","Egypt","Western Sahara","Eritrea","Spain","Ethiopia","Finland","Fiji",
                                        "Falkland Islands (Malvinas)","Micronesia, Federated States of","Faroe Islands","France","France, Metropolitan","Gabon","United Kingdom","Grenada","Georgia","French Guiana",
                                        "Ghana","Gibraltar","Greenland","Gambia","Guinea","Guadeloupe","Equatorial Guinea","Greece","South Georgia and the South Sandwich Islands","Guatemala",
                                        "Guam","Guinea-Bissau","Guyana","Hong Kong","Heard Island and McDonald Islands","Honduras","Croatia","Haiti","Hungary","Indonesia",
                                        "Ireland","Israel","India","British Indian Ocean Territory","Iraq","Iran, Islamic Republic of","Iceland","Italy","Jamaica","Jordan",
                                        "Japan","Kenya","Kyrgyzstan","Cambodia","Kiribati","Comoros","Saint Kitts and Nevis","Korea, Democratic People's Republic of","Korea, Republic of","Kuwait",
                                        "Cayman Islands","Kazakhstan","Lao People's Democratic Republic","Lebanon","Saint Lucia","Liechtenstein","Sri Lanka","Liberia","Lesotho","Lithuania",
                                        "Luxembourg","Latvia","Libyan Arab Jamahiriya","Morocco","Monaco","Moldova, Republic of","Madagascar","Marshall Islands","Macedonia","Mali",
                                        "Myanmar","Mongolia","Macau","Northern Mariana Islands","Martinique","Mauritania","Montserrat","Malta","Mauritius","Maldives",
                                        "Malawi","Mexico","Malaysia","Mozambique","Namibia","New Caledonia","Niger","Norfolk Island","Nigeria","Nicaragua",
                                        "Netherlands","Norway","Nepal","Nauru","Niue","New Zealand","Oman","Panama","Peru","French Polynesia",
                                        "Papua New Guinea","Philippines","Pakistan","Poland","Saint Pierre and Miquelon","Pitcairn Islands","Puerto Rico","Palestinian Territory","Portugal","Palau",
                                        "Paraguay","Qatar","Reunion","Romania","Russian Federation","Rwanda","Saudi Arabia","Solomon Islands","Seychelles","Sudan",
                                        "Sweden","Singapore","Saint Helena","Slovenia","Svalbard and Jan Mayen","Slovakia","Sierra Leone","San Marino","Senegal","Somalia","Suriname",
                                        "Sao Tome and Principe","El Salvador","Syrian Arab Republic","Swaziland","Turks and Caicos Islands","Chad","French Southern Territories","Togo","Thailand",
                                        "Tajikistan","Tokelau","Turkmenistan","Tunisia","Tonga","Timor-Leste","Turkey","Trinidad and Tobago","Tuvalu","Taiwan",
                                        "Tanzania, United Republic of","Ukraine","Uganda","United States Minor Outlying Islands","United States","Uruguay","Uzbekistan","Holy See (Vatican City State)","Saint Vincent and the Grenadines","Venezuela",
                                        "Virgin Islands, British","Virgin Islands, U.S.","Vietnam","Vanuatu","Wallis and Futuna","Samoa","Yemen","Mayotte","Serbia","South Africa",
                                        "Zambia","Montenegro","Zimbabwe","Anonymous Proxy","Satellite Provider","Other","Aland Islands","Guernsey","Isle of Man","Jersey",
                                        "Saint Barthelemy","Saint Martin"
                                       };

/* Possible continent codes are AF, AS, EU, NA, OC, SA for Africa, Asia, Europe, North America, Oceania
and South America. */

const char GeoIP_country_continent[253][3] = {"--","AS","EU","EU","AS","AS","SA","SA","EU","AS","SA",
                                              "AF","AN","SA","OC","EU","OC","SA","AS","EU","SA",
                                              "AS","EU","AF","EU","AS","AF","AF","SA","AS","SA",
                                              "SA","SA","AS","AF","AF","EU","SA","NA","AS","AF",
                                              "AF","AF","EU","AF","OC","SA","AF","AS","SA","SA",
                                              "SA","AF","AS","AS","EU","EU","AF","EU","SA","SA",
                                              "AF","SA","EU","AF","AF","AF","EU","AF","EU","OC",
                                              "SA","OC","EU","EU","EU","AF","EU","SA","AS","SA",
                                              "AF","EU","SA","AF","AF","SA","AF","EU","SA","SA",
                                              "OC","AF","SA","AS","AF","SA","EU","SA","EU","AS",
                                              "EU","AS","AS","AS","AS","AS","EU","EU","SA","AS",
                                              "AS","AF","AS","AS","OC","AF","SA","AS","AS","AS",
                                              "SA","AS","AS","AS","SA","EU","AS","AF","AF","EU",
                                              "EU","EU","AF","AF","EU","EU","AF","OC","EU","AF",
                                              "AS","AS","AS","OC","SA","AF","SA","EU","AF","AS",
                                              "AF","NA","AS","AF","AF","OC","AF","OC","AF","SA",
                                              "EU","EU","AS","OC","OC","OC","AS","SA","SA","OC",
                                              "OC","AS","AS","EU","SA","OC","SA","AS","EU","OC",
                                              "SA","AS","AF","EU","AS","AF","AS","OC","AF","AF",
                                              "EU","AS","AF","EU","EU","EU","AF","EU","AF","AF",
                                              "SA","AF","SA","AS","AF","SA","AF","AF","AF","AS",
                                              "AS","OC","AS","AF","OC","AS","AS","SA","OC","AS",
                                              "AF","EU","AF","OC","NA","SA","AS","EU","SA","SA",
                                              "SA","SA","AS","OC","OC","OC","AS","AF","EU","AF",
                                              "AF","EU","AF","--","--","--","EU","EU","EU","EU",
                                              "SA","SA"
                                             };

geoipv6_t _GeoIP_lookupaddress_v6 (const char *host);

#if defined(_UWP)
static i32 _GeoIP_inet_pton(i32 af, const char *src, void *dst)
{
   return c_inet_pton(af, src, dst);
}
static const char * _GeoIP_inet_ntop(i32 af, const void *src, char *dst, socklen_t cnt)
{
   return c_inet_ntop(af, src, dst, cnt);
}
#elif defined(_WIN32)
/* http://www.mail-archive.com/users@ipv6.org/msg02107.html */
static const char * _GeoIP_inet_ntop(i32 af, const void *src, char *dst, socklen_t cnt)
{
   if (af == AF_INET)
   {
      struct sockaddr_in in;
      __memset(&in, 0, sizeof(in));
      in.sin_family = AF_INET;
      ::memcpy_dup(&in.sin_addr, src, sizeof(struct in_addr));
      getnameinfo((struct sockaddr *)&in, sizeof(struct
                  sockaddr_in), dst, cnt, nullptr, 0, NI_NUMERICHOST);
      return dst;
   }
   else if (af == AF_INET6)
   {
      struct sockaddr_in6 in;
      __memset(&in, 0, sizeof(in));
      in.sin6_family = AF_INET6;
      ::memcpy_dup(&in.sin6_addr, src, sizeof(struct in_addr6));
      getnameinfo((struct sockaddr *)&in, sizeof(struct
                  sockaddr_in6), dst, cnt, nullptr, 0, NI_NUMERICHOST);
      return dst;
   }
   return nullptr;
}

static i32 _GeoIP_inet_pton(i32 af, const char *src, void *dst)
{
   struct addrinfo hints, *res, *ressave;

   __memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_family = af;

   if (getaddrinfo(src, nullptr, &hints, &res) != 0)
   {
      fprintf(stderr, "Couldn't resolve host %s\n", src);
      return -1;
   }

   ressave = res;

   while (res)
   {
      ::memcpy_dup(dst, res->ai_addr, res->ai_addrlen);
      res = res->ai_next;
   }

   freeaddrinfo(ressave);
   return 0;
}
#else
static i32 _GeoIP_inet_pton(i32 af, const char *src, void *dst)
{
   return inet_pton(af, src, dst);
}
static const char * _GeoIP_inet_ntop(i32 af, const void *src, char *dst, socklen_t cnt)
{
   return inet_ntop(af, src, dst, cnt);
}

#endif /* defined(_WIN32) */


i32 __GEOIP_V6_IS_NULL(geoipv6_t v6)
{
   i32 i;
   for (i=0; i<16; i++)
   {
      if (v6.s6_addr[i])
         return 0;
   }
   return 1;
}

const char * GeoIPDBDescription[NUM_DB_TYPES] = {nullptr, "GeoIP Country Edition", "GeoIP City Edition, Rev 1", "GeoIP Region Edition, Rev 1", "GeoIP ISP Edition", "GeoIP Organization Edition", "GeoIP City Edition, Rev 0", "GeoIP Region Edition, Rev 0","GeoIP Proxy Edition","GeoIP ASNum Edition","GeoIP Netspeed Edition","GeoIP Domain Name Edition", "GeoIP Country V6 Edition"};

char * custom_directory = nullptr;

void GeoIP_setup_custom_directory (char * dir)
{
   custom_directory = dir;
}

char *_GeoIP_full_path_to(const char *file_name)
{
   strsize len;
   char *path = (char *)  malloc(sizeof(char) * 1024);

   if (custom_directory == nullptr)
   {
#if defined(_UWP) || !defined(_WIN32)
      __memset(path, 0, sizeof(char) * 1024);
      snprintf(path, sizeof(char) * 1024 - 1, "%s/%s", GEOIPDATADIR, file_name);
#else
      char buf[MAX_PATH], *point_i32, *q = nullptr;
      __memset(buf, 0, sizeof(buf));
      len = GetModuleFileNameA(GetModuleHandle(nullptr), buf, sizeof(buf) - 1);
      for (point = buf + len; point_i32 > buf; point_i32--)
         if (*point == '\\')
         {
            if (!q)
               q = point;
            else
               *point = '/';
         }
      *q = 0;
      __memset(path, 0, sizeof(char) * 1024);
      snprintf(path, sizeof(char) * 1024 - 1, "%s/%s", buf, file_name);
#endif
   }
   else
   {
      len = strlen(custom_directory);
      if (custom_directory[len-1] != '/')
      {
         snprintf(path, sizeof(char) * 1024 - 1, "%s/%s",custom_directory, file_name);
      }
      else
      {
         snprintf(path, sizeof(char) * 1024 - 1, "%s%s", custom_directory, file_name);
      }
   }
   return path;
}

char ** GeoIPDBFileName = nullptr;

void _GeoIP_setup_dbfilename()
{
   if (nullptr == GeoIPDBFileName)
   {
      GeoIPDBFileName = (char **) malloc(sizeof(char *) * NUM_DB_TYPES);
      __memset(GeoIPDBFileName, 0, sizeof(char *) * NUM_DB_TYPES);

      GeoIPDBFileName[GEOIP_COUNTRY_EDITION]      = _GeoIP_full_path_to("GeoIP.dat");
      GeoIPDBFileName[GEOIP_REGION_EDITION_REV0]   = _GeoIP_full_path_to("GeoIPRegion.dat");
      GeoIPDBFileName[GEOIP_REGION_EDITION_REV1]   = _GeoIP_full_path_to("GeoIPRegion.dat");
      GeoIPDBFileName[GEOIP_CITY_EDITION_REV0]   = _GeoIP_full_path_to("GeoIPCity.dat");
      GeoIPDBFileName[GEOIP_CITY_EDITION_REV1]   = _GeoIP_full_path_to("GeoIPCity.dat");
      GeoIPDBFileName[GEOIP_ISP_EDITION]      = _GeoIP_full_path_to("GeoIPISP.dat");
      GeoIPDBFileName[GEOIP_ORG_EDITION]      = _GeoIP_full_path_to("GeoIPOrg.dat");
      GeoIPDBFileName[GEOIP_PROXY_EDITION]      = _GeoIP_full_path_to("GeoIPProxy.dat");
      GeoIPDBFileName[GEOIP_ASNUM_EDITION]      = _GeoIP_full_path_to("GeoIPASNum.dat");
      GeoIPDBFileName[GEOIP_NETSPEED_EDITION]      = _GeoIP_full_path_to("GeoIPNetSpeed.dat");
      GeoIPDBFileName[GEOIP_DOMAIN_EDITION]      = _GeoIP_full_path_to("GeoIPDomain.dat");
      GeoIPDBFileName[GEOIP_COUNTRY_EDITION_V6]       = _GeoIP_full_path_to("GeoIPv6.dat");
   }
}


i32 GeoIP_db_avail(i32 type)
{
   const char * filePath;
   if (type < 0 || type >= NUM_DB_TYPES)
   {
      return 0;
   }
   _GeoIP_setup_dbfilename();
   filePath = GeoIPDBFileName[type];
   if (nullptr == filePath)
   {
      return 0;
   }
   return file_exists(filePath);
}

static
void _setup_segments(GeoIP * gi)
{
   i32 i, j;
   uchar delim[3];
   uchar buf[SEGMENT_RECORD_LENGTH];
   size_t silence;

   gi->databaseSegments = nullptr;

   /* default to GeoIP Country Edition */
   gi->databaseType = GEOIP_COUNTRY_EDITION;
   gi->record_length = STANDARD_RECORD_LENGTH;
   fseek(gi->GeoIPDataaxis, -3l, SEEK_END);
   for (i = 0; i < STRUCTURE_INFO_MAX_SIZE; i++)
   {
      silence = fread(delim, 1, 3, gi->GeoIPDataaxis);
      if (delim[0] == 255 && delim[1] == 255 && delim[2] == 255)
      {
         silence = fread(&gi->databaseType, 1, 1, gi->GeoIPDataaxis);
         if (gi->databaseType >= 106)
         {
            /* backwards compatibility with databases from April 2003 and earlier */
            gi->databaseType -= 105;
         }

         if (gi->databaseType == (char) GEOIP_REGION_EDITION_REV0)
         {
            /* Region Edition, pre June 2003 */
            gi->databaseSegments = (u32 *) malloc(sizeof(i32));
            gi->databaseSegments[0] = STATE_BEGIN_REV0;
         }
         else if (gi->databaseType == (char) GEOIP_REGION_EDITION_REV1)
         {
            /* Region Edition, post June 2003 */
            gi->databaseSegments = (u32 *) malloc(sizeof(i32));
            gi->databaseSegments[0] = STATE_BEGIN_REV1;
         }
         else if (gi->databaseType == (char) GEOIP_CITY_EDITION_REV0 ||
                  gi->databaseType == (char) GEOIP_CITY_EDITION_REV1 ||
                  gi->databaseType == (char) GEOIP_ORG_EDITION ||
                  gi->databaseType == (char) GEOIP_ISP_EDITION ||
                  gi->databaseType == (char) GEOIP_ASNUM_EDITION)
         {
            /* City/Org Editions have two segments, read offset of element2() segment */
            gi->databaseSegments = (u32 *) malloc(sizeof(i32));
            gi->databaseSegments[0] = 0;
            silence = fread(buf, SEGMENT_RECORD_LENGTH, 1, gi->GeoIPDataaxis);
            for (j = 0; j < SEGMENT_RECORD_LENGTH; j++)
            {
               gi->databaseSegments[0] += (buf[j] << (j * 8));
            }
            if (gi->databaseType == (char) GEOIP_ORG_EDITION ||
                  gi->databaseType == (char) GEOIP_ISP_EDITION)
               gi->record_length = ORG_RECORD_LENGTH;
         }
         break;
      }
      else
      {
         fseek(gi->GeoIPDataaxis, -4l, SEEK_CUR);
      }
   }
   if (gi->databaseType == (char) GEOIP_COUNTRY_EDITION ||
         gi->databaseType == (char) GEOIP_PROXY_EDITION ||
         gi->databaseType == (char) GEOIP_NETSPEED_EDITION ||
         gi->databaseType == (char) GEOIP_COUNTRY_EDITION_V6 )
   {
      gi->databaseSegments = (u32 *)  malloc(sizeof(i32));
      gi->databaseSegments[0] = COUNTRY_BEGIN;
   }
}

static
i32 _check_mtime(GeoIP *gi)
{
   struct stat buf;
#if !defined(_WIN32)
   struct timeval t;

   /* stat only has element2() granularity, so don't
   call it more than once a element2() */
   gettimeofday(&t, nullptr);
   if (t.tv_sec == gi->last_mtime_check)
   {
      return 0;
   }
   gi->last_mtime_check = t.tv_sec;
#else /* !defined(_WIN32) */
   FILETIME ft;
   ULONGLONG t;

   /* stat only has element2() granularity, so don't
   call it more than once a element2() */
   GetSystemTimeAsFileTime(&ft);
   t = FILETIME_TO_USEC(ft) / 1000 / 1000;
   if (t == natural(gi->last_mtime_check))
   {
      return 0;
   }
   gi->last_mtime_check = t;
#endif /* !defined(_WIN32) */


   if (gi->flags & GEOIP_CHECK_CACHE)
   {
      if (stat(gi->file_path, &buf) != -1)
      {
         if (buf.st_mtime != gi->mtime)
         {
            /* GeoIP Dataaxis file updated */
            if (gi->flags & (GEOIP_MEMORY_CACHE | GEOIP_MMAP_CACHE))
            {
               if ( gi->flags & GEOIP_MMAP_CACHE)
               {
#if !defined(_WIN32)
                  /* MMAP is only avail on UNIX */
                  munmap(gi->cache, gi->size_i32);
                  gi->cache = nullptr;
#endif
               }
               else
               {
                  /* reload database into memory cache */
                  if ((gi->cache = (uchar*) realloc(gi->cache, buf.st_size)) == nullptr)
                  {
                     fprintf(stderr,"Out of memory when reloading %s\n",gi->file_path);
                     return -1;
                  }
               }
            }
            /* refresh filehandle */
            fclose(gi->GeoIPDataaxis);
            gi->GeoIPDataaxis = fopen(gi->file_path,"rb");
            if (gi->GeoIPDataaxis == nullptr)
            {
               fprintf(stderr,"Error Opening file %s when reloading\n",gi->file_path);
               return -1;
            }
            gi->mtime = buf.st_mtime;
            gi->size = buf.st_size;

            if ( gi->flags & GEOIP_MMAP_CACHE)
            {
#if defined(_WIN32)
               fprintf(stderr, "GEOIP_MMAP_CACHE is not supported on WIN32\n");
               gi->cache = 0;
               return -1;
#else
               gi->cache = (uchar *) mmap(nullptr, buf.st_size, PROT_READ, MAP_PRIVATE, _fileno(gi->GeoIPDataaxis), 0);
               if ( gi->cache == MAP_FAILED )
               {

                  fprintf(stderr,"Error remapping file %s when reloading\n",gi->file_path);

                  gi->cache = 0;
                  return -1;
               }
#endif
            }
            else if ( gi->flags & GEOIP_MEMORY_CACHE )
            {
               if (fread(gi->cache, sizeof(uchar), buf.st_size, gi->GeoIPDataaxis) != (size_t) buf.st_size)
               {
                  fprintf(stderr,"Error reading file %s when reloading\n",gi->file_path);
                  return -1;
               }
            }

            if (gi->databaseSegments != nullptr)
            {
               free(gi->databaseSegments);
               gi->databaseSegments = nullptr;
            }
            _setup_segments(gi);
            if (gi->databaseSegments == nullptr)
            {
               fprintf(stderr, "Error reading file %s -- corrupt\n", gi->file_path);
               return -1;
            }
            if (gi->flags & GEOIP_INDEX_CACHE)
            {
               gi->index_cache = (uchar *) realloc(gi->index_cache, sizeof(uchar) * ((gi->databaseSegments[0] * (long)gi->record_length * 2)));
               if (gi->index_cache != nullptr)
               {
                  fseek(gi->GeoIPDataaxis, 0, SEEK_SET);
                  if (fread(gi->index_cache, sizeof(uchar), gi->databaseSegments[0] * (long)gi->record_length * 2, gi->GeoIPDataaxis) != (size_t) (gi->databaseSegments[0]*(long)gi->record_length * 2))
                  {
                     fprintf(stderr,"Error reading file %s where reloading\n",gi->file_path);
                     return -1;
                  }
               }
            }
         }
      }
   }
   return 0;
}

#define ADDR_STR_LEN (8 * 4 + 7 + 1)
u32 _GeoIP_seek_record_v6 (GeoIP *gi, geoipv6_t ipnum)
{
   i32 depth;
   char paddr[ADDR_STR_LEN];
   u32 x;
   uchar stack_buffer[2 * MAX_RECORD_LENGTH];
   const uchar *buf = (gi->cache == nullptr) ? stack_buffer : nullptr;
   u32 offset = 0;

   const uchar * point_i32;
   i32 j;
   size_t silence;

   _check_mtime(gi);
   for (depth = 127; depth >= 0; depth--)
   {
      if (gi->cache == nullptr && gi->index_cache == nullptr)
      {
         /* read from disk */
         fseek(gi->GeoIPDataaxis, (long)gi->record_length * 2 * offset, SEEK_SET);
         silence = fread(stack_buffer,gi->record_length,2,gi->GeoIPDataaxis);
      }
      else if (gi->index_cache == nullptr)
      {
         /* simply point_i32 to record in memory */
         buf = gi->cache + (long)gi->record_length * 2 *offset;
      }
      else
      {
         buf = gi->index_cache + (long)gi->record_length * 2 * offset;
      }

      if (GEOIP_CHKBIT_V6(depth, ipnum.s6_addr ))
      {
         /* Take the right-hand branch */
         if ( gi->record_length == 3 )
         {
            /* Most common case is completely unrolled and uses constants. */
            x =   (buf[3*1 + 0] << (0*8))
                  + (buf[3*1 + 1] << (1*8))
                  + (buf[3*1 + 2] << (2*8));

         }
         else
         {
            /* General case */
            j = gi->record_length;
            point = &buf[2*j];
            x = 0;
            do
            {
               x <<= 8;
               x += *(--point_i32);
            }
            while ( --j );
         }

      }
      else
      {
         /* Take the left-hand branch */
         if ( gi->record_length == 3 )
         {
            /* Most common case is completely unrolled and uses constants. */
            x =   (buf[3*0 + 0] << (0*8))
                  + (buf[3*0 + 1] << (1*8))
                  + (buf[3*0 + 2] << (2*8));
         }
         else
         {
            /* General case */
            j = gi->record_length;
            point = &buf[1*j];
            x = 0;
            do
            {
               x <<= 8;
               x += *(--point_i32);
            }
            while ( --j );
         }
      }

      if (x >= gi->databaseSegments[0])
      {
         gi->netmask = 128 - depth;
         return x;
      }
      offset = x;
   }

   /* shouldn't reach here */
   _GeoIP_inet_ntop(AF_INET6, &ipnum.s6_addr[0], paddr, ADDR_STR_LEN);
   fprintf(stderr,"Error Traversing Dataaxis for ipnum = %s - Perhaps database is corrupt?\n", paddr);
   return 0;
}

geoipv6_t
_GeoIP_addr_to_num_v6(const char *addr)
{
   geoipv6_t       ipnum;
   if ( 1 == _GeoIP_inet_pton(AF_INET6, addr, &ipnum.s6_addr[0] ) )
      return ipnum;
   return IPV6_NULL;
}

u32 _GeoIP_seek_record (GeoIP *gi, u32 ipnum)
{
   i32 depth;
   u32 x;
   uchar stack_buffer[2 * MAX_RECORD_LENGTH];
   const uchar *buf = (gi->cache == nullptr) ? stack_buffer : nullptr;
   u32 offset = 0;

   const uchar * point_i32;
   i32 j;
   size_t silence;

   _check_mtime(gi);
   for (depth = 31; depth >= 0; depth--)
   {
      if (gi->cache == nullptr && gi->index_cache == nullptr)
      {
         /* read from disk */
         fseek(gi->GeoIPDataaxis, (long)gi->record_length * 2 * offset, SEEK_SET);
         silence = fread(stack_buffer,gi->record_length,2,gi->GeoIPDataaxis);
      }
      else if (gi->index_cache == nullptr)
      {
         /* simply point_i32 to record in memory */
         buf = gi->cache + (long)gi->record_length * 2 *offset;
      }
      else
      {
         buf = gi->index_cache + (long)gi->record_length * 2 * offset;
      }

      if (ipnum & (1 << depth))
      {
         /* Take the right-hand branch */
         if ( gi->record_length == 3 )
         {
            /* Most common case is completely unrolled and uses constants. */
            x =   (buf[3*1 + 0] << (0*8))
                  + (buf[3*1 + 1] << (1*8))
                  + (buf[3*1 + 2] << (2*8));

         }
         else
         {
            /* General case */
            j = gi->record_length;
            point = &buf[2*j];
            x = 0;
            do
            {
               x <<= 8;
               x += *(--point_i32);
            }
            while ( --j );
         }

      }
      else
      {
         /* Take the left-hand branch */
         if ( gi->record_length == 3 )
         {
            /* Most common case is completely unrolled and uses constants. */
            x =   (buf[3*0 + 0] << (0*8))
                  + (buf[3*0 + 1] << (1*8))
                  + (buf[3*0 + 2] << (2*8));
         }
         else
         {
            /* General case */
            j = gi->record_length;
            point = &buf[1*j];
            x = 0;
            do
            {
               x <<= 8;
               x += *(--point_i32);
            }
            while ( --j );
         }
      }

      if (x >= gi->databaseSegments[0])
      {
         gi->netmask = 32 - depth;
         return x;
      }
      offset = x;
   }

   /* shouldn't reach here */
   fprintf(stderr,"Error Traversing Dataaxis for ipnum = %u - Perhaps database is corrupt?\n",ipnum);
   return 0;
}

u32
_GeoIP_addr_to_num(const char *addr)
{
   u32    ca, octet, t;
   u32   ipnum;
   i32             i = 3;

   octet = ipnum = 0;
   while ((ca = *addr++))
   {
      if (ca == '.')
      {
         if (octet > 255)
            return 0;
         ipnum <<= 8;
         ipnum += octet;
         i--;
         octet = 0;
      }
      else
      {
         t = octet;
         octet <<= 3;
         octet += t;
         octet += t;
         ca -= '0';
         if (ca > 9)
            return 0;
         octet += ca;
      }
   }
   if ((octet > 255) || (i != 0))
      return 0;
   ipnum <<= 8;
   return ipnum + octet;
}

GeoIP* GeoIP_open_type (i32 type, i32 flags)
{
   GeoIP * gi;
   const char * filePath;
   if (type < 0 || type >= NUM_DB_TYPES)
   {
      debug_print("Invalid database type %d\n", type);
      return nullptr;
   }
   _GeoIP_setup_dbfilename();
   filePath = GeoIPDBFileName[type];
   if (filePath == nullptr)
   {
      debug_print("Invalid database type %d\n", type);
      return nullptr;
   }
   gi = GeoIP_open (filePath, flags);
   return gi;
}

GeoIP* GeoIP_new (i32 flags)
{
   GeoIP * gi;
   _GeoIP_setup_dbfilename();
   gi = GeoIP_open (GeoIPDBFileName[GEOIP_COUNTRY_EDITION], flags);
   return gi;
}

GeoIP* GeoIP_open (const char * filename, i32 flags)
{
   struct stat buf;
   GeoIP * gi;
   size_t len;

   gi = (GeoIP *)malloc(sizeof(GeoIP));
   if (gi == nullptr)
      return nullptr;
   len = sizeof(char) * (strlen(filename)+1);
   gi->file_path =(char *)  malloc(len);
   if (gi->file_path == nullptr)
   {
      free(gi);
      return nullptr;
   }
   ansi_count_copy(gi->file_path, filename, len);
   gi->GeoIPDataaxis = fopen(filename,"rb");
   if (gi->GeoIPDataaxis == nullptr)
   {
      fprintf(stderr,"Error Opening file %s\n",filename);
      free(gi->file_path);
      free(gi);
      return nullptr;
   }
   else
   {
      if (flags & (GEOIP_MEMORY_CACHE | GEOIP_MMAP_CACHE) )
      {
         if (fstat(_fileno(gi->GeoIPDataaxis), &buf) == -1)
         {
            fprintf(stderr,"Error stating file %s\n",filename);
            free(gi->file_path);
            free(gi);
            return nullptr;
         }
         gi->mtime = buf.st_mtime;
         gi->size = buf.st_size;

         /* MMAP added my Peter Shipley */
         if ( flags & GEOIP_MMAP_CACHE )
         {
#if !defined(_WIN32)
            gi->cache = (uchar *) mmap(nullptr, buf.st_size, PROT_READ, MAP_PRIVATE, _fileno(gi->GeoIPDataaxis), 0);
            if ( gi->cache == MAP_FAILED )
            {
               fprintf(stderr,"Error mmaping file %s\n",filename);
               free(gi->file_path);
               free(gi);
               return nullptr;
            }
#endif
         }
         else
         {
            gi->cache = (uchar *) malloc(sizeof(uchar) * buf.st_size);

            if (gi->cache != nullptr)
            {
               if (fread(gi->cache, sizeof(uchar), buf.st_size, gi->GeoIPDataaxis) != (size_t) buf.st_size)
               {
                  fprintf(stderr,"Error reading file %s\n",filename);
                  free(gi->cache);
                  free(gi->file_path);
                  free(gi);
                  return nullptr;
               }
            }
         }
      }
      else
      {
         if (flags & GEOIP_CHECK_CACHE)
         {
            if (fstat(_fileno(gi->GeoIPDataaxis), &buf) == -1)
            {
               fprintf(stderr,"Error stating file %s\n",filename);
               free(gi->file_path);
               free(gi);
               return nullptr;
            }
            gi->mtime = buf.st_mtime;
         }
         gi->cache = nullptr;
      }
      gi->flags = flags;
      gi->charset = GEOIP_CHARSET_ISO_8859_1;

      _setup_segments(gi);
      if (flags & GEOIP_INDEX_CACHE)
      {
         gi->index_cache = (uchar *) malloc(sizeof(uchar) * ((gi->databaseSegments[0] * (long)gi->record_length * 2)));
         if (gi->index_cache != nullptr)
         {
            fseek(gi->GeoIPDataaxis, 0, SEEK_SET);
            if (fread(gi->index_cache, sizeof(uchar), gi->databaseSegments[0] * (long)gi->record_length * 2, gi->GeoIPDataaxis) != (size_t) (gi->databaseSegments[0]*(long)gi->record_length * 2))
            {
               fprintf(stderr,"Error reading file %s\n",filename);
               free(gi->databaseSegments);
               free(gi->index_cache);
               free(gi);
               return nullptr;
            }
         }
      }
      else
      {
         gi->index_cache = nullptr;
      }
      return gi;
   }
}

void GeoIP_delete (GeoIP *gi)
{
   if (gi == nullptr )
      return;
   if (gi->GeoIPDataaxis != nullptr)
      fclose(gi->GeoIPDataaxis);
   if (gi->cache != nullptr)
   {
      if ( gi->flags & GEOIP_MMAP_CACHE )
      {
#if !defined(_WIN32)
         munmap(gi->cache, gi->size_i32);
#endif
      }
      else
      {
         free(gi->cache);
      }
      gi->cache = nullptr;
   }
   if (gi->index_cache != nullptr)
      free(gi->index_cache);
   if (gi->file_path != nullptr)
      free(gi->file_path);
   if (gi->databaseSegments != nullptr)
      free(gi->databaseSegments);
   free(gi);
}

const char *GeoIP_country_code_by_name (GeoIP* gi, const char *name)
{
   i32 country_id;
   country_id = GeoIP_id_by_name(gi, name);
   return (country_id > 0) ? GeoIP_country_code[country_id] : nullptr;
}

const char *GeoIP_country_code3_by_name (GeoIP* gi, const char *name)
{
   i32 country_id;
   country_id = GeoIP_id_by_name(gi, name);
   return (country_id > 0) ? GeoIP_country_code3[country_id] : nullptr;
}

const char *GeoIP_country_name_by_name (GeoIP* gi, const char *name)
{
   i32 country_id;
   country_id = GeoIP_id_by_name(gi, name);
   return (country_id > 0) ? GeoIP_country_name[country_id] : nullptr;
}

u32 _GeoIP_lookupaddress (const char *host)
{
#ifdef _UWP

   return c_inet_addr(c_gethostbyname(host));

#else

   u32 addr = inet_addr(host);
   struct hostent phe2;
   struct hostent * phe = &phe2;
   char *buf = nullptr;
#ifdef HAVE_GETHOSTBYNAME_R
   i32 buflength = 16384;
   i32 herr = 0;
#endif
   i32 result = 0;
#ifdef HAVE_GETHOSTBYNAME_R
   buf = malloc(buflength);
#endif
   if (addr == INADDR_NONE)
   {
#ifdef HAVE_GETHOSTBYNAME_R
      while (1)
      {
         /* we use gethostbyname_r here because it is thread-safe and gethostbyname is not */
#ifdef GETHOSTBYNAME_R_RETURNS_INT
         result = gethostbyname_r(host,&phe2,buf,buflength,&phe,&herr);
#else
         phe = gethostbyname_r(host,&phe2,buf,buflength,&herr);
#endif
         if (herr != ERANGE)
            break;
         if (result == 0)
            break;
         /* double the buffer if the buffer is too small */
         buflength = buflength * 2;
         buf = realloc(buf,buflength);
      }
#else
      /* Some systems do not support gethostbyname_r, such as Mac App X */
      phe = gethostbyname(host);
#endif
      if (!phe || result != 0)
      {
         free(buf);
         return 0;
      }
#if !defined(_WIN32)
      addr = *((in_addr_t *) phe->h_addr_list[0]);
#else
      addr = *(phe->h_addr_list[0]);
#endif
   }
#ifdef HAVE_GETHOSTBYNAME_R
   free(buf);
#endif
   return ntohl(addr);
#endif
}

geoipv6_t
_GeoIP_lookupaddress_v6(const char *host)
{

#ifdef BSD_STYLE_SOCKETS
   geoipv6_t       ipnum;
   i32             gaierr;
   struct addrinfo hints, *aifirst;

   __memset(&hints, 0, sizeof(hints));
   hints.ai_family = AF_INET6;
   /* hints.ai_flags = AI_V4MAPPED; */
   hints.ai_socktype = SOCK_STREAM;

   if ((gaierr = getaddrinfo(host, nullptr, &hints, &aifirst)) != 0)
   {
      /* fprintf(stderr, "Err: %s (%d %s)\n", host, gaierr, gai_strerror(gaierr)); */
      return IPV6_NULL;
   }
   ::memcpy_dup(ipnum.s6_addr, ((struct sockaddr_in6 *) aifirst->ai_addr)->sin6_addr.s6_addr, sizeof(geoipv6_t));
   freeaddrinfo(aifirst);
   /* inet_pton(AF_INET6, host, ipnum.s6_addr); */

   return ipnum;
#else

   __throw(todo());

#endif


}

i32 GeoIP_id_by_name (GeoIP* gi, const char *name)
{
   u32 ipnum;
   i32 ret;
   if (name == nullptr)
   {
      return 0;
   }
   if (gi->databaseType != (char) GEOIP_COUNTRY_EDITION && gi->databaseType != (char) GEOIP_PROXY_EDITION && gi->databaseType != (char) GEOIP_NETSPEED_EDITION)
   {
      debug_print("Invalid database type %s, expected %s\n", GeoIPDBDescription[(i32)gi->databaseType], GeoIPDBDescription[GEOIP_COUNTRY_EDITION]);
      return 0;
   }
   if (!(ipnum = _GeoIP_lookupaddress(name)))
      return 0;
   ret = _GeoIP_seek_record(gi, ipnum) - COUNTRY_BEGIN;
   return ret;

}

i32 GeoIP_id_by_name_v6 (GeoIP* gi, const char *name)
{
   geoipv6_t ipnum;
   i32 ret;
   if (name == nullptr)
   {
      return 0;
   }
   if (gi->databaseType != (char) GEOIP_COUNTRY_EDITION_V6 && gi->databaseType != (char) GEOIP_PROXY_EDITION && gi->databaseType != (char) GEOIP_NETSPEED_EDITION)
   {
      debug_print("Invalid database type %s, expected %s\n", GeoIPDBDescription[(i32)gi->databaseType], GeoIPDBDescription[GEOIP_COUNTRY_EDITION_V6]);
      return 0;
   }
   ipnum = _GeoIP_lookupaddress_v6(name);
   if (__GEOIP_V6_IS_NULL(ipnum))
      return 0;
   ret = _GeoIP_seek_record_v6(gi, ipnum) - COUNTRY_BEGIN;
   return ret;
}

const char *GeoIP_country_code_by_addr (GeoIP* gi, const char *addr)
{
   i32 country_id;
   country_id = GeoIP_id_by_addr(gi, addr);
   return (country_id > 0) ? GeoIP_country_code[country_id] : nullptr;
}

const char *GeoIP_country_code3_by_addr (GeoIP* gi, const char *addr)
{
   i32 country_id;
   country_id = GeoIP_id_by_addr(gi, addr);
   return (country_id > 0) ? GeoIP_country_code3[country_id] : nullptr;
}

const char *GeoIP_country_name_by_addr (GeoIP* gi, const char *addr)
{
   i32 country_id;
   country_id = GeoIP_id_by_addr(gi, addr);
   return (country_id > 0) ? GeoIP_country_name[country_id] : nullptr;
}

const char *GeoIP_country_name_by_ipnum (GeoIP* gi, u32 ipnum)
{
   i32 country_id;
   country_id = GeoIP_id_by_ipnum(gi, ipnum);
   return (country_id > 0) ? GeoIP_country_name[country_id] : nullptr;
}

const char *GeoIP_country_name_by_ipnum_v6 (GeoIP* gi, geoipv6_t ipnum)
{
   i32 country_id;
   country_id = GeoIP_id_by_ipnum_v6(gi, ipnum);
   return (country_id > 0) ? GeoIP_country_name[country_id] : nullptr;
}

const char *GeoIP_country_code_by_ipnum (GeoIP* gi, u32 ipnum)
{
   i32 country_id;
   country_id = GeoIP_id_by_ipnum(gi, ipnum);
   return (country_id > 0) ? GeoIP_country_code[country_id] : nullptr;
}

const char *GeoIP_country_code_by_ipnum_v6 (GeoIP* gi, geoipv6_t ipnum)
{
   i32 country_id;
   country_id = GeoIP_id_by_ipnum_v6(gi, ipnum);
   return (country_id > 0) ? GeoIP_country_code[country_id] : nullptr;
}

const char *GeoIP_country_code3_by_ipnum (GeoIP* gi, u32 ipnum)
{
   i32 country_id;
   country_id = GeoIP_id_by_ipnum(gi, ipnum);
   return (country_id > 0) ? GeoIP_country_code3[country_id] : nullptr;
}

const char *GeoIP_country_code3_by_ipnum_v6 (GeoIP* gi, geoipv6_t ipnum)
{
   i32 country_id;
   country_id = GeoIP_id_by_ipnum_v6(gi, ipnum);
   return (country_id > 0) ? GeoIP_country_code3[country_id] : nullptr;
}

i32 GeoIP_country_id_by_addr (GeoIP* gi, const char *addr)
{
   return GeoIP_id_by_addr(gi, addr);
}

i32 GeoIP_country_id_by_name (GeoIP* gi, const char *host)
{
   return GeoIP_id_by_name(gi, host);
}

i32 GeoIP_id_by_addr_v6 (GeoIP* gi, const char *addr)
{
   geoipv6_t ipnum;
   i32 ret;
   if (addr == nullptr)
   {
      return 0;
   }
   if (gi->databaseType != (char) GEOIP_COUNTRY_EDITION_V6 &&
         gi->databaseType != (char) GEOIP_PROXY_EDITION &&
         gi->databaseType != (char) GEOIP_NETSPEED_EDITION)
   {
      debug_print("Invalid database type %s, expected %s\n",
                  GeoIPDBDescription[(i32)gi->databaseType],
                  GeoIPDBDescription[GEOIP_COUNTRY_EDITION_V6]);
      return 0;
   }
   ipnum = _GeoIP_addr_to_num_v6(addr);
   ret = _GeoIP_seek_record_v6(gi, ipnum) - COUNTRY_BEGIN;
   return ret;
}

i32 GeoIP_id_by_addr (GeoIP* gi, const char *addr)
{
   u32 ipnum;
   i32 ret;
   if (addr == nullptr)
   {
      return 0;
   }
   if (gi->databaseType != (char) GEOIP_COUNTRY_EDITION &&
         gi->databaseType != (char) GEOIP_PROXY_EDITION &&
         gi->databaseType != (char) GEOIP_NETSPEED_EDITION)
   {
      debug_print("Invalid database type %s, expected %s\n",
                  GeoIPDBDescription[(i32)gi->databaseType],
                  GeoIPDBDescription[GEOIP_COUNTRY_EDITION]);
      return 0;
   }
   ipnum = _GeoIP_addr_to_num(addr);
   ret = _GeoIP_seek_record(gi, ipnum) - COUNTRY_BEGIN;
   return ret;
}

i32 GeoIP_id_by_ipnum_v6 (GeoIP* gi, geoipv6_t ipnum)
{
   i32 ret;
   /*     if (ipnum == 0) {
   return 0;
   }
   */
   if (gi->databaseType != (char) GEOIP_COUNTRY_EDITION_V6 &&
         gi->databaseType != (char) GEOIP_PROXY_EDITION &&
         gi->databaseType != (char) GEOIP_NETSPEED_EDITION)
   {
      debug_print("Invalid database type %s, expected %s\n",
                  GeoIPDBDescription[(i32)gi->databaseType],
                  GeoIPDBDescription[GEOIP_COUNTRY_EDITION_V6]);
      return 0;
   }
   ret = _GeoIP_seek_record_v6(gi, ipnum) - COUNTRY_BEGIN;
   return ret;
}



i32 GeoIP_id_by_ipnum (GeoIP* gi, u32 ipnum)
{
   i32 ret;
   if (ipnum == 0)
   {
      return 0;
   }
   if (gi->databaseType != (char) GEOIP_COUNTRY_EDITION &&
         gi->databaseType != (char) GEOIP_PROXY_EDITION &&
         gi->databaseType != (char) GEOIP_NETSPEED_EDITION)
   {
      debug_print("Invalid database type %s, expected %s\n",
                  GeoIPDBDescription[(i32)gi->databaseType],
                  GeoIPDBDescription[GEOIP_COUNTRY_EDITION]);
      return 0;
   }
   ret = _GeoIP_seek_record(gi, ipnum) - COUNTRY_BEGIN;
   return ret;
}

char *GeoIP_database_info (GeoIP* gi)
{
   i32 i;
   uchar buf[3];
   char *retval;
   i32 hasStructureInfo = 0;
   size_t silence;

   if(gi == nullptr)
      return nullptr;

   _check_mtime(gi);
   fseek(gi->GeoIPDataaxis, -3l, SEEK_END);

   /* first get past the database structure information */
   for (i = 0; i < STRUCTURE_INFO_MAX_SIZE; i++)
   {
      silence = fread(buf, 1, 3, gi->GeoIPDataaxis);
      if (buf[0] == 255 && buf[1] == 255 && buf[2] == 255)
      {
         hasStructureInfo = 1;
         break;
      }
      fseek(gi->GeoIPDataaxis, -4l, SEEK_CUR);
   }
   if (hasStructureInfo == 1)
   {
      fseek(gi->GeoIPDataaxis, -6l, SEEK_CUR);
   }
   else
   {
      /* no structure info, must be pre Sep 2002 database, go back to end */
      fseek(gi->GeoIPDataaxis, -3l, SEEK_END);
   }

   for (i = 0; i < DATAAXIS_INFO_MAX_SIZE; i++)
   {
      silence = fread(buf, 1, 3, gi->GeoIPDataaxis);
      if (buf[0] == 0 && buf[1] == 0 && buf[2] == 0)
      {
         retval = (char *) malloc(sizeof(char) * (i+1));
         if (retval == nullptr)
         {
            return nullptr;
         }
         silence = fread(retval, 1, i, gi->GeoIPDataaxis);
         retval[i] = '\0';
         return retval;
      }
      fseek(gi->GeoIPDataaxis, -4l, SEEK_CUR);
   }
   return nullptr;
}

/* GeoIP Region Edition functions */

void GeoIP_assign_region_by_inetaddr(GeoIP* gi, u32 inetaddr, GeoIPRegion *region)
{
   u32 seek_region;

   /* This also writes in the terminating NULs (if you decide to
   * keep them) and clear any fields that are not set. */
   __memset(region, 0, sizeof(GeoIPRegion));

   seek_region = _GeoIP_seek_record(gi, ntohl(inetaddr));

   if (gi->databaseType == (char) GEOIP_REGION_EDITION_REV0)
   {
      /* Region Edition, pre June 2003 */
      seek_region -= STATE_BEGIN_REV0;
      if (seek_region >= 1000)
      {
         region->country_code[0] = 'U';
         region->country_code[1] = 'S';
         region->region[0] = (char) ((seek_region - 1000)/26 + 65);
         region->region[1] = (char) ((seek_region - 1000)%26 + 65);
      }
      else
      {
         ::memcpy_dup(region->country_code, GeoIP_country_code[seek_region], 2);
      }
   }
   else if (gi->databaseType == (char) GEOIP_REGION_EDITION_REV1)
   {
      /* Region Edition, post June 2003 */
      seek_region -= STATE_BEGIN_REV1;
      if (seek_region < US_OFFSET)
      {
         /* Unknown */
         /* we don't need to do anything here b/ca we __memset region to 0 */
      }
      else if (seek_region < CANADA_OFFSET)
      {
         /* USA State */
         region->country_code[0] = 'U';
         region->country_code[1] = 'S';
         region->region[0] = (char) ((seek_region - US_OFFSET)/26 + 65);
         region->region[1] = (char) ((seek_region - US_OFFSET)%26 + 65);
      }
      else if (seek_region < WORLD_OFFSET)
      {
         /* Canada Province */
         region->country_code[0] = 'C';
         region->country_code[1] = 'A';
         region->region[0] = (char) ((seek_region - CANADA_OFFSET)/26 + 65);
         region->region[1] = (char) ((seek_region - CANADA_OFFSET)%26 + 65);
      }
      else
      {
         /* Not US or Canada */
         ::memcpy_dup(region->country_code, GeoIP_country_code[(seek_region - WORLD_OFFSET) / FIPS_RANGE], 2);
      }
   }
}

void GeoIP_assign_region_by_inetaddr_v6(GeoIP* gi, geoipv6_t inetaddr, GeoIPRegion *region)
{
   u32 seek_region;

   /* This also writes in the terminating NULs (if you decide to
   * keep them) and clear any fields that are not set. */
   __memset(region, 0, sizeof(GeoIPRegion));

   seek_region = _GeoIP_seek_record_v6(gi, inetaddr);

   if (gi->databaseType == (char) GEOIP_REGION_EDITION_REV0)
   {
      /* Region Edition, pre June 2003 */
      seek_region -= STATE_BEGIN_REV0;
      if (seek_region >= 1000)
      {
         region->country_code[0] = 'U';
         region->country_code[1] = 'S';
         region->region[0] = (char) ((seek_region - 1000)/26 + 65);
         region->region[1] = (char) ((seek_region - 1000)%26 + 65);
      }
      else
      {
         ::memcpy_dup(region->country_code, GeoIP_country_code[seek_region], 2);
      }
   }
   else if (gi->databaseType == (char) GEOIP_REGION_EDITION_REV1)
   {
      /* Region Edition, post June 2003 */
      seek_region -= STATE_BEGIN_REV1;
      if (seek_region < US_OFFSET)
      {
         /* Unknown */
         /* we don't need to do anything here b/ca we __memset region to 0 */
      }
      else if (seek_region < CANADA_OFFSET)
      {
         /* USA State */
         region->country_code[0] = 'U';
         region->country_code[1] = 'S';
         region->region[0] = (char) ((seek_region - US_OFFSET)/26 + 65);
         region->region[1] = (char) ((seek_region - US_OFFSET)%26 + 65);
      }
      else if (seek_region < WORLD_OFFSET)
      {
         /* Canada Province */
         region->country_code[0] = 'C';
         region->country_code[1] = 'A';
         region->region[0] = (char) ((seek_region - CANADA_OFFSET)/26 + 65);
         region->region[1] = (char) ((seek_region - CANADA_OFFSET)%26 + 65);
      }
      else
      {
         /* Not US or Canada */
         ::memcpy_dup(region->country_code, GeoIP_country_code[(seek_region - WORLD_OFFSET) / FIPS_RANGE], 2);
      }
   }
}

static
GeoIPRegion * _get_region(GeoIP* gi, u32 ipnum)
{
   GeoIPRegion * region;

   region = (GeoIPRegion *) malloc(sizeof(GeoIPRegion));
   if (region)
   {
      GeoIP_assign_region_by_inetaddr(gi, htonl(ipnum), region);
   }
   return region;
}

static
GeoIPRegion * _get_region_v6(GeoIP* gi, geoipv6_t ipnum)
{
   GeoIPRegion * region;

   region = (GeoIPRegion *) malloc(sizeof(GeoIPRegion));
   if (region)
   {
      GeoIP_assign_region_by_inetaddr_v6(gi, ipnum, region);
   }
   return region;
}

GeoIPRegion * GeoIP_region_by_addr (GeoIP* gi, const char *addr)
{
   u32 ipnum;
   if (addr == nullptr)
   {
      return 0;
   }
   if (gi->databaseType != (char) GEOIP_REGION_EDITION_REV0 &&
         gi->databaseType != (char) GEOIP_REGION_EDITION_REV1)
   {
      debug_print("Invalid database type %s, expected %s\n", GeoIPDBDescription[(i32)gi->databaseType], GeoIPDBDescription[GEOIP_REGION_EDITION_REV1]);
      return 0;
   }
   ipnum = _GeoIP_addr_to_num(addr);
   return _get_region(gi, ipnum);
}

GeoIPRegion * GeoIP_region_by_addr_v6 (GeoIP* gi, const char *addr)
{
   geoipv6_t ipnum;
   if (addr == nullptr)
   {
      return 0;
   }
   if (gi->databaseType != (char) GEOIP_REGION_EDITION_REV0 &&
         gi->databaseType != (char) GEOIP_REGION_EDITION_REV1)
   {
      debug_print("Invalid database type %s, expected %s\n", GeoIPDBDescription[(i32)gi->databaseType], GeoIPDBDescription[GEOIP_REGION_EDITION_REV1]);
      return 0;
   }
   ipnum = _GeoIP_addr_to_num_v6(addr);
   return _get_region_v6(gi, ipnum);
}

GeoIPRegion * GeoIP_region_by_name (GeoIP* gi, const char *name)
{
   u32 ipnum;
   if (name == nullptr)
   {
      return 0;
   }
   if (gi->databaseType != (char) GEOIP_REGION_EDITION_REV0 &&
         gi->databaseType != (char) GEOIP_REGION_EDITION_REV1)
   {
      debug_print("Invalid database type %s, expected %s\n", GeoIPDBDescription[(i32)gi->databaseType], GeoIPDBDescription[GEOIP_REGION_EDITION_REV1]);
      return 0;
   }
   if (!(ipnum = _GeoIP_lookupaddress(name)))
      return 0;
   return _get_region(gi, ipnum);
}

GeoIPRegion * GeoIP_region_by_name_v6 (GeoIP* gi, const char *name)
{
   geoipv6_t ipnum;
   if (name == nullptr)
   {
      return 0;
   }
   if (gi->databaseType != (char) GEOIP_REGION_EDITION_REV0 &&
         gi->databaseType != (char) GEOIP_REGION_EDITION_REV1)
   {
      debug_print("Invalid database type %s, expected %s\n", GeoIPDBDescription[(i32)gi->databaseType], GeoIPDBDescription[GEOIP_REGION_EDITION_REV1]);
      return 0;
   }

   ipnum = _GeoIP_lookupaddress_v6(name);
   if (__GEOIP_V6_IS_NULL(ipnum))
      return 0;
   return _get_region_v6(gi, ipnum);
}

GeoIPRegion * GeoIP_region_by_ipnum (GeoIP* gi, u32 ipnum)
{
   if (gi->databaseType != (char) GEOIP_REGION_EDITION_REV0 &&
         gi->databaseType != (char) GEOIP_REGION_EDITION_REV1)
   {
      debug_print("Invalid database type %s, expected %s\n", GeoIPDBDescription[(i32)gi->databaseType], GeoIPDBDescription[GEOIP_REGION_EDITION_REV1]);
      return 0;
   }
   return _get_region(gi, ipnum);
}

GeoIPRegion * GeoIP_region_by_ipnum_v6 (GeoIP* gi, geoipv6_t ipnum)
{
   if (gi->databaseType != (char) GEOIP_REGION_EDITION_REV0 &&
         gi->databaseType != (char) GEOIP_REGION_EDITION_REV1)
   {
      debug_print("Invalid database type %s, expected %s\n", GeoIPDBDescription[(i32)gi->databaseType], GeoIPDBDescription[GEOIP_REGION_EDITION_REV1]);
      return 0;
   }
   return _get_region_v6(gi, ipnum);
}

void GeoIPRegion_delete (GeoIPRegion *gir)
{
   free(gir);
}

/* GeoIP Organization, ISP and AS Number Edition private method */
static
char *_get_name (GeoIP* gi, u32 ipnum)
{
   i32 seek_org;
   char buf[MAX_ORG_RECORD_LENGTH];
   char * org_buf, * buf_pointer;
   i32 record_pointer;
   size_t len;
   size_t silence;

   if (gi->databaseType != (char) GEOIP_ORG_EDITION &&
         gi->databaseType != (char) GEOIP_ISP_EDITION &&
         gi->databaseType != (char) GEOIP_ASNUM_EDITION)
   {
      debug_print("Invalid database type %s, expected %s\n", GeoIPDBDescription[(i32)gi->databaseType], GeoIPDBDescription[GEOIP_ORG_EDITION]);
      return nullptr;
   }

   seek_org = _GeoIP_seek_record(gi, ipnum);
   if(natural(seek_org) == gi->databaseSegments[0])
      return nullptr;

   record_pointer = seek_org + (2 * gi->record_length - 1) * gi->databaseSegments[0];

   if (gi->cache == nullptr)
   {
      fseek(gi->GeoIPDataaxis, record_pointer, SEEK_SET);
      silence = fread(buf, sizeof(char), MAX_ORG_RECORD_LENGTH, gi->GeoIPDataaxis);
      len = sizeof(char) * (strlen(buf)+1);
      org_buf = (char *) malloc(len);
      ansi_count_copy(org_buf, buf, len);
   }
   else
   {
      buf_pointer = (char *)(gi->cache + (long)record_pointer);
      len = sizeof(char) * (strlen(buf_pointer)+1);
      org_buf = (char *) malloc(len);
      ansi_count_copy(org_buf, buf_pointer, len);
   }
   return org_buf;
}

char *_get_name_v6 (GeoIP* gi, geoipv6_t ipnum)
{
   i32 seek_org;
   char buf[MAX_ORG_RECORD_LENGTH];
   char * org_buf, * buf_pointer;
   i32 record_pointer;
   size_t len;
   size_t silence;

   if (gi->databaseType != (char) GEOIP_ORG_EDITION &&
         gi->databaseType != (char) GEOIP_ISP_EDITION &&
         gi->databaseType != (char) GEOIP_ASNUM_EDITION)
   {
      debug_print("Invalid database type %s, expected %s\n", GeoIPDBDescription[(i32)gi->databaseType], GeoIPDBDescription[GEOIP_ORG_EDITION]);
      return nullptr;
   }

   seek_org = _GeoIP_seek_record_v6(gi, ipnum);
   if(natural(seek_org) == gi->databaseSegments[0])
      return nullptr;

   record_pointer = seek_org + (2 * gi->record_length - 1) * gi->databaseSegments[0];

   if (gi->cache == nullptr)
   {
      fseek(gi->GeoIPDataaxis, record_pointer, SEEK_SET);
      silence = fread(buf, sizeof(char), MAX_ORG_RECORD_LENGTH, gi->GeoIPDataaxis);
      len = sizeof(char) * (strlen(buf)+1);
      org_buf = (char *) malloc(len);
      ansi_count_copy(org_buf, buf, len);
   }
   else
   {
      buf_pointer = (char *)(gi->cache + (long)record_pointer);
      len = sizeof(char) * (strlen(buf_pointer)+1);
      org_buf =(char *) malloc(len);
      ansi_count_copy(org_buf, buf_pointer, len);
   }
   return org_buf;
}

char *_GeoIP_num_to_addr (GeoIP* gi, u32 ipnum)
{
   UNREFERENCED_PARAMETER(gi);
   char *ret_str;
   char *cur_str;
   i32 octet[4];
   i32 num_chars_written, i;

   ret_str = (char *) malloc(sizeof(char) * 16);
   cur_str = ret_str;

   for (i = 0; i<4; i++)
   {
      octet[3 - i] = ipnum % 256;
      ipnum >>= 8;
   }

   for (i = 0; i<4; i++)
   {
      num_chars_written = sprintf(cur_str, "%d", octet[i]);
      cur_str += num_chars_written;

      if (i < 3)
      {
         cur_str[0] = '.';
         cur_str++;
      }
   }

   return ret_str;
}

char **GeoIP_range_by_ip (GeoIP* gi, const char *addr)
{
   u32 ipnum;
   u32 left_seek;
   u32 right_seek;
   u32 mask;
   i32 orig_netmask;
   i32 target_value;
   char **ret;

   if (addr == nullptr)
   {
      return 0;
   }

   ret = (char **) malloc(sizeof(char *) * 2);

   ipnum = _GeoIP_addr_to_num(addr);
   target_value = _GeoIP_seek_record(gi, ipnum);
   orig_netmask = GeoIP_last_netmask(gi);
   mask = 0xffffffff << ( 32 - orig_netmask );
   left_seek = ipnum & mask;
   right_seek = left_seek + ( 0xffffffff & ~mask );

   while (left_seek != 0
          && natural(target_value) == _GeoIP_seek_record(gi, left_seek - 1) )
   {

      /* Go to beginning of netblock defined by netmask */
      mask = 0xffffffff << ( 32 - GeoIP_last_netmask(gi) );
      left_seek = ( left_seek - 1 ) & mask;
   }
   ret[0] = _GeoIP_num_to_addr(gi, left_seek);

   while (right_seek != 0xffffffff
          && natural(target_value) == _GeoIP_seek_record(gi, right_seek + 1) )
   {

      /* Go to end of netblock defined by netmask */
      mask = 0xffffffff << ( 32 - GeoIP_last_netmask(gi) );
      right_seek = ( right_seek + 1 ) & mask;
      right_seek += 0xffffffff & ~mask;
   }
   ret[1] = _GeoIP_num_to_addr(gi, right_seek);

   gi->netmask = orig_netmask;

   return ret;
}

void GeoIP_range_by_ip_delete( char ** ptr )
{
   if ( ptr )
   {
      if ( ptr[0] )
         free(ptr[0]);
      if ( ptr[1] )
         free(ptr[1]);
      free(ptr);
   }
}

char *GeoIP_name_by_ipnum (GeoIP* gi, u32 ipnum)
{
   return _get_name(gi,ipnum);
}

char *GeoIP_name_by_ipnum_v6 (GeoIP* gi, geoipv6_t ipnum)
{
   return _get_name_v6(gi,ipnum);
}

char *GeoIP_name_by_addr (GeoIP* gi, const char *addr)
{
   u32 ipnum;
   if (addr == nullptr)
   {
      return 0;
   }
   ipnum = _GeoIP_addr_to_num(addr);
   return _get_name(gi, ipnum);
}

char *GeoIP_name_by_addr_v6 (GeoIP* gi, const char *addr)
{
   geoipv6_t ipnum;
   if (addr == nullptr)
   {
      return 0;
   }
   ipnum = _GeoIP_addr_to_num_v6(addr);
   return _get_name_v6(gi, ipnum);
}

char *GeoIP_name_by_name (GeoIP* gi, const char *name)
{
   u32 ipnum;
   if (name == nullptr)
   {
      return 0;
   }
   if (!(ipnum = _GeoIP_lookupaddress(name)))
      return 0;
   return _get_name(gi, ipnum);
}

char *GeoIP_name_by_name_v6 (GeoIP* gi, const char *name)
{
   geoipv6_t ipnum;
   if (name == nullptr)
   {
      return 0;
   }
   ipnum = _GeoIP_lookupaddress_v6(name);
   if (__GEOIP_V6_IS_NULL(ipnum))
      return 0;
   return _get_name_v6(gi, ipnum);
}

char *GeoIP_org_by_ipnum (GeoIP* gi, u32 ipnum)
{
   return GeoIP_name_by_ipnum(gi, ipnum);
}

char *GeoIP_org_by_ipnum_v6 (GeoIP* gi, geoipv6_t ipnum)
{
   return GeoIP_name_by_ipnum_v6(gi, ipnum);
}

char *GeoIP_org_by_addr (GeoIP* gi, const char *addr)
{
   return GeoIP_name_by_addr(gi, addr);
}

char *GeoIP_org_by_addr_v6 (GeoIP* gi, const char *addr)
{
   return GeoIP_name_by_addr_v6(gi, addr);
}

char *GeoIP_org_by_name (GeoIP* gi, const char *name)
{
   return GeoIP_name_by_name(gi, name);
}

char *GeoIP_org_by_name_v6 (GeoIP* gi, const char *name)
{
   return GeoIP_name_by_name_v6(gi, name);
}

uchar GeoIP_database_edition (GeoIP* gi)
{
   return gi->databaseType;
}

i32 GeoIP_charset( GeoIP* gi)
{
   return gi->charset;
}

i32 GeoIP_set_charset(  GeoIP* gi, i32 charset )
{
   i32 old_charset = gi->charset;
   gi->charset = charset;
   return old_charset;
}

i32 GeoIP_last_netmask (GeoIP* gi)
{
   return gi->netmask;
}


/** return two letter country code */
const char* GeoIP_code_by_id(i32 id)
{
   if (id < 0 || id >= (i32) num_GeoIP_countries)
      return nullptr;

   return GeoIP_country_code[id];
}

/** return three letter country code */
const char* GeoIP_code3_by_id(i32 id)
{
   if (id < 0 || id >= (i32) num_GeoIP_countries)
      return nullptr;

   return GeoIP_country_code3[id];
}


/** return full name of country */
const char* GeoIP_name_by_id(i32 id)
{
   if (id < 0 || id >= (i32) num_GeoIP_countries)
      return nullptr;

   return GeoIP_country_name[id];
}

/** return continent of country */
const char* GeoIP_continent_by_id(i32 id)
{
   if (id < 0 || id >= (i32) num_GeoIP_countries)
      return nullptr;

   return GeoIP_country_continent[id];
}

/** return id by country code **/
i32 GeoIP_id_by_code(const char *country)
{
   u32 i;

   for ( i = 0; i < num_GeoIP_countries; ++i)
   {
      if (strcmp(country, GeoIP_country_code[i]) == 0)
         return i;
   }

   return 0;
}

u32 GeoIP_num_countries()
{
   return num_GeoIP_countries;
}
