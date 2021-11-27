/*------------------------------------------------
    
    [MappingVS.hlsl]
    Author : èoçá„ƒëæ

------------------------------------------------*/
#include "Common.hlsli"

void main(in VS_IN In, out VS_IN Out)
{
	matrix wvp;
	wvp = mul(_World, _View);
	wvp = mul(wvp, _Projection);

	float4 worldNormal, normal;
	normal = float4(In.Normal.xyz, 0.0);
	worldNormal = mul(normal, _World);
	worldNormal = normalize(worldNormal);
    
	Out.Position = mul(In.Position, wvp);
	//Out.WorldPosition = mul(In.Position, World);
	Out.Normal = worldNormal;
	Out.Diffuse = In.Diffuse;
	Out.TexCoord = In.TexCoord;
}