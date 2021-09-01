/*==============================================================================*/
/* Main C File(for unit test)							*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "wall_exist_judgement.h"
#include "goal_judgement.h"

/*------------------------------------------------------------------------------*/
/* Function prototype								*/
/*------------------------------------------------------------------------------*/
void main(void);				// メイン関数

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* メイン関数									*/
/* 										*/
/* 単体テスト用コードを記述する							*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void main(void)
{
	int front,left,right;  // 関数の引数指定
	int result;            // 関数の戻り値

	// 引数を設定
	front  = NO_WALL;
	left   = NO_WALL;
	right  = NO_WALL;
	result = -1;

	// 単体テスト対象関数の呼び出し
	result = judgement_goal( front, left, right );

	return;
}
