class CfgPatches {
	class RadiationMetro {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};

class CfgMods {
	class RadiationMetro {
		dir = "RadiationMetro";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "RadiationMetro";
		overview = "RadiationMetro";
		credits = "Juze";
		author = "Juze";
		authorID = "0";
		version = 0.8;
		extra = 0;
		type = "mod";
		dependencies[] = {"Game", "World"};
		
		class defs {
			class gameScriptModule {
				value = "";
				files[] = {"RadiationMetro/scripts/3_Game"};
			};
			
			class worldScriptModule {
				value = "";
				files[] = {"RadiationMetro/scripts/4_World"};
			};

			class missionScriptModule {
				value = "";
				files[] = {"RadiationMetro/scripts/5_Mission"};
			};
		};
	};
};

class CfgSoundShaders
{
	class Choke_SoundShader {
		samples[] = {{"RadiationMetro\data\gas_mask_death_gas.ogg", 1}};
		volume = 0.5;
		range = 10000;
	};
	class Heartbeat_SoundShader{
		samples[] = {{"RadiationMetro\data\Heart.ogg", 1}};
		volume = 0.1;
		range = 10000;
	};
	class GasMask1_SoundShader{
		samples[] = {{"RadiationMetro\data\GasMask_1.ogg", 1}};
		volume = 0.3;
		range = 10000;
	};
	class GasMask2_SoundShader{
		samples[] = {{"RadiationMetro\data\GasMask_2.ogg", 1}};
		volume = 0.3;
		range = 10000;
	};
	class GasMask3_SoundShader{
		samples[] = {{"RadiationMetro\data\GasMask_3.ogg", 1}};
		volume = 0.3;
		range = 10000;
	};
	class Gas1_SoundShader{
		samples[] = {{"RadiationMetro\data\1.ogg", 1}};
		volume = 0.3;
		range = 10000;
	};
	class Gas2_SoundShader{
		samples[] = {{"RadiationMetro\data\2.ogg", 1}};
		volume = 1;
		range = 10000;
	};
};

class CfgSoundSets
{
	class Choke_SoundSet
    {
        soundShaders[] = {"Choke_SoundShader"};
        //sound3DProcessingType = "infected3DProcessingType";
        //volumeCurve = "infectedAttenuationCurve";
        spatial = 1;
        doppler = 0;
		loop = 1;
    };
	class Heartbeat_SoundSet
    {
        soundShaders[] = {"Heartbeat_SoundShader"};
        sound3DProcessingType = "infected3DProcessingType";
        volumeCurve = "infectedAttenuationCurve";
        spatial = 1;
        doppler = 0;
		loop = 1;
    };
	class GasMask1_SoundSet
	{
		soundShaders[] = {"GasMask1_SoundShader"};
        sound3DProcessingType = "infected3DProcessingType";
        volumeCurve = "infectedAttenuationCurve";
        spatial = 1;
        doppler = 0;
		loop = 1;
	};
	class GasMask2_SoundSet
	{
		soundShaders[] = {"GasMask2_SoundShader"};
        sound3DProcessingType = "infected3DProcessingType";
        volumeCurve = "infectedAttenuationCurve";
        spatial = 1;
        doppler = 0;
		loop = 1;
	};
	class GasMask3_SoundSet
	{
		soundShaders[] = {"GasMask3_SoundShader"};
        //sound3DProcessingType = "infected3DProcessingType";
        //volumeCurve = "infectedAttenuationCurve";
        spatial = 1;
        doppler = 0;
		loop = 1;
	};
	class Gas1_SoundSet
	{
		soundShaders[] = {"Gas1_SoundShader"};
        //sound3DProcessingType = "infected3DProcessingType";
        //volumeCurve = "infectedAttenuationCurve";
        spatial = 1;
        doppler = 0;
		loop = 1;
	};
	class Gas2_SoundSet
	{
		soundShaders[] = {"Gas2_SoundShader"};
        //sound3DProcessingType = "infected3DProcessingType";
        //volumeCurve = "infectedAttenuationCurve";
        spatial = 1;
        doppler = 0;
		loop = 1;
	};

};

class CfgVehicles
{
	class Inventory_Base;
	class Clothing {};
	class GP5GasMask_Filter : Inventory_Base {};

	class GP5GasMask : Clothing
	{	
		attachments[] = {"GasMaskFilter"};
		displayName = "GP-5";
		noHelmet = 0;
		noEyewear = 1;
		

		class EnergyManager
		{
			autoSwitchOffWhenInCargo = 1;
			energyUsagePerSecond = 18;
			plugType = 1;
			attachmentAction = 1;
			updateInterval = 20;
			autoSwitchOff = 1;
			energyStorageMax = 50;
		};
		soundVoiceType = "gasmask";
		soundVoicePriority = 5;
	};

	class GasMask : Clothing 
	{
		attachments[] = {"GasMaskFilter"};
		displayName = "M10M";
		noHelmet = 0;
		noEyewear = 1;
		quantityBar = 0;
		varQuantityInit=0;
		varQuantityMin=0;
		varQuantityMax=0;

		class EnergyManager
		{
			autoSwitchOffWhenInCargo = 1;
			energyUsagePerSecond = 16;
			plugType = 1;
			attachmentAction = 1;
			updateInterval = 20;
			autoSwitchOff = 1;
			energyStorageMax = 50;
		};
		soundVoiceType = "gasmask";
		soundVoicePriority = 5;
	};
	class AirborneMask : Clothing 
	{
		attachments[] = {"GasMaskFilter"};
		displayName = "S10";
		noHelmet = 0;
		noEyewear = 1;

		class EnergyManager
		{
			autoSwitchOffWhenInCargo = 1;
			energyUsagePerSecond = 12;
			plugType = 1;
			attachmentAction = 1;
			updateInterval = 40;
			autoSwitchOff = 1;
			energyStorageMax = 50;
		};
		soundVoiceType = "gasmask";
		soundVoicePriority = 5;
	};

	class JZ_GP5GasMask_Filter : GP5GasMask_Filter
	{
		scope = 2;
		inventorySlot[] = {"GasMaskFilter"};
		stackedUnit = "w";
		quantityBar = 1;
		varQuantityInit = 3000;
		varQuantityMin = 1;
		varQuantityMax = 3000;
		varQuantityDestroyOnMin = 0; //1
		weight = 200;
		itemSize[] = {1, 1};

		class EnergyManager
		{
			switchOnAtSpawn = 1;
			isPassiveDevice = 1;
			energyStorageMax = 3000;
			energyAtSpawn = 3000;
			convertEnergyToQuantity = 1;
			reduceMaxEnergyByDamageCoef = 1;
			powerSocketsCount = 1;
			compatiblePlugTypes[] = {1};
		};
	};
	
	class GasMask_Filter_Improvised : GP5GasMask_Filter
	{
		scope = 2;
		inventorySlot[] = {"GasMaskFilter"};
		stackedUnit = "w";
		quantityBar = 1;
		varQuantityInit = 1500;
		varQuantityMin = 1;
		varQuantityMax = 1500;
		varQuantityDestroyOnMin = 0; //1
		weight = 200;
		itemSize[] = {1, 1};

		class EnergyManager
		{
			switchOnAtSpawn = 1;
			isPassiveDevice = 1;
			energyStorageMax = 1500;
			energyAtSpawn = 1500;
			convertEnergyToQuantity = 1;
			reduceMaxEnergyByDamageCoef = 1;
			powerSocketsCount = 1;
			compatiblePlugTypes[] = {1};
		};
	};
};