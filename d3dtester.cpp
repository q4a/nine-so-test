
#include "d3dtester.h"

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
