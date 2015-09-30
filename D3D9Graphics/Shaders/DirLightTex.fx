float4x4 gWorld			: WORLD;
float4x4 gWorldInvTrans	: WORLDINVERSETRANSPOSE;
float4x4 gWVP			: WORLDVIEWPROJECTION;

float4 gAmbientMtrl;
float4 gAmbientLight;
float4 gDiffuseMtrl;
float4 gDiffuseLight;
float4 gSpecularMtrl;
float4 gSpecularLight;
float  gSpecularPower	: SPECULARPOWER;
float3 gLightVecW		: DIRECTION;
float3 gEyePosW			: VIEWPOINT;

texture gTex			: TEXTURE;

sampler TexSampler = sampler_state
{
	Texture = <gTex>;
	MinFilter = Anisotropic;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	MaxAnisotropy = 8;
	AddressU  = WRAP;
    AddressV  = WRAP;
};

struct A2V
{
	float3 positionL : POSITION0;
	float3 normalL   : NORMAL0;
	float2 tex       : TEXCOORD0;
};

struct V2P
{
    float4 positionH : POSITION0;
    float4 diffuse   : COLOR0;
    float4 specular  : COLOR1;
    float2 tex       : TEXCOORD0;
};

V2P DirLightTexVS(A2V IN)
{
    // Zero out our output.
	V2P OUT = (V2P)0;
	
	// Pass on texture coordinates to be interpolated in rasterization.
	OUT.tex = IN.tex;
	
	// Transform to homogeneous local space.
	float4 positionH = float4(IN.positionL, 1);	// location
	float4 normalH   = float4(IN.normalL,   0);	// direction

	// Transform local position to homogeneous clip space.
	OUT.positionH = mul(positionH, gWVP);
	
	// Transform position and normal to world space.
	float3 N = normalize(mul(normalH, gWorldInvTrans).xyz);
	float3 P = mul(positionH, gWorld).xyz;
	
	//=======================================================
	// Compute the color at this position
	
	float3 V = normalize(gEyePosW - P);		// view direction vector
	float3 R = reflect(-gLightVecW, N);		// reflection direction vector
	 
	// Phong lighting:
	float4 I = lit(dot(N, gLightVecW), dot(V, R), gSpecularPower);
	
	// lit returns (ambient intensity, diffuse intensity, specular intensity, 1)
	float3 ambient  = I.x * (gAmbientMtrl  * gAmbientLight).rgb;
	float3 diffuse  = I.y * (gDiffuseMtrl  * gDiffuseLight).rgb;
	float3 specular = I.z * (gSpecularMtrl * gSpecularLight).rgb;
	
	// Sum all the terms together and copy over the diffuse alpha.
	OUT.diffuse = float4(ambient + diffuse, gDiffuseMtrl.a);
	OUT.specular = float4(specular, 1);
	//=======================================================
	
    return OUT;
}

float4 DirLightTexPS(V2P IN) : COLOR
{
	float4 texColor = tex2D(TexSampler, IN.tex);
	IN.diffuse *= texColor;
	return float4(IN.diffuse + IN.specular.rgb, texColor.a * IN.diffuse.a);
}

technique Main
{
    pass FirstPass
    {
        // Specify the vertex and pixel shader associated with this pass.
        vertexShader = compile vs_2_0 DirLightTexVS();
        pixelShader  = compile ps_2_0 DirLightTexPS();
    }
}
