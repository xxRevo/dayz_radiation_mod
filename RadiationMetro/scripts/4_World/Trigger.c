class RadTrigger extends Trigger
{
    protected string m_TriggerName;
    protected int m_TriggerDelay;
    protected int m_LastTriggerTime;

    const static string Rad_Tagfolder = "RadiationMetro\\";
    const static string Rad_fileName = "RadiationMetro.json";
    const static string ProfileFolder = "$profile:\\";
    string m_radFilePath = ProfileFolder+Rad_Tagfolder+Rad_fileName;

    RadConfig config = GetDayZGame().ReadRadConfig();


    void SetTriggerName(string name)
	{
		m_TriggerName = name;
	}

    string GetTriggerName()
	{
		return m_TriggerName;
	}

    void SetLastTriggerTime(int time)
	{
		m_LastTriggerTime = time;
	}

    void SetTriggerDelay(int delay)
	{
		m_TriggerDelay = delay;
	}

    void OnEnter(Object obj)
    {
		RADLogger.GetInstance().Log( "RADIATION ENTER" );

		if (obj.IsMan() && GetGame().IsServer())
		{
			// porovnat s ulozenym casem tiku, kdyz je vetsi nez cooldown ulozit novy a povolit akci
			//GetGame().CreateObject("Seachest", obj.GetPosition() );
			//GetGame().CreateObject("ZmbM_ClerkFat_White", obj.GetPosition(), false, true, true );
			RADLogger.GetInstance().Log( "Triggered " + GetTriggerName() + " time " + GetGame().GetTime()/1000);

            if (PlayerBase.Cast(obj) && PlayerBase.Cast(obj).GetIdentity())
            {
                if (PlayerBase.Cast(obj).GetIdentity().GetName())
                {	
                    if(GetGame().GetTime() - m_LastTriggerTime > 3500)
                    {
                        if(obj.IsAlive())
                        {
                            m_LastTriggerTime = GetGame().GetTime();
                            PlayerBase player = PlayerBase.Cast(obj);
                            ref array<string> masks = config.GasMasks;
                            ref array<string> filtr = config.Filters;
                            if(player)
                            {
                                GetGame().RPCSingleParam(player, INSIDE, new Param2<array<string>,array<string>>(masks,filtr), true, player.GetIdentity());
                            }
                            
                            Print("RADIATION TRIGGERED");
                        }
                        RADLogger.GetInstance().Log( PlayerBase.Cast(obj).GetIdentity().GetName() + " triggered " + GetTriggerName(), RADLogger.LOGLEVEL_CRITICAL);
                    }
                }
            }
			else
			{
				RADLogger.GetInstance().Log("Cannot trigger action it was called at " +  m_LastTriggerTime );
			}
		}
		
    }

     void OnLeave(Object obj)
    {    
        if (PlayerBase.Cast(obj) && PlayerBase.Cast(obj).GetIdentity())
            {
                if (PlayerBase.Cast(obj).GetIdentity().GetName())
                {	
                    if(obj.IsAlive())
                    {
                        PlayerBase player = PlayerBase.Cast(obj);
                        GetGame().RPCSingleParam(player, OUTSIDE, null, true, player.GetIdentity());
                    }
                }
            }
		RADLogger.GetInstance().Log( "RADIATION EXIT" );
    }
}