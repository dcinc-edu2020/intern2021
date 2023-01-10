/*==============================================================================*/
/* Judgement Module C File							*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "distance_recognition.h"
#include "wall_exist_judgement.h"
#include "goal_judgement.h"
#include "run_mode_judgement.h"
#include "judgement_module.h"

/*------------------------------------------------------------------------------*/
/* Externs Variable								*/
/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* 判断					                                        */
/* 										*/
/* 認知グループから与えられる情報をもとに、マイクロマウスの移動させるための	*/
/* 出力を制御する先を座標単位で判断する						*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void judgement(void)
{
	int existence_right_wall;	// 右壁有無判断結果
	int existence_left_wall;	// 左壁有無判断結果
	int existence_front_wall;	// 前壁有無判断結果
	int goal_judgement_result;	// ゴール判定結果
	
	/* 壁検知 */
	existence_right_wall = judgement_existence_right_wall(rightside_dictance);			// 右壁検知
	existence_left_wall  = judgement_existence_left_wall(leftside_distance);			// 左壁検知
	existence_front_wall = judgement_existence_front_wall(front_left_distance, front_right_distance);// 前壁検知

	/* ゴール検知 */ 
	goal_judgement_result = judgement_goal(existence_front_wall, existence_left_wall, existence_right_wall);
	
	/* 走行モード決定 */
	judgement_run_mode(existence_front_wall, existence_left_wall, existence_right_wall, goal_judgement_result);

	return;
}