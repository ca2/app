// Added get_time_zone memberby camilo on 2021-12-02 14:23 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/collection/int_map.h"
#include "acme/prototype/collection/string_map.h"
#include "apex/platform/api.h"
#include "apex/platform/api_client.h"
#include "acme/prototype/datetime/time_zone.h"
#include "acme/platform/department.h"


class CLASS_DECL_AXIS string_timeout
{
public:


   string               m_str;
   ::earth::time     m_time; /// time when this network_payload was last updated


   bool is_valid(const class ::time& timeTimeOut) const
   {

      return m_time.elapsed() < timeTimeOut;

   }


};


namespace geo
{


   class CLASS_DECL_AXIS geo :
      virtual public ::acme::department,
      virtual public ::api_client
   {
   public:



      //bool                                                            m_bInitialCountryTimeZoneInit;
      bool                                                  m_bInitialLocalityTimeZoneInit;

      ::pointer < ::mutex >                                               m_pmutexOpenweatherCity;

      ::pointer < ::mutex >                                               m_pmutexCityTimeZone;
      index_map < ::datetime::time_zone >                   m_cityTimeZone;
      bool                                                  m_bLoadedCityTimeZoneFromFile;
      ::file::path                                          m_pathCityTimeZoneFile;
      task_pointer                                          m_ptaskSaveCityTimeZone;
      bool                                                  m_bCityTimeZoneModified;



      ::pointer < ::mutex >                                               m_pmutexLocalityTimeZone;
      double_map < double_map < ::datetime::time_zone > >   m_localityTimeZone;
      bool                                                  m_bLoadedLocalityTimeZoneFromFile;
      ::file::path                                          m_pathLocalityTimeZoneFile;
      task_pointer                                          m_ptaskSaveLocalityTimeZone;
      bool                                                  m_bLocalityTimeZoneModified;


      ::pointer < ::mutex >                                               m_pmutexCityWeather;
      index_map < string_timeout >                          m_cityWeather;
      bool                                                  m_bLoadedCityWeatherFromFile;
      ::file::path                                          m_pathCityWeatherFile;
      task_pointer                                          m_ptaskSaveCityWeather;
      bool                                                  m_bCityWeatherModified;


      //string_map < time_zone >      m_countryTimeZone;

      string_array                                       m_straCityLo;
      string_array                                       m_straCity;
      huge_integer_array                                          m_iaIds;
      double_array                                       m_daLon;
      double_array                                       m_daLat;

      string_map < openweather_city* >                  m_mapCity;


      geo();
      ~geo() override;


      void initialize(::particle* pparticle) override;


      virtual void defer_check_openweather_city_list();

      ::pointer< ::mutex > get_openweather_city_mutex() { return m_pmutexOpenweatherCity; }

      virtual openweather_city* openweather_find_city(string strQuery);
      virtual ::collection::index openweather_find_city2(string strQuery, string& strCit, huge_integer& iId, double& dLat, double& dLon);
      virtual ::collection::index openweather_find_city2(string strQ1, string strQ2, string& strCit, huge_integer& iId, double& dLat, double& dLon, bool bPrefix);



      virtual bool locality_sunset(openweather_city* pcity, int& iRise, int& iSet);
      virtual string initial_locality_time_zone(openweather_city* pcity, double& dZone);
      virtual bool locality_sunset(string strCountry, string strLocality, int& iRise, int& iSet);
      virtual string initial_locality_time_zone(string strCountry, string strLocality, double& dZone);
      virtual string initial_country_time_zone(string strCountry);
      virtual string utc_offset_string(double dUTCOffset);
      virtual double time_zone(string str, string strCountryCode);


      virtual ::datetime::time_zone get_time_zone(openweather_city* pcity);

      virtual ::datetime::time_zone _get_time_zone(openweather_city* pcity);

      virtual ::datetime::time_zone get_time_zone(double dLat, double dLng);

      virtual ::datetime::time_zone _get_time_zone(double dLat, double dLng);

      virtual ::payload get_weather(openweather_city* pcity);

      virtual ::payload _get_weather(openweather_city* pcity);

      virtual void set_city_time_zone_modified();

      virtual void set_locality_time_zone_modified();

      virtual void set_city_weather_modified();

      virtual void save_city_time_zone();

      virtual void save_locality_time_zone();

      virtual void save_city_weather();

   };


   CLASS_DECL_AXIS bool utc_offset_invalid(double dUTCOffset);


} // namespace geo




