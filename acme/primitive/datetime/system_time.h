#pragma once


#pragma pack(push, system_time, 1)


struct system_time_t
{


   unsigned short wYear;
   unsigned short wMonth;
   unsigned short wDayOfWeek;
   unsigned short wDay;
   unsigned short wHour;
   unsigned short wMinute;
   unsigned short wSecond;
   unsigned short wMilliseconds;


};


#pragma pack(pop, system_time)


class CLASS_DECL_ACME system_time :
   public system_time_t
{
public:

};


//
//
//Specifies a date and time, using individual members for the month, day, year, weekday, hour, minute, second, and ::duration.The time is either in coordinated universal time(UTC) or local time, depending on the function that is being called.
//
//Syntax
//C++
//
//Copy
//typedef struct _SYSTEMTIME {
//   WORD wYear;
//   WORD wMonth;
//   WORD wDayOfWeek;
//   WORD wDay;
//   WORD wHour;
//   WORD wMinute;
//   WORD wSecond;
//   WORD wMilliseconds;
//} SYSTEMTIME, * PSYSTEMTIME, * LPSYSTEMTIME;
//Members
//wYear
//
//The year.The valid values for this member are 1601 through 30827.
//
//wMonth
//
//The month.This member can be one of the following values.
//
//MEMBERS
//Value	Meaning
//1
//January
//2
//February
//3
//March
//4
//April
//5
//May
//6
//June
//7
//July
//8
//August
//9
//September
//10
//October
//11
//November
//12
//December
//wDayOfWeek
//
//The day of the week.This member can be one of the following values.
//
//TABLE 2
//Value	Meaning
//0
//Sunday
//1
//Monday
//2
//Tuesday
//3
//Wednesday
//4
//Thursday
//5
//Friday
//6
//Saturday
//wDay
//
//The day of the month.The valid values for this member are 1 through 31.
//
//wHour
//
//The hour.The valid values for this member are 0 through 23.
//
//wMinute
//
//The minute.The valid values for this member are 0 through 59.
//
//wSecond
//
//The second.The valid values for this member are 0 through 59.
//
//wMilliseconds
//
//The ::duration.The valid values for this member are 0 through 999.
//
//Remarks
//Note
//
//The SYSTEMTIME does not check to see if the date represented is a real and valid date.When working with this API, you should ensure its validity, especially in leap year scenarios.See leap day readiness for more information.
//
//It is not recommended that you add and subtract values from the SYSTEMTIME structure to obtain relative times.Instead, you should
//
//Convert the SYSTEMTIME structure to a FILETIME structure.
//Copy the resulting FILETIME structure to a ULARGE_INTEGER structure.
//Use normal 64 - bit arithmetic on the ULARGE_INTEGER value.
//The system can periodically refresh the time by synchronizing with a time source.Because the system time can be adjusted either forward or backward, do not compare system time readings to determine elapsed time.Instead, use one of the methods described in Windows Time.
