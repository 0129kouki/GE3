#pragma once
#include<Windows.h>
#include<wrl.h>
#define DIRECTINPUT_VERSION  0x0800
#include <dinput.h>

#include"WinApp.h"


//入力
class Input
{
public:
	template <class T> using Comptr = Microsoft::WRL::ComPtr<T>;

public://メンバ関数
	//初期化
	void Initialize(WinApp* winApp);

	//更新
	void Update();
	bool TriggerKey(BYTE keyNumbe);
	bool PushKey(BYTE keyNumber);
private:
	//DirectInputのインスタンス生成
	Comptr<IDirectInput8> directInput;
	//全キーの状態
	BYTE key[256] = {};
	BYTE keyPre[256] = {};
	//キーボードデバイス生成
	Comptr<IDirectInputDevice8>keyboard;
private:
	//WindowsAPI
	WinApp* winApp = nullptr;
};