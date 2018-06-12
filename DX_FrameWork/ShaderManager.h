#pragma once

//���̴� �߰��� enum�� �߰�, ���� ��밡�� ���̴� Ȯ�ο���
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

