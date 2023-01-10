/*==============================================================================*/
/* Wall Exist Judgement C File							*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "DeviceDriver/Hardware/sensor_driver.h"
#include "Application/Recognition/distance_recognition.h"
#include "Application/Judgement/wall_exist_judgement.h"

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* 壁があるか否かの閾値 */
#define THRESHOLD_R_WALL	(TH_SEN_R)	// 右壁判定用閾値
#define THRESHOLD_L_WALL	(TH_SEN_L)	// 左壁判定用閾値
#define THRESHOLD_FR_WALL	(TH_SEN_FR)	// 右前壁判定用閾値
#define THRESHOLD_FL_WALL	(TH_SEN_FL)	// 左前壁判定用閾値

/*------------------------------------------------------------------------------*/
/* Global Variable								*/
/*------------------------------------------------------------------------------*/
int existence_front_wall;			// 前壁有無
int existence_left_wall;			// 左壁有無
int existence_right_wall;			// 右壁有無

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/*  初期化									*/
/* ---------------------------------------------------------------------------- */
/*  入力:		-							*/
/*  出力:		existence_front_wall	前壁有無			*/
/*			existence_left_wall	左壁有無			*/
/*			existence_right_wall	右壁有無			*/
/*==============================================================================*/
void init_wall_exist_judgement(void)
{
	existence_front_wall = NO_WALL;
	existence_left_wall = NO_WALL;
	existence_right_wall = NO_WALL;

	return;
}

/*==============================================================================*/
/*  前壁検知									*/
/* 										*/
/*  左右の前方物標距離から、前壁の有無を判断する				*/
/* ---------------------------------------------------------------------------- */
/*  入力:		front_right_distance	右前方物標距離			*/
/*			front_left_distance	左前方物標距離			*/
/*  出力:		existence_front_wall	前壁有無			*/
/*==============================================================================*/
void judgement_existence_front_wall(void)
{
	// 前壁からの距離に従い壁の有無を判断
	existence_front_wall = WALL;
	if( (front_right_distance < THRESHOLD_FR_WALL) && (front_left_distance < THRESHOLD_FL_WALL) )
	{
		existence_front_wall =  NO_WALL;
	}

	return;
}

/*==============================================================================*/
/*  左壁検知									*/
/* 										*/
/*  左側物標距離から、左壁の有無を判断する					*/
/* ---------------------------------------------------------------------------- */
/*  入力:		leftside_distance	左側物標距離			*/
/*  出力:		existence_left_wall	左壁有無			*/
/*==============================================================================*/
void judgement_existence_left_wall(void)
{
	// 左壁からの距離に従い壁の有無を判断
	existence_left_wall = WALL;
	if(leftside_distance < THRESHOLD_L_WALL)
	{
		existence_left_wall = NO_WALL;
	}

	return;
}

/*==============================================================================*/
/*  右壁検知									*/
/* 										*/
/*  右壁物標距離から、右壁の有無を判断する					*/
/* ---------------------------------------------------------------------------- */
/*  入力:		rightside_distance	右側物標距離			*/
/*  出力:		existence_right_wall	右壁有無			*/
/*==============================================================================*/
void judgement_existence_right_wall(void)
{
	// 右壁からの距離に従い壁の有無を判断
	existence_right_wall = WALL;
	if(rightside_distance < THRESHOLD_R_WALL)
	{
		existence_right_wall = NO_WALL;
	}

	return;
}