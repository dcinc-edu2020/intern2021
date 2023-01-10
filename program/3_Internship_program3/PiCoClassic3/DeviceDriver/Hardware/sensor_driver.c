/*==============================================================================*/
/* Sensor Driver C File								*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "DeviceDriver/Core/iodefine.h"
#include "DeviceDriver/Hardware/led_driver.h"
#include "DeviceDriver/Hardware/sensor_driver.h"

/*------------------------------------------------------------------------------*/
/* Global Variable								*/
/*------------------------------------------------------------------------------*/
t_sensor	sen_r;		// 右センサ構造体
t_sensor	sen_l;		// 左センサ構造体
t_sensor	sen_fr;		// 右前センサ構造体
t_sensor	sen_fl;		// 左前センサ構造体
t_control	con_wall;	// 制御構造体

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* センサーパラメータ初期化		                                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void init_sensor(void)
{
	sen_r.ref = REF_SEN_R;			// 右センサのリファレンス値を初期化
	sen_l.ref = REF_SEN_L;			// 左センサのリファレンス値を初期化

	sen_r.th_wall = TH_SEN_R;		// 右センサの壁有無判断の閾値を初期化
	sen_l.th_wall = TH_SEN_L;		// 左センサの壁有無判断の閾値を初期化

	sen_fr.th_wall = TH_SEN_FR;		// 右前センサの壁有無判断の閾値を初期化
	sen_fl.th_wall = TH_SEN_FL;		// 左前センサの壁有無判断の閾値を初期化

	sen_r.th_control = CONTH_SEN_R;		// 右センサの壁制御かけるか否かの閾値を初期化
	sen_l.th_control = CONTH_SEN_L;		// 左センサの壁制御かけるか否かの閾値を初期化

	con_wall.kp = CON_WALL_KP;		// 壁比例制御の比例定数を初期化

	return;
}

/*==============================================================================*/
/* 物標距離取得		                                        		*/
/* 										*/
/* 指定されたセンサー種別の物標距離を取得する					*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		sensor_kind	センサー種別			       	*/
/*  Return   :         	distance	物標距離				*/
/*==============================================================================*/
int get_distance(int sensor_kind)
{
	int distance = 0;

	switch(sensor_kind)
	{
		case SENSOR_R:
			distance = sen_r.value;		// 右側物標距離
			break;
		case SENSOR_L:
			distance = sen_l.value;		// 左側物標距離
			break;
		case SENSOR_FR:
			distance = sen_fr.value;	// 右前方物標距離
			break;
		case SENSOR_FL:
			distance = sen_fl.value;	// 左前方物標距離
			break;
		default:
			break;
	}

	return distance;
}

/*==============================================================================*/
/* PID制御有効化設定	                                        		*/
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void set_pid_enable(void)
{
	con_wall.enable = true;

	return;
}
/*==============================================================================*/
/* PID制御無効化設定	                                        		*/
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void set_pid_disable(void)
{
	con_wall.enable = false;

	return;
}

/*==============================================================================*/
/*  センサー読み込み用(CMT1)	           		                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void int_periodic_sensor(void)
{
	static int state = 0;	// 読み込むセンサのローテーション管理用変数
	int i;

	switch(state)
	{
		case 0:							// 右センサ読み込み
			SLED_R = 1;					// LED点灯
			for(i = 0; i < WAITLOOP_SLED; i++)	;	// フォトトランジスタの応答待ちループ
			S12AD.ADANS0.BIT.ANS0=0x0040;			// AN006
			S12AD.ADCSR.BIT.ADST=1;				// AD変換開始
			while(S12AD.ADCSR.BIT.ADST);			// AD変換終了まで待つ
			SLED_R = 0;					// LED消灯

			sen_r.p_value = sen_r.value;			// 過去の値を保存
			sen_r.value = S12AD.ADDR6;			// 値を保存

			if(sen_r.value > sen_r.th_wall)			// 壁の有無を判断
			{
				sen_r.is_wall = true;			// 右壁あり
			}
			else
			{
				sen_r.is_wall = false;			// 右壁なし
			}

			if(sen_r.value > sen_r.th_control)		// 制御をかけるか否かを判断
			{
				sen_r.error = sen_r.value - sen_r.ref;	// 制御をかける場合は偏差を計算
				sen_r.is_control = true;		// 右センサを制御に使う
			}
			else
			{
				sen_r.error = 0;			// 制御に使わない場合は偏差を0にしておく
				sen_r.is_control = false;		// 右センサを制御に使わない
			}
			break;


		case 1:							// 前左センサ読み込み
			SLED_FL = 1;					// LED点灯
			for(i = 0; i < WAITLOOP_SLED; i++);		// フォトトランジスタの応答待ちループ
			S12AD.ADANS0.BIT.ANS0=0x0010;			// AN004
			S12AD.ADCSR.BIT.ADST=1;				// AD変換開始
			while(S12AD.ADCSR.BIT.ADST);			// AD変換終了まで待つ
			SLED_FL = 0;					// LED消灯

			sen_fl.p_value = sen_fl.value;			// 過去の値を保存
			sen_fl.value = S12AD.ADDR4;			// 値を保存

			if(sen_fl.value > sen_fl.th_wall)		// 壁の有無を判断
			{
				sen_fl.is_wall = true;			// 左前壁あり
			}
			else
			{
				sen_fl.is_wall = false;			// 左前壁なし
			}
			break;


		case 2:							// 前右センサ読み込み
			SLED_FR = 1;					// LED点灯
			for(i = 0; i < WAITLOOP_SLED; i++);		// フォトトランジスタの応答待ちループ
			S12AD.ADANS0.BIT.ANS0=0x0200;			// AN009
			S12AD.ADCSR.BIT.ADST=1;				// AD変換開始
			while(S12AD.ADCSR.BIT.ADST);			// AD変換終了まで待つ
			SLED_FR = 0;					// LED消灯

			sen_fr.p_value = sen_fr.value;			// 過去の値を保存
			sen_fr.value = S12AD.ADDR9;			// 値を保存

			if(sen_fr.value > sen_fr.th_wall)		// 壁の有無を判断
			{
				sen_fr.is_wall = true;			// 右前壁あり
			}
			else
			{
				sen_fr.is_wall = false;			// 右前壁なし
			}
			break;


		case 3:							// 左センサ読み込み
			SLED_L = 1;					// LED点灯
			for(i = 0; i < WAITLOOP_SLED; i++)	;	// フォトトランジスタの応答待ちループ
			S12AD.ADANS0.BIT.ANS0=0x0004;			// AN002
			S12AD.ADCSR.BIT.ADST=1;				// AD変換開始
			while(S12AD.ADCSR.BIT.ADST);			// AD変換終了まで待つ
			SLED_L = 0;					// LED消灯

			sen_l.p_value = sen_l.value;			// 過去の値を保存
			sen_l.value = S12AD.ADDR2;			// 値を保存

			if(sen_l.value > sen_l.th_wall)			// 壁の有無を判断
			{
				sen_l.is_wall = true;			// 左壁あり
			}
			else
			{
				sen_l.is_wall = false;			// 左壁なし
			}

			if(sen_l.value > sen_l.th_control)		// 制御をかけるか否かを判断
			{
				sen_l.error = sen_l.value - sen_l.ref;	// 制御をかける場合は偏差を計算する
				sen_l.is_control = true;		// 左センサを制御に使う
			}
			else
			{
				sen_l.error = 0;			// 制御に使わない場合は偏差を0にしておく
				sen_l.is_control = false;		// 左センサを制御に使わない
			}

			break;
	}

	state++;		//４回ごとに繰り返す
	if(state > 3)
	{
		state = 0;
	}

	return;
}
