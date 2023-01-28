#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include<vector>
#include"WinApp.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

//DirectX���
class DirectXCommon
{
	//�����o�֐�
public:
	/// <summary>
	/// ������
	/// </summary>
	void Inityalize(WinApp* winApp);
	/// <summary>
	/// �`��O����
	/// </summary>
	void PreDraw();
	/// <summary>
	/// �`��㏈��
	/// </summary>
	void PosDraw();
	/// <summary>
	/// �f�o�C�X������
	/// </summary>
	void InityalizeDevice();
	/// <summary>
	/// �R�}���h�֘A�̏�����
	/// </summary>
	void InityalizeCommand();
	/// <summary>
	/// �X���b�v�`�F�[��������
	/// </summary>
	void InityalizeSwapchain();
	/// <summary>
	/// �����_�[�^�[�Q�b�g�r���[������
	/// </summary>
	void InityalizeRenderTargetView();
	/// <summary>
	/// �[�x�o�b�t�@�̏�����
	/// </summary>
	void InityalizeDepthBuffer();
	/// <summary>
	/// �t�F���X�̏�����
	/// </summary>
	void InityalizeFence();
	//�f�o�C�X�擾
	ID3D12Device* GetDevice()const { return device.Get(); }
	//�R�}���h���X�g
	ID3D12GraphicsCommandList*GetCommandList()const { return commandList.Get(); }
private:
	//DirectX12�f�o�C�X
	Microsoft::WRL::ComPtr<ID3D12Device>device;
	//DXGI�t�@�N�g��
	Microsoft::WRL::ComPtr<IDXGIFactory7>dxgiFactory;
	//�R�}���h�֘A
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	//�X���b�v�`�F�[���֘A
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	//�����_�[�^�[�Q�b�g�r���[
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap;
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
	//�[�x�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;
	//�t�F���X
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;
private:
	//WindowsAPI
	WinApp* winApp = nullptr;

private:
	//dxCommon = new DirectXCommon();
	//dxCommon->Inityalize();


};

