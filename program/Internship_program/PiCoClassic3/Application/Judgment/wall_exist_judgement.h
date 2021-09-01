/*==============================================================================*/
/* Wall Exist Judgement Header File						*/
/*==============================================================================*/
#ifndef _WALL_EXIST_JUDGEMENT_H
#define _WALL_EXIST_JUDGEMENT_H

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* 壁有無判定結果 */
#define	WALL	(0)	// 壁有り
#define	NO_WALL	(1)	// 壁無し

/*------------------------------------------------------------------------------*/
/* Function Prototype								*/
/*------------------------------------------------------------------------------*/
int judgement_existence_front_wall(int front_right_distance, int front_left_distance);	// 前壁検知
int judgement_existence_left_wall(int leftside_distance);				// 左壁検知
int judgement_existence_right_wall(int rightside_dictance);				// 右壁検知

#endif
