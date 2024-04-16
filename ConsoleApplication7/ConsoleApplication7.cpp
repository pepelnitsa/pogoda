#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <windows.h>
#include <Urlmon.h>

#pragma comment(lib, "urlmon.lib")

using namespace std;

void findTemperature(const string& srcURL, const char* city)
{
    const char* destFile = "weather.txt";

    // Clear the contents of the file
    ofstream clearFile(destFile);
    clearFile.close();

    HRESULT hr = URLDownloadToFileA(NULL, srcURL.c_str(), destFile, 0, NULL);
    if (FAILED(hr))
    {
        cout << "Failed to download weather data for " << city << endl;
        return;
    }

    ifstream file(destFile);
    if (!file.is_open())
    {
        cout << "Failed to open downloaded file for " << city << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        size_t pos = line.find("js_value w_temperature");
        if (pos != string::npos)
        {
            pos = line.find(">", pos);
            if (pos != string::npos)
            {
                pos++;
                size_t end = line.find("<", pos);
                if (end != string::npos)
                {
                    string temperature = line.substr(pos, end - pos);
                    cout << "Temperature in " << city << ": " << temperature << endl;
                    break;
                }
            }
        }
    }

    file.close();
}

int main()
{
    const char* srcOdessa = "https://www.gismeteo.ua/weather-odessa-4982/";
    const char* srcKyiv = "https://www.gismeteo.ua/weather-kyiv-4944/";
    const char* srcLviv = "https://www.gismeteo.ua/weather-lviv-4949";
    const char* srcKharkiv = "https://www.gismeteo.ua/weather-kharkiv-5053/";
    const char* srcSumy = "https://www.gismeteo.ua/weather-sumy-4936/";
    const char* srcDnipro = "https://www.gismeteo.ua/weather-dnipro-5077/";
    const char* srcZaporizhzhia = "https://www.gismeteo.ua/weather-zaporizhzhia-5093/";
    const char* srcKryviyRig = "https://www.gismeteo.ua/weather-kryvyi-rih-4978/";
    const char* srcVinnytsia = "https://www.gismeteo.ua/weather-vinnytsia-4962/";
    const char* srcPoltava = "https://www.gismeteo.ua/weather-poltava-4957/";
    const char* srcChernihiv = "https://www.gismeteo.ua/weather-chernihiv-4923/";

    findTemperature(srcOdessa, "Odessa");
    findTemperature(srcKyiv, "Kyiv");
    findTemperature(srcLviv, "Lviv");
    findTemperature(srcKharkiv, "Kharkiv");
    findTemperature(srcSumy, "Sumy");
    findTemperature(srcDnipro, "Dnipro");
    findTemperature(srcZaporizhzhia, "Zaporizhzhia");
    findTemperature(srcKryviyRig, "Donetsk");
    findTemperature(srcVinnytsia, "Mariupol");
    findTemperature(srcPoltava, "Kherson");
    findTemperature(srcChernihiv, "Mykolaiv");

    return 0;
}
