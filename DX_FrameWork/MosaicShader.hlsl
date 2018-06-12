float2 _mosaicSize;
float2 _renderSize;
float2 _startUV;
bool _blendOk;

texture _map;

sampler _samp
{
    Texture = _map;
};

float4 main(float2 uv : TEXCOORD0) : SV_TARGET
{
    //float alphaSave = tex2D(_samp, uv).a;
    float2 temp = uv - _startUV;

    int x = (int) ((temp.x * _renderSize.x) / _mosaicSize.x);
    int y = (int) ((temp.y * _renderSize.y) / _mosaicSize.y);

    float2 result = float2(_startUV.x + (x * _mosaicSize.x) / _renderSize.x, _startUV.y + (y * _mosaicSize.y) / _renderSize.y);

    float4 endColor = tex2D(_samp, result);
   // endColor.a = alphaSave;
    return endColor;
}

technique tech
{
    pass pass1
    {
        AlphaBlendEnable = _blendOk;
        BlendOp = Add;
        DestBlend = InvSrcAlpha;
        SrcBlend = SrcAlpha;

        PixelShader = compile ps_2_0 main();
    }
}