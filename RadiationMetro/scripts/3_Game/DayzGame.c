class RadPlace
{
    string name;
    string radpos;
    float radius;

    void RadPlace(string nm, string rp, float rd)
    {
        name = nm;
        radpos = rp;
        radius = rd;
    }
}

class RadConfig
{
    ref array<string> GasMasks;
    ref array<string> Filters;
    ref array< ref RadPlace > RadLocations;
    int loglevel;

    void RadConfig()
    {
        GasMasks = new array<string>;
        Filters = new array<string>;
        RadLocations = new ref array< ref RadPlace >;
        loglevel=0;
    }

}

modded class DayZGame
{
    const static string Rad_Tagfolder = "RadiationMetro\\";
    const static string Rad_fileName = "RadiationMetro.json";
    const static string ProfileFolder = "$profile:\\";

    protected ref RadConfig RadConfig_Data;
    string m_radFilePath = ProfileFolder+Rad_Tagfolder+Rad_fileName;

    RadConfig ReadRadConfig()
    {
        if(RadConfig_Data){
            return RadConfig_Data;
        }
        return null;
    }

    void SaveRadConfig(ref RadConfig Rad_config)
    {
        RadConfig_Data = Rad_config;
    }
}

class RadiationConfig
{

    protected const static string m_ConfigRoot = "$profile:\\RadiationMetro\\";

    static void LoadConfig(string configName, out RadConfig configData)
    {
        string configPath = m_ConfigRoot + configName;

        if (!FileExist(configPath))
        {
            RADLogger.GetInstance().Log("'" + configName + "' does not exist, creating default config", RADLogger.LOGLEVEL_CRITICAL);
            CreateDefaultConfig(configData);
            SaveConfig(configName, configData);
            return;
        }

        JsonFileLoader<RadConfig>.JsonLoadFile(configPath, configData);
        RADLogger.GetInstance().Log("'" + configName + "' found, loading existing config", RADLogger.LOGLEVEL_CRITICAL);
    }

    protected static void SaveConfig(string configName, RadConfig configData)
    {
        string configPath = m_ConfigRoot + configName;

        if (!FileExist(m_ConfigRoot))
        {
            RADLogger.GetInstance().Log("'" + m_ConfigRoot + "' does not exist, creating directory", RADLogger.LOGLEVEL_CRITICAL);
            MakeDirectory(m_ConfigRoot);
        }

        JsonFileLoader<RadConfig>.JsonSaveFile(configPath, configData);
    }
	
	static void UpgradeConfig(string configName, out RadConfig configData)
    {
        string configPath = m_ConfigRoot + configName;

        if (!FileExist(configPath))
        {
            RADLogger.GetInstance().Log("'"  + configName + "' does not exist, creating default config", RADLogger.LOGLEVEL_CRITICAL);
            CreateDefaultConfig(configData);
            SaveConfig(configName, configData);
            return;
        }
		JsonFileLoader<RadConfig>.JsonLoadFile(configPath, configData);
		
		//upgrades...

		if(!configData.loglevel) configData.loglevel = 0;

		for ( int i=0; i < configData.RadLocations.Count(); i++)
		{
			
			if (!configData.RadLocations.Get(i).radius)
			{
				configData.RadLocations.Get(i).radius = 0;
			}

		}
			
        JsonFileLoader<RadConfig>.JsonSaveFile(configPath, configData);
    }

    protected static void CreateDefaultConfig(out RadConfig configData)
    {

        configData = new RadConfig();
        configData.RadLocations.Insert(new RadPlace("test", "0 0 0", 0));
		//hmm some limit ??
		//configData.BubakLocations.Insert( new BubakPlace("trigger1", "0-24", "1683 457 14219", "-1 -0.2 -1", "1 1 1" ,0, 0, 0,"" , 2, 1800, {"1683 457 14219", "1684 457 14218"}, 0, 4, 1, 1, {"ZmbM_ClerkFat_White", "ZmbM_SoldierNormal"} ));
		//configData.BubakLocations.Insert( new BubakPlace("trigger2", "23-6", "1530 0 8", "-1 -0.2 -1", "1 1 1" ,0, 0, 0, "", 2, 3600, {"1358 500 25", "0 0 0"}, 0, 20, 0, 0, {"ZmbM_ClerkFat_White", "ZmbM_SoldierNormal"} ));
	}
}

class RADLogger {
	
	static int LOGLEVEL_CRITICAL = 0;
	static int LOGLEVEL_DEBUG = 100;
	private int m_loglevel;

	static protected ref RADLogger s_Instance;

	void RADLogger()
	{
		s_Instance = this;
		m_loglevel = LOGLEVEL_CRITICAL;

 		RadConfig config = GetDayZGame().ReadRadConfig();
		if(config && config.loglevel) m_loglevel = config.loglevel;
	}

	static RADLogger GetInstance()
	{
		if(!s_Instance) new RADLogger();
		return s_Instance;
	}

	void Log(string txt, int loglevel = 100)
	{
		if(loglevel > m_loglevel) return;

		string file_path = "$profile:\\RadiationMetro\\RadiationMetro.log";
		FileHandle logFile = OpenFile(file_path, FileMode.APPEND);

		if (logFile != 0) {
				FPrintln(logFile, GetDate() + " [Radiation] " + txt);
				CloseFile(logFile);
		}
	}
	
	private string GetDate(bool fileFriendly = false) {
		int year, month, day, hour, minute, second;

		GetYearMonthDayUTC(year, month, day);
		GetHourMinuteSecondUTC(hour, minute, second);

		string date = year.ToStringLen(4) + "-" + month.ToStringLen(2) + "-" + day.ToStringLen(2) + "|"  + hour.ToStringLen(2) + ":" + minute.ToStringLen(2) + ":" + second.ToStringLen(2) + " ";
		if (fileFriendly) {
			date.Replace(" ", "_");
			date.Replace(".", "-");
			date.Replace(":", "-");
		}

		return date;
	}
}