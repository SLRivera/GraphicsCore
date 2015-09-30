#include "SharedShaderInfo.fxh"

texture farFocusTex;
texture onFocusTex;
texture nearFocusTex;

float4 gFarClipPlane;
float4 gFarFocusPlane;
float4 gNearClipPlane;
float4 gNearFocusPlane;
float4 gFocusPlane;

float2 GaussKernel[12];/* =
{
	{ 1.0f, 0.0f },
    { 0.5f, 0.8660f },
	{ -0.5f, 0.8660f },
	{ -1.0f, 0.0f },
	{ -0.5f, -0.8660f },
	{ 0.5f, -0.8660f },

	{ 1.5f, 0.8660f },
	{ 0.0f, 1.7320f },
	{ -1.5f, 0.8660f },
	{ -1.5f, -0.8660f },
	{ 0.0f, -1.7320f },
	{ 1.5f, -0.8660f },
};*/


sampler2D farTexSampler = sampler_state
{
	Texture = < farFocusTex > ;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
	AddressU = Wrap;
	AddressV = Wrap;
};

sampler2D nearTexSampler = sampler_state
{
	Texture = < nearFocusTex >;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
	AddressU = Wrap;
	AddressV = Wrap;
};

sampler2D focusTexSampler = sampler_state
{
	Texture = < onFocusTex >;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
	AddressU = Wrap;
	AddressV = Wrap;
};

InputPS_General QuadTestVS(InputVS_VPNC currVert)
{
	InputPS_General Out = (InputPS_General)0;
	Out.PositionH = mul(float4(currVert.Position, 1.0f), gWVP);
	Out.PositionW = mul(float4(currVert.Position, 1.0f), gWorld).xyz;
	Out.Normal = mul(float4(currVert.Normal, 1.0f), gWIT).xyz;
	Out.Normal = normalize(Out.Normal);

	Out.DistToEye = distance(gEye.xyz, Out.PositionW);
	float3 vPos = mul(float4(currVert.Position, 1.0f), gWIT);
		float4 norm = normalize(gFocusPlane);
		float blurr = dot(float4(vPos, 1.0f), norm) * 0.4f;
	Out.Color.a = blurr * blurr;
	Out.Color.a = min(Out.Color.a, 0.923f);

	return Out;
}

float4 QuadTestPS(InputPS_General currPix) : COLOR
{
	currPix.Normal = normalize(currPix.Normal);

	float3 toEye = normalize(gEye.xyz - currPix.PositionW.xyz);
	float3 lightDir = normalize(gLightPos.xyz - currPix.PositionW.xyz);

	float3 H = normalize(lightDir + toEye);
	float T = pow(max(dot(H, currPix.Normal), 0.0f), gSpecularExp);
	float S = max(dot(lightDir, currPix.Normal), 0.0f);

	float3 spec = T * (gMtrlSpecularColor * gLightSpecular).rgb;

		float3 diffuse = S * (gMtrlDiffuseColor * gLightDiffuse).rgb;

		float3 ambient = (gMtrlAmbientColor * gLightAmbient).rgb;

		//float d = abs(distance(gLightPos.xyz, currPix.PositionW.xyz));
		// TODO: make this be able to be set by the client
		//float A = 10.45f * (10.450f * d) + (10.45f * d * d);
		//float4 finalColor = (0.0f, 1.0f, 1.0f, 0.5f);
		//float4 finalColor = float4(spec + ambient + diffuse, gMtrlDiffuseColor.a);
		
		currPix.Color.rgb = ambient + diffuse + spec;

	return currPix.Color;
}

float4 NoDofPS(in float2 UVS : TEXCOORD0) : COLOR
{
	return tex2D(focusTexSampler, UVS);
}

float4 DofPS(in float2 OrgUV : TEXCOORD0) : COLOR
{
	float4 org = tex2D(farTexSampler, OrgUV);
	float3 blurred = 0;

	for (int i = 0; i < 12; ++i) {
		float4 current = tex2D(farTexSampler, OrgUV + GaussKernel[i]);
		blurred += lerp(org.rgb, current.rgb, saturate(org.a * current.a));
	}
	return float4(blurred / 12, 1.0f);
}

technique RenderToTex
{
	pass P0
	{
		VertexShader = compile vs_2_0 QuadTestVS();
		PixelShader = compile ps_2_0 QuadTestPS();
	}
}

technique NoDOF
{
	pass P0
	{
		PixelShader = compile ps_2_0 NoDofPS();
	}
}

technique DOF
{
	pass P0
	{
		PixelShader = compile ps_2_0 DofPS();
	}
}