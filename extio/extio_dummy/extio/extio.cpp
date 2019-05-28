// extio.cpp : Hiermit werden die exportierten Funktionen für die DLL definiert.
//

#include "pch.h"
#include "framework.h"
#include "extio.h"


#if (0)
// Dies ist ein Beispiel für eine exportierte Variable.
//EXTIO_API int nextio=0;

// Dies ist ein Beispiel für eine exportierte Funktion.
//EXTIO_API int fnextio(void)
//{
//    return 0;
//}

// Dies ist der Konstruktor einer Klasse, die exportiert wurde.
Cextio::Cextio()
{
    return;
}


// red pitaya

char gBuffer[4096];

long gRate = 100000;
int gCorr = 0;

long gFreq = 600000;
long gFreqMin = 100000;
long gFreqMax = 60000000;

bool gInitHW = false;

bool gExitThread = false;
bool gThreadRunning = false;


//---------------------------------------------------------------------------

void (*ExtIOCallback)(int, int, float, void*) = 0;

DWORD WINAPI GeneratorThreadProc(__in LPVOID lpParameter)
{
	unsigned long size = 0;

	while (!gExitThread)
	{
		SleepEx(1, FALSE);
		if (gExitThread) break;

//		ioctlsocket(gSock, FIONREAD, &size);


		// grab from UART

		// *abcde12345

		// * I Q




//		while (size >= 4096)
		{

			SleepEx(20, FALSE);

//			recv(gSock, gBuffer, 4096, 0);
			if (ExtIOCallback) (*ExtIOCallback)(512, 0, 0.0, gBuffer);
//			ioctlsocket(gSock, FIONREAD, &size);

		}
	}
	gExitThread = false;
	gThreadRunning = false;
	return 0;
}


static void StopThread()
{
	if (gThreadRunning)
	{
		gExitThread = true;
		while (gThreadRunning)
		{
			SleepEx(10, FALSE);
		}
	}
}

//---------------------------------------------------------------------------

static void StartThread()
{
	gExitThread = false;
	gThreadRunning = true;
	CreateThread(NULL, (SIZE_T)(64 * 1024), GeneratorThreadProc, NULL, 0, NULL);
}




/******************************************************
  Mandatory Functions
*******************************************************/
//typedef int(*pfnExtIOCallback)  (int cnt, int status, float IQoffs, void* IQdata);

extern "C" bool EXTIO_API InitHW(char* name, char* model, int& type)
{
//	if (gLoadedExtIO) delete gLoadedExtIO;
//	gLoadedExtIO = CreateExtIO();
//	return gLoadedExtIO->InitHW(name, model, type);

	strcpy_s(name, 8, "MAXDAQ1");
	strcpy_s(model, 1, "");

	type = 6; // 32 bit integer

	
	if (!gInitHW)
	{
		// globals, settings, GUI ?

		gInitHW = true;
	}

	return gInitHW;

}

extern "C" bool EXTIO_API OpenHW(void)
{
//	return gLoadedExtIO->OpenHW();


	return gInitHW;
}

extern "C" void EXTIO_API CloseHW(void)
{
//	gLoadedExtIO->CloseHW();
	
	gInitHW = false;
}

extern "C" int  EXTIO_API StartHW(long freq)
{
//	return gLoadedExtIO->StartHW(freq);

	if (!gInitHW) return 0;


	StopThread();


	StartThread();

	return 512;
}

extern "C" void EXTIO_API StopHW(void)
{
//	gLoadedExtIO->StopHW();
	
	StopThread();
}

//extern "C" void EXTIO_API SetCallback(pfnExtIOCallback funcptr)
extern "C" void EXTIO_API SetCallback(void (*callback)(int, int, float, void*))
{
//	gLoadedExtIO->SetCallback(funcptr);
	ExtIOCallback = callback;
}

extern "C" int  EXTIO_API SetHWLO(long LOfreq)
{
//	return gLoadedExtIO->SetHWLO(LOfreq);


//	if (gFreq != LOfreq && ExtIOCallback) (*ExtIOCallback)(-1, 101, 0.0, 0);

	if (ExtIOCallback) (*ExtIOCallback)(-1, 101, 0.0, 0);

	return 0; // OK
}

extern "C" int  EXTIO_API GetStatus(void)
{
//	return gLoadedExtIO->GetStatus();

	return 0; // not used  but must exist
}

extern "C"
long EXTIO_API GetHWSR()
{
	return gRate;
}
#endif
