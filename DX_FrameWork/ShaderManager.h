#pragma once

//쉐이더 추가시 enum값 추가, 순수 사용가능 쉐이더 확인용임
enum SHADERS
{
	S_ColorShader,
	S_BlurShader,
	S_LightShader,
	S_AlphaShader,
	S_MosaicShader,
};

class ShaderManager
{
public:
	static ShaderManager * Get();
	void AddShader(string name, Shader* shader);

	Shader* GetShader(string name="nomalShader");
private:
	ShaderManager();
	~ShaderManager();
	static ShaderManager* instance;

	map<string, Shader*> ShaderList;
	map<string, Shader*>::iterator it;
};

