/*==============================================================================*/
/* Distance Recognition Header File						*/
/*==============================================================================*/
#ifndef _DISTANCE_RECOGNITION_H
#define _DISTANCE_RECOGNITION_H

/*------------------------------------------------------------------------------*/
/* Global Variable								*/
/*------------------------------------------------------------------------------*/
extern int rightside_dictance;			// 右側物標距離
extern int leftside_distance;			// 左側物標距離
extern int front_right_distance;		// 右前方物標距離
extern int front_left_distance;		// 左前方物標距離

/*------------------------------------------------------------------------------*/
/* Function Prototype								*/
/*------------------------------------------------------------------------------*/
void distance_recognition(void);		// 物標距離計測

#endif