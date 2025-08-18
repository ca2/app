// Added get_time_zone memberby camilo on 2021-12-02 14:23 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "system.h"
#include "_binary_stream.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/http.h"
#include "acme/platform/keep.h"
#include "acme/prototype/datetime/_binary_stream.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/prototype/datetime/earth_zone_time.h"
#include "acme/prototype/collection/_array_binary_stream.h"
#include "acme/prototype/collection/_map_binary_stream.h"
#include "acme/prototype/datetime/_binary_stream.h"
#include "acme/prototype/mathematics/number_double.h"
#include "acme/filesystem/file/binary_stream.h"
#include "acme/prototype/string/international.h"
#include "acme/prototype/string/str.h"
#include "acme/nano/nano.h"
#include "acme/user/micro/user.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/networking/open_weather_city.h"
#include "apex/networking/http/context.h"
#include "axis/platform/application.h"


#define STRESS_DEBUGGING 1


#include <unac.h>


namespace geo
{


   geo::geo()
   {


      m_bOpenWeatherCityListLock = false;

      m_bInitialLocalityTimeZoneInit = false;

      m_bLoadedCityTimeZoneFromFile = false;
      m_bLoadedLocalityTimeZoneFromFile = false;

      m_bCityTimeZoneModified = false; 
      m_bLocalityTimeZoneModified = false;

      m_strImplementation = "ca2";
//      m_strBrowserAccount = "weather";
      //m_strApiClientConfig = "camilothomas";

   }


   geo::~geo()
   {


   }


   void geo::initialize(::particle * pparticle)
   {

      ::acme::department::initialize(pparticle);

      m_pathCityTimeZoneFile = directory_system()->userconfig() / "datetime_departament_cityTimeZone.bin";

      m_pathLocalityTimeZoneFile = directory_system()->userconfig() / "datetime_departament_LocalityTimeZone.bin";

   }
   
#define DEBUGF_LINE(...)
#define DEBUGF_OUT(...)


   void geo::defer_check_openweather_city_list()
   {

      _synchronous_lock synchronouslock(get_openweather_city_mutex());

      if (m_bOpenWeatherCityListLock)
      {

         return;

      }

      __keep_true(m_bOpenWeatherCityListLock);

      if (m_straCityLo.get_size() == m_straCity.get_size()
         && m_straCity.get_size() == m_iaIds.get_size()
         && m_iaIds.get_size() == m_daLon.get_size()
         && m_daLon.get_size() == m_daLat.get_size()
         && m_straCity.get_size() > 1)
      {

         return;

      }

      DEBUGF_LINE("abcxxx1");

      ::file::path pathFolder = directory_system()->userconfig();

      bool bOk = false;

      auto pcontext = m_papplication->m_papplication;

      auto pfile = file();

      ::file::path pathWeatherBin;

      pathWeatherBin = pathFolder / "weather.bin";

      {

         try
         {

            DEBUGF_LINE("abcxxx2 Going to open file : \"%s\".", pathWeatherBin.c_str());

            auto memory = pfile->as_memory(pathWeatherBin);

            DEBUGF_LINE("abcxxx3");

            auto pfile = øallocate memory_file(memory);

            DEBUGF_LINE("abcxxx4");

            binary_stream stream(pfile);

            DEBUGF_LINE("abcxxx5");

            stream >> m_straCity;
            DEBUGF_LINE("abcxxx5.1 m_straCity.size() == %d", m_straCity.size());
            stream >> m_straCityLo;
            DEBUGF_LINE("abcxxx5.2 m_straCityLo.size() == %d", m_straCityLo.size());
            stream >> m_iaIds;
            DEBUGF_LINE("abcxxx5.3 m_iaIds == %d", m_iaIds.size());
            stream >> m_daLon;
            DEBUGF_LINE("abcxxx5.4 m_daLon == %d", m_daLon.size());
            stream >> m_daLat;
            DEBUGF_LINE("abcxxx5.5 m_daLat == %d", m_daLat.size());


            //file()->to_array(m_straCity,          auto psystem = system();

   //         auto pdirectorysystem = psystem->m_pdirectorysystem;
   //
   //pdirectorysystem->system() / "weather-cit.bin");
            //file()->to_array(m_straCityLo,          auto psystem = system();

   //         auto pdirectorysystem = psystem->m_pdirectorysystem;
   //
   //pdirectorysystem->system() / "weather-cil.bin");
            //file()->to_array(m_iaIds,          auto psystem = system();

   //         auto pdirectorysystem = psystem->m_pdirectorysystem;
   //
   //pdirectorysystem->system() / "weather-ids.bin");
            //file()->to_array(m_daLon,          auto psystem = system();

   //         auto pdirectorysystem = psystem->m_pdirectorysystem;
   //
   //pdirectorysystem->system() / "weather-lon.bin");
            //file()->to_array(m_daLat,          auto psystem = system();

   //         auto pdirectorysystem = psystem->m_pdirectorysystem;
   //
   //pdirectorysystem->system() / "weather-lat.bin");


            bOk = m_straCityLo.get_size() == m_straCity.get_size()
               && m_straCity.get_size() == m_iaIds.get_size()
               && m_iaIds.get_size() == m_daLon.get_size()
               && m_daLon.get_size() == m_daLat.get_size()
               && m_straCity.get_size() > 1;

            if (bOk && m_straCity.size() > 20)
            {

               for (int i = 0; i < 20; i++)
               {

                  informationf("dump: %s, %s, %d, %f, %f\n", m_straCity[i].c_str(), m_straCityLo[i].c_str(), m_iaIds[i], m_daLon[i], m_daLat[i]);

               }

            }

         }
         catch (...)
         {

            DEBUGF_LINE("defxxa1");

         }

      }

      if (!bOk)
      {

         try
         {

            DEBUGF_LINE("ghixxb1");

            if (pfile->exists(pathWeatherBin))
            {

               DEBUGF_LINE("ghixxb2");

               pfile->erase(pathWeatherBin);

               DEBUGF_LINE("ghixxb3");

            }

         }
         catch (const ::exception & exception)
         {

            DEBUGF_LINE("jklxxc1");

            auto pmessagebox = __initialize_new ::message_box(exception, "geo::defer_check_openweather_city_list");

            DEBUGF_LINE("jklxxc3");

            pmessagebox->async();

         }
         catch (...)
         {

            DEBUGF_LINE("jklxxc3");

            ::exception exception(error_catch_all_exception);

            DEBUGF_LINE("jklxxc4");

            auto pmessagebox = __initialize_new ::message_box(exception, "geo::defer_check_openweather_city_list");

            DEBUGF_LINE("jklxxc5");

            pmessagebox->async();

         }

         m_straCityLo.erase_all();
         m_straCity.erase_all();
         m_iaIds.erase_all();
         m_daLon.erase_all();
         m_daLat.erase_all();

      }

      if (m_straCityLo.get_size() == m_straCity.get_size()
         && m_straCity.get_size() == m_iaIds.get_size()
         && m_iaIds.get_size() == m_daLon.get_size()
         && m_daLon.get_size() == m_daLat.get_size()
         && m_straCity.get_size() > 1)
      {
      }
      else
      {

         try
         {

            DEBUGF_LINE("mnoxxd1");

            string str;

            ::payload payload;

            payload["nocache"] = true;
            payload["url"] = "https://ca2.network/city-list_base.json";

            DEBUGF_LINE("mnoxxd2");

            str = pfile->as_string(payload);

            DEBUGF_LINE("mnoxxd3");

            if (str.has_character())
            {

               DEBUGF_LINE("mnoxxd4");

               string_array_base stra;

               stra.add_lines(str);

               DEBUGF_LINE("mnoxxd5");

               int iLine = 1;

               for (auto strJson : stra)
               {

                  strJson.trim();

                  if (strJson.is_empty())
                  {

                     DEBUGF_LINE("mnoxxd6 Line %09d Empty!!");

                     iLine++;

                     continue;

                  }

                  const_char_pointer pszJson = strJson;

                  DEBUGF_OUT("mnoxxd6 Line %09d %s", iLine, pszJson);

                  iLine++;

                  //const_char_pointer pszJson = "{\"_id\":6322752, \"name\" : \"Curitiba\", \"country\" : \"BR\", \"coord\" : {\"lon\":-49.290821, \"lat\" : -25.50395}}";

                  ::payload v;

                  v.parse_network_payload(pszJson);

                  DEBUGF_OUT(" A");

                  string strLine = v["name"] + ", " + v["country"];

                  DEBUGF_OUT("B");

                  m_straCity.add(strLine);

                  DEBUGF_OUT("C");

                  m_straCityLo.add(strLine.lowered());

                  DEBUGF_OUT("D");

                  long long iId;

                  iId = v["_id"].as_long_long();

                  DEBUGF_OUT("E");

                  m_iaIds.add(iId);

                  DEBUGF_OUT("F");

                  double dLon = v["coord"]["lon"].as_double();

                  DEBUGF_OUT("G");

                  m_daLon.add(dLon);

                  DEBUGF_OUT("H");

                  double dLat = v["coord"]["lat"].as_double();

                  DEBUGF_OUT("I");

                  m_daLat.add(dLat);

                  DEBUGF_OUT("J\n");

               }

               auto pfileOut = pfile->get_writer(pathWeatherBin);

               binary_stream stream(pfileOut);

               stream << m_straCity;
               stream << m_straCityLo;
               stream << m_iaIds;
               stream << m_daLon;
               stream << m_daLat;

            }

         }
         catch (const ::exception & exception)
         {

            DEBUGF_LINE("pqrxxe1 exception type : " + ::type(exception).name());

            auto pmessagebox = __initialize_new ::message_box(exception, "geo::defer_check_openweather_city_list");

            DEBUGF_LINE("pqrxxe2");

            pmessagebox->async();

         }
         catch (...)
         {

            DEBUGF_LINE("pqrxxe3");

            auto pmessagebox = __initialize_new::message_box("Unable to download \"https://ca2.network/city-list_base.json\"");

            DEBUGF_LINE("pqrxxe4");

            pmessagebox->async();

         }

      }

   }


   openweather_city* geo::openweather_find_city(const ::scoped_string & scopedstrQuery)
   {

      auto& pcity = m_mapCity[scopedstrQuery];

      if (!pcity)
      {

         auto pcityNew = __raw_new openweather_city();

         pcityNew->m_iIndex = openweather_find_city2(
            scopedstrQuery,
            pcityNew->m_strCit,
            pcityNew->m_iId,
            pcityNew->m_dLat,
            pcityNew->m_dLon);

         if (pcityNew->m_iIndex < 0)
         {

            delete pcityNew;

            return nullptr;

         }

         pcity = pcityNew;

      }

      return pcity;

   }


   ::collection::index geo::openweather_find_city2(const ::scoped_string & scopedstrQuery, string& strCit, long long& iId, double& dLat, double& dLon)
   {

      string_array_base stra;

      stra.explode(",", scopedstrQuery);

      stra.trim();

      stra.erase_empty();

      if (stra.get_count() <= 0)
      {

         return -1;

      }

      if (stra.get_count() == 1)
      {

         return openweather_find_city2(scopedstrQuery, "", strCit, iId, dLat, dLon, true);

      }


      for (::collection::index iCount = stra.get_count() - 1; iCount >= 1; iCount--)
      {

         ::collection::index iIndex = openweather_find_city2(stra.slice(0, iCount).implode(", "), stra.last(), strCit, iId, dLat, dLon, false);

         if (iIndex >= 0)
         {

            return iIndex;

         }

      }

      for (::collection::index iCount = stra.get_count() - 1; iCount >= 1; iCount--)
      {

         ::collection::index iIndex = openweather_find_city2(stra.slice(0, iCount).implode(", "), stra.last(), strCit, iId, dLat, dLon, true);

         if (iIndex >= 0)
         {

            return iIndex;

         }

      }

      return -1;

   }



   ::collection::index geo::openweather_find_city2(const ::scoped_string & scopedstrQ1, const ::scoped_string & scopedstrQ2, string& strCit, long long& iId, double& dLat, double& dLon, bool bPrefix)
   {

      string strQueryLo;

      string strTry;

      string strTry1;

      string strTry2;

      ::string strQ1(scopedstrQ1);

      ::string strQ2(scopedstrQ2);

      ::collection::index iFind;

      defer_check_openweather_city_list();

      if (strQ1.case_insensitive_order("Cologne") == 0 && strQ2.case_insensitive_order("DE") == 0)
      {

         strQ1 = "Koeln";

      }
      else if (strQ1.case_insensitive_order("Washington DC") == 0)
      {

         strQ1 = "Washington, D. C.";

      }

      strQueryLo = strQ1 + ", " + strQ2;

      strQueryLo.make_lower();

      if (bPrefix)
      {

         iFind = m_straCityLo.find_first_begins(strQueryLo);

      }
      else
      {

         iFind = m_straCityLo.find_first(strQueryLo);

      }

      if (found(iFind))
      {

         goto found;

      }









      strTry = strQueryLo;

      strTry.replace_with("", "'");

      if (bPrefix)
      {

         iFind = m_straCityLo.find_first_begins(strTry);

      }
      else
      {

         iFind = m_straCityLo.find_first(strTry);

      }

      if (::found(iFind))
      {

         goto found;

      }

































      strTry = strQueryLo;

      strTry.replace_with("saint", "st.");

      {

         char * out = nullptr;
         size_t out_length = 0;

         auto in = strTry.begin();

         auto in_length = strTry.size();

         int iError = unac_string("UTF-8", in, in_length, &out, &out_length);

         if (iError != 0)
         {

            warning() << "unac_string returned error : " << iError;
            //throw ::exception(error_wrong_state, "unac_string returned error");
            //throw_errno_exception();

         }

         strTry.assign(out, out_length);

         ::free(out);

      }

      if (bPrefix)
      {

         iFind = m_straCityLo.find_first_begins(strTry);

      }
      else
      {

         iFind = m_straCityLo.find_first(strTry);

      }

      if (::found(iFind))
      {

         goto found;

      }









      return -1;

   found:

      strCit = m_straCity[iFind];

      iId = m_iaIds[iFind];

      dLat = m_daLat[iFind];

      dLon = m_daLon[iFind];

      return iFind;

   }


   bool geo::locality_sunset(openweather_city* pcity, int& iRise, int& iSet)
   {

      if (pcity == nullptr)
      {

         return false;

      }

      const_char_pointer pszId =
#include "sensitive/openweather.txt"
         ;

      double dZone = 0.0;

      initial_locality_time_zone(pcity, dZone);

      int iTimeZone = (int)(dZone * 3600.0);

      ::property_set set;

      string strUrl = "http://api.openweathermap.org/data/2.5/weather?atom=" + ::as_string(pcity->m_iId) + "&APPID=" + string(pszId);

      auto psystem = system();

      string strGetUrl = "https://ca2.network/api/account/openweather?request=" + ::url::encode(strUrl);

      // auto pcontext = get_context();

      string str = http()->get(strGetUrl, set);

      _synchronous_lock synchronouslock(this->synchronization());

      const_char_pointer pszJson = str;

      ::payload v;

      v.parse_network_payload(pszJson);

      ::earth::zone_time timeSunrise({ posix_time_t{}, v["sys"]["sunrise"].as_long_long() }, iTimeZone);

      ::earth::zone_time timeSunset({ posix_time_t{}, v["sys"]["sunset"].as_long_long() }, iTimeZone);

      iRise = (int)timeSunrise.GetZoneTimeOfDay().m_iSecond;

      iSet = (int)timeSunset.GetZoneTimeOfDay().m_iSecond;

      string strSunrise(timeSunrise.FormatZone(INTERNATIONAL_DATE_TIME_FORMAT));

      string strSunset(timeSunset.FormatZone(INTERNATIONAL_DATE_TIME_FORMAT));

      information("sunrise:" + strSunrise + "\n");

      information("sunset:" + strSunset + "\n");

      return true;

   }


   bool  geo::locality_sunset(const ::scoped_string & scopedstrCountry, const ::scoped_string & scopedstrLocality, int& iRise, int& iSet)
   {

      auto psystem = system();

      auto pcity = psystem->geo()->openweather_find_city(scopedstrLocality + ", " + scopedstrCountry);

      if (pcity == nullptr)
      {

         return false;

      }

      return locality_sunset(pcity, iRise, iSet);


   }


   string geo::initial_locality_time_zone(openweather_city* pcity, double& dZone)
   {

      ::datetime::time_zone timezone;

      timezone = get_time_zone(pcity);

      dZone = timezone.m_dZone;

      return timezone.m_strZone;

   }


   string  geo::initial_locality_time_zone(const ::scoped_string & scopedstrCountry, const ::scoped_string & scopedstrLocality, double& dZone)
   {

      string str;

      if (scopedstrLocality.is_empty())
      {

         str = initial_country_time_zone(scopedstrCountry);

         dZone = time_zone(str, scopedstrCountry);

         return str;

      }

      string strQ;

      strQ = scopedstrLocality;

      if (scopedstrCountry.has_character())
      {

         strQ += ", ";

         strQ += scopedstrCountry;

      }


      //  long long iId;

//      double dLat;

      //    double dLon;

      auto psystem = system();

      auto pcity = psystem->geo()->openweather_find_city(strQ);

      return initial_locality_time_zone(pcity, dZone);

      //      if (pcity != nullptr)
      //      {
      //
      //
      //
      //         ::property_set set;
      //
      //         string strLat = as_string(pcity->m_dLat);
      //
      //         string strLng = as_string(pcity->m_dLon);
      //
      //         string strKey;
      //
      //#ifdef WINDOWS
      //
      //         strKey = file_system()->as_string("C:\\sensitive\\sensitive\\seed\\timezonedb.txt");
      //
      //#else
      //
      //         strKey = file_system()->as_string("/sensitive/sensitive/seed/timezonedb.txt");
      //
      //#endif
      //
      //         str = papp->http_get("http://api.timezonedb.com/?key=" + strKey + "&format=network_payload&lat=" + strLat + "&lng=" + strLng, set);
      //
      //         if (str.has_character())
      //         {
      //
      //            const_char_pointer pszJson = str;
      //
      //            ::payload v;
      //
      //            try
      //            {
      //
      //               v.parse_network_payload(scopedstrJson);
      //
      //               str = v["abbreviation"].get_string().lowered();
      //
      //               dZone = v["gmtoffset"].get_double() / 3600.0;
      //
      //            }
      //            catch (...)
      //            {
      //
      //               str = "utc";
      //
      //               dZone = 0.0;
      //
      //            }
      //
      //         }
      //         else
      //         {
      //
      //            str = "utc";
      //
      //            dZone = 0.0;
      //
      //         }
      //
      //      }
      //      else
      //      {
      //
      //         str = "utc";
      //
      //         dZone = 0.0;
      //
      //      }
      //
      //
      //      timezone.m_strZone = str;
      //
      //      timezone.m_dZone = dZone;
      //
      //      timezone.m_time = now;
      //
      //      {
      //
      //         synchronous_lock synchronouslock(&m);
      //
      //         m_countryLocalityTimeZone[strCountry][strLocality] = timezone;
      //
      //         ::file::path path = directory_system()->public_system() / "datetime_departament_m_countryLocalityTimeZone.bin";
      //
      //         auto & file = file()->friendly_get_file(path, ::file::e_open_binary | ::file::e_open_write | ::file::e_open_create | ::file::e_open_defer_create_directory);
      //
      //         stream os(file);
      //
      //         ::file::map_base::write(os, m_countryLocalityTimeZone);
      //
      //      }
      //
      //      return str;

   }

   // remark: initial does mean "official default" is certainly a rough guess
   string  geo::initial_country_time_zone(const ::scoped_string & scopedstrCountry)
   {

      if (scopedstrCountry == "br")
      {

         return "brt";

      }
      else if (scopedstrCountry == "ua")
      {

         return "eest";

      }
      else if (scopedstrCountry == "us")
      {

         return "pdt";

      }
      else if (scopedstrCountry == "jp")
      {

         return "jst";

      }
      else if (scopedstrCountry == "de")
      {

         return "cest";

      }
      else if (scopedstrCountry == "fr")
      {

         return "cest";

      }
      else if (scopedstrCountry == "int_point")
      {

         return "west";

      }
      else if (scopedstrCountry == "es")
      {

         return "cest";

      }
      else if (scopedstrCountry == "it")
      {

         return "cest";

      }
      else if (scopedstrCountry == "ar")
      {

         return "art";

      }
      else if (scopedstrCountry == "cl")
      {

         return "clst";

      }
      else if (scopedstrCountry == "uk")
      {

         return "bst";

      }
      else if (scopedstrCountry == "nl")
      {

         return "cest";

      }
      else if (scopedstrCountry == "cn")
      {

         return "cst";

      }
      else if (scopedstrCountry == "tw")
      {

         return "cst";

      }
      else if (scopedstrCountry == "ru")
      {

         return "msk";

      }
      else if (scopedstrCountry == "pl")
      {

         return "cest";

      }
      else if (scopedstrCountry == "am")
      {

         return "amt";

      }
      else if (scopedstrCountry == "dk")
      {

         return "cest";

      }
      else if (scopedstrCountry == "se")
      {

         return "cest";

      }
      else if (scopedstrCountry == "fi")
      {

         return "eest";

      }
      else if (scopedstrCountry == "ua")
      {

         return "eest";

      }
      else if (scopedstrCountry == "no")
      {

         return "cest";

      }
      else if (scopedstrCountry == "no")
      {

         return "cest";

      }
      else if (scopedstrCountry == "be")
      {

         return "cest";

      }
      else if (scopedstrCountry == "at")
      {

         return "cest";

      }
      else if (scopedstrCountry == "lu")
      {

         return "cest";

      }
      else if (scopedstrCountry == "li")
      {

         return "cest";

      }
      else if (scopedstrCountry == "ch")
      {

         return "cest";

      }
      else if (scopedstrCountry == "au")
      {

         return "aest";

      }
      else if (scopedstrCountry == "nz")
      {

         return "nzst";

      }
      else if (scopedstrCountry == "kr")
      {

         return "kst";

      }
      else if (scopedstrCountry == "ph")
      {

         return "pht";

      }
      else if (scopedstrCountry == "my")
      {

         return "myt";

      }
      else if (scopedstrCountry == "hk")
      {

         return "hkt";

      }
      else if (scopedstrCountry == "vn")
      {

         return "ict";

      }
      else if (scopedstrCountry == "in")
      {

         return "ist";

      }
      else if (scopedstrCountry == "ca")
      {

         return "adt";

      }
      else if (scopedstrCountry == "bg")
      {

         return "eet";

      }
      else
      {

         return "utc";

      }

   }



   string geo::utc_offset_string(double dUTCOffset)
   {

      if (dUTCOffset == 1000000.0)
      {

         return "";

      }
      else if (dUTCOffset == 0.0)
      {

         return "UTC";

      }
      else if (utc_offset_invalid(dUTCOffset))
      {

         return "(" + ::str::signed_double(dUTCOffset) + " : invalid UTC?)";

      }
      else
      {

         string strUTCOffset;

         strUTCOffset = "UTC " + ::str::signed_int((int)dUTCOffset);

         double dMod = fmod(fabs(dUTCOffset), 1.0);

         if (dMod > 0.0)
         {

            string strMinutes;

            strMinutes.formatf("%02d", (int)(60.0 * dMod));

            strUTCOffset += ":" + strMinutes;

         }

         return strUTCOffset;

      }

   }


   double geo::time_zone(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrCountryCode)
   {

      ::string str(scopedstr);
      str.make_lower();
      ::string strCountryCode(scopedstrCountryCode);
      strCountryCode.make_lower();
      double dTimeZoneOffset = 0.0;
      //"Moscow Time"(TranslateFromRussian) (UTC+3)
      if (str == "msk")
      {

         dTimeZoneOffset = 3.0;

      }
      else if (str == "brt")
      {

         dTimeZoneOffset = -3.0;

      }
      else if (str == "cet")
      {

         dTimeZoneOffset = 1.0;

      }
      else if (str == "cest")
      {

         dTimeZoneOffset = 2.0;

      }
      else if (str == "eet")
      {

         dTimeZoneOffset = 2.0;

      }
      else if (str == "eest")
      {

         dTimeZoneOffset = 3.0;

      }
      else if (str == "pdt")
      {

         dTimeZoneOffset = -7.0;

      }
      else if (str == "est")
      {

         dTimeZoneOffset = -5.0;

      }
      else if (str == "edt")
      {

         dTimeZoneOffset = -4.0;

      }
      else if (str == "mst")
      {

         dTimeZoneOffset = -7.0;

      }
      else if (str == "mdt")
      {

         dTimeZoneOffset = -6.0;

      }
      else if (str == "jst")
      {

         dTimeZoneOffset = 9.0;

      }
      else if (str == "west")
      {

         dTimeZoneOffset = 1.0;

      }
      else if (str == "art")
      {

         dTimeZoneOffset = -3.0;

      }
      else if (str == "clst")
      {

         dTimeZoneOffset = -3.0;

      }
      else if (str == "bst")
      {

         dTimeZoneOffset = 1.0;

      }
      else if (str == "cdt")
      {

         dTimeZoneOffset = -5.0;

      }
      else if (str == "cst")
      {

         if (strCountryCode == "cn")
         {

            dTimeZoneOffset = 8.0;

         }
         else
         {

            dTimeZoneOffset = -6.0;

         }

      }
      else if (str == "amt")
      {

         dTimeZoneOffset = 4.0;

      }
      else if (str == "aest")
      {

         dTimeZoneOffset = 10.0;

      }
      else if (str == "nzst")
      {

         dTimeZoneOffset = 12.0;

      }
      else if (str == "kst")
      {

         dTimeZoneOffset = 9.0;

      }
      else if (str == "pht")
      {

         dTimeZoneOffset = 8.0;

      }
      else if (str == "myt")
      {

         dTimeZoneOffset = 8.0;

      }
      else if (str == "hkt")
      {

         dTimeZoneOffset = 8.0;

      }
      else if (str == "ict")
      {

         dTimeZoneOffset = 7.0;

      }
      else if (str == "utc")
      {

         dTimeZoneOffset = 0.0;

      }
      else if (str == "alphatime")
      {

         dTimeZoneOffset = -2.0;

      }
      else if (str == "ist")
      {

         dTimeZoneOffset = 5.5;

      }
      else if (str == "adt")
      {

         dTimeZoneOffset = -3.0;

      }
      else if (str == "brst")
      {

         dTimeZoneOffset = -2.0;

      }
      else if (::mathematics::convert_to_double(dTimeZoneOffset, str))
      {

      }
      else if (strCountryCode == "br")
      {

         dTimeZoneOffset = -3.0;

      }
      else if (!::mathematics::convert_to_double(dTimeZoneOffset, strCountryCode))
      {

         informationf("(2) ERROR !! Missing timezone offset information for \"%s\" - \"%s\"", str.c_str(), strCountryCode.c_str());

      }

      return dTimeZoneOffset;

   }

  

   bool utc_offset_invalid(double dUTCOffset)
   {

      return dUTCOffset < -12.0 || dUTCOffset > 14.0;  // don't know (is invalid?)

   }


   ::datetime::time_zone geo::get_time_zone(openweather_city* pcity)
   {

      if (::is_null(pcity))
      {

         return {};

      }

      auto iOpenweatherCity = pcity->m_iId;

      if (iOpenweatherCity < 0)
      {

         return {};

      }

      if (!m_bLoadedCityTimeZoneFromFile)
      {

         m_bLoadedCityTimeZoneFromFile = true;

         ::file::path path = m_pathCityTimeZoneFile;

         try
         {

            auto pfile = file()->get_reader(path);

            if (pfile.ok())
            {

               binary_stream reader(pfile);

               _synchronous_lock synchronouslock(m_pmutexCityTimeZone);

               reader >> m_cityTimeZone;

            }

         }
         catch (...)
         {

         }

      }

      try
      {

         _synchronous_lock synchronouslock(m_pmutexCityTimeZone);

         auto& timezone = m_cityTimeZone[iOpenweatherCity];

#if STRESS_DEBUGGING
         if (timezone.is_valid(10_s))
#else
         if (timezone.is_valid(1_day))
#endif
         {

            return timezone;

         }

         synchronouslock.unlock();

         timezone = _get_time_zone(pcity);

         if (timezone.m_strZone.has_character())
         {

            set_locality_time_zone_modified();

         }

         return timezone;

      }
      catch (...)
      {

      }

      return {};

   }


   ::datetime::time_zone geo::_get_time_zone(openweather_city* pcity)
   {

      return get_time_zone(pcity->m_dLat, pcity->m_dLon);

   }


   ::datetime::time_zone geo::get_time_zone(double dLat, double dLng)
   {

      if (!m_bLoadedLocalityTimeZoneFromFile)
      {

         m_bLoadedLocalityTimeZoneFromFile = true;

         ::file::path path = m_pathLocalityTimeZoneFile;

         try
         {

            auto pfile = file()->get_reader(path);

            if (pfile.ok())
            {

               binary_stream reader(pfile);

               _synchronous_lock synchronouslock(m_pmutexLocalityTimeZone);

               reader >> m_localityTimeZone;

            }

         }
         catch (...)
         {

         }

      }

      dLat = ceil(dLat * 100.0) / 100.0;

      dLng = ceil(dLng * 100.0) / 100.0;

      try
      {

         _synchronous_lock synchronouslock(m_pmutexCityTimeZone);

         auto& timezone = m_localityTimeZone[dLat][dLng];

#if STRESS_DEBUGGING
         if (timezone.is_valid(10_s))
#else
         if (timezone.is_valid(1_day))
#endif
         {

            return timezone;

         }

         synchronouslock.unlock();

         timezone = _get_time_zone(dLat, dLng);

         if (timezone.m_strZone.has_character())
         {

            set_locality_time_zone_modified();

         }

         timezone.m_time.Now();

         return timezone;

      }
      catch (...)
      {

      }

      return {};

   }


   ::datetime::time_zone geo::_get_time_zone(double dLat, double dLng)
   {

      ::datetime::time_zone timezone;

      ::property_set set;

      string strLat;

      strLat.formatf("%0.2f", dLat);

      string strLng;

      strLng.formatf("%0.2f", dLng);

      string strUrl = "https://ca2.network/account/time_zone";

      try
      {

         ::property_set set;

         set["post"]["lat"] = strLat;

         set["post"]["lng"] = strLng;

         //auto estatus = 

         auto payload = api_get(strUrl, set);

         //if (!estatus)
         //{

         //   return timezone;

         //}

         timezone.m_strZone = payload["zone_name"];

         timezone.m_dZone = payload["zone_offset"].as_double();

      }
      catch (...)
      {

      }

      return timezone;

   }


   ::payload geo::get_weather(openweather_city* pcity)
   {

      if (!m_bLoadedCityWeatherFromFile)
      {

         m_bLoadedCityWeatherFromFile = true;

         ::file::path path = m_pathCityWeatherFile;

         try
         {

            auto file = ::particle::file()->get_reader(path);

            binary_stream reader(file);

            _synchronous_lock synchronouslock(m_pmutexCityWeather);

            reader >> m_cityWeather;

         }
         catch (...)
         {

         }

      }

      if (::is_null(pcity))
      {

         return "";

      }

      if (pcity->m_iId < 0)
      {

         return "";

      }

      try
      {

         _synchronous_lock synchronouslock(m_pmutexCityTimeZone);

         auto& stringtimeout = m_cityWeather[pcity->m_iId];

#if STRESS_DEBUGGING
         if (stringtimeout.is_valid(10_s))
#else
         if (stringtimeout.is_valid(1_minute))
#endif
         {

            return stringtimeout.m_str;

         }

         synchronouslock.unlock();

         stringtimeout.m_str = _get_weather(pcity);

         if (stringtimeout.m_str.has_character())
         {

            set_city_weather_modified();

         }

         stringtimeout.m_time.Now();

         return stringtimeout.m_str;

      }
      catch (...)
      {

      }

      return {};

   }


   ::payload geo::_get_weather(openweather_city * pcity)
   {

      ::property_set set;

      string strId = ::as_string(pcity->m_iId);

      string strUrl = "http://ca2.network/account/weather";

      try
      {

         //string strNetworkPayload;

         ::property_set set;

         set["city_id"] = strId;

         //auto estatus = 
         
         auto payload = api_get(strUrl, set);

  /*       if (!estatus)
         {

            return strNetworkPayload;

         }*/

         return payload;

      }
      catch (...)
      {

      }

      return "";

   }


   void geo::set_city_time_zone_modified()
   {

      m_bCityTimeZoneModified = true;

      if (!m_ptaskSaveCityTimeZone)
      {

         m_ptaskSaveCityTimeZone = fork([this]()
            {

               try
               {

                  while (m_ptaskSaveCityTimeZone->task_get_run())
                  {

                     preempt(1_s);

                     if (m_bCityTimeZoneModified)
                     {

                        try
                        {

                           save_city_time_zone();

                           m_bCityTimeZoneModified = false;

                        }
                        catch (...)
                        {

                        }

                     }

                  }

               }
               catch (...)
               {

               }

               m_ptaskSaveCityTimeZone.release();

            });

      }

   }


   void geo::set_locality_time_zone_modified()
   {

      m_bLocalityTimeZoneModified = true;

      if (!m_ptaskSaveLocalityTimeZone)
      {

         m_ptaskSaveLocalityTimeZone = m_papplication->fork([this]()
            {

               try
               {

                  while(!m_ptaskSaveLocalityTimeZone)
                  {

                     preempt(1_s);

                  }

                  while (m_ptaskSaveLocalityTimeZone->task_get_run())
                  {

                     task_sleep(1_s);

                     if (m_bLocalityTimeZoneModified)
                     {

                        try
                        {

                           save_locality_time_zone();

                           m_bLocalityTimeZoneModified = false;

                        }
                        catch (...)
                        {

                        }

                     }

                  }

               }
               catch (...)
               {

               }

               m_ptaskSaveLocalityTimeZone.release();

            });

      }

   }


   void geo::set_city_weather_modified()
   {

      m_bCityWeatherModified = true;

      if (!m_ptaskSaveCityWeather)
      {

         m_ptaskSaveCityWeather = fork([this]()
            {

               try
               {

                  while (m_ptaskSaveCityWeather->task_get_run())
                  {

                     preempt(1_s);

                     if (m_bCityWeatherModified)
                     {

                        try
                        {

                           save_city_weather();

                           m_bCityWeatherModified = false;

                        }
                        catch (...)
                        {

                        }

                     }

                  }

               }
               catch (...)
               {

               }

               m_ptaskSaveCityWeather.release();

            });

      }

   }


   void geo::save_city_time_zone()
   {
      
      ::file::path path = m_pathLocalityTimeZoneFile;

      try
      {

         auto pfile = file()->get_writer(path);

         if (pfile)
         {

            binary_stream writer(pfile);

            _synchronous_lock synchronouslock(m_pmutexCityTimeZone);

            writer << m_cityTimeZone;

         }

      }
      catch (...)
      {

      }

   }


   void geo::save_locality_time_zone()
   {

      ::file::path path = m_pathLocalityTimeZoneFile;

      try
      {

         auto pfile = file()->get_writer(path);

         if (pfile)
         {

            binary_stream writer(pfile);

            _synchronous_lock synchronouslock(m_pmutexLocalityTimeZone);

            writer << m_localityTimeZone;

         }

      }
      catch (...)
      {

      }

   }


   void geo::save_city_weather()
   {

      ::file::path path = m_pathCityWeatherFile;

      try
      {

         auto pfile = file()->get_writer(path);

         binary_stream writer(pfile);

         _synchronous_lock synchronouslock(m_pmutexCityWeather);

         writer << m_cityWeather;

      }
      catch (...)
      {

      }

   }


} // namespace geo



