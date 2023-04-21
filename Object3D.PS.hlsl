struct PixelShaderOutPut {
	float32_4t color : SV_TARGET0;
};

PixelShaderOutPut main()
{
	PixelShaderOutPut output;

	output.color = float32_4t(1.0, 1.0, 1.0, 1.0);

	return output;
}