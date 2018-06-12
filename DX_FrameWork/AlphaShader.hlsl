float _alpha;
bool _blendOk;

texture _map;

sampler _samp
{
    Texture = _map;

    MinFilter = Point;
    MagFilter = Point;
};

float4 main(float2 uv : TEXCOORD0) : COLOR0
{
    float4 result = tex2D(_samp, uv);

    if(result.a==1.0)
    {
        result.a = _alpha;
    }

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
}