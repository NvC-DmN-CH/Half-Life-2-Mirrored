#ifndef TNERENDERTARGETS_H_
#define TNERENDERTARGETS_H_
#ifdef _WIN32
#pragma once
#endif

#include "baseclientrendertargets.h" // Base class, with interfaces called by engine and inherited members to init common render   targets

// externs
class IMaterialSystem;
class IMaterialSystemHardwareConfig;

class CTNERenderTargets : public CBaseClientRenderTargets
{
	// no networked vars 
	DECLARE_CLASS_GAMEROOT(CTNERenderTargets, CBaseClientRenderTargets);
public:
	virtual void InitClientRenderTargets(IMaterialSystem* pMaterialSystem, IMaterialSystemHardwareConfig* pHardwareConfig);
	virtual void ShutdownClientRenderTargets();
	
	ITexture* CreateCameraPreFlipTexture(IMaterialSystem* pMaterialSystem);

private:
	CTextureReference		m_CameraPreFlipTexture;
};

extern CTNERenderTargets* TNERenderTargets;

#endif //TNERENDERTARGETS_H_