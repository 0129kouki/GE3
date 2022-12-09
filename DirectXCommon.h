#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include"WinApp.h"
//DirectX基盤
class DirectXCommon
{
	//メンバ関数
public:
	//初期化
	void Inityalize();
	void InityalizeDevice();
	void InityalizeCommand();
	void InityalizeSwapchain();
private:
	//DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device>device;
	//DXGIファクトリ
	Microsoft::WRL::ComPtr<IDXGIFactory7>dxgiFactory;
private:
	//WindowsAPI
	WinApp* winApp = nullptr;
};

