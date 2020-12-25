#include "appdata.h"

AppData::AppData()
{

}


bool AppData::IsValid()
{
	if(!notes.IsValid())
	{
		return false;
	}

	return true;
}
