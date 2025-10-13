//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <memory>

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;

int Step = 0;
int ResumesLeft = 0;
String LastTime = "";
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	// настройки
	MainForm->Caption = Application->Title;
	Tray->Hint = Application->Title;
}
//---------------------------------------------------------------------------

void TMainForm::Start(bool minimized)
{
	ShowWeb();
	N2->Caption = "Скрыть браузер";
    MainForm->Position = poScreenCenter;
	MainForm->AlphaBlend = false;

	StatusBar->SimpleText = "Статус: открываю HeadHunter...";
	Navigate(Domain + "/locale?language=RU");
	Step = 1;
	MainTimer->Enabled = true;
	StatusBar->SimpleText = "Статус: проверяю авторизацию...";

	if (minimized == true) {
		Application->Minimize();
		ShowWindow(Handle, SW_HIDE);
		Tray->Visible = true;
	}
}
//---------------------------------------------------------------------------

void TMainForm::Navigate(String URL)
{
	try {
		Web->Navigate(WideString(URL).c_bstr());
	} catch(...) {}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AuthTimerTimer(TObject *Sender)
{
	AuthTimer->Enabled = false;
	Web->ExecuteScript(R"(
		(function() {
			return document.body.innerHTML.includes('Резюме и&nbsp;профиль') ? 1 : 0;
		})();
	)");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MainTimerTimer(TObject *Sender)
{
	// проверка авторизации
	if (Step == 1) {
		Web->ExecuteScript(R"(
			(function() {
				return document.body.innerHTML.includes('Резюме и&nbsp;профиль') ? 1 : 0;
			})();
		)");

		return;
	}

	// переход в "Мои резюме"
	if (Step == 2) {
		Navigate(Domain + "/applicant/resumes?hhtmFrom=main&hhtmFromLabel=header");
		Step = 3;
		return;
	}

	if (Step == 3) {
		// считаем кол-во доступных резюме для поднятия
		Web->ExecuteScript(R"(
			(function() {
				const buttons = document.querySelectorAll('button');
				const matches = Array.from(buttons).filter(btn => (/Поднять в поиске/i).test(btn.textContent));
				return matches.length;
			})();
		)");

		return;
	}

	if (Step == 4) {
		// поднимаем резюме в поиске
		StatusBar->SimpleText = "Статус: поднимаю резюме в поиске (осталось " + IntToStr(ResumesLeft) + ").";

		Web->ExecuteScript(R"(
			(function() {
				const btn = Array.from(document.querySelectorAll('button'))
					.find(b => /Поднять в поиске/i.test(b.textContent));

				if (btn) {
					btn.click();

					setTimeout(() => {
						const closeBtn = document.querySelector('button[data-qa="bot-update-resume-modal__close-button"]');
						if (closeBtn) {
							closeBtn.click();
						}
					}, 700);
					return 1;
				}
				return 0;
			})();
		)");

		return;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::LongTimerTimer(TObject *Sender)
{
	LongTimer->Enabled = false;
	Navigate(Domain + "/locale?language=RU");
    Step = 1;
	MainTimer->Enabled = true;
}
//---------------------------------------------------------------------------

void TMainForm::ClearMemory()
{
	try {
		THandle MainHandle;
		HANDLE ProcessHandle, ThreadHandle;
		DWORD ProcessID = GetCurrentProcessId();
		ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, false, ProcessID);
		SetProcessWorkingSetSize(ProcessHandle, DWORD(-1), DWORD(-1));
		CloseHandle(ProcessHandle);
	} catch(...) {}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ApplicationEventsMinimize(TObject *Sender)
{
	MainForm->Visible = false;
	ShowWindow(Application->Handle, SW_HIDE);
	Tray->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TrayClick(TObject *Sender)
{
	MainForm->Visible = true;
	ShowWindow(Application->Handle, SW_SHOW);
	Application->Restore();
	Tray->Visible = false;
	SetForegroundWindow(MainForm->Handle);
    SetActiveWindow(MainForm->Handle);
}
//---------------------------------------------------------------------------

void TMainForm::ShowWeb()
{
	MainForm->Height = 685;
}
//---------------------------------------------------------------------------

void TMainForm::HideWeb()
{
	MainForm->Height = 75;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::WebExecuteScript(TCustomEdgeBrowser *Sender, HRESULT AResult,
		  const UnicodeString AResultObjectAsJson)
{
	int result = 0;
	try {
		result = StrToInt(AResultObjectAsJson);
	} catch (...) {
		return;
	}

	if (Step == 1) {
		if (result > 0) {
            MainTimer->Enabled = true;
			StatusBar->SimpleText = "Статус: авторизация успешна.";
			Step = 2;
		} else {
			MainTimer->Enabled = false;
			AuthTimer->Enabled = true;
			Step = 1;
			LastTime = "";
			StatusBar->SimpleText = "Статус: жду авторизации пользователя...";
		}
		return;
	}

	if (Step == 3) {
		ResumesLeft = result;
		if (ResumesLeft > 0) {
			StatusBar->SimpleText = "Статус: могу поднять " + AResultObjectAsJson + " резюме.";
			Step = 4;
		} else {
			StatusBar->SimpleText = "Статус: поднятие недоступно. Ожидаем...";
			MainTimer->Enabled = false;
			Step = 1;
			ClearMemory();
			LongTimer->Enabled = true;
		}
		return;
	}

	if (Step == 4) {
		if (result > 0) {
			ResumesLeft--;
		}

		StatusBar->SimpleText = "Статус: поднимаю резюме в поиске (осталось " + IntToStr(ResumesLeft) + ").";

		if (ResumesLeft == 0) {
			MainTimer->Enabled = false;
			Step = 5;
		}
	}

	if (Step == 5) {
		LastTime = Now().FormatString("hh:nn");
		StatusBar->SimpleText = "Статус: резюме подняты в " + LastTime + ". Ожидаем...";
		Step = 1;
		ClearMemory();
		LongTimer->Enabled = true;
		return;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N1Click(TObject *Sender)
{
	SettingsForm->Position = poMainFormCenter;
	SettingsForm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N2Click(TObject *Sender)
{
	if (MainForm->Height == 685) {
		HideWeb();
		N2->Caption = "Показать браузер";
	} else {
		ShowWeb();
		N2->Caption = "Скрыть браузер";
	}
}
//---------------------------------------------------------------------------

