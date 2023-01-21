class RadiationZone
{
    protected static ref RadiationZone Instance;

    static RadiationZone GetInstance()
	{
		if (!Instance)
        {
            Instance = new RadiationZone();
        }
		return Instance;
	}

    static void ClearInstance()
	{
		Instance = null;
	}


    void RadiationZone()
    {
        RadConfig config = GetDayZGame().ReadRadConfig();
        RadTrigger trigger;
        float radius;
        for(int i=0; i < config.RadLocations.Count(); i++)
        {
            string posrot = config.RadLocations.Get(i).radpos;
            TStringArray loc = new TStringArray;
            posrot.Split( "|", loc );
            string pos = loc.Get(0);
            string rot = loc.Get(1);
            if(!rot)
            {
                pos = config.RadLocations.Get(i).radpos;
                rot = "0 0 0";
            }
            RADLogger.GetInstance().Log("Created trigger " + config.RadLocations.Get(i).name + " at " + pos + " ori: " + rot, RADLogger.LOGLEVEL_CRITICAL);
            trigger = RadTrigger.Cast(GetGame().CreateObject("RadTrigger", pos.ToVector() ));
            trigger.SetOrientation(rot.ToVector());
            radius = config.RadLocations.Get(i).radius;
            if(radius)
            {
                trigger.SetCollisionSphere(radius);
            }
            trigger.SetTriggerName(config.RadLocations.Get(i).name);
        }
    }
}