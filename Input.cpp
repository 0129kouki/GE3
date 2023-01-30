#include"Input.h"

#include<cassert>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

using namespace Microsoft::WRL;

void Input::Initialize(WinApp* winApp)
{
	HRESULT result;

	this->winApp = winApp;

	//DirectInputの初期化
	//ComPtr<IDirectInput8>directInput;
	result = DirectInput8Create(this->winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	//キーボードデバイスの生成
	//ComPtr<IDirectInputDevice8>keyboard;
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	//入力データ形式のセット
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);//標準形式
	assert(SUCCEEDED(result));
	//排他制御レベルのセット
	result = keyboard->SetCooperativeLevel(this->winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}
void Input::Update()
{
	// キーボード情報の取得開始
	keyboard->Acquire();

	//前回の情報をコピー
	memcpy(keyPre, key, sizeof(key));

	// 全キーの入力状態を取得する
	BYTE key[256] = {};
	keyboard->GetDeviceState(sizeof(key), key);
}

bool Input::PushKey(BYTE keyNumber)
{
	//指定キーを押していればtrueを返す
	if (key[keyNumber])
	{
		return true;
	}

	//押されなかった場合
	return false;
}

bool Input::TriggerKey(BYTE keyNumbe)
{
	return false;
}