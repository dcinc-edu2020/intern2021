/*==============================================================================*/
/* Wall Exist Judgement Header File						*/
/*==============================================================================*/
#ifndef WALL_EXIST_JUDGEMENT_H
#define WALL_EXIST_JUDGEMENT_H

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* 壁有無判定結果 */
#define	WALL	(0)	// 壁有り
#define	NO_WALL	(1)	// 壁無し

/*------------------------------------------------------------------------------*/
/* Externs Variable								*/
/*------------------------------------------------------------------------------*/
extern int existence_front_wall;			// 前壁有無
extern int existence_left_wall;				// 左壁有無
extern int existence_right_wall;			// 右壁有無

/*------------------------------------------------------------------------------*/
/* Function Prototype								*/
/*------------------------------------------------------------------------------*/
void init_wall_exist_judgement(void);			// 初期化
void judgement_existence_front_wall(void);		// 前壁検知
void judgement_existence_left_wall(void);		// 左壁検知
void judgement_existence_right_wall(void);		// 右壁検知

#endif
