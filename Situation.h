/******************************************************************************
*
*	戦況クラス宣言	[main.cpp]
*	Author:			AT11D243 22 中田一志
*
******************************************************************************/

/******************************************************************************
	インクルードガード
******************************************************************************/
#ifndef __SITUATION_H__
#define __SITUATION_H__

/******************************************************************************
	インクルードファイル
******************************************************************************/
#include "Definitions.h"

/******************************************************************************
	クラス宣言
******************************************************************************/
/*継承可*/
class Situation
{
public:
	/*マス目の状態*/
	enum Cell : short
	{
		CellNon	= 0,	/*false*/
		CellBlack,
		CellWhite
	};
	/*どちらのターンか*/
	enum Turn : short
	{
		TurnBlack,
		TurnWhite
	};
	/*一手を表すクラス・継承可*/
	class Move{
	public:
		/*作成用*/
		static Move To(Turn in_turn, const short in_x, const short in_y);
		short x,y;	/*座標*/
		Turn turn;	/*どちらのターンか*/
	};
	/*コンストラクタ(盤面初期化)*/
	Situation(void);
	/*デストラクタ*/
	virtual ~Situation(void);
	/*その座標の状態を得る*/
	Cell get(const short x, const short y) const throw();
	/*その場所に石を置けるかを確認し、置けたらtrueを返し引数のポインタの先を書き換える。(自分自身のポインタ可)*/
	bool move(Situation* target, const Move move) throw();
	/*今の戦況でそのターンにとって石をおけるところがあるかどうか*/
	bool can_move(const Turn turn) const throw();
	/*現在の戦況を得る*/
	void get_condition(short *Black_num, short *white_num) const throw();
	/*戦況が同じか*/
	bool operator==(const Situation& in) const throw();
	/*ソート用・比較演算子*/
	bool operator<(const Situation& in) const throw();
protected:
	/*ゲームボードの状態*/
	Cell board[Definition::BOARDSIZE][Definition::BOARDSIZE];
};

/*******************************************************************************
	インクルードガード
*******************************************************************************/
#endif