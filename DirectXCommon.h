#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include<vector>
#include"WinApp.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

//DirectX基盤
class DirectXCommon
{
	//メンバ関数
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Inityalize(WinApp* winApp);
	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw();
	/// <summary>
	/// 描画後処理
	/// </summary>
	void PosDraw();
	/// <summary>
	/// デバイス初期化
	/// </summary>
	void InityalizeDevice();
	/// <summary>
	/// コマンド関連の初期化
	/// </summary>
	void InityalizeCommand();
	/// <summary>
	/// スワップチェーン初期化
	/// </summary>
	void InityalizeSwapchain();
	/// <summary>
	/// レンダーターゲットビュー初期化
	/// </summary>
	void InityalizeRenderTargetView();
	/// <summary>
	/// 深度バッファの初期化
	/// </summary>
	void InityalizeDepthBuffer();
	/// <summary>
	/// フェンスの初期化
	/// </summary>
	void InityalizeFence();
	//デバイス取得
	ID3D12Device* GetDevice()const { return device.Get(); }
	//コマンドリスト
	ID3D12GraphicsCommandList*GetCommandList()const { return commandList.Get(); }
private:
	//DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device>device;
	//DXGIファクトリ
	Microsoft::WRL::ComPtr<IDXGIFactory7>dxgiFactory;
	//コマンド関連
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	//スワップチェーン関連
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	//レンダーターゲットビュー
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap;
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
	//深度バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;
	//フェンス
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;
private:
	//WindowsAPI
	WinApp* winApp = nullptr;

private:
	//dxCommon = new DirectXCommon();
	//dxCommon->Inityalize();


};

