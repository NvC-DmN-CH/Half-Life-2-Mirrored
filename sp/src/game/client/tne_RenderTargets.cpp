#include "cbase.h"
#include "tne_RenderTargets.h"
#include "materialsystem\imaterialsystem.h"
#include "rendertexture.h"

ITexture* CTNERenderTargets::CreateCameraPreFlipTexture(IMaterialSystem* pMaterialSystem)
{
	//	DevMsg("Creating Scope Render Target: _rt_Scope\n");
	return pMaterialSystem->CreateNamedRenderTargetTextureEx2(
		"_rt_Camera_PreFlip",
		256, 256, RT_SIZE_DEFAULT,
		pMaterialSystem->GetBackBufferFormat(),
		MATERIAL_RT_DEPTH_SHARED,
		0,
		CREATERENDERTARGETFLAGS_HDR);
}

//-----------------------------------------------------------------------------
// Purpose: Called by the engine in material system init and shutdown.
//			Clients should override this in their inherited version, but the base
//			is to init all standard render targets for use.
// Input  : pMaterialSystem - the engine's material system (our singleton is not yet inited at the time this is called)
//			pHardwareConfig - the user hardware config, useful for conditional render target setup
//-----------------------------------------------------------------------------
void CTNERenderTargets::InitClientRenderTargets(IMaterialSystem* pMaterialSystem, IMaterialSystemHardwareConfig* pHardwareConfig)
{
	m_CameraPreFlipTexture.Init(CreateCameraPreFlipTexture(pMaterialSystem));

	// Water effects & camera from the base class (standard HL2 targets) 
	BaseClass::InitClientRenderTargets(pMaterialSystem, pHardwareConfig);
}

//-----------------------------------------------------------------------------
// Purpose: Shut down each CTextureReference we created in InitClientRenderTargets.
//			Called by the engine in material system shutdown.
// Input  :  - 
//-----------------------------------------------------------------------------
void CTNERenderTargets::ShutdownClientRenderTargets()
{
	m_CameraPreFlipTexture.Shutdown();

	// Clean up standard HL2 RTs (camera and water) 
	BaseClass::ShutdownClientRenderTargets();
}

//add the interface!
static CTNERenderTargets g_TNERenderTargets;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CTNERenderTargets, IClientRenderTargets, CLIENTRENDERTARGETS_INTERFACE_VERSION, g_TNERenderTargets);
CTNERenderTargets* TNERenderTargets = &g_TNERenderTargets;