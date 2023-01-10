/*==============================================================================*/
/* Run Mode Judgement C File							*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "goal_judgement.h"
#include "wall_exist_judgement.h"
#include "tire_control.h"
#include "run_mode_judgement.h"

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/*  走行モード決定			                                        */
/* 										*/
/*  進行方向を決定する								*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		existence_front_Wall	前壁有無		       	*/
/*  			existence_left_wall	左壁有無			*/
/*  			existence_right_wall	右壁有無			*/
/*  	         	goal_judgment_result	ゴール判定結果			*/
/*  Return   :         	-							*/
/*==============================================================================*/
void judgement_run_mode(int existence_front_wall, int existence_left_wall, int existence_right_wall, int goal_judgement_result)
{
	/* 走行モードの決定 */
	if(goal_judgement_result == GOAL)			
	{	
		set_run_mode(Stop);		// ゴールなら停止
		return;
	}
	
	if(existence_left_wall == NO_WALL)		// 左に壁が無いなら左旋回
	{	
		set_run_mode(TurnLeft);
	}
	else if(existence_front_wall == NO_WALL)	// 前に壁が無いなら前進
	{	
		set_run_mode(Forward);
	}
	else if(existence_right_wall == NO_WALL)	// 右に壁が無いなら右旋回
	{	
		set_run_mode(TurnRight);
	}
	else						// 3方向のいずれにも壁が有る場合は反転
	{
		set_run_mode(Reverse);
	}
	
	return;
}