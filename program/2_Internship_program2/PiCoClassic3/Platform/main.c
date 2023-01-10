/*==============================================================================*/
/* Main C File									*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "DeviceDriver/Core/init.h"
#include "DeviceDriver/Hardware/buzzer_driver.h"
#include "DeviceDriver/Hardware/motor_driver.h"
#include "DeviceDriver/Hardware/led_driver.h"
#include "DeviceDriver/Hardware/switch_driver.h"
#include "DeviceDriver/Hardware/sensor_driver.h"
#include "Platform/timer.h"
#include "Platform/scheduler.h"

/*------------------------------------------------------------------------------*/
/* Function Prototype								*/
/*------------------------------------------------------------------------------*/
void main(void);					// メイン関数
static void sound_buzzer_poweron(void);			// ブザー吹鳴(電源ON)
static void wait_push_switch(void);			// スイッチの押下待ち
static void sound_buzzer_enter(void);			// ブザー吹鳴(決定ボタン)

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* メイン関数									*/
/* 										*/
/* 各モード選択スイッチの押下内容に応じて、プログラムの動作を制御する		*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-							*/
/*  Return   :		-							*/
/*==============================================================================*/
void main(void)
{
	// レジスタ初期化
	init_core();

	// ドライバ初期化
	init_sensor();
	init_motor();

	// 電源を入れた時の起動音を鳴らす
	sound_buzzer_poweron();

	// スイッチが押されるまで待ち、押されたらプログラムを起動する
	motor_power_off();		// ステッピングモーターを脱力

	wait_push_switch();		// スイッチが押されるまで待つ

	display_led(MODE_LED_PATTERN_1); // 車体前方のLEDを点灯する
	sound_buzzer_enter();		// 決定スイッチが押されたときの音を鳴らす
	motor_power_on();		// ステッピングモーターを励磁

	// プログラム実行
	task_routine();

	return;
}

/*==============================================================================*/
/* ブザー吹鳴(電源ON)								*/
/* 										*/
/* 電源がONになったときの音を鳴らす						*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-							*/
/*  Return   :		-							*/
/*==============================================================================*/
static void sound_buzzer_poweron(void)
{
	set_buzzer_freq(INC_FREQ);	// 値が増加した時の周波数を設定
	buzzer_on();			// ブザーを発振させる
	wait_ms(80);			// 適当な待ち時間
	buzzer_off();			// ブザーの発振を停止させる

	return;
}

/*==============================================================================*/
/* スイッチの押下待ち								*/
/* 										*/
/* スイッチが押されるまでウェイトする						*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-							*/
/*  Return   :		-							*/
/*==============================================================================*/
static void wait_push_switch(void)
{
	/* スイッチ状態初期化 */
	int switch_state_left   = SW_OFF;	// 左スイッチ(赤)の状態
	int switch_state_center = SW_OFF;	// 中央スイッチ(黄)の状態
	int switch_state_right  = SW_OFF;	// 右スイッチ(青)の状態

	wait_ms(CHATTERING_WAIT*3);		// チャタリング防止の待ち時間

	while( !(switch_state_left & switch_state_center & switch_state_right) )
	{
		// スイッチが離されるまで待つ
		switch_state_left   = get_switch_state(MODE_SW_RED);
		switch_state_center = get_switch_state(MODE_SW_YELLOW);
		switch_state_right  = get_switch_state(MODE_SW_BLUE);
	}

	wait_ms(CHATTERING_WAIT);		// チャタリング防止の待ち時間

	while( (switch_state_left & switch_state_center & switch_state_right) )
	{
		// いずれかのスイッチが押されるまで待つ
		switch_state_left   = get_switch_state(MODE_SW_RED);
		switch_state_center = get_switch_state(MODE_SW_YELLOW);
		switch_state_right  = get_switch_state(MODE_SW_BLUE);
	}

	return;
}

/*==============================================================================*/
/* ブザー吹鳴(決定ボタン)							*/
/* 										*/
/* 決定スイッチが押されたときの音を鳴らす(ピロッ音)				*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
static void sound_buzzer_enter(void)
{
	set_buzzer_freq(DEC_FREQ);		// 音(周波数)を変更する　（ピ）
	buzzer_on();				// ブザーを発振させる
	wait_ms(80);				// 適当な待ち時間

	set_buzzer_freq(INC_FREQ);		// 音(周波数)を変更する　（ロッ）
	wait_ms(80);				// 適当な待ち時間
	buzzer_off();				// ブザーの発振を停止させる

	return;
}
