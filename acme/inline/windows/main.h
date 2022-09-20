// Created by camilo on 2022-05-30 05:21 <3ThomasbBorregaardSorensen!! ThomasLIkesNumber5 (05-30)
#pragma once


i32 WINAPI acme_win_main(::acme::application* papp, HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, CHAR* pCmdLine, int nCmdShow);


i32 WINAPI WinMain(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, CHAR* pCmdLine, int nCmdShow)
{

	auto papp = __new(APPLICATION::application);

	return ::acme::win_main(papp, hinstanceThis, hinstancePrev, pCmdLine, nCmdShow);

}



