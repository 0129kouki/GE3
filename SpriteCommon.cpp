#include "SpriteCommon.h"
#include<string>

#include<d3dcompiler.h>
#include<cassert>

#pragma comment(lib,"d3dcompiler.lib")

using namespace Microsoft::WRL;

void SpriteCommon::Initialize(DirectXCommon* _dxCommon)
{
	HRESULT result{};
	assert(_dxCommon);
	dxCommon = _dxCommon;

	//シェーダー
	ID3DBlob* vsBlob;
	ID3DBlob* psBlob;
	ID3DBlob* errorBlob;

	//読み込み
	result = D3DCompileFromFile(
		L"Resources/Shaders/SpriteVS.hlsl",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main", "vs_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&vsBlob, &errorBlob);

	if (FAILED(result)) {
		std::string error;
		error.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		OutputDebugStringA(error.c_str());
		assert(0);
	}
		//読み込み
		result = D3DCompileFromFile(
			L"Resources/Shaders/SpritePS.hlsl",
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"main", "ps_5_0",
			D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
			0,
			&psBlob, &errorBlob);

		if (FAILED(result)) {
			std::string error;
			error.resize(errorBlob->GetBufferSize());
			std::copy_n((char*)errorBlob->GetBufferPointer(),
				errorBlob->GetBufferSize(),
				error.begin());
			error += "\n";
			OutputDebugStringA(error.c_str());
			assert(0);
		}
		// 頂点レイアウト
		D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{
		"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
	};
		// グラフィックスパイプライン
		//パイプライン設定
		D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};
		//シェーダー設定
		pipelineDesc.VS.pShaderBytecode = vsBlob->GetBufferPointer();
		pipelineDesc.VS.BytecodeLength = vsBlob->GetBufferSize();
		pipelineDesc.PS.pShaderBytecode = psBlob->GetBufferPointer();
		pipelineDesc.PS.BytecodeLength = psBlob->GetBufferSize();
		// サンプルマスク設定
		pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
		// ラスタライザの設定
		pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
		pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
		pipelineDesc.RasterizerState.DepthClipEnable = true; 
		// ブレンドステート
		pipelineDesc.BlendState.RenderTarget[0].RenderTargetWriteMask= D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA全てのチャンネルを描画
		// 頂点レイアウト
		pipelineDesc.InputLayout.pInputElementDescs = inputLayout;
		pipelineDesc.InputLayout.NumElements = _countof(inputLayout);
		// 図形の形状設定
		pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		// その他
		pipelineDesc.NumRenderTargets = 1;
		pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; 
		pipelineDesc.SampleDesc.Count = 1;

		//// ルートシグネチャ
		//ID3D12RootSignature* rootSignature;
		//設定
		D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
		rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		//シリアライズ
		ID3DBlob* rootSigBlob;
		result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0,
			&rootSigBlob, &errorBlob);
		assert(SUCCEEDED(result));
		result = dxCommon->GetDevice()->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
			IID_PPV_ARGS(&rootSignature));
		assert(SUCCEEDED(result));
		rootSigBlob->Release();
		// パイプラインにルートシグネチャをセット
		pipelineDesc.pRootSignature = rootSignature.Get();
		// パイプランステートの生成
		result = dxCommon->GetDevice()->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState));
		assert(SUCCEEDED(result));
}

void SpriteCommon::PreDraw()
{
	// プリミティブ形状の設定コマンド
	dxCommon->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// パイプラインステートとルートシグネチャの設定コマンド
	dxCommon->GetCommandList()->SetPipelineState(pipelineState.Get());
	dxCommon->GetCommandList()->SetGraphicsRootSignature(rootSignature.Get());
}
