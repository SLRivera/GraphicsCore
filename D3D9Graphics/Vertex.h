/*!
* \file Vertex.h
*
* \author Sam Rivera
* \date September 2015
*
* Last Revision: 9/23/15
*/
#pragma once

#include <d3dx9.h>

namespace GFXCore
{
	// Call in constructor and destructor, respectively, of derived application class.
	void initAllVertexDeclarations();
	void destroyAllVertexDeclarations();

	struct VertexPos;
	struct VertexCol;
	struct VertexPNT;

	//===============================================================
	struct VertexPos
	{
		VertexPos()
			: position(0.0f, 0.0f, 0.0f)
		{}
		VertexPos(float x, float y, float z)
			: position(x, y, z)
		{}
		VertexPos(const D3DXVECTOR3& v)
			: position(v)
		{}

		D3DXVECTOR3 position;
		static IDirect3DVertexDeclaration9* Decl;
	};

	//===============================================================
	struct VertexCol
	{
		VertexCol()
			: position(0.0f, 0.0f, 0.0f), color(0x00000000)
		{}
		VertexCol(float x, float y, float z, D3DCOLOR c)
			: position(x, y, z), color(c)
		{}
		VertexCol(const D3DXVECTOR3& v, D3DCOLOR c)
			: position(v), color(c)
		{}

		D3DXVECTOR3 position;
		D3DCOLOR    color;
		static IDirect3DVertexDeclaration9* Decl;
	};

	//===============================================================
	struct VertexPT
	{
		VertexPT() :
			position(0.0f, 0.0f, 0.0f),
			tex(0.0f, 0.0f)
		{}
		VertexPT(D3DXVECTOR3& p, D3DXVECTOR2& t) :
			position(p),
			tex(t)
		{}
		VertexPT(float x, float y, float z, float u, float v) :
			position(x, y, z),
			tex(u, v)
		{}

		D3DXVECTOR3	position;
		D3DXVECTOR2	tex;

		static IDirect3DVertexDeclaration9* Decl;
	};

	//===============================================================
	struct VertexPN
	{
		VertexPN()
			: position(0.0f, 0.0f, 0.0f), normal(0.0f, 0.0f, 0.0f)
		{}
		VertexPN(float x, float y, float z, float nx, float ny, float nz)
			: position(x, y, z), normal(nx, ny, nz)
		{}
		VertexPN(const D3DXVECTOR3& v, const D3DXVECTOR3& n)
			: position(v), normal(n)
		{}

		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		static IDirect3DVertexDeclaration9* Decl;
	};

	//===============================================================
	struct VertexPNT
	{
		VertexPNT()
			: position(0.0f, 0.0f, 0.0f), normal(0.0f, 0.0f, 0.0f), tex(0.0f, 0.0f)
		{}
		VertexPNT(float x, float y, float z, float nx, float ny, float nz, float u, float v)
			: position(x, y, z), normal(nx, ny, nz), tex(u, v)
		{}
		VertexPNT(const D3DXVECTOR3& v, const D3DXVECTOR3& n, const D3DXVECTOR2& uv)
			: position(v), normal(n), tex(uv)
		{}

		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		D3DXVECTOR2 tex;

		static IDirect3DVertexDeclaration9* Decl;
	};

	//===============================================================
	struct VertexPNC
	{
		VertexPNC() :
			position(0.0f, 0.0f, 0.0f),
			normal(0.0f, 0.0f, 0.0f),
			color(0x00000000){}
		VertexPNC(float x, float y, float z, float nx, float ny, float nz, D3DXCOLOR c) :
			position(x, y, z),
			normal(nx, ny, nz),
			color(c) {}
		VertexPNC(D3DXVECTOR3& p, D3DXVECTOR3& n, D3DXCOLOR& c) :
			position(p),
			normal(n),
			color(c) {}

		D3DXVECTOR3	position,
			normal;

		D3DCOLOR			color;

		static IDirect3DVertexDeclaration9* Decl;
	};

	//===============================================================
	struct VertexPOM
	{
		VertexPOM() :
			position(0.0f, 0.0f, 0.0f),
			normal(0.0f, 0.0f, 0.0f),
			tex(0.0f, 0.0f),
			tangent(0.0f, 0.0f, 0.0f),
			binormal(0.0f, 0.0f, 0.0f) {}

		VertexPOM(float x, float y, float z, float nx, float ny, float nz, float u, float v, float tx, float ty, float tz, float bx, float by, float bz) :
			position(x, y, z),
			tex(u, v),
			normal(nx, ny, nz),
			tangent(tx, ty, tz),
			binormal(bx, by, bz) {}

		VertexPOM(D3DXVECTOR3& p, D3DXVECTOR2& uv, D3DXVECTOR3& n, D3DXVECTOR3& t, D3DXVECTOR3& b) :
			position(p),
			tex(uv),
			normal(n),
			tangent(t),
			binormal(b) {}

		D3DXVECTOR3	position;
		D3DXVECTOR3	normal;
		D3DXVECTOR2	tex;
		D3DXVECTOR3	tangent;
		D3DXVECTOR3	binormal;

		static IDirect3DVertexDeclaration9* Decl;
	};

}