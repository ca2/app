// Created by camilo:hi5! on 2024-05-07 10:47 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "quantum.h"



quantum::~quantum()
{



}


void quantum::call_request(::request* prequest)
{

   request(prequest);

}


void quantum::request(::request * prequest)
{

   on_request(prequest);

}


void quantum::on_request(::request * prequest)
{


}



