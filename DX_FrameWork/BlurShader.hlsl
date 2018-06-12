float2 _uvSize;
int _blurCount;
bool _blendOk;

texture _map;

sampler linearFilter
{
    Texture = _map;

    MinFilter = Linear;
    MagFilter = Linear;
};

float4 main(float2 uv : TEXCOORD0) : SV_TARGET
{
    return tex2D(linearFilter, uv);
}

float4 main1(float2 uv : TEXCOORD0) : SV_TARGET
{
    float4 result = tex2D(linearFilter, uv);

    [unroll(4)]
    for (int i = 0; i < _blurCount; i++)
    {
        result += tex2D(linearFilter, float2(uv.x + _uvSize.x * (i + 1), uv.y));
        result += tex2D(linearFilter, float2(uv.x - _uvSize.x * (i + 1), uv.y));
        result += tex2D(linearFilter, float2(uv.x, uv.y + _uvSize.y * (i + 1)));
        result += tex2D(linearFilter, float2(uv.x, uv.y - _uvSize.y * (i + 1)));
    }

    result /= (float) _blurCount * 4.0f + 1;

    return result;
}

float4 GaussianBlur(float2 uv : TEXCOORD0) : SV_TARGET
{
    const float weight[7] =
    {
        0.486f, 0.726f, 0.923, 1, 0.923f, 0.726f, 0.486f
    };

    float4 result = tex2D(linearFilter, uv);;

    if(result.a==1)
    {
        result.rgb=0;

        int i = 0;

        for (i = -3; i < 3; i++)
        {
            float2 temp = float2(uv.x + i * _uvSize.x, uv.y);
            result += weight[3 + i] * tex2D(linearFilter, temp);
        }

        for (i = -3; i < 3; i++)
        {
            float2 temp = float2(uv.x, i * _uvSize.y + uv.y);
            result += weight[3 + i] * tex2D(linearFilter, temp);
        }

        result /= 10.54f;
    }
    
    return result;
}


technique tech
{
    pass pass0
    {
        AlphaBlendEnable = _blendOk;
        BlendOp = Add;
        DestBlend = InvSrcAlpha;
        SrcBlend = SrcAlpha;

        PixelShader = compile ps_2_0 main1();
    }

    pass pass1
    {
        AlphaBlendEnable = _blendOk;
        BlendOp = Add;
        DestBlend = InvSrcAlpha;
        SrcBlend = SrcAlpha;

        PixelShader = compile ps_2_0 GaussianBlur();
    }
}