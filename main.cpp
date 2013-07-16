#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include "OpenGL.h"

using namespace std;

#include "KeyboardManager.h"
#include "MouseManager.h"
#include "SceneManager.h"
#include "StartMenu.h"
#include "Game.h"
#include "GameDecorator.h"
#include "XorShift.h"

void resize(int w, int h)
{
	/* ウィンドウ全体をビューポートにする */
	glViewport(0, 0, w, h);

	/* 透視変換行列の指定 */
	glMatrixMode(GL_PROJECTION);

	/* 透視変換行列の初期化 */
	glLoadIdentity();

	gluPerspective(30.0, (double)w / h, 1.0, 200.0);

	/* モデル・ビュー変換行列の指定 */
	glMatrixMode(GL_MODELVIEW);
}

void init()
{
	/* 初期設定 */
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	// 光源の特性の配列を宣言
	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f },
		light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f },
		light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };	

	// 最初の光源の特性指定
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	// 次の光源の特性指定
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

	XorShift::instance().setSeed(static_cast<unsigned int>(time(NULL)));

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void keyboard(unsigned char key, int x, int y)
{
	/* ESC か q をタイプしたら終了 */
	if(key == '\033' || key == 'q'){
		exit(0);
	}
}

void explain()
{
	cout << "☆ Batting Game ☆" << endl;
	cout << "----- 基本ルール -----" << endl;
	cout << "・奥にあるロボットアームが赤い枠の中に目掛けてボールを投げてきます。" << endl;
	cout << "・緑色の丸いカーソルとボールが重なったときバットを振っていれば\n　ボールを打ち返すことが出来ます。" << endl;
	cout << "・打ち返されたボールが落ちた場所によって加点されるスコアが変化します。" << endl;
	cout << "・全部で10球投げて、出来るだけ高いスコアを目指します。" << endl;
	cout << "----------------------" << endl;

	cout << '\n';
	cout << "----- 加点されるスコアについて -----" << endl;
	cout << "・加点されるスコアにはファール(foul)、ヒット(hit)、\n　ホームラン(homerun)があります。" << endl;
	cout << "・ファール(foul)は、具体的に線は引いていませんが、\n　あまり脇の方へ出るとファールとなり、加点は1点です。" << endl;
	cout << "・ヒット(hit)は、ボールを打ち返していて、\n　ファールでもホームランでもないものがヒットとなり、加点は2点です。" << endl;
	cout << "・ホームランは奥にある壁を越えるとホームランとなり、加点は3点です。" << endl;
	cout << "　ただし、壁の外側を通ったとしても、ファールとはならない場合があり、\n　ホームランとなる場合があります。" << endl;
	cout << "・空振り(strike)の場合は点数は加点されません" << endl;
	cout << "------------------------------------" << endl;

	cout << '\n';
	cout << "----- 使用するキー -----" << endl;
	cout << "○ボールを投げる関係" << endl;
	cout << "　t:" << "ボールを投げる" << endl;
	cout << "　y:" << "ボールをセットする(投げたあとこのキーを押さないと次のボールを投げられない)" << endl;
	cout << "　r:" << "スコアと残りのボールの数をリセットする" << endl;
	cout << "○ゲームの処理系" << endl;
	cout << "　p:" << "ポーズする" << endl;
	cout << "　q:" << "ゲームを終了する(ESCでも同じ効果がある)" << endl;
	cout << "○難易度調節系" << endl;
	cout << "　1:" << "難易度を簡単(easy)にする" << endl;
	cout << "　2:" << "難易度を普通(normal)にする" << endl;
	cout << "○バッティングフィールド(赤い枠)関係" << endl;
	cout << "　8:" << "バッティングフィールド(赤い枠)を狭くする" << endl;
	cout << "　9:" << "バッティングフィールド(赤い枠)を広くする" << endl;
	cout << "○使用するデバイス関係" << endl;
	cout << "　m:" << "マウスを使用する" << endl;
	cout << "　k:" << "キーボードを使用する" << endl;
	cout << "○当たり判定関係" << endl;
	cout << "　z:" << "遅延ありの当たり判定" << endl;
	cout << "　x:" << "遅延なしの当たり判定" << endl;
	cout << "○カメラ関係" << endl;
	cout << "　a:" << "左側に回り込んでいく" << endl;
	cout << "　d:" << "右側に回り込んでいく" << endl;
	cout << "　w:" << "上側に回り込んでいく" << endl;
	cout << "　s:" << "下側に回り込んでいく" << endl;
	cout << "　n:" << "近づいていく" << endl;
	cout << "　f:" << "遠のいていく" << endl;
	cout << "-------------------------" << endl;

	cout << '\n';
	cout << "----- 難易度について -----" << endl;
	cout << "・簡単(easy)では、スローボールとストレートを投げます。" << endl;
	cout << "　速度の差もそれほどなくそこまで難しくないと思います。\n　しかし3次元ということもあり、" << endl;
	cout << "　なかなか距離感が掴めないかと思いますが、それは慣れるしかありません。" << endl;
	cout << "・普通(normal)では、スローボールとストレートに加えて、カーブも投げます。" << endl;
	cout << "　速度の差もかなりあり、打ちにくいかもしれません。\n　カーブは変化の量がかなり大きく、" << endl;
	cout << "　慣れるまでは全く打てないかもしれません。" << endl;
	cout << "　'8'キーを押してバッティングフィールド(赤い枠)を狭くするのも手です。" << endl;
	cout << "--------------------------" << endl;

	cout << '\n';
	cout << "----- 使用できるデバイスについて -----" << endl;
	cout << "基本的にはマウスを使ってゲームをすることを勧めますが、" << endl;
	cout << "ノートパソコンのようにタッチパッドを使って\nゲームをするとやりにくい場合があります。" << endl;
	cout << "そこでキーボードでもゲームが出来るようにしました。" << endl;
	cout << "使用するデバイスをマウスやキーボードにする方法は" << endl;
	cout << "上記にある\"使用するキー\"の\"使用するデバイス関係\"のところを参照してください。" << endl;
	cout << "--------------------------------------" << endl;

	cout << '\n';
	cout << "----- バットを振る方法、カーソル(緑色の円)を動かす方法 -----" << endl;
	cout << "○マウスを使用" << endl;
	cout << "　バットを振る:左クリック" << endl;
	cout << "　カーソルを動かす:バッティングフィールド(赤い枠)内でマウスカーソルを動かす" << endl;
	cout << "○キーボードを使用" << endl;
	cout << "　バットを振る:スペースキー" << endl;
	cout << "　カーソルを動かす:矢印キー" << endl;
	cout << "------------------------------------------------------------" << endl;

	cout << '\n';
	cout << "----- 当たり判定について -----" << endl;
	cout << "本来ならバットとボールが当たった時にボールを打ち返すべきですが、" << endl;
	cout << "ゲーム中どうしてもボールがカーソル(緑色の円)に来た時にバットを振ってしまい、" << endl;
	cout << "空振りをしてしまう場合が多いです。" << endl;
	cout << "そのため、バットを振ると入力してすぐに\n当たり判定を行う方法を出来るようにしました。" << endl;
	cout << "それは起動時からそのようになっています。" << endl;
	cout << "ちゃんとバットとボールが当たるタイミングで当たり判定をしたい場合は" << endl;
	cout << "'z'キーを入力すれば出来ます。" << endl;
	cout << "起動時からある機能に戻したい場合は'x'キーを押して下さい。" << endl;
	cout << "------------------------------" << endl;

}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(400, 300);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow(argv[0]);
	glutReshapeFunc(resize);

	KeyboardManager::getInstance().useCharKeyboard();
	KeyboardManager::getInstance().useSpecialKeyboard();
	KeyboardManager::getInstance().setKeyboardHandlar(keyboard);

	MouseManager::getInstance().useMouse();

	SceneManager::getInstance().setScene(new GameDecorator());

	init();
	explain();
	glutMainLoop();
	return 0;
}