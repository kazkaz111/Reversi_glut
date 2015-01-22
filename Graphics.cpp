/*******************************************************************************
*	�^�C�g��:	�I�Z���Q�[��(glut��)�`��p�֐��Q
*	�t�@�C����:	Graphics.cpp
*	�쐬��:		���c��u
*	�쐬��:		2014/11/02
*******************************************************************************/

/*******************************************************************************
	�R���\�[���E�C���h�E��\�����Ȃ�
*******************************************************************************/
#ifdef _WIN32
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif

/*******************************************************************************
*	�C���N���[�h�t�@�C��
*******************************************************************************/
#include <cmath>
#include <string>
#include <sstream>
#include <GL/glut.h>
#include "Definitions.h"
#include "Situation.h"
#include "Graphics.h"

/*******************************************************************************
*	�}�N����`
*******************************************************************************/

/*******************************************************************************
*	�\���̂̒�`
*******************************************************************************/

/*******************************************************************************
*	�O���[�o���ϐ�
*******************************************************************************/
extern Situation g_gameBoard;
extern Situation::Turn g_turn;
std::string g_message;
bool g_end = false;

/*******************************************************************************
*	�֐���:	void myGlutSetting( int *p_argc , char *argv[] )
*			glut�̗l�X�ȃZ�b�e�B���O������
*	����:	�Ȃ�
*	�߂�l:	�Ȃ�
*	����:	glut�̃Z�b�e�B���O(�E�C���h�E�T�C�Y��)
*******************************************************************************/
void myGlutSetting( int *p_argc , char *argv[] )
{
	using namespace Definition;
	/* �E�C���h�E�T�C�Y�̐ݒ� */
	glutInitWindowSize( WINDOW_SIZE , WINDOW_SIZE );
	/* glut������ */
	glutInit( p_argc , argv );
	/* RGB���[�h */
	glutInitDisplayMode( GLUT_RGB );
	/* �E�C���h�E�쐬 */
	glutCreateWindow( argv[0] );
	/* �`��֐��̐ݒ� */
	glutDisplayFunc( display );
	/* �E�C���h�E���T�C�Y���̐ݒ� */
	glutReshapeFunc( resize );
	/* �}�E�X�������ꂽ�Ƃ��̏��� */
	glutMouseFunc( mouse );
	/* �w�i�F�̐ݒ� */
	glClearColor( WINDOW_COLOR_R , WINDOW_COLOR_G , WINDOW_COLOR_B , WINDOW_COLOR_A );
}

/*******************************************************************************
*	�֐���:	void display( void )
*			�`��֐�
*	����:	�Ȃ�
*	�߂�l:	�Ȃ�
*	����:	glut�ɓo�^����`��֐�
*******************************************************************************/
void display( void )
{
	glClear( GL_COLOR_BUFFER_BIT );
	if( g_message.empty() )
	{
		/* �Ֆʂ̐��̕`�� */
		drawLines( );
		/* �΂̔z�u*/
		drawStones( );
	}
	else
	{
		/* ���b�Z�[�W����������\�� */
		drawMessage( );
	}
	/* �`�挋�ʂ̔��f */
	glFlush();
}

/*******************************************************************************
*	�֐���:	void drawMessage( void )
*			�`��֐�
*	����:	�Ȃ�
*	�߂�l:	�Ȃ�
*	����:	�����̕`��֐�
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
*	�֐���:	void drawLines( void )
*			�`��֐�
*	����:	�Ȃ�
*	�߂�l:	�Ȃ�
*	����:	�Ֆʂ̐���`��
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
*	�֐���:	void drawStones( void )
*			�`��֐�
*	����:	�Ȃ�
*	�߂�l:	�Ȃ�
*	����:	�Տ�̐΂�`��
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
*	�֐���:	void resize( int width , int height )
*			�E�C���h�E�T�C�Y�ύX��
*	����:	width	:�ύX���ꂽ�E�C���h�E�̉��T�C�Y
*			height	:�ύX���ꂽ�E�C���h�E�̏c�T�C�Y
*	�߂�l:	�Ȃ�
*	����:	�E�C���h�E�T�C�Y�͌Œ�
*******************************************************************************/
void resize( int width , int height )
{
	glutReshapeWindow( Definition::WINDOW_SIZE , Definition::WINDOW_SIZE );
	return;
}

/*******************************************************************************
*	�֐���:	void mouse( int button, int state, int x, int y )
*			�}�E�X�����͂��ꂽ���ɌĂяo�����֐�
*	����:	button	:�ǂ̃{�^���������ꂽ��
*			state	:�ǂ�ȏ�ԂɂȂ�����
*			x		:�}�E�X�̍��Wx
*			y		:�}�E�X�̍��Wy
*	�߂�l:	�Ȃ�
*	����:	�}�E�X�������ꂽ���ɐ΂�u���B
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
			/* �p�X���邩 */
			if( !g_gameBoard.can_move( g_turn ) )
			{
				g_turn = g_turn == Situation::TurnBlack ? Situation::TurnWhite : Situation::TurnBlack;
				if( !g_gameBoard.can_move( g_turn ) )
				{
					/* ���ʕ\�� */
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
