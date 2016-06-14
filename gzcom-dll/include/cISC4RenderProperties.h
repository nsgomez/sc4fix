#pragma once
#include "cIGZUnknown.h"

/**
 * Allowable property names seem to be:
 *      ViewOffsetY, ViewOffsetX, UseViewCleanup, UseVertexBuffers,
 *      UseUpdateRectClipping, UseSecondStage, UseScreenShake,
 *      UseScreenFlash, UseOverlayCulling, UseCursorEffects, TextureBits,
 *      TexBindMaxFree, StringTextureCacheSize, SplatTextureScale,
 *      SoundDetail, ShowUpdateRegions, ShowBoundingBoxes, ShadowQuality,
 *      ShadowModelThreshold, ShadowDebug, RenderWaterEffects, RenderUI,
 *      RenderTerrain, RenderStaticView, RenderSnapshot, RenderShadows,
 *      RenderParticleEffects, RenderModelThresholdScroll,
 *      RenderModelThreshold, RenderFloraShadows, RenderDynamicView,
 *      RenderDecals, RenderCloudsAndFog, RenderAutomata, PreferOpaque,
 *      ParticleSizeThreshold, ParticleScale, ParticleLODOffset,
 *      ParticleEffectsLOD, ParticleDensity, ParticleDamping,
 *      OpaqueUIAlphaValue, NoPartialBackingStoreCopies, NoAddSigned,
 *      ModelLODOffset, MinVehicleZoom, MinPedZoom, MaxVehiclePct, MaxPedPct,
 *      MaxParticlesTarget, LightingUpdateDelta, LODOffset,
 *      ForceTextureRepeat, ForceSoftwareDriver, ForcePointSampling,
 *      ForceNoAlphaTest, ForceNoAlphaBlend, ForceDebugTexture, ForceBilinear,
 *      EffectPriorityLevel, DrawLotWalls, DrawLotTextures,
 *      DrawLotOpaqueTextures, DrawLotFoundations, DoAutoZoomAndRotationChanges,
 *      DisplayAlertBorders, DirtyRectMergeFrames, DepthOffset,
 *      DemolishModelThreshold, DebugTexture, CursorType, BuildingVariety,
 *      BuildingLoaderSpeed, BackingStoreMaxZoomTerrain,
 *      BackingStoreMaxZoomFlora, BackingStoreMaxZoomBuildingsProps,
 *      BackingStoreMaxZoomAll
 */
class cISC4RenderProperties : public cIGZUnknown
{
	public:
		virtual int32_t NumIntProperties(void) = 0;
		virtual int32_t NumFloatProperties(void) = 0;
		
		virtual bool BoolValue(uint32_t dwPropKey) = 0;
		virtual int32_t IntValue(uint32_t dwPropKey) = 0;
		virtual float FloatValue(uint32_t dwPropKey) = 0;

		virtual int32_t SetBoolValue(uint32_t dwPropKey, bool bValue) = 0;
		virtual int32_t SetIntValue(uint32_t dwPropKey, int32_t nValue) = 0;
		virtual int32_t SetFloatValue(uint32_t dwPropKey, float fValue) = 0;

		virtual uint32_t BoolPropertyIDFromName(char const* pszName) = 0;
		virtual uint32_t IntPropertyIDFromName(char const* pszName) = 0;
		virtual uint32_t FloatPropertyIDFromName(char const* pszName) = 0;

		virtual char const* NameFromBoolPropertyID(uint32_t dwPropKey) = 0;
		virtual char const* NameFromIntPropertyID(uint32_t dwPropKey) = 0;
		virtual char const* NameFromFloatPropertyID(uint32_t dwPropKey) = 0;
};