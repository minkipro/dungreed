float2 _startUV;
float2 _pixelSize;
float2 _texturePos;
float2 _lightPos;
float _amount;
float _range;
float _deleteValue;
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
    float4 result = tex2D(linearFilter, uv);

    float2 pixelPos = _texturePos+(uv - _startUV)*_pixelSize;
    float dist = distance(pixelPos, _lightPos);

    result.rgb *= 1.0f - ((0.1f / _amount) * dist);
    
    return result;
}

float4 main1(float2 uv : TEXCOORD0) : SV_TARGET
{
    float4 result = tex2D(linearFilter, uv);

    float2 pixelPos = _texturePos+(uv - _startUV) * _pixelSize;
    float dist = distance(pixelPos, _lightPos);

    if (_range < dist)
    {
        result.rgb -= _deleteValue;
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

        PixelShader = compile ps_2_0 main();
    }

    pass pass1
    {
        AlphaBlendEnable = _blendOk;
        BlendOp = Add;
        DestBlend = InvSrcAlpha;
        SrcBlend = SrcAlpha;

        PixelShader = compile ps_2_0 main1();
    }
}