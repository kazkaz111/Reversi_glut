/*******************************************************************************
*
*	定数宣言:	[Definitions.h]
*	Author:		AT11D243 22 中田一志	
*
*******************************************************************************/

/*******************************************************************************
	インクルードガード
*******************************************************************************/
#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

/*******************************************************************************
	定数宣言
*******************************************************************************/
namespace Definition
{
	/*ボードのマス目縦横*/
	const short BOARDSIZE			=	8;
	/*ウィンドウの大きさX*/
	const int	WINDOW_SIZE			=	400;
	/*ウィンドウの背景色*/
	const float	WINDOW_COLOR_R		=	0.0f;
	const float	WINDOW_COLOR_G		=	1.0f;
	const float	WINDOW_COLOR_B		=	0.0f;
	const float	WINDOW_COLOR_A		=	1.0f;
	/*マス目を区切る色*/
	const float	LINE_COLOR_R		=	0.0f;
	const float	LINE_COLOR_G		=	0.0f;
	const float	LINE_COLOR_B		=	0.0f;
	const float	LINE_COLOR_A		=	1.0f;
	/*黒い石の色*/
	const float	BLACKSTONE_COLOR_R	=	0.0f;
	const float	BLACKSTONE_COLOR_G	=	0.0f;
	const float	BLACKSTONE_COLOR_B	=	0.0f;
	const float	BLACKSTONE_COLOR_A	=	1.0f;
	/*白い石の色*/
	const float	WHITESTONE_COLOR_R	=	1.0f;
	const float	WHITESTONE_COLOR_G	=	1.0f;
	const float	WHITESTONE_COLOR_B	=	1.0f;
	const float	WHITESTONE_COLOR_A	=	1.0f;
	/* 文字の色 */
	const float MES_COLOR_R			=	1.0f;
	const float MES_COLOR_G			=	0.0f;
	const float MES_COLOR_B			=	0.0f;
	const float MES_COLOR_A			=	1.0f;
	/* 円周率 */
	const float PI					=	3.14f;
}

/*******************************************************************************
	インクルードガード
*******************************************************************************/
#endif