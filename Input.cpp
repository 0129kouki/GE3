#include"Input.h"
#include<cassert>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

void Input::Initialize(HINSTANCE hInstance, HWND hwnd)
{
	HRESULT result;

	//IDirectInput8* directInput = nullptr;
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));


	//IDirectInputDevice8* keyboard = nullptr;
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	//���̓f�[�^�`���̃Z�b�g
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(result));

	//�r�����䃌�x���̃Z�b�g
	result = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));

}
void Input::Update()
{
	HRESULT result;

	// �L�[�{�[�h���̎擾�J�n
	result = keyboard->Acquire();

	memcpy(keyPre, key, sizeof(key));

	// �S�L�[�̓��͏�Ԃ��擾����
	result = keyboard->GetDeviceState(sizeof(key), key);
}

bool Input::PushKey(BYTE keyNumber)
{
	//�w��L�[�������Ă����true��Ԃ�
	if (key[keyNumber])
	{
		return true;
	}

	//�����łȂ����false��Ԃ�
	return false;
}

bool Input::TriggerKey(BYTE keyNumbe)
{
	if (key[keyNumbe] && !keyPre[keyNumbe])
	{
		return true;
	}
	return false;
}