#pragma once
#include<wrl.h>
#define DIRECTINPUT_VERSION     0x0800   // DirectInput�̃o�[�W�����w��
#include <dinput.h>
#include<Windows.h>


//����
class Input
{
public:
	template <class T> using Comptr = Microsoft::WRL::ComPtr<T>;

public://�����o�֐�
	//������
	void Initialize(HINSTANCE hInstance, HWND hwnd);

	//�X�V
	void Update();
	bool TriggerKey(BYTE keyNumbe);
	bool PushKey(BYTE keyNumber);
private:
	//DirectInput�̃C���X�^���X����
	Comptr<IDirectInput8> directInput;
	//�S�L�[�̏��
	BYTE key[256] = {};
	BYTE keyPre[256] = {};
	//�L�[�{�[�h�f�o�C�X����
	Comptr<IDirectInputDevice8>keyboard;
};