#include <CtrlLib/CtrlLib.h>

#include <cstdlib>
#include <fstream>
#include <windows.h>

#define LAYOUTFILE <FirstProject/Something.lay>
#include <CtrlCore/lay.h>

using namespace Upp;
using namespace std;

class MainMenuDlg : public WithMainMenu<TopWindow> {
private:
	bool music_paused = false;
public:
	MainMenuDlg();
};

class ScoreDlg : public WithScore<TopWindow> {
public:
	ScoreDlg();
};

ScoreDlg::ScoreDlg()
{
	CtrlLayout(*this, "");
	
	this->btnOK.WhenAction = [&] {
		this->Hide();
		this->Close();	
	};
}


MainMenuDlg::MainMenuDlg()
{
	mciSendString("open \"music.mp3\" type mpegvideo alias bgMusic", NULL, 0, NULL);
	mciSendString("play bgMusic", NULL, 0, NULL);
	
	CtrlLayout(*this, "");
	
	this->btnPlay.WhenAction = [&] {
		this->Hide();
		mciSendString("pause bgMusic", NULL, 0, NULL);
		system("Game.exe");	
		Break();
	};
	
	this->btnToggleMusic.WhenAction = [&] {
		music_paused = !music_paused;
		btnToggleMusic.SetLabel(music_paused ? "TURN ON MUSIC" : "TURN OFF MUSIC");
		if(music_paused) {
			mciSendString("pause bgMusic", NULL, 0, NULL);
		} else {
			mciSendString("resume bgMusic", NULL, 0, NULL);
		}
	};
	
	this->btnExit.WhenAction = [&] {
		Break();	
	};
	
	this->btnScore.WhenAction = [&] {
		ifstream infile("score.dat");
		int score;
		infile >> score;
		
		ScoreDlg* scoreWindow = new ScoreDlg();
		scoreWindow->lblHighscore.SetLabel(("Highest Score: " + to_string(score)).c_str());
		scoreWindow->RunAppModal();
	};
}

GUI_APP_MAIN
{
	MainMenuDlg* menu = new MainMenuDlg();
	menu->Run();
}
