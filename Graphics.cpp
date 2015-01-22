/*******************************************************************************
*	タイトル:	オセロゲーム(glut版)描画用関数群
*	ファイル名:	Graphics.cpp
*	作成者:		中田一志
*	作成日:		2014/11/02
*******************************************************************************/

/*******************************************************************************
	コンソールウインドウを表示しない
*******************************************************************************/
#ifdef _WIN32
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif

/*******************************************************************************
*	インクルードファイル
*******************************************************************************/
#include <cmath>
#include <string>
#include <sstream>
#include <GL/glut.h>
#include "Definitions.h"
#include "Situation.h"
#include "Graphics.h"

/*******************************************************************************
*	マクロ定義
*******************************************************************************/

/*******************************************************************************
*	構造体の定義
*******************************************************************************/

/*******************************************************************************
*	グローバル変数
*******************************************************************************/
extern Situation g_gameBoard;
extern Situation::Turn g_turn;
std::string g_message;
bool g_end = false;

/*******************************************************************************
*	関数名:	void myGlutSetting( int *p_argc , char *argv[] )
*			glutの様々なセッティングをする
*	引数:	なし
*	戻り値:	なし
*	説明:	glutのセッティング(ウインドウサイズ等)
*******************************************************************************/
void myGlutSetting( int *p_argc , char *argv[] )
{
	using namespace Definition;
	/* ウインドウサイズの設定 */
	glutInitWindowSize( WINDOW_SIZE , WINDOW_SIZE );
	/* glut初期化 */
	glutInit( p_argc , argv );
	/* RGBモード */
	glutInitDisplayMode( GLUT_RGB );
	/* ウインドウ作成 */
	glutCreateWindow( argv[0] );
	/* 描画関数の設定 */
	glutDisplayFunc( display );
	/* ウインドウリサイズ時の設定 */
	glutReshapeFunc( resize );
	/* マウスが押されたときの処理 */
	glutMouseFunc( mouse );
	/* 背景色の設定 */
	glClearColor( WINDOW_COLOR_R , WINDOW_COLOR_G , WINDOW_COLOR_B , WINDOW_COLOR_A );
}

/*******************************************************************************
*	関数名:	void display( void )
*			描画関数
*	引数:	なし
*	戻り値:	なし
*	説明:	glutに登録する描画関数
*******************************************************************************/
void display( void )
{
	glClear( GL_COLOR_BUFFER_BIT );
	if( g_message.empty() )
	{
		/* 盤面の線の描画 */
		drawLines( );
		/* 石の配置*/
		drawStones( );
	}
	else
	{
		/* メッセージがあったら表示 */
		drawMessage( );
	}
	/* 描画結果の反映 */
	glFlush();
}

/*******************************************************************************
*	関数名:	void drawMessage( void )
*			描画関数
*	引数:	なし
*	戻り値:	なし
*	説明:	文字の描画関数
*******************************************************************************/
void drawMessage( void )
{
	using namespace Definition;
	glColor3f( MES_COLOR_R , MES_COLOR_G , MES_COLOR_B );
	glRasterPos3d( -1.0, -1.0, 0.0);
	const char *c = g_message.c_str();
	while( *c )
	{
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24 , *c );
		c++;
	}
	return;
}

/*******************************************************************************
*	関数名:	void drawLines( void )
*			描画関数
*	引数:	なし
*	戻り値:	なし
*	説明:	盤面の線を描く
*******************************************************************************/
void drawLines( void )
{
	using namespace Definition;
	glColor3f( LINE_COLOR_R , LINE_COLOR_G , LINE_COLOR_B );
	glBegin( GL_LINES );
	for( int cnt_x = 1; cnt_x <= ( BOARDSIZE - 1 ); cnt_x++ )
	{
		glVertex2d( ( cnt_x * 2.0 / BOARDSIZE ) - 1.0 , 1.0 );
		glVertex2d( ( cnt_x * 2.0 / BOARDSIZE ) - 1.0 , -1.0 );
	}
	for( int cnt_y = 1; cnt_y <= ( BOARDSIZE - 1 ); cnt_y++ )
	{
		glVertex2d( 1.0 , ( cnt_y *  2.0 / BOARDSIZE ) - 1.0  );
		glVertex2d( -1.0 , ( cnt_y *  2.0 / BOARDSIZE ) - 1.0  );
	}
	glEnd();
	return;
}

/*******************************************************************************
*	関数名:	void drawStones( void )
*			描画関数
*	引数:	なし
*	戻り値:	なし
*	説明:	盤上の石を描く
*******************************************************************************/
void drawStones( void )
{
	using namespace Definition;
	for( int cnt_x = 0; cnt_x < BOARDSIZE; cnt_x++ )
	{
		for( int cnt_y = 0; cnt_y < BOARDSIZE; cnt_y++ )
		{
			switch( g_gameBoard.get( cnt_x , cnt_y ) )
			{
			case Situation::CellBlack:
				glColor3f( BLACKSTONE_COLOR_R , BLACKSTONE_COLOR_G , BLACKSTONE_COLOR_B );
				glBegin( GL_POLYGON );
				break;
			case Situation::CellWhite:
				glColor3f( WHITESTONE_COLOR_R , WHITESTONE_COLOR_G , WHITESTONE_COLOR_B );
				glBegin( GL_POLYGON );
				break;
			default:
				continue;
				break;
			}
			float center_x = ( cnt_x * ( 2.0 / BOARDSIZE ) ) - 1.0 + ( 2.0 / ( BOARDSIZE * 2 ) );
			float center_y = ( cnt_y * ( 2.0 / BOARDSIZE ) ) - 1.0 + ( 2.0 / ( BOARDSIZE * 2 ) );
			for( float angle = 0.0f; angle < ( 2 * PI ); angle += ( PI / 10 ) )
			{
				glVertex2d( center_x + ( cos( angle ) * ( 2.0 / ( BOARDSIZE * 2 ) ) ) ,
					center_y + ( sin( angle ) * ( 2.0 / ( BOARDSIZE * 2 ) ) ) );
			}
			glEnd( );
		}
	}
	return;
}

/*******************************************************************************
*	関数名:	void resize( int width , int height )
*			ウインドウサイズ変更時
*	引数:	width	:変更されたウインドウの横サイズ
*			height	:変更されたウインドウの縦サイズ
*	戻り値:	なし
*	説明:	ウインドウサイズは固定
*******************************************************************************/
void resize( int width , int height )
{
	glutReshapeWindow( Definition::WINDOW_SIZE , Definition::WINDOW_SIZE );
	return;
}

/*******************************************************************************
*	関数名:	void mouse( int button, int state, int x, int y )
*			マウスが入力された時に呼び出される関数
*	引数:	button	:どのボタンが押されたか
*			state	:どんな状態になったか
*			x		:マウスの座標x
*			y		:マウスの座標y
*	戻り値:	なし
*	説明:	マウスが押された時に石を置く。
*******************************************************************************/
void mouse( int button, int state, int x, int y )
{
	using namespace Definition;
	if( button != GLUT_LEFT_BUTTON || state != GLUT_DOWN ) return;
	if( g_end ) exit( 0 );
	if( g_message.empty() )
	{
		if( g_gameBoard.move( &g_gameBoard ,
			Situation::Move::To( g_turn , x / ( WINDOW_SIZE / BOARDSIZE ) , ( WINDOW_SIZE - y ) / (WINDOW_SIZE / BOARDSIZE) ) ) )
		{
			g_turn = g_turn == Situation::TurnBlack ? Situation::TurnWhite : Situation::TurnBlack;
			/* パスするか */
			if( !g_gameBoard.can_move( g_turn ) )
			{
				g_turn = g_turn == Situation::TurnBlack ? Situation::TurnWhite : Situation::TurnBlack;
				if( !g_gameBoard.can_move( g_turn ) )
				{
					/* 結果表示 */
					std::stringstream stream;
					short blackNum , whiteNum;
					g_gameBoard.get_condition( &blackNum , &whiteNum );
					stream << "end_black:" << blackNum << "_" << "white:" << whiteNum;
					stream >> g_message;
					g_end = true;
				}
				else
				{
					/* pass */
					g_message = "pass";
				}
			}
		}
	}
	else
	{
		g_message.clear( );
	}
	glutPostRedisplay( );
	return;
}
