/******************************************************************************
*
*	戦況クラス実装	[Situation.cpp]
*	Author:			AT11D243 22 中田一志
*
*******************************************************************************/


/*******************************************************************************
	インクルードファイル
*******************************************************************************/
#include <memory>
#include "Definitions.h"
#include "Situation.h"

/*******************************************************************************
	実装
*******************************************************************************/
/*Situation::Moveクラス(一手の動き)*/


/*変換用*/
Situation::Move Situation::Move::To(Turn in_turn, const short in_x, const short in_y)
{
	/*変数宣言*/
	Move temporary;
	/*代入*/
	temporary.turn	=	in_turn;
	temporary.x		=	in_x;
	temporary.y		=	in_y;
	/*結果を返す*/
	return temporary;
};

/*デフォルトコンストラクタ(コンストラクタはこれのみ)*/
Situation::Situation(void)
{
	/*データのゼロクリア(高速)*/
	memset(&(this->board), 0, sizeof(Situation::Cell)*Definition::BOARDSIZE*Definition::BOARDSIZE);
	/*石の初期配置*/
	this->board[3][3] = CellBlack;
	this->board[3][4] = CellWhite;
	this->board[4][3] = CellWhite;
	this->board[4][4] = CellBlack;
	/*戻る*/
	return;
}

/*何もしないデストラクタ(継承用)*/
Situation::~Situation(void)
{
	return;
}

/*その座標の状態を得る*/
Situation::Cell Situation::get(const short x, const short y) const throw()
{
	return this->board[x][y];
}


/*その場所に石を置けるかを確認し、置けたらtrueを返し引数のポインタの先を書き換える。(自分自身のポインタ可)*/
bool Situation::move(Situation* target, const Move move) throw()
{
	/*変数宣言*/
	short	current_x, current_y;
	short	distance_result;
	bool	puted;
	Cell	my_celltype,target_celltype;
	/*変数初期化*/
	puted = false;
	/*書き換え先に自身の現在の状況をコピー*/
	if(this != target) *target = *this;
	/*もしすでに石が置かれていたら抜ける*/
	if(target->board[move.x][move.y] != Situation::CellNon) return false;
	/*挟む石の種類と自分の石の種類*/
	if(TurnBlack == move.turn) 
	{
		my_celltype		=	CellBlack;
		target_celltype	=	CellWhite;
	}
	else
	{
		my_celltype		=	CellWhite;
		target_celltype	=	CellBlack;
	}
	/*全ての方向について行う*/
	for(short direction_x = -1; direction_x <= 1; direction_x++ )
	{
		for(short direction_y = -1; direction_y <= 1; direction_y++ )
		{
			/*方向が両方共0だったらやり直し*/
			if((!direction_x) && (!direction_y)) continue;
			/*その方向の一つ先の座標*/
			current_x = move.x + direction_x;
			current_y = move.y + direction_y;
			/*一つ先の座標が盤からはみ出していないかチェックし、はみ出していたらやり直し*/
			if((current_x < 0) || (Definition::BOARDSIZE < current_x) || (current_y < 0) || (Definition::BOARDSIZE < current_y))
				continue;
			/*次の座標に挟めるものがあるかチェックし、なければやり直し*/
			if(target->board[current_x][current_y] != target_celltype) continue;
			/*挟める距離を近いところから調べていく*/
			/*どれくらいの距離挟めるか結果をdistance_resultに・自分の石がなくて挟めなかったら-1*/
			for(short distance = 2; ; distance++ )
			{
				/*現在調べている座標*/
				current_x = move.x + direction_x * distance;
				current_y = move.y + direction_y * distance;
				/*盤の中でなかったらdistance_resultに-1を代入し抜ける*/
				if(((current_x) < 0) || (Definition::BOARDSIZE < (current_x)) ||
					((current_y) < 0) || (Definition::BOARDSIZE < (current_y)))
				{
					distance_result = -1;
					break;
				}
				/*もし自分の石だったら、挟めるので結果を代入し、抜ける*/
				if(target->board[current_x][current_y] == my_celltype)
				{
					distance_result = distance;
					break;
				}
				/*もし相手の石だったら、調べ続ける*/
				else if(target->board[current_x][current_y] == target_celltype)
				{
					continue;
				}
				/*石がなかったら、distace_resultに-1を代入し、抜ける*/
				else
				{
					distance_result = -1;
					break;
				}
			}
			/*もし挟んでいたら*/
			if(distance_result != -1)
			{
				/*挟んでいたフラグをtrueに*/
				puted = true;
				/*挟んでいる間の石を変える*/
				for(short change_distance = 1;change_distance <= (distance_result - 1); change_distance++)
				{
					/*現在調べている座標*/
					current_x = move.x + direction_x * change_distance;
					current_y = move.y + direction_y * change_distance;
					/*座標に代入*/
					target->board[current_x][current_y] = my_celltype;
				}
			}
		}
	}
	/*もし石が置かれていたら、石を置く(データに書き込む)*/
	if(puted) target->board[move.x][move.y] = move.turn == Situation::TurnBlack ? Situation::CellBlack : Situation::CellWhite;
	return puted;
}

/*そのターンに石がおける場所があるかどうか*/
bool Situation::can_move(const Turn turn) const throw()
{
	/* 石を置けるか全ての座標について確かめる */
	Situation tmp = *this;
	Move move;
	move.turn = turn;
	for( int current_y = 0; current_y <= Definition::BOARDSIZE; current_y++ )
	{
		for( int current_x = 0; current_x <= Definition::BOARDSIZE; current_x++ )
		{
			move.x = current_x;
			move.y = current_y;
			if( tmp.move( &tmp , move ) == true )
			{
				return true;
			}
		}
	}
	return false;
}

void Situation::get_condition(short *Black_num, short *white_num) const throw()
{
	/*ゼロクリア*/
	*Black_num	= 0;
	*white_num	= 0;
	for(short x = 0; x < Definition::BOARDSIZE; x++)
	{
		for(short y = 0; y < Definition::BOARDSIZE; y++)
		{
			switch(this->board[x][y])
			{
			case Situation::CellBlack:
				(*Black_num)++;
				break;
			case Situation::CellWhite:
				(*white_num)++;
				break;
			default:
				break;
			}
		}
	}
	return;
}

/*戦況が同じかどうか*/
bool Situation::operator==(const Situation& in) const throw()
{
	/*座標を一つづつ調べていき、一つでも違ったらfalseを返す*/
	for(short x = 0; x < Definition::BOARDSIZE; x++)
	{
		for(short y = 0; y < Definition::BOARDSIZE; y++)
		{
			if(this->board[x][y] != in.board[x][y]) return false;
		}
	}
	return true;
}

/*ソート用*/
bool Situation::operator<(const Situation& in) const throw()
{
	/*座標を一つづつ調べていき、上の桁の差を優先して大小を判断する*/
	for(short x = 0; x < Definition::BOARDSIZE; x++)
	{
		for(short y = 0; y < Definition::BOARDSIZE; y++)
		{
			if(this->board[x][y] < in.board[x][y]) return true;
		}
	}
	return false;
}