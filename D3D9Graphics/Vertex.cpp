/*!
 * \file Vertex.cpp
 *
 * \author Sam Rivera
 * \date 9/27/2015
 *
 * 
 */
#include "Vertex.h"
#include "D3DCore.h"

using namespace GFXCore;

// Initialize static variables.
IDirect3DVertexDeclaration9* VertexPos::Decl = NULL;
IDirect3DVertexDeclaration9* VertexCol::Decl = NULL;
IDirect3DVertexDeclaration9* VertexPN::Decl  = NULL;
IDirect3DVertexDeclaration9* GFXCore::VertexPNT::Decl = NULL;
IDirect3DVertexDeclaration9* VertexPNC::Decl = NULL;
IDirect3DVertexDeclaration9* VertexPOM::Decl = NULL;
IDirect3DVertexDeclaration9* VertexPT::Decl = NULL;

void GFXCore::initAllVertexDeclarations()
{
	//===============================================================
	// VertexPos

	D3DVERTEXELEMENT9 VertexPosElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		D3DDECL_END()
	};	
	HR(D3DCore::get()->getDevice()->CreateVertexDeclaration(VertexPosElements, &VertexPos::Decl));

	//===============================================================
	// VertexCol

	D3DVERTEXELEMENT9 VertexColElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
		D3DDECL_END()
	};	
	HR(D3DCore::get()->getDevice()->CreateVertexDeclaration(VertexColElements, &VertexCol::Decl));

	//===============================================================
	// VertexPN

	D3DVERTEXELEMENT9 VertexPNElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		D3DDECL_END()
	};	
	HR(D3DCore::get()->getDevice()->CreateVertexDeclaration(VertexPNElements, &VertexPN::Decl));

	//===============================================================
	// VertexPNT

	D3DVERTEXELEMENT9 VertexPNTElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};	
	HR(D3DCore::get()->getDevice()->CreateVertexDeclaration(VertexPNTElements, &VertexPNT::Decl));

	//===============================================================
	// VertexPNC
	D3DVERTEXELEMENT9 VertexPNCElements[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 24, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		D3DDECL_END()
	};
	HR(D3DCore::get()->getDevice()->CreateVertexDeclaration(VertexPNCElements, &VertexPNC::Decl));

	//===============================================================
	// VertexPOM
	D3DVERTEXELEMENT9 VertexPOMElements[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		{ 0, 32, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0 },
		{ 0, 44, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 },
		D3DDECL_END()
	};
	HR(D3DCore::get()->getDevice()->CreateVertexDeclaration(VertexPOMElements, &VertexPOM::Decl));

	//===============================================================
	// VertexPT
	D3DVERTEXELEMENT9 VertexPTElements[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};
	HR(D3DCore::get()->getDevice()->CreateVertexDeclaration(VertexPTElements, &VertexPT::Decl));
}


void GFXCore::destroyAllVertexDeclarations()
{
	ReleaseCom(VertexPos::Decl);
	ReleaseCom(VertexCol::Decl);
	ReleaseCom(VertexPN::Decl);
	ReleaseCom(VertexPNT::Decl);
	ReleaseCom(VertexPNC::Decl);
	ReleaseCom(VertexPOM::Decl);
	ReleaseCom(VertexPT::Decl);
}