// Created by camilo on 2022-05-30 05:21 <3ThomasbBorregaardSorensen!! ThomasLIkesNumber5 (05-30)
#pragma once


int WINAPI acme_win_main(::platform::application* papp, HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, CHAR* pCmdLine, int nCmdShow);


int WINAPI WinMain(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, CHAR* pCmdLine, int nCmdShow)
{

	auto papp = __allocate APPLICATION::application();

	return ::acme::win_main(papp, hinstanceThis, hinstancePrev, pCmdLine, nCmdShow);

}



