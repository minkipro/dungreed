float4 _color;
bool _blendOk;

texture _map;

sampler _samp
{
    Texture = _map;
};

float4 main(float2 uv : TEXCOORD0) : COLOR0
{
    float4 result = tex2D(_samp, uv);

    result.rgb = _color.rgb;

    return result;
}

float4 main1(float2 uv : TEXCOORD0) : COLOR0
{
    float4 result = tex2D(_samp, uv);

    result.rgb *= _color.rgb;

    return result;
}

float4 main2(float2 uv : TEXCOORD0) : COLOR0
{
    float4 result = tex2D(_samp, uv);

    return result;
}

technique tech
{
    pass p
    {
        AlphaBlendEnable = _blendOk;
        BlendOp = Add;
        DestBlend = InvSrcAlpha;
        SrcBlend = SrcAlpha;

        PixelShader = compile ps_2_0 main();
    }

    pass p1
    {
        AlphaBlendEnable = _blendOk;
        BlendOp = Add;
        DestBlend = InvSrcAlpha;
        SrcBlend = SrcAlpha;

        PixelShader = compile ps_2_0 main1();
    }

    pass p2
    {
        AlphaBlendEnable = _blendOk;
        BlendOp = Add;
        DestBlend = InvSrcAlpha;
        SrcBlend = SrcAlpha;

        PixelShader = compile ps_2_0 main2();
    }
}