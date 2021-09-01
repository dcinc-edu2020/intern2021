/*==============================================================================*/
/* Sesor Driver Header File							*/
/*==============================================================================*/
#ifndef _SENSOR_DRIVER_H
#define _SENSOR_DRIVER_H

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* センサー種別 */
#define SENSOR_R	(0)	// 右側物標距離センサー
#define SENSOR_L	(1)	// 左側物標距離センサー
#define SENSOR_FR	(2)	// 右前方物標距離センサー
#define SENSOR_FL	(3)	// 左前方物標距離センサー

/* センサ関連パラメータ */
#define WAITLOOP_SLED	300				// LEDを光らせてからAD変換を開始するまでの時間稼ぎ用定数

// マウスD パラメータ
#define REF_SEN_R	1704				// マウスを迷路中央に置いた時のセンサの値
#define REF_SEN_L	1728				// マウスを迷路中央に置いた時のセンサの値

#define TH_SEN_R	1660				// 壁があるか否かの閾値
#define TH_SEN_L	1677				// 壁があるか否かの閾値
#define TH_SEN_FR	1661				// 壁があるか否かの閾値
#define TH_SEN_FL	1671				// 壁があるか否かの閾値

#define CONTH_SEN_R	TH_SEN_R			// 制御をかけるか否かの閾値
#define CONTH_SEN_L	TH_SEN_L			// 制御をかけるか否かの閾値
#define CON_WALL_KP	(0.3)				// 壁センサによる姿勢制御の比例制御の比例定数

/* 関数マクロ */
#define CONV_SEN2WALL(w) ((w) ? WALL : NOWALL)		// センサ情報から壁情報へ変換

/*------------------------------------------------------------------------------*/
/* Type Definitions								*/
/*------------------------------------------------------------------------------*/
/* 真偽値を取り扱う列挙型 */
typedef enum
{
	false = 0,		// 偽
	true = 1,		// 真
}t_bool;

/* センサ構造体 */
typedef struct
{
	short value;		// 現在の値
	short p_value;		// 1mS過去の値
	short error;		// value - ref
	short ref;		// リファレンス値
	short th_wall;		// 壁があるか否かの閾値
	short th_control;	// 制御をかけるか否かの閾値
	t_bool is_wall;		// 壁があるか無いか ( true = 壁あり false = 壁なし )
	t_bool is_control;	// 制御に使うか否か
}t_sensor;

/* 制御構造体 */
typedef struct
{
	float control;		// 最終的な制御量
	float error;		// 偏差
	float p_error;		// 過去の偏差
	float diff;		// 偏差の微分値
	float sum;		// 偏差の積分値
	float sum_max;		// 積分値の制限値
	float kp;		// 比例制御定数
	float kd;		// 微分制御定数
	float ki;		// 積分制御定数
	t_bool enable;		// 制御のon/off
}t_control;

/*------------------------------------------------------------------------------*/
/* Externs Variable								*/
/*------------------------------------------------------------------------------*/
extern t_sensor	sen_r;		// 右センサ構造体
extern t_sensor	sen_l;		// 左センサ構造体
extern t_sensor	sen_fr;		// 右前センサ構造体
extern t_sensor	sen_fl;		// 左前センサ構造体
extern t_control	con_wall;	// 制御構造体

/*------------------------------------------------------------------------------*/
/* Function Prototype								*/
/*------------------------------------------------------------------------------*/
void init_sensor(void);			// センサーパラメータ初期化
int get_distance(int sensor_kind);	// 物標距離取得
void set_pid_enable(void);		// PID制御有効化設定
void set_pid_disable(void);		// PID制御無効化設定

#endif