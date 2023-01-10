/*==============================================================================*/
/* State Draw Map Header File							*/
/*==============================================================================*/
#ifndef STATE_DRAW_MAP_H
#define STATE_DRAW_MAP_H

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "Application/Judgement/maze_setting.h"
#include "Application/Judgement/run_info_judgement.h"
#include "Application/Judgement/wall_exist_judgement.h"

/*------------------------------------------------------------------------------*/
/* Struct Definitions								*/
/*------------------------------------------------------------------------------*/
/* 壁情報を格納する構造体 */
typedef struct
{
	unsigned char north;	// 北の壁情報
	unsigned char east;	// 東の壁情報
	unsigned char south;	// 南の壁情報
	unsigned char west;	// 西の壁情報
} stWallType;

/*------------------------------------------------------------------------------*/
/* Externs Variable								*/
/*------------------------------------------------------------------------------*/
extern eRunInfoType draw_map_run_info;			// マップ作成走行指示情報
extern stWallType wall_info[MAZESIZE_X][MAZESIZE_Y];	// マップ壁情報

/*------------------------------------------------------------------------------*/
/* Function Prototype                                                           */
/*------------------------------------------------------------------------------*/
void init_draw_map(void);
void draw_map(void);

#endif
