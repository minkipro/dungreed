#pragma once

#define DX2DFRAME

#include "targetver.h"

#include <Windows.h>
#include <assert.h>
#include <Math.h>
#include <time.h>
#include <thread>

#include <string>
#include <vector>
#include <queue>
#include <map>
#include <functional>
#include <io.h>
#include <fstream>
#include <algorithm>
#include <utility>
#include <exception>
#include <iterator>
using namespace std;

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#pragma comment(lib, "winmm.lib")

#define SAFE_RELEASE(p) {if(p){(p)->Release(); (p)=NULL;}}
#define SAFE_DELETE(p) { if (p) { delete (p); (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p); (p)=NULL; } }

#define DEVICE Device::GetDevice()
#define KEYBOARD Keyboard::Get()
#define MOUSE Mouse::Get()
#define TEXTUREMANAGER TextureManager::Get()
#define SCENEMANAGER SceneManager::Get()
#define TIMER TimeManager::Get()
#define DELTATIME TIMER->GetElapsedTime()
#define SOUND SoundManager::Get()
#define SHADER ShaderManager::Get()
#define GET_RENDER(p,info) {if(p==nullptr) {p=TEXTUREMANAGER->GetRenderInfo(info);}}

typedef function<void()> CALL_FUNC;
typedef function<void(void*)> CALL_FUNC_PARAM;

#include "Math.h"
#include "Size.h"
#include "Point.h"
#include "Rect.h"
#include "Physics.h"
#include "Xml.h"

#include "Device.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "D2Vertex.h"
#include "TriVertex.h"
#include "RectVertex.h"
#include "VertexBuffer.h"
#include "Timer.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "DrawLine.h"

#include "Shader.h"
#include "ShaderManager.h"

#include "LocationInfo.h"
#include "TEXTURE.h"
#include "Font.h"
#include "RenderInfo.h"
#include "Button.h"
#include "TextureManager.h"
#include "Effecter.h"
#include "TextureEditer.h"

#include "SceneMain.h"
#include "SceneManager.h"

//Shader List
#include "ColorShader.h"
#include "BlurShader.h"
#include "LightShader.h"
#include "AlphaShader.h"
#include "MosaicShader.h"

//game Object
#include "cat.h"

//map
#include "Tile.h"
#include "Map.h"
#include "Maze.h"

//Scene List
#include "TextureEditerScene.h"
#include "GameScene.h"
#include "MapEditScene.h"

#include "GameMain.h"

#define WIN_X 0 //시작 X위치
#define WIN_Y 0 //시작 Y위치
#define WIN_WIDTH 1400 //시작 윈도우 크기
#define WIN_HEIGHT 700 //시작 윈도우 크기
#define WIN_TITLE L"Win32 Game" //윈도우 타이틀 및 클래스명
#define WIN_SHOW_CURSOR TRUE //윈도우 커서를 보여줄지?

using namespace Xml;
