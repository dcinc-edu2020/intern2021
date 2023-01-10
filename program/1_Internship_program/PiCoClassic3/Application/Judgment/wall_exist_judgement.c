/*==============================================================================*/
/* Wall Exist Judgement C File							*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "sensor_driver.h"
#include "wall_exist_judgement.h"

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* 壁があるか否かの閾値 */
#define THRESHOLD_R_WALL	(TH_SEN_R)	// 右壁判定用閾値
#define THRESHOLD_L_WALL	(TH_SEN_L)	// 左壁判定用閾値
#define THRESHOLD_FR_WALL	(TH_SEN_FR)	// 右前壁判定用閾値
#define THRESHOLD_FL_WALL	(TH_SEN_FL)	// 左前壁判定用閾値


/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/*  前壁検知				                                        */
/* 										*/
/*  左右の前方物標距離から、前壁の有無を判断する				*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		front_right_distance	右前方物標距離		       	*/
/*  			front_left_distance	左前方物標距離			*/
/*  Return   :         	existence_front_wall	前壁有無			*/
/*			(WALL / NO_WALL)				        */
/*==============================================================================*/
int judgement_existence_front_wall(int front_right_distance, int front_left_distance)
{
	int existence_front_wall = WALL;		// 初期値は壁有りに設定
		
	// 前壁の有無を判断
	if( (front_right_distance < THRESHOLD_FR_WALL) && (front_left_distance < THRESHOLD_FL_WALL) )
	{
		existence_front_wall =  NO_WALL;	// 壁無し
	}
	
	return existence_front_wall;
}

/*==============================================================================*/
/*  左壁検知				                                        */
/* 										*/
/*  左側物標距離から、左壁の有無を判断する					*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		leftside_distance	左側物標距離		       	*/
/*  Return   :         	existence_left_wall	左壁有無			*/
/*			(WALL / NO_WALL)				        */
/*==============================================================================*/
int judgement_existence_left_wall(int leftside_distance)
{
	int existence_left_wall = WALL;		// 初期値は壁有りに設定
	
	// 左壁の有無を判断
	if(leftside_distance < THRESHOLD_L_WALL)
	{
		existence_left_wall = NO_WALL;		// 壁無し
	}
	
	return existence_left_wall;
}

/*==============================================================================*/
/*  右壁検知				                                        */
/* 										*/
/*  右壁物標距離から、右壁の有無を判断する					*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		rightside_dictance	右側物標距離		       	*/
/*  Return   :         	existence_right_wall	右壁有無			*/
/*			(WALL / NO_WALL)				        */
/*==============================================================================*/
int judgement_existence_right_wall(int rightside_dictance)
{
	int existence_right_wall = WALL;		// 初期値は壁有りに設定
	
	// 右壁の有無を判断
	if(rightside_dictance < THRESHOLD_R_WALL)	
	{
		existence_right_wall = NO_WALL;		// 壁無し
	}
	
	return existence_right_wall;
}