/*==============================================================================*/
/* Judgement Module C File							*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "Application/Judgement/wall_exist_judgement.h"
#include "Application/Judgement/goal_judgement.h"
#include "Application/Judgement/run_info_judgement.h"
#include "Application/Judgement/judgement_module.h"

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* 判断コンポーネントグループの初期化						*/
/* ---------------------------------------------------------------------------- */
/*  入力:		-							*/
/*  出力:		-							*/
/*==============================================================================*/
void init_judgement(void)
{
	init_wall_exist_judgement();
	init_goal_judgement();
	init_run_info_judgement();

	return;
}

/*==============================================================================*/
/* 判断										*/
/* 										*/
/* 認知グループから与えられる情報をもとに、マイクロマウスの移動させるための	*/
/* 出力を制御する先を座標単位で判断する						*/
/* ---------------------------------------------------------------------------- */
/*  入力:		-							*/
/*  出力:		-							*/
/*==============================================================================*/
void judgement(void)
{
	/* 壁検知 */
	judgement_existence_right_wall();	// 右壁検知
	judgement_existence_left_wall();	// 左壁検知
	judgement_existence_front_wall();	// 前壁検知

	/* ゴール検知 */ 
	judgement_goal();
	
	/* 走行指示情報決定 */
	judgement_run_info();

	return;
}
