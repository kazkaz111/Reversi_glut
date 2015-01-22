/******************************************************************************
*
*	�틵�N���X����	[Situation.cpp]
*	Author:			AT11D243 22 ���c��u
*
*******************************************************************************/


/*******************************************************************************
	�C���N���[�h�t�@�C��
*******************************************************************************/
#include <memory>
#include "Definitions.h"
#include "Situation.h"

/*******************************************************************************
	����
*******************************************************************************/
/*Situation::Move�N���X(���̓���)*/


/*�ϊ��p*/
Situation::Move Situation::Move::To(Turn in_turn, const short in_x, const short in_y)
{
	/*�ϐ��錾*/
	Move temporary;
	/*���*/
	temporary.turn	=	in_turn;
	temporary.x		=	in_x;
	temporary.y		=	in_y;
	/*���ʂ�Ԃ�*/
	return temporary;
};

/*�f�t�H���g�R���X�g���N�^(�R���X�g���N�^�͂���̂�)*/
Situation::Situation(void)
{
	/*�f�[�^�̃[���N���A(����)*/
	memset(&(this->board), 0, sizeof(Situation::Cell)*Definition::BOARDSIZE*Definition::BOARDSIZE);
	/*�΂̏����z�u*/
	this->board[3][3] = CellBlack;
	this->board[3][4] = CellWhite;
	this->board[4][3] = CellWhite;
	this->board[4][4] = CellBlack;
	/*�߂�*/
	return;
}

/*�������Ȃ��f�X�g���N�^(�p���p)*/
Situation::~Situation(void)
{
	return;
}

/*���̍��W�̏�Ԃ𓾂�*/
Situation::Cell Situation::get(const short x, const short y) const throw()
{
	return this->board[x][y];
}


/*���̏ꏊ�ɐ΂�u���邩���m�F���A�u������true��Ԃ������̃|�C���^�̐������������B(�������g�̃|�C���^��)*/
bool Situation::move(Situation* target, const Move move) throw()
{
	/*�ϐ��錾*/
	short	current_x, current_y;
	short	distance_result;
	bool	puted;
	Cell	my_celltype,target_celltype;
	/*�ϐ�������*/
	puted = false;
	/*����������Ɏ��g�̌��݂̏󋵂��R�s�[*/
	if(this != target) *target = *this;
	/*�������łɐ΂��u����Ă����甲����*/
	if(target->board[move.x][move.y] != Situation::CellNon) return false;
	/*���ސ΂̎�ނƎ����̐΂̎��*/
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
	/*�S�Ă̕����ɂ��čs��*/
	for(short direction_x = -1; direction_x <= 1; direction_x++ )
	{
		for(short direction_y = -1; direction_y <= 1; direction_y++ )
		{
			/*������������0���������蒼��*/
			if((!direction_x) && (!direction_y)) continue;
			/*���̕����̈��̍��W*/
			current_x = move.x + direction_x;
			current_y = move.y + direction_y;
			/*���̍��W���Ղ���͂ݏo���Ă��Ȃ����`�F�b�N���A�͂ݏo���Ă������蒼��*/
			if((current_x < 0) || (Definition::BOARDSIZE < current_x) || (current_y < 0) || (Definition::BOARDSIZE < current_y))
				continue;
			/*���̍��W�ɋ��߂���̂����邩�`�F�b�N���A�Ȃ���΂�蒼��*/
			if(target->board[current_x][current_y] != target_celltype) continue;
			/*���߂鋗�����߂��Ƃ��납�璲�ׂĂ���*/
			/*�ǂꂭ�炢�̋������߂邩���ʂ�distance_result�ɁE�����̐΂��Ȃ��ċ��߂Ȃ�������-1*/
			for(short distance = 2; ; distance++ )
			{
				/*���ݒ��ׂĂ�����W*/
				current_x = move.x + direction_x * distance;
				current_y = move.y + direction_y * distance;
				/*�Ղ̒��łȂ�������distance_result��-1������������*/
				if(((current_x) < 0) || (Definition::BOARDSIZE < (current_x)) ||
					((current_y) < 0) || (Definition::BOARDSIZE < (current_y)))
				{
					distance_result = -1;
					break;
				}
				/*���������̐΂�������A���߂�̂Ō��ʂ������A������*/
				if(target->board[current_x][current_y] == my_celltype)
				{
					distance_result = distance;
					break;
				}
				/*��������̐΂�������A���ב�����*/
				else if(target->board[current_x][current_y] == target_celltype)
				{
					continue;
				}
				/*�΂��Ȃ�������Adistace_result��-1�������A������*/
				else
				{
					distance_result = -1;
					break;
				}
			}
			/*��������ł�����*/
			if(distance_result != -1)
			{
				/*����ł����t���O��true��*/
				puted = true;
				/*����ł���Ԃ̐΂�ς���*/
				for(short change_distance = 1;change_distance <= (distance_result - 1); change_distance++)
				{
					/*���ݒ��ׂĂ�����W*/
					current_x = move.x + direction_x * change_distance;
					current_y = move.y + direction_y * change_distance;
					/*���W�ɑ��*/
					target->board[current_x][current_y] = my_celltype;
				}
			}
		}
	}
	/*�����΂��u����Ă�����A�΂�u��(�f�[�^�ɏ�������)*/
	if(puted) target->board[move.x][move.y] = move.turn == Situation::TurnBlack ? Situation::CellBlack : Situation::CellWhite;
	return puted;
}

/*���̃^�[���ɐ΂�������ꏊ�����邩�ǂ���*/
bool Situation::can_move(const Turn turn) const throw()
{
	/* �΂�u���邩�S�Ă̍��W�ɂ��Ċm���߂� */
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
	/*�[���N���A*/
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

/*�틵���������ǂ���*/
bool Situation::operator==(const Situation& in) const throw()
{
	/*���W����Â��ׂĂ����A��ł��������false��Ԃ�*/
	for(short x = 0; x < Definition::BOARDSIZE; x++)
	{
		for(short y = 0; y < Definition::BOARDSIZE; y++)
		{
			if(this->board[x][y] != in.board[x][y]) return false;
		}
	}
	return true;
}

/*�\�[�g�p*/
bool Situation::operator<(const Situation& in) const throw()
{
	/*���W����Â��ׂĂ����A��̌��̍���D�悵�đ召�𔻒f����*/
	for(short x = 0; x < Definition::BOARDSIZE; x++)
	{
		for(short y = 0; y < Definition::BOARDSIZE; y++)
		{
			if(this->board[x][y] < in.board[x][y]) return true;
		}
	}
	return false;
}