class JZ_GP5GasMask_Filter extends ItemBase
{
	private int				m_Efficiency0To10;
	static private float 	m_EfficiencyDecayStart = 0.1;
	
	void JZ_GP5GasMask_Filter()
	{
		m_Efficiency0To10 = 10;
		RegisterNetSyncVariableInt("m_Efficiency0To10");
	}

	float GetEfficiency0To1()
	{
		return m_Efficiency0To10 / 10;
	}
	
	float GetEfficiencyDecayStart()
	{
		return m_EfficiencyDecayStart;
	}

	override void OnEnergyConsumed()
	{
		super.OnEnergyConsumed();
		
		if ( GetGame().IsServer() )
		{
			float energy_coef = GetCompEM().GetEnergy0To1();
			
			if ( energy_coef < m_EfficiencyDecayStart  &&  m_EfficiencyDecayStart > 0 )
			{
				m_Efficiency0To10 = Math.Round(  (energy_coef / m_EfficiencyDecayStart) * 10  );
				SetSynchDirty();
			}
		}
	}

	override void OnWorkStart()
	{
		
	}
	
	override void OnWorkStop()
	{
		if ( GetGame().IsServer() )
		{
			if (GetCompEM().GetEnergy() > 0)
				return;
			
			SetHealth(0);
		}
	}

	override void OnInitEnergy()
	{

	}

	override void OnWork (float consumed_energy)
	{
		// float efficiency = GetEfficiency0To1();
			
		// 	if ( efficiency < 1 )
		// 	{

		// 	}
	}
	
	override void SetActions()
	{
		super.SetActions();

		// AddAction(ActionTurnOnWhileInHands);
		// AddAction(ActionMeasureBattery);
	}

}

modded class GasMask_Filter_Improvised extends ItemBase
{
	private int				m_Efficiency0To10;
	static private float 	m_EfficiencyDecayStart = 0.1;
	
	void JZ_GP5GasMask_Filter()
	{
		m_Efficiency0To10 = 10;
		RegisterNetSyncVariableInt("m_Efficiency0To10");
	}

	float GetEfficiency0To1()
	{
		return m_Efficiency0To10 / 10;
	}
	
	float GetEfficiencyDecayStart()
	{
		return m_EfficiencyDecayStart;
	}

	override void OnEnergyConsumed()
	{
		super.OnEnergyConsumed();
		
		if ( GetGame().IsServer() )
		{
			float energy_coef = GetCompEM().GetEnergy0To1();
			
			if ( energy_coef < m_EfficiencyDecayStart  &&  m_EfficiencyDecayStart > 0 )
			{
				m_Efficiency0To10 = Math.Round(  (energy_coef / m_EfficiencyDecayStart) * 10  );
				SetSynchDirty();
			}
		}
	}

	override void OnWorkStart()
	{
		
	}
	
	override void OnWorkStop()
	{
		if ( GetGame().IsServer() )
		{
			if (GetCompEM().GetEnergy() > 0)
				return;
			
			SetHealth(0);
		}
	}

	override void OnInitEnergy()
	{

	}

	override void OnWork (float consumed_energy)
	{
		// float efficiency = GetEfficiency0To1();
			
		// 	if ( efficiency < 1 )
		// 	{

		// 	}
	}
	
	override void SetActions()
	{
		super.SetActions();

		// AddAction(ActionTurnOnWhileInHands);
		// AddAction(ActionMeasureBattery);
	}
}
