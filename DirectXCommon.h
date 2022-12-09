#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include"WinApp.h"
//DirectX���
class DirectXCommon
{
	//�����o�֐�
public:
	//������
	void Inityalize();
	void InityalizeDevice();
	void InityalizeCommand();
	void InityalizeSwapchain();
private:
	//DirectX12�f�o�C�X
	Microsoft::WRL::ComPtr<ID3D12Device>device;
	//DXGI�t�@�N�g��
	Microsoft::WRL::ComPtr<IDXGIFactory7>dxgiFactory;
private:
	//WindowsAPI
	WinApp* winApp = nullptr;
};

