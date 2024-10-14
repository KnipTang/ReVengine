struct ps_input
{
    float3 position_local : POS;
};

struct ps_output
{
    float4 position_clip : SV_POSITION;
};

float4 ps_main(ps_input input) : SV_TARGET
{
    return float4(1.0, 0.0, 1.0, 1.0);
}