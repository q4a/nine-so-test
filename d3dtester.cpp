
#include "d3dtester.h"

// This is wrong definition WINAPI for Gallium Nine
//#define WINAPI
#include <d3d9.h>
#include <SDL2/SDL.h>

void CHW::CreateD3D()
{
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
};

void CHW::DestroyD3D()
{
	pD3D->Release();
	pD3D = nullptr;
};
