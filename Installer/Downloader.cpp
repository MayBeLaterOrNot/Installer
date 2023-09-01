#include "Downloader.h"
#include <Windows.h>
#include "resource.h"
#include <Urlmon.h>
#include <functional>
#include <future>
#include <string>
#include <sstream>
#include "Util.h"

static bool abortDownloadFlag = false;

class DownloadStatus :public IBindStatusCallback {
	public:
		ULONG presize{ 0 };
		STDMETHOD(OnStartBinding)(DWORD dwReserved, IBinding __RPC_FAR* pib)
		{
			return abortDownloadFlag ? E_ABORT : E_NOTIMPL;
		}
		STDMETHOD(GetPriority)(LONG __RPC_FAR* pnPriority)
		{
			return E_NOTIMPL;
		}
		STDMETHOD(OnLowResource)(DWORD reserved)
		{
			return E_NOTIMPL;
		}
		STDMETHOD(OnProgress)(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR wszStatusText)
		{
			//float ps = 0;
			//if (ulProgressMax != 0) {
			//	ps = (float)ulProgress * 100 / ulProgressMax;
			//}
			return abortDownloadFlag ? E_ABORT : E_NOTIMPL;
		}
		STDMETHOD(OnStopBinding)(HRESULT hresult, LPCWSTR szError)
		{
			return E_NOTIMPL;
		}
		STDMETHOD(GetBindInfo)(DWORD __RPC_FAR* grfBINDF, BINDINFO __RPC_FAR* pbindinfo)
		{
			return E_NOTIMPL;
		}
		STDMETHOD(OnDataAvailable)(DWORD grfBSCF, DWORD dwSize, FORMATETC __RPC_FAR* pformatetc, STGMEDIUM __RPC_FAR* pstgmed)
		{
			return abortDownloadFlag ? E_ABORT : E_NOTIMPL;
		}
		STDMETHOD(OnObjectAvailable)(REFIID riid, IUnknown __RPC_FAR* punk)
		{
			return abortDownloadFlag ? E_ABORT : E_NOTIMPL;
		}
		STDMETHOD_(ULONG, AddRef)()
		{
			return E_NOTIMPL;
		}
		STDMETHOD_(ULONG, Release)()
		{
			return E_NOTIMPL;
		}
		STDMETHOD(QueryInterface)(REFIID riid, void __RPC_FAR* __RPC_FAR* ppvObject)
		{
			return E_NOTIMPL;
		}
};


Downloader::Downloader()
{

}
Downloader::~Downloader()
{
	AbortDownload();
}
void Downloader::AbortDownload()
{
	if (!downloadThread.joinable()) return;
	abortDownloadFlag = true;
	downloadThread.join();
}
void Downloader::Download(const std::wstring& url)
{
	AbortDownload();
	abortDownloadFlag = false;
	downloadThread = std::thread([]() {
		DownloadStatus ds;
		LPTSTR cacheFilePath = new TCHAR[MAX_PATH];
		const HRESULT hr = URLDownloadToCacheFile(nullptr, L"https://avatars.githubusercontent.com/u/2980915?v=4", 
			cacheFilePath, URLOSTRM_USECACHEDCOPY, 0, &ds);
		if (FAILED(hr))
		{
			delete[] cacheFilePath;
			MessageBox(NULL, L"下载失败",L"系统提示",MB_ICONWARNING | MB_OK);
			return;
		}
		MessageBox(NULL, cacheFilePath, L"系统提示", MB_ICONWARNING | MB_OK);
		//std::wstringstream ss;
		//ss << cacheFilePath;
		//delete[] cacheFilePath;
		//auto path = ConvertToUTF8(ss.str());
		//if (path.empty()) {
		//	//todo
		//}
	});
}