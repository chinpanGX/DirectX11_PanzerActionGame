/*---------------------------------------------------------
    
    [GrayscaleTexturePS.hlsl]
    Author : 出合翔太

-----------------------------------------------------------*/
#include "Common.hlsli"

Texture2D g_Texture : register(t0);
SamplerState g_SamperState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    outDiffuse = g_Texture.Sample(g_SamperState, In.TexCoord);
    outDiffuse *= In.Diffuse;

    // グレースケール
    outDiffuse.rgb = 0.299 * outDiffuse.r + 0.587 * outDiffuse.g, + 0.114 * outDiffuse.b;

}