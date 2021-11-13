/*-----------------------------------------------------
    
    [PixelLightingVS.hlsl]
    Author : èoçá„ƒëæ

------------------------------------------------------*/
#include "Common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
    matrix wvp;
    wvp = mul(_World, _View);
    wvp = mul(wvp, _Projection);
    Out.Position = mul(In.Position, wvp);
    
    float4 worldNormal, normal;
    normal = float4(In.Normal.xyz, 0.0);
    worldNormal = mul(normal, _World);
    worldNormal = normalize(worldNormal);
    Out.Normal = worldNormal;

    Out.Diffuse = In.Diffuse;
    Out.TexCoord = In.TexCoord;
    
    Out.WorldPosition = mul(In.Position, _World);
}