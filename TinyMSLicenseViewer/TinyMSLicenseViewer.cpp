// TinyMSLicenseViewer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "Version.h"
#include "resource.h"
#include "M2Win32Helpers.h"

#include <string>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	const wchar_t* LicenseStatusText[] =
	{
		L"未经授权",
		L"已授权",
		L"初始宽限期",
		L"附加宽限期(KMS 许可证过期或硬件超出允许期限)",
		L"非正版宽限期",
		L"通知",
		L"延长的宽限期"
	};

	const wchar_t* QuerySource[] =
	{
		L"SoftwareLicensingProduct",
		L"PartialProductKey"
	};
	
	HRESULT hr = S_OK;

	std::wstring Result;

	Result += L"TinyMSLicenseViewer " PROJECT_VERSION_STRING "\r\n";
	Result += L"\xA9 M2-Team. All rights reserved.\r\n\r\n";
	Result += L"========以下是本机上微软产品的授权情况========\r\n";
	Result += L"\r\n";

	IWbemLocator *pLoc = nullptr;
	IWbemServices *pSvc = nullptr;

	do
	{
		// 初始化 COM
		hr = CoInitializeEx(
			nullptr,
			COINIT_MULTITHREADED);
		if (FAILED(hr)) break;

		// 设置进程安全级别
		hr = CoInitializeSecurity(
			nullptr,
			-1,
			nullptr,
			nullptr,
			RPC_C_AUTHN_LEVEL_DEFAULT,
			RPC_C_IMP_LEVEL_IMPERSONATE,
			nullptr,
			EOAC_NONE,
			nullptr);
		if (FAILED(hr)) break;

		// 创建一个CLSID_WbemLocator对象		
		hr = CoCreateInstance(
			CLSID_WbemLocator,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_IWbemLocator,
			(LPVOID *)&pLoc);
		if (FAILED(hr)) break;

		// 使用pLoc连接到"root\cimv2" 获取IWbemServices接口
		hr = pLoc->ConnectServer(
			L"ROOT\\CIMV2",
			nullptr,
			nullptr,
			nullptr,
			0,
			nullptr,
			nullptr,
			&pSvc);
		if (FAILED(hr)) break;

		// 设置连接的安全级别
		hr = CoSetProxyBlanket(
			pSvc,
			RPC_C_AUTHN_WINNT,
			RPC_C_AUTHZ_NONE,
			nullptr,
			RPC_C_AUTHN_LEVEL_CALL,
			RPC_C_IMP_LEVEL_IMPERSONATE,
			nullptr,
			EOAC_NONE);
		if (FAILED(hr)) break;

		for (size_t i = 0; i < sizeof(QuerySource) / sizeof(*QuerySource); ++i)
		{
			std::wstring QueryString;

			QueryString += L"SELECT * FROM ";
			QueryString += std::wstring(QuerySource[i]);
			QueryString += L" WHERE PartialProductKey <> null";

			IEnumWbemClassObject* pSLPEnumerator = nullptr;

			hr = pSvc->ExecQuery(
				L"WQL",
				const_cast<BSTR>(QueryString.c_str()),
				WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
				nullptr,
				&pSLPEnumerator);

			if (SUCCEEDED(hr))
			{
				IWbemClassObject *pSLPClassObject = nullptr;
				ULONG uReturn = 0;
				VARIANT vtDescription, vtLicenseStatus;

				while (true)
				{
					pSLPEnumerator->Next(
						WBEM_INFINITE,
						1,
						&pSLPClassObject,
						&uReturn);

					if (0 == uReturn) break;

					pSLPClassObject->Get(
						L"Name",
						0,
						&vtDescription,
						nullptr,
						nullptr);
					pSLPClassObject->Get(
						L"LicenseStatus",
						0,
						&vtLicenseStatus,
						nullptr,
						nullptr);


					Result += std::wstring(vtDescription.bstrVal) + L"\r\n";
					Result += std::wstring(LicenseStatusText[vtLicenseStatus.lVal]) + L"\r\n";
					Result += L"\r\n";

					VariantClear(&vtDescription);
					VariantClear(&vtLicenseStatus);

					pSLPClassObject->Release();
				}
				pSLPEnumerator->Release();
			}
		}

		M2MessageDialog(hInstance, nullptr, MAKEINTRESOURCE(IDI_ICON1), L"TinyMSLicenseViewer", Result.c_str());

	} while (false);

	if (pSvc) pSvc->Release();
	if (pLoc) pLoc->Release();
	CoUninitialize();
	return 0;
}
