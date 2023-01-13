/*==============================================================================*/
/* Tire Control Header File							*/
/*==============================================================================*/
#ifndef TIRE_CONTROL_H
#define TIRE_CONTROL_H

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* 旋回方向 */
#define TURN_RIGHT	(0)
#define TURN_LEFT	(1)

/* 駆動距離 */
#define HALF_SECTION	(90)	// 半区画の距離(mm)
#define SECTION		(180)	// 1区画の距離(mm)
#define TURN_90		(90)	// ターン角度90度
#define TURN_180	(180)	// ターン角度180度

/*------------------------------------------------------------------------------*/
/* Function Prototype								*/
/*------------------------------------------------------------------------------*/
void init_tire_control(void);					// タイヤ制御初期化
void tire_control(void);					// タイヤ制御
void run_straight(int distance, float target_speed);		// タイヤ制御(直進)
void run_rotate(int rotate_direction, int rotate_angle);	// タイヤ制御(旋回)

#endif