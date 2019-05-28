// Der folgende ifdef-Block ist die Standardmethode zum Erstellen von Makros, die das Exportieren
// aus einer DLL vereinfachen. Alle Dateien in dieser DLL werden mit dem EXTIO_EXPORTS-Symbol
// (in der Befehlszeile definiert) kompiliert. Dieses Symbol darf für kein Projekt definiert werden,
// das diese DLL verwendet. Alle anderen Projekte, deren Quelldateien diese Datei beinhalten, sehen
// EXTIO_API-Funktionen als aus einer DLL importiert an, während diese DLL
// mit diesem Makro definierte Symbole als exportiert ansieht.
#ifdef EXTIO_EXPORTS
#define EXTIO_API __declspec(dllexport) 
#else
#define EXTIO_API __declspec(dllimport)
#endif

// Diese Klasse wird aus der DLL exportiert.
class Cextio {
public:
	Cextio(void);
	// TODO: Methoden hier hinzufügen.

	bool InitHW(char* name, char* model, int& index) { index = -1; return false; }
	bool OpenHW(void) { return false; }
	void CloseHW(void) {}

	int  StartHW(long freq) { return 0; }
	void StopHW(void) {}

	int SetHWLO(long LOfreq) { return 0; }
	long GetHWLO(void) { return 0; }

	//long GetHWSR(void) { return 0; }
	int GetStatus(void) { return 0; }

	//void ShowGUI(void) {}
	//void HideGUI(void) {}

};

//extern EXTIO_API int nextio;

//EXTIO_API int fnextio(void);
