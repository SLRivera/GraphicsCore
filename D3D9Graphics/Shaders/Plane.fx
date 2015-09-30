
float4x4 gWVP;
float4 gFogColor;
float3 gLightDirL;
float gFogEnd;
float gFogStart;

struct OutputVS
{
    float4 posH : POSITION0;
	float4 color : COLOR0;
	float	 fogF : TEXCOORD0;
};

OutputVS TransformVS(float3 posL : POSITION0, float4 color : COLOR0)
{
	OutputVS outVS = (OutputVS)0;
	
	outVS.posH = mul(float4(posL, 1.0f), gWVP);
	outVS.color = color;
	outVS.fogF = ((gFogEnd - outVS.posH.z) / (gFogEnd - gFogStart));
	clamp(outVS.fogF, 0.0f, 1.0f);
    return outVS;
}

float4 TransformPS(OutputVS IN) : COLOR
{
	return (IN.fogF * IN.color) + ((1 - IN.fogF) * gFogColor);
}

technique TransformTech
{
    pass P0
    {
        // Specify the vertex and pixel shader associated with this pass.
        vertexShader = compile vs_2_0 TransformVS();
        pixelShader  = compile ps_2_0 TransformPS();

		// Specify the render/device states associated with this pass.
		//FillMode = WireFrame;
    }
}
