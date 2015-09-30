#include "SharedShaderInfo.fxh"

texture	gBaseTexture;
texture	gNmhTexture;

float		gBaseTextureRepeat;
float		gHeightMapScale;

float2	gTextureDims;
int			gLodThreshold;
float		gShadowSoftening;
int			gMinSamples;
int			gMaxSamples;

sampler tBase =
sampler_state
{
	Texture = < gBaseTexture >;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};
sampler tNormalHeightMap =
sampler_state
{
	Texture = < gNmhTexture >;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

struct VS_OUTPUT
{
	float4 position          : POSITION;
	float2 texCoord          : TEXCOORD0;
	float3 vLightTS          : TEXCOORD1;   // light vector in tangent space, denormalized
	float3 vViewTS           : TEXCOORD2;   // view vector in tangent space, denormalized
	float2 vParallaxOffsetTS : TEXCOORD3;   // Parallax offset vector in tangent space
	float3 vNormalWS         : TEXCOORD4;   // Normal vector in world space
	float3 vViewWS           : TEXCOORD5;   // View vector in world space
};