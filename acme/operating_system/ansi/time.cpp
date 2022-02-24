
void system_time_to_time(time_t * ptime, const system_time_t * psystemtime, i32 nDST)
{

   struct tm tm;

   system_time_to_tm(&tm, psystemtime);

   *ptime = timegm(&tm);

}
