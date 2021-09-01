/*==============================================================================*/
/* Motor Driver Header File							*/
/*==============================================================================*/
#ifndef _MOTOR_DRIVER_H
#define _MOTOR_DRIVER_H

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* モーター種別 */
#define MOTOR_RIGHT	(0)	// 右ステッピングモーター
#define MOTOR_LEFT	(1)	// 左ステッピングモーター

/* モータ駆動用パラメータ */
#define MOT_FORWARD	(0)	// モータドライバのCWCCW端子にLOWを出力すると前進する
#define MOT_BACK	(1)	// モータドライバのCWCCW端子にHIGHを出力するとバックする

/* 物理的なパラメータ */
#define TIRE_DIAMETER	(48.0)			// タイヤの直径 [mm]
#define TREAD_WIDTH	(65.0+4.2)		// トレッド幅 [mm]
#define TREAD_CIRCUIT	(TREAD_WIDTH*PI/4)	// 超信地旋回の時にタイヤが動く距離
#define PI 		(3.141592653589793)	// 円周率
#define TIRE_CIRCUIT	(PI*TIRE_DIAMETER)	//タイヤの円周…直径から算出(PIは円周率)

/* 走行パラメータ */
#define MIN_SPEED	(30)			// 最低速度.ジェネラルレジスタが16bitであることと、MTUの動作周波数から求められる値がおおよそ18mm/sなので、余裕を持って30mm/s
#define DEFAULT_ACCEL	(1.5)			// 走行の加速度
#define DEFAULT_SPEED	(400)			// 走行速度 400[mm/s]
#define MAX_SPEED	(400)			// 最高速度 400[mm/s]
#define TURN_ACCEL	(0.3)			// 超信地旋回の加速度
#define TURN_SPEED	(400)			// 超信地旋回の最高速のリミット

/* 関数マクロ */
#define SPEED2GREG(v)	(7500/(((v)/TIRE_CIRCUIT)))		//スピードからジェネラルレジスタの値を計算

/*------------------------------------------------------------------------------*/
/* Variable Externs								*/
/*------------------------------------------------------------------------------*/
extern	unsigned int	step_r;			// 右モーターステップ数(割り込み内でカウントアップ)
extern	unsigned int	step_l;			// 左モーターステップ数(割り込み内でカウントアップ)
extern	float		accel;			// 加速度(設定値→符号なし)
extern	float		r_accel;		// 加速度(実際の値→符号あり)
extern	float		max_speed;		// 最高速度(設定値)
extern	float		min_speed;		// 最低速度(設定値)
extern	float		speed;			// 速度(現在の値)

/*------------------------------------------------------------------------------*/
/* Function prototype								*/
/*------------------------------------------------------------------------------*/
void init_motor(void);						// モーター制御用パラメータ初期化
void motor_power_on(void);					// モーター励磁
void motor_power_off(void);					// モーター脱力
void set_motor_direction_r(int motor_direction);		// 右モーター回転方向設定
void set_motor_direction_l(int motor_direction);		// 左モーター回転方向設定
void reset_motor_step(void);					// モーターステップ数リセット
void start_motor_control(void);					// モーター回転開始
void stop_motor_control(void);					// モーター回転停止
unsigned int get_motor_step(float distance);			// 走行ステップ数取得
unsigned int get_mileage_step(int motor_kind);			// モーター走行距離取得
void set_current_speed(float set_speed);			// 現在速度設定
void set_max_speed(float set_speed);				// 最高速度設定
void set_min_speed(float set_speed);				// 最低速度設定
void control_accel(int mileage, float target_speed);		// 加速度設定
void control_accel_turn(int mileage, float target_speed);	// 加速度設定（旋回）
void set_accel(float set_accel);				// 加速度設定
void set_r_accel(float set_accel);				// 加速度設定

#endif