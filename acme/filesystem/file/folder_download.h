// Created by camilo on 2026-11-14 01:20 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
#pragma once


class folder_download :
   virtual public ::task
{
public:


   class item :
      virtual public ::particle
   {
   public:

      ::file::path         m_path;
      ::particle_array     m_particleaNotify;
      ::file_pointer       m_pfile;

   };

   ::pointer < folder > m_pfolder;

   ::pointer_array < item >    m_itema;
   //::pointer< ::parallelization::mutex >           m_pmutexBackgroundDownload;
   ::pointer< ::manual_reset_happening >           m_pmanualresethappening;


   folder_download();
   ~folder_download() override;

   void initialize(::particle* pparticle) override;
   void add_download_path(const ::file::path& path, const ::particle_array & particleaNotify);

   void run() override;

};




