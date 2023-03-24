#ifndef __D3DTESTER_H__
#define __D3DTESTER_H__

struct IDirect3D9;

class CHW
{
public:
	CHW(){};
	~CHW(){};

	IDirect3D9* pD3D = nullptr; // D3D
	void CreateD3D();
	void DestroyD3D();
};

#endif // __D3DTESTER_H__
