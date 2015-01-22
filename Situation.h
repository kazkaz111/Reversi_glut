/******************************************************************************
*
*	�틵�N���X�錾	[main.cpp]
*	Author:			AT11D243 22 ���c��u
*
******************************************************************************/

/******************************************************************************
	�C���N���[�h�K�[�h
******************************************************************************/
#ifndef __SITUATION_H__
#define __SITUATION_H__

/******************************************************************************
	�C���N���[�h�t�@�C��
******************************************************************************/
#include "Definitions.h"

/******************************************************************************
	�N���X�錾
******************************************************************************/
/*�p����*/
class Situation
{
public:
	/*�}�X�ڂ̏��*/
	enum Cell : short
	{
		CellNon	= 0,	/*false*/
		CellBlack,
		CellWhite
	};
	/*�ǂ���̃^�[����*/
	enum Turn : short
	{
		TurnBlack,
		TurnWhite
	};
	/*����\���N���X�E�p����*/
	class Move{
	public:
		/*�쐬�p*/
		static Move To(Turn in_turn, const short in_x, const short in_y);
		short x,y;	/*���W*/
		Turn turn;	/*�ǂ���̃^�[����*/
	};
	/*�R���X�g���N�^(�Ֆʏ�����)*/
	Situation(void);
	/*�f�X�g���N�^*/
	virtual ~Situation(void);
	/*���̍��W�̏�Ԃ𓾂�*/
	Cell get(const short x, const short y) const throw();
	/*���̏ꏊ�ɐ΂�u���邩���m�F���A�u������true��Ԃ������̃|�C���^�̐������������B(�������g�̃|�C���^��)*/
	bool move(Situation* target, const Move move) throw();
	/*���̐틵�ł��̃^�[���ɂƂ��Đ΂�������Ƃ��낪���邩�ǂ���*/
	bool can_move(const Turn turn) const throw();
	/*���݂̐틵�𓾂�*/
	void get_condition(short *Black_num, short *white_num) const throw();
	/*�틵��������*/
	bool operator==(const Situation& in) const throw();
	/*�\�[�g�p�E��r���Z�q*/
	bool operator<(const Situation& in) const throw();
protected:
	/*�Q�[���{�[�h�̏��*/
	Cell board[Definition::BOARDSIZE][Definition::BOARDSIZE];
};

/*******************************************************************************
	�C���N���[�h�K�[�h
*******************************************************************************/
#endif