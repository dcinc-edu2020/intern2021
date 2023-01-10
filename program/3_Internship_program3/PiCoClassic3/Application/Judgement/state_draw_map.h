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
/* �Ǐ����i�[����\���� */
typedef struct
{
	unsigned char north;	// �k�̕Ǐ��
	unsigned char east;	// ���̕Ǐ��
	unsigned char south;	// ��̕Ǐ��
	unsigned char west;	// ���̕Ǐ��
} stWallType;

/*------------------------------------------------------------------------------*/
/* Externs Variable								*/
/*------------------------------------------------------------------------------*/
extern eRunInfoType draw_map_run_info;			// �}�b�v�쐬���s�w�����
extern stWallType wall_info[MAZESIZE_X][MAZESIZE_Y];	// �}�b�v�Ǐ��

/*------------------------------------------------------------------------------*/
/* Function Prototype                                                           */
/*------------------------------------------------------------------------------*/
void init_draw_map(void);
void draw_map(void);

#endif
