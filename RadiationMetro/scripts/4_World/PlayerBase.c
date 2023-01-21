modded class PlayerBase
{
    bool RadState = false;
    //RadConfig config = GetDayZGame().ReadRadConfig();
    const static string Rad_Tagfolder = "RadiationMetro\\";
    const static string Rad_fileName = "RadiationMetro.json";
    const static string ProfileFolder = "$profile:\\";
    string m_radFilePath = ProfileFolder+Rad_Tagfolder+Rad_fileName;
    ref array<string> GasMasks = new array<string>;
    ref array<string> Filters = new array<string>;

    //ref array<string> GasMasks = {"GP5GasMask","PMK_5A_Gas_Mask","GasMask", "AirborneMask", "XS_EQP_GASMASK_Slon", "XS_EQP_GASMASK_R5_P_filter_black", "XS_EQP_GASMASK_R5_P_filter_orange", "XS_EQP_GASMASK_R5_P_filter_black", "XS_EQP_GASMASK_R5_SH2_filter_orange", "XS_EQP_GASMASK_GP7_filter_black", "XS_EQP_GASMASK_GP7_filter_black_l2"};
    //ref array<string> Filters = {"JZ_GP5GasMask_Filter"};

    bool GetRadState()
    {
        return this.RadState;
    }

    void SetRadState(bool r)
    {
        this.RadState = r;
    }

    void SetGasmasks(array<string> mk)
    {
        this.GasMasks = mk;
    }

    array<string> GetGasMasks()
    {
        return this.GasMasks;
    }

    void SetFilters(array<string> ft)
    {
        this.Filters = ft;
    }

    array<string> GetFilters()
    {
        return this.Filters;
    }

    override void OnScheduledTick(float deltaTime)
    {
        super.OnScheduledTick(deltaTime);

		OnScheduledTickRAD(deltaTime);
    }

    void OnScheduledTickRAD(float deltaTime)
	{
        PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		if (!player)
			return;
		int currentTime = GetGame().GetTime() * 0.001;
		static int nTime = 0;
		if (currentTime >= nTime+3.5)  
		{
			player.RadSystem();
			nTime = currentTime;
		}
	}
    protected EffectSound 	m_GasSound;

    void RadSystem()
    {
        if(GetGame().IsClient())
        {
            PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
            if(GetRadState() == true)
            {
                bool inGasMask = false;
                int RadAttCount = player.GetInventory().AttachmentCount();
                for(int RadAttIndx = 0; RadAttIndx < RadAttCount; RadAttIndx++)
                {
                    EntityAI RadZoneAttach = player.GetInventory().GetAttachmentFromIndex(RadAttIndx);
                    if(RadZoneAttach.IsItemBase())
                    {
                        ItemBase RadZoneItem = ItemBase.Cast(RadZoneAttach);
                        string RadZoneClass = RadZoneItem.GetType();
                        if(GasMasks.Find(RadZoneClass) >= 0)
                        {
                            EntityAI FilterAtt = EntityAI.Cast(RadZoneItem);
                            int slotID = InventorySlots.GetSlotIdFromString("GasMaskFilter");
                            EntityAI filter = FilterAtt.GetInventory().FindAttachment(slotID);
                            string FilterType = filter.GetType();
                            if(Filters.Find(FilterType) >= 0)
                            {
                                int FilterQuant = filter.GetQuantity();
                                if(FilterQuant > 1)
                                {
                                    inGasMask = true;
                                    //GasMaskSound(player);
                                }
                            }
                        }
                    }
                }
                if(inGasMask == false)
                {
                    GetGame().RPCSingleParam(player, INRAD, null, true, player.GetIdentity());
                    HeartbeatSound(player);
                    GasSound(player);
                }
            }
            else if(GetRadState() == false)
            {

            }
        }
            
    }

    void RequestRadConfig(PlayerBase player)
    {

    }

    void SendRadConfigBack()
    {

    }

    string GetRadGasMask()
    {
        EntityAI itemClothing;
        itemClothing = FindAttachmentBySlotName( "Mask" );
        if(itemClothing)
        {
            ItemBase MaskG = ItemBase.Cast(itemClothing);
        }
        if(MaskG)
        {   
            return MaskG.GetType();
        }
        return "null";
    }

    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);

        PlayerBase player = GetPlayerByIdentity(sender);
		switch(rpc_type)
		{
			case INRAD:
				float playerShockRD = player.GetHealth("GlobalHealth", "Shock");
				if(playerShockRD > 25)
				{
					player.SetHealth("GlobalHealth", "Shock", playerShockRD - 20);

				}
				if(playerShockRD < 25)
				{
					float playerHealthRD = player.GetHealth("GlobalHealth", "Health");
					player.SetHealth("GlobalHealth", "Health", playerHealthRD - 15);
				}
			break;

			case INSIDE:
            Param2<array<string>,array<string>> masks;
            if(!ctx.Read(masks))
                return;
            ref array<string> gm = masks.param1;
            ref array<string> ft = masks.param2;
            SetGasmasks(gm);
            SetFilters(ft);
            SetRadState(true);
			break;
            case OUTSIDE:
            SetRadState(false);
            break;
		}
	}

    static PlayerBase GetPlayerByIdentity(PlayerIdentity sender)
   	{
        int highBits, lowBits;

        if (!GetGame().IsMultiplayer())
            return GetGame().GetPlayer();

        if (sender == null)
            return null;

        GetGame().GetPlayerNetworkIDByIdentityID(sender.GetPlayerId(), lowBits, highBits);
        return PlayerBase.Cast(GetGame().GetObjectByNetworkId(lowBits, highBits));
   	}


    void ChokeSound(PlayerBase player)
	{
		SEffectManager.PlaySoundOnObject("Choke_SoundSet", player, 0, 0, false);
	}

	void GasMaskSound(PlayerBase player)
	{
		SEffectManager.PlaySoundOnObject("GasMask1_SoundSet", player, 0, 0, false);
	}

	void HeartbeatSound(PlayerBase player)
	{
		SEffectManager.PlaySoundOnObject("Heartbeat_SoundSet", player, 0, 0, false);
	}

	void GasSound(PlayerBase player)
	{
		SEffectManager.PlaySoundOnObject("Gas1_SoundSet", player, 0, 0, false);
	}


}