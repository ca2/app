// Added get_time_zone memberby camilo on 2021-12-02 14:23 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "apex/platform/api.h"
#include "apex/platform/api_client.h"


class CLASS_DECL_AXIS string_timeout
{
public:


   string               m_str;
   ::earth::time     m_duration; /// time when this network_payload was last updated


   bool is_valid(const ::duration& durationTimeOut) const
   {

      return m_duration.elapsed() < durationTimeOut;

   }


};


inline void __exchange(::stream& stream, class ::string_timeout& t)
{

   __TYPE_EXCHANGE(str);
   __TYPE_EXCHANGE(duration);

}


namespace geo
{


   class CLASS_DECL_AXIS department :
      virtual public ::acme::department,
      virtual public ::api_client
   {
   public:



      //bool                                          m_bInitialCountryTimeZoneInit;
      bool                                            m_bInitialLocalityTimeZoneInit;

      ::mutex                                         m_mutexOpenweatherCity;
      
      ::mutex                                                           m_mutexCityTimeZone;
      iptr_map < ::datetime::department::time_zone >                    m_cityTimeZone;
      bool                                                              m_bLoadedCityTimeZoneFromFile;
      ::file::path                                                      m_pathCityTimeZoneFile;
      task_pointer                                                      m_ptaskSaveCityTimeZone;
      bool                                                              m_bCityTimeZoneModified;



      ::mutex                                                           m_mutexLocalityTimeZone;
      double_map < double_map < ::datetime::department::time_zone > >   m_localityTimeZone;
      bool                                                              m_bLoadedLocalityTimeZoneFromFile;
      ::file::path                                                      m_pathLocalityTimeZoneFile;
      task_pointer                                                      m_ptaskSaveLocalityTimeZone;
      bool                                                              m_bLocalityTimeZoneModified;


      ::mutex                                                           m_mutexCityWeather;
      index_map < string_timeout >                                      m_cityWeather;
      bool                                                              m_bLoadedCityWeatherFromFile;
      ::file::path                                                      m_pathCityWeatherFile;
      task_pointer                                                      m_ptaskSaveCityWeather;
      bool                                                              m_bCityWeatherModified;


      //string_map < time_zone >      m_countryTimeZone;

      string_array                                       m_straCityLo;
      string_array                                       m_straCity;
      i64_array                                          m_iaIds;
      double_array                                       m_daLon;
      double_array                                       m_daLat;

      string_map < __pointer(openweather_city) >         m_mapCity;


      department();
      ~department() override;


      void initialize(::object* pobject) override;


      virtual void defer_check_openweather_city_list();

      ::mutex * get_openweather_city_mutex() { return &m_mutexOpenweatherCity; }

      virtual openweather_city* openweather_find_city(string strQuery);
      virtual index openweather_find_city2(string strQuery, string& strCit, i64& iId, double& dLat, double& dLon);
      virtual index openweather_find_city2(string strQ1, string strQ2, string& strCit, i64& iId, double& dLat, double& dLon, bool bPrefix);



      virtual bool locality_sunset(openweather_city* pcity, int& iRise, int& iSet);
      virtual string initial_locality_time_zone(openweather_city* pcity, double& dZone);
      virtual bool locality_sunset(string strCountry, string strLocality, int& iRise, int& iSet);
      virtual string initial_locality_time_zone(string strCountry, string strLocality, double& dZone);
      virtual string initial_country_time_zone(string strCountry);
      virtual string utc_offset_string(double dUTCOffset);
      virtual double time_zone(string str, string strCountryCode);


      virtual ::datetime::department::time_zone get_time_zone(openweather_city* pcity);

      virtual ::datetime::department::time_zone _get_time_zone(openweather_city* pcity);

      virtual ::datetime::department::time_zone get_time_zone(double dLat, double dLng);

      virtual ::datetime::department::time_zone _get_time_zone(double dLat, double dLng);

      virtual string get_weather(openweather_city* pcity);

      virtual string _get_weather(openweather_city* pcity);

      virtual void set_city_time_zone_modified();

      virtual void set_locality_time_zone_modified();

      virtual void set_city_weather_modified();

      virtual void save_city_time_zone();

      virtual void save_locality_time_zone();

      virtual void save_city_weather();

   };


   CLASS_DECL_AXIS bool utc_offset_invalid(double dUTCOffset);


} // namespace geo




