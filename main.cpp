#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cstdint>
#include <memory>
#include <cassert>
#include <string>
#include <format>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

// ウィンドプロシージャ
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void Log(const std::string& meg) {
	OutputDebugStringA(meg.c_str());
}

std::wstring ConvertString(const std::string& msg) {
	if (msg.empty()) {
		return std::wstring();
	}

	auto sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&msg[0]), static_cast<int>(msg.size()), NULL, 0);
	if (sizeNeeded == 0) {
		return std::wstring();
	}
	std::wstring result(sizeNeeded, 0);
	MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&msg[0]), static_cast<int>(msg.size()), &result[0], sizeNeeded);
	return result;
}

std::string ConvertString(const std::wstring& msg) {
	if (msg.empty()) {
		return std::string();
	}

	auto sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, msg.data(), static_cast<int>(msg.size()), NULL, 0, NULL, NULL);
	if (sizeNeeded == 0) {
		return std::string();
	}
	std::string result(sizeNeeded, 0);
	WideCharToMultiByte(CP_UTF8, 0, msg.data(), static_cast<int>(msg.size()), result.data(), sizeNeeded,NULL,NULL);
	return result;
}

// Windowsアプリでのエントリーポイント
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	WNDCLASS wc{};
	// ウィンドウプロシージャ
	wc.lpfnWndProc = WindowProc;

	// ウィンドウクラス名
	wc.lpszClassName = L"DirectXGame";

	// インスタンスハンドル
	wc.hInstance = GetModuleHandle(nullptr);

	// カーソル
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

	// ウィンドウクラスを登録
	RegisterClass(&wc);

	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;

	// ウィンドウサイズを表す構造体にクライアント領域を入れる
	RECT wrc = { 0,0,kClientWidth,kClientHeight };


	// クライアント領域を元に実際のサイズにwrcを変更してもらう
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);


	// ウィンドウの生成
	HWND hwnd = CreateWindow(
		wc.lpszClassName,      // 利用するクラス名
		L"DirectXGame",        // タイトルバーの文字
		WS_OVERLAPPEDWINDOW,   // よく見るウィンドウタイトル
		CW_USEDEFAULT,         // 表示X座標(Windowsに任せる)
		CW_USEDEFAULT,         // 表示Y座標(Windowsに任せる)
		wrc.right - wrc.left,  // ウィンドウ横幅
		wrc.bottom - wrc.top,  // ウィンドウ縦幅
		nullptr,               // 親ウィンドウハンドル
		nullptr,               // メニューハンドル
		wc.hInstance,          // インスタンスハンドル
		nullptr                // オプション
	);

	// ウィンドウを表示する
	ShowWindow(hwnd, SW_SHOW);

	IDXGIFactory7* dxgiFactory = nullptr;

	HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));

	assert(SUCCEEDED(hr));



	IDXGIAdapter4* useAdapter = nullptr;

	for (UINT i = 0;
		dxgiFactory->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&useAdapter)) != DXGI_ERROR_NOT_FOUND;
		++i) {

		DXGI_ADAPTER_DESC3 adapterDesc{};
		hr = useAdapter->GetDesc3(&adapterDesc);
		assert(SUCCEEDED(hr));

		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {
			Log(ConvertString(std::format(L"Use Adapter:{}\n", adapterDesc.Description)));
			break;
		}
		useAdapter = nullptr;
	}

	assert(useAdapter != nullptr);




	ID3D12Device* device = nullptr;

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_12_2,
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0
	};

	const char* featureLevelString[] = {
		"12.2","12.1", "12.0"
	};

	for (size_t i = 0; i < _countof(featureLevels); ++i) {
		hr = D3D12CreateDevice(useAdapter, featureLevels[i], IID_PPV_ARGS(&device));

		if (SUCCEEDED(hr)) {
			Log(std::format("FeatureLevel:{}\n", featureLevelString[i]));
			break;
		}
	}

	assert(device != nullptr);
	Log("Complete create D3D12Device!!!\n");


	MSG msg{};
	// ウィンドウのxボタンが押されるまでループ
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} 
		else {

		}
	}

	OutputDebugStringA("Hello, DirectX\n");

	return 0;
}