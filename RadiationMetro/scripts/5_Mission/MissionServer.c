modded class MissionServer
{
	void MissionServer()
    {
		RadConfig config;
		FileAttr fileAttr;
		string fileName;
		TStringArray fajly;
		fajly = new TStringArray();
		FindFileHandle handle = FindFile("$profile:\\RadiationMetro\\RadiationMetro*.json", fileName, fileAttr, 0);
		fajly.Insert(fileName);
		//RADLogger.GetInstance().Log("Filename " + fileName, RADLogger.LOGLEVEL_CRITICAL);
		while ( FindNextFile(handle, fileName, fileAttr))
		{
			fajly.Insert(fileName);
			//RADLogger.GetInstance().Log("Filename " + fileName, RADLogger.LOGLEVEL_CRITICAL);
		}
		fileName = fajly.GetRandomElement();
		fileName = fajly.GetRandomElement();
		if (fajly.Count()>1)
		{
			RADLogger.GetInstance().Log("Selected Filename " + fileName, RADLogger.LOGLEVEL_CRITICAL);
		}
		else
		{
			fileName = "RadiationMetro.json";
		}
		RadiationConfig.UpgradeConfig(fileName, config);
        GetDayZGame().SaveRadConfig(config);

		if (GetGame().IsServer()) 
        {
			RadiationZone.ClearInstance();
			RadiationZone.GetInstance();
        }
		
    }
};
