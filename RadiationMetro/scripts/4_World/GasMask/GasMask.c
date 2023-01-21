modded class GP5GasMask
{
	static float 			m_WorkingTimePerPills = 20;
	protected bool 			m_CanStart;
	protected bool 			m_IsFilter;

	void GP5GasMask()
	{

	}

	void ~GP5GasMask()
	{

	}

    override bool CanPutAsAttachment( EntityAI parent )
	{
		if(!super.CanPutAsAttachment(parent)) {return false;}
		bool headgear_present = false;
		
		if ( parent.FindAttachmentBySlotName( "Headgear" ) )
		{
			headgear_present = parent.FindAttachmentBySlotName( "Headgear" ).ConfigGetBool( "noMask" );
		}
		
		if ( ( GetNumberOfItems() == 0 || !parent || parent.IsMan() ) && !headgear_present )
		{
			return true;
		}
		return false;
	}
	override void OnWasAttached(EntityAI parent, int slot_id)
	{
		super.OnWasAttached(parent,slot_id);

		PlayerBase player;
		Class.CastTo(player, parent.GetHierarchyRootPlayer());

		if ( player && slot_id == InventorySlots.MASK )
		{
			m_CanStart=true;

			EntityAI m_item = this.FindAttachmentBySlotName("GasMaskFilter");
			if( m_item )
			{
				CanStartGasMask(m_item, "GasMaskFilter");
			}
		}
	}

	override void OnWasDetached(EntityAI parent, int slot_id)
	{
		super.OnWasDetached(parent,slot_id);

		PlayerBase player = PlayerBase.Cast(parent);

		if ( player )
		{
			m_CanStart=false;
			GetCompEM().SwitchOff();
		}
	}



	override bool CanReceiveAttachment(EntityAI attachment, int slotId)
	{
		// ItemBase att = ItemBase.Cast(GetInventory().FindAttachment(slotId));
		// if (att && att.IsFullQuantity())
		// 	return false;

		// return true;
	}

	override bool CanReleaseAttachment (EntityAI attachment)
	{
		if( !super.CanReleaseAttachment( attachment ) )
			return false;
		return !GetCompEM().IsWorking();
	}

	override void EEItemAttached ( EntityAI item, string slot_name )
	{
		super.EEItemAttached( item, slot_name );
		CanStartGasMask(item,slot_name);
	}

	void CanStartGasMask(EntityAI item, string slot_name)
	{
		if ( GetGame().IsServer() )
		{
			ItemBase m_filter = ItemBase.Cast(item);
			// if(m_filter.GetQuantity() >= 1)
			// {
			// 	m_filter.AddQuantity(-1);
				GetCompEM().AddEnergy(m_WorkingTimePerPills);
				GetCompEM().SwitchOn();
			// }
		}
	}

	


	override void OnSwitchOn()
	{
		if ( !GetCompEM().HasEnoughStoredEnergy() ) GetCompEM().SwitchOff();
	}

	override void OnWork ( float consumed_energy )
	{
		if ( GetGame().IsServer() )
		{

			ConsumeFilter();

			PlayerBase player;
			Class.CastTo(player, GetHierarchyRootPlayer());

			if(player && !player.IsAlive())
			{

				GetCompEM().SwitchOff();
				return;
			}
		}
	}

	override void OnWorkStart()
	{

	}

	override void OnWorkStop()
	{

	}

	void ConsumeFilter()
	{
		JZ_GP5GasMask_Filter m_gasmaskfilter = GetGP5GasMaskFilter();

		if (m_gasmaskfilter)
		{
			if(m_gasmaskfilter.GetQuantity() == 0)
			{
				GetCompEM().AddEnergy(-1*GetCompEM().GetEnergy());
			}
			m_gasmaskfilter.AddQuantity(-1);
			GetCompEM().AddEnergy(m_WorkingTimePerPills);
		}
	}

	JZ_GP5GasMask_Filter GetGP5GasMaskFilter()
	{
		return JZ_GP5GasMask_Filter.Cast(GetAttachmentByType(JZ_GP5GasMask_Filter));
	}

};


modded class GasMask
{
	static float 			m_WorkingTimePerPills = 20;
	protected bool 			m_CanStart;
	protected bool 			m_IsFilter;

	void GasMask()
	{

	}

	void ~GasMask()
	{

	}

    override bool CanPutAsAttachment( EntityAI parent )
	{
		if(!super.CanPutAsAttachment(parent)) {return false;}
		bool headgear_present = false;
		
		if ( parent.FindAttachmentBySlotName( "Headgear" ) )
		{
			headgear_present = parent.FindAttachmentBySlotName( "Headgear" ).ConfigGetBool( "noMask" );
		}
		
		if ( ( GetNumberOfItems() == 0 || !parent || parent.IsMan() ) && !headgear_present )
		{
			return true;
		}
		return false;
	}
	override void OnWasAttached(EntityAI parent, int slot_id)
	{
		super.OnWasAttached(parent,slot_id);

		PlayerBase player;
		Class.CastTo(player, parent.GetHierarchyRootPlayer());

		if ( player && slot_id == InventorySlots.MASK )
		{
			m_CanStart=true;

			EntityAI m_item = this.FindAttachmentBySlotName("GasMaskFilter");
			if( m_item )
			{
				CanStartGasMask(m_item, "GasMaskFilter");
			}
		}
	}

	override void OnWasDetached(EntityAI parent, int slot_id)
	{
		super.OnWasDetached(parent,slot_id);

		PlayerBase player = PlayerBase.Cast(parent);

		if ( player )
		{
			m_CanStart=false;
			GetCompEM().SwitchOff();
		}
	}



	override bool CanReceiveAttachment(EntityAI attachment, int slotId)
	{
		// ItemBase att = ItemBase.Cast(GetInventory().FindAttachment(slotId));
		// if (att && att.IsFullQuantity())
		// 	return false;

		// return true;
	}

	override bool CanReleaseAttachment (EntityAI attachment)
	{
		if( !super.CanReleaseAttachment( attachment ) )
			return false;
		return !GetCompEM().IsWorking();
	}

	override void EEItemAttached ( EntityAI item, string slot_name )
	{
		super.EEItemAttached( item, slot_name );
		CanStartGasMask(item,slot_name);
	}

	void CanStartGasMask(EntityAI item, string slot_name)
	{
		if ( GetGame().IsServer() )
		{
			ItemBase m_filter = ItemBase.Cast(item);
			// if(m_filter.GetQuantity() >= 1)
			// {
			// 	m_filter.AddQuantity(-1);
				GetCompEM().AddEnergy(m_WorkingTimePerPills);
				GetCompEM().SwitchOn();
			// }
		}
	}


	override void OnSwitchOn()
	{
		if ( !GetCompEM().HasEnoughStoredEnergy() )
			GetCompEM().SwitchOff();
	}

	override void OnWork ( float consumed_energy )
	{
		if ( GetGame().IsServer() )
		{

			ConsumeFilter();

			PlayerBase player;
			Class.CastTo(player, GetHierarchyRootPlayer());

			if(player && !player.IsAlive())
			{

				GetCompEM().SwitchOff();
				return;
			}
		}
	}

	override void OnWorkStart()
	{

	}

	override void OnWorkStop()
	{

	}

	void ConsumeFilter()
	{
		JZ_GP5GasMask_Filter m_gasmaskfilter = GetGP5GasMaskFilter();

		if (m_gasmaskfilter)
		{
			if(m_gasmaskfilter.GetQuantity() == 0)
			{
				GetCompEM().AddEnergy(-1*GetCompEM().GetEnergy());
			}
			m_gasmaskfilter.AddQuantity(-1);
			GetCompEM().AddEnergy(m_WorkingTimePerPills);
		}
	}


	JZ_GP5GasMask_Filter GetGP5GasMaskFilter()
	{
		return JZ_GP5GasMask_Filter.Cast(GetAttachmentByType(JZ_GP5GasMask_Filter));
	}

};

modded class AirborneMask
{
	static float 			m_WorkingTimePerPills = 20;
	protected bool 			m_CanStart;
	protected bool 			m_IsFilter;

	void AirborneMask()
	{

	}

	void ~AirborneMask()
	{

	}

    override bool CanPutAsAttachment( EntityAI parent )
	{
		if(!super.CanPutAsAttachment(parent)) {return false;}
		bool headgear_present = false;
		
		if ( parent.FindAttachmentBySlotName( "Headgear" ) )
		{
			headgear_present = parent.FindAttachmentBySlotName( "Headgear" ).ConfigGetBool( "noMask" );
		}
		
		if ( ( GetNumberOfItems() == 0 || !parent || parent.IsMan() ) && !headgear_present )
		{
			return true;
		}
		return false;
	}
	
	override void OnWasAttached(EntityAI parent, int slot_id)
	{
		super.OnWasAttached(parent,slot_id);

		PlayerBase player;
		Class.CastTo(player, parent.GetHierarchyRootPlayer());

		if ( player && slot_id == InventorySlots.MASK )
		{
			m_CanStart=true;

			EntityAI m_item = this.FindAttachmentBySlotName("GasMaskFilter");
			if( m_item )
			{
				CanStartGasMask(m_item, "GasMaskFilter");
			}
		}
	}

	override void OnWasDetached(EntityAI parent, int slot_id)
	{
		super.OnWasDetached(parent,slot_id);

		PlayerBase player = PlayerBase.Cast(parent);

		if ( player )
		{
			m_CanStart=false;
			GetCompEM().SwitchOff();
		}
	}



	override bool CanReceiveAttachment(EntityAI attachment, int slotId)
	{
		// ItemBase att = ItemBase.Cast(GetInventory().FindAttachment(slotId));
		// if (att && att.IsFullQuantity())
		// 	return false;

		// return true;
	}

	override bool CanReleaseAttachment (EntityAI attachment)
	{
		if( !super.CanReleaseAttachment( attachment ) )
			return false;
		return !GetCompEM().IsWorking();
	}

	override void EEItemAttached ( EntityAI item, string slot_name )
	{
		super.EEItemAttached( item, slot_name );
		CanStartGasMask(item,slot_name);
	}

	void CanStartGasMask(EntityAI item, string slot_name)
	{
		if ( GetGame().IsServer() )
		{
			ItemBase m_filter = ItemBase.Cast(item);
			// if(m_filter.GetQuantity() >= 1)
			// {
			// 	m_filter.AddQuantity(-1);
				GetCompEM().AddEnergy(m_WorkingTimePerPills);
				GetCompEM().SwitchOn();
			// }
		}
	}


	override void OnSwitchOn()
	{
		if ( !GetCompEM().HasEnoughStoredEnergy() )
			GetCompEM().SwitchOff();
	}

	override void OnWork ( float consumed_energy )
	{
		if ( GetGame().IsServer() )
		{

			ConsumeFilter();

			PlayerBase player;
			Class.CastTo(player, GetHierarchyRootPlayer());

			if(player && !player.IsAlive())
			{

				GetCompEM().SwitchOff();
				return;
			}
		}
	}

	override void OnWorkStart()
	{

	}

	override void OnWorkStop()
	{

	}

	void ConsumeFilter()
	{
		JZ_GP5GasMask_Filter m_gasmaskfilter = GetGP5GasMaskFilter();

		if (m_gasmaskfilter)
		{
			if(m_gasmaskfilter.GetQuantity() == 0)
			{
				GetCompEM().AddEnergy(-1*GetCompEM().GetEnergy());
			}
			m_gasmaskfilter.AddQuantity(-1);
			GetCompEM().AddEnergy(m_WorkingTimePerPills);
		}
	}


	JZ_GP5GasMask_Filter GetGP5GasMaskFilter()
	{
		return JZ_GP5GasMask_Filter.Cast(GetAttachmentByType(JZ_GP5GasMask_Filter));
	}

};