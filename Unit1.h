//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Edge.hpp>
#include <Winapi.ActiveX.hpp>
#include <Winapi.WebView2.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu;
	TMenuItem *N1;
	TTimer *MainTimer;
	TTimer *LongTimer;
	TTimer *AuthTimer;
	TTrayIcon *Tray;
	TApplicationEvents *ApplicationEvents;
	TEdgeBrowser *Web;
	TStatusBar *StatusBar;
	TMenuItem *N2;
	void __fastcall MainTimerTimer(TObject *Sender);
	void __fastcall LongTimerTimer(TObject *Sender);
	void __fastcall AuthTimerTimer(TObject *Sender);
	void __fastcall ApplicationEventsMinimize(TObject *Sender);
	void __fastcall TrayClick(TObject *Sender);
	void __fastcall WebExecuteScript(TCustomEdgeBrowser *Sender, HRESULT AResult, const UnicodeString AResultObjectAsJson);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	void Navigate(String URL);
	void ClearMemory();
	void ShowWeb();
	void HideWeb();
	void Start(bool minimized);
	String Domain;
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
