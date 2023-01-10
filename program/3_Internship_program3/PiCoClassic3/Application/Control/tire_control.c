/*==============================================================================*/
/* Tire Control C File								*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "DeviceDriver/Hardware/motor_driver.h"
#include "DeviceDriver/Hardware/sensor_driver.h"
#include "Platform/timer.h"
#include "Application/Judgement/run_info_judgement.h"
#include "Application/Control/tire_control.h"

/*------------------------------------------------------------------------------*/
/* Global Variable								*/
/*------------------------------------------------------------------------------*/
static eRunInfoType pre_run_info;	// 前回の走行指示情報

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/
/*==============================================================================*/
/* タイヤ制御初期化								*/
/* ---------------------------------------------------------------------------- */
/*  入力:		-							*/
/*  出力:		-							*/
/*==============================================================================*/
void init_tire_control(void)
{
	pre_run_info = Stop;
}

/*==============================================================================*/
/* タイヤ制御									*/
/* 										*/
/* 走行指示情報に応じてタイヤ制御する						*/
/* ---------------------------------------------------------------------------- */
/*  入力:		run_info		走行指示情報			*/
/*  出力:		-							*/
/*==============================================================================*/
void tire_control(void)
{
	/* 制御処理 */
	switch(run_info)
	{
		case Forward:		// 直進制御
			run_straight(SECTION, DEFAULT_SPEED);		// 1区画直進する
			break;
		case TurnRight:		// 右旋回制御
			run_straight(HALF_SECTION, MIN_SPEED);		// 0.5区画直進する（旋回前に減速する）
			run_rotate(TURN_RIGHT, TURN_90);		// その場で90度右旋回する
			run_straight(HALF_SECTION, DEFAULT_SPEED);	// 0.5区画直進する（旋回後に加速する）
			break;
		case TurnLeft:		// 左旋回制御
			run_straight(HALF_SECTION, MIN_SPEED);		// 0.5区画直進する（旋回前に減速する）
			run_rotate(TURN_LEFT, TURN_90);			// その場で90度左旋回する
			run_straight(HALF_SECTION, DEFAULT_SPEED);	// 0.5区画直進する（旋回後に加速する）
			break;
		case Reverse:		// 反転制御
			run_straight(HALF_SECTION, MIN_SPEED);		// 0.5区画直進する（旋回前に減速する）
			run_rotate(TURN_RIGHT, TURN_180);		// その場で180度右旋回する
			run_straight(HALF_SECTION, DEFAULT_SPEED);	// 0.5区画直進する（旋回後に加速する）
			break;
		case Stop:		// 停止制御
			// 走行中なら、0.5区画直進しながら停止(区画の中央に停止)
			if( pre_run_info != Stop )
			{
				run_straight(HALF_SECTION, MIN_SPEED);
			}
			wait_ms(10);
			break;
		case Half:		// 0.5区画直進
			run_straight(HALF_SECTION, DEFAULT_SPEED);	//  0.5区画直進する（加速する）
			break;
		default:
			break;
	}
	pre_run_info = run_info;

	return;
}

/*==============================================================================*/
/*  タイヤ制御(直進)								*/
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		distance		走行距離 [mm]			*/
/*			target_speed		目標速度(加速・減速の設定)	*/
/*  Return   :		-							*/
/*==============================================================================*/
void run_straight(int distance, float target_speed)
{
	/* 走行距離初期化 */
	unsigned int mileage_r = 0;		// 右モーターの走行距離[mm]
	unsigned int mileage_l = 0;		// 左モーターの走行距離[mm]

	/* モータの駆動方向の設定 */
	set_motor_direction_r(MOT_FORWARD);	// 右モーター駆動方向：正転
	set_motor_direction_l(MOT_FORWARD);	// 左モーター駆動方向：正転

	/* 直進中は壁制御（PID制御）を有効にする */
	set_pid_enable();

	/* モーター駆動 */
	reset_motor_step();			// ステッピングモーターのステップ数カウントをリセット
	start_motor_control();			// モーター回転開始

	/* 目標地点まで走行 */
	while( ((mileage_r + mileage_l) / 2) < distance)	// 蛇行走行分を考慮して右モーターと左モーターの走行距離の平均値で判定
	{
		/* 加減速の設定 */
		control_accel(distance, target_speed);		// 減速を始める必要がある距離に達した場合、加速度をマイナスに設定する

		/* 各ステッピングモーターの現在までの走行距離を取得 */
		mileage_r = get_mileage_step(MOTOR_RIGHT);
		mileage_l = get_mileage_step(MOTOR_LEFT);
	}

	stop_motor_control();	// モーター回転停止

	return;
}
/*==============================================================================*/
/*  タイヤ制御(旋回)								*/
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		rotate_direction	回転方向（右/左）		*/
/*			rotate_angle		回転角度（90度/180度）		*/
/*  Return   :		-							*/
/*==============================================================================*/
void run_rotate(int rotate_direction, int rotate_angle)
{
	/* 目標走行距離算出 */
	unsigned int distance = (TREAD_WIDTH * PI) / (360 / rotate_angle);	// トレッド幅×π/ (360 / 角度)

	/* 走行距離初期化 */
	unsigned int mileage_r = 0;		// 右モーターの走行距離[mm]
	unsigned int mileage_l = 0;		// 左モーターの走行距離[mm]

	/* モータの駆動方向の設定 */
	switch(rotate_direction)
	{
		case TURN_RIGHT:
			set_motor_direction_r(MOT_BACK);	// 右モーター駆動方向：逆転
			set_motor_direction_l(MOT_FORWARD);	// 左モーター駆動方向：正転
			break;
		case TURN_LEFT:
			set_motor_direction_r(MOT_FORWARD);	// 右モーター駆動方向：正転
			set_motor_direction_l(MOT_BACK);	// 左モーター駆動方向：逆転
			break;
		default:
			return;
			break;
	}

	/* 旋回中は壁制御（PID制御）を無効にする */
	set_pid_disable();

	/* 速度設定 */
	float target_speed = MIN_SPEED;		// 目標速度(固定)…30mm/s
	set_r_accel(TURN_ACCEL);		// 加速度設定

	/* モーター駆動 */
	reset_motor_step();			// ステッピングモーターのステップ数カウントをリセット
	wait_ms(250);				// いきなり回ると姿勢が乱れるので、少し待機
	start_motor_control();			// モーター回転開始

	/* 目標地点まで走行 */
	while( ((mileage_r + mileage_l) / 2) < distance)	// 蛇行走行分を考慮して右モーターと左モーターの走行距離の平均値で判定
	{
		/* 加減速の設定 */
		control_accel_turn(distance, target_speed);	// 減速を始める必要がある距離に達した場合、加速度をマイナスに設定する

		/* 各ステッピングモーターの現在までの走行距離を取得 */
		mileage_r = get_mileage_step(MOTOR_RIGHT);
		mileage_l = get_mileage_step(MOTOR_LEFT);
	}

	stop_motor_control();	// モーター回転停止
	wait_ms(250);		// 旋回後、少し待機

	return;
}
