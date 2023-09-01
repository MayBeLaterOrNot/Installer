#pragma once
#include <string>
#include <thread>
class Downloader
{
public:
	Downloader();
	~Downloader();
	void Download(const std::wstring& url);
	void AbortDownload();
private:
	std::thread downloadThread;
};

