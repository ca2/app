#pragma once



struct prop_variant :
	public PROPVARIANT
{

	prop_variant()
	{

		::PropVariantInit(this);

	}

	~prop_variant()
	{

		::PropVariantClear(this);

	}


};

