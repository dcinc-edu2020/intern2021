/*==============================================================================*/
/* Main C File									*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "common.h"
#include "init.h"
#include "buzzer_driver.h"
#include "motor_driver.h"
#include "led_driver.h"
#include "switch_driver.h"
#include "scheduler.h"

/*------------------------------------------------------------------------------*/
/* Function Prototype								*/
/*------------------------------------------------------------------------------*/
void main(void);					// メイン関数
void sound_buzzer_enter(void);				// ブザー吹鳴(決定ボタン)
void execute_program(void);				// プログラム実行

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* メイン関数									*/
/* 										*/
/* 各モード選択スイッチの押下内容に応じて、プログラムの動作を制御する		*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void main(void)
{
	/* スイッチ状態初期化 */
	int switch_state_left   = SW_OFF;	// 左スイッチ(赤)の状態
	int switch_state_center = SW_OFF;	// 中央スイッチ(黄)の状態
	int switch_state_right  = SW_OFF;	// 右スイッチ(青)の状態
	
	/* 全体初期化 */
	init_all();

	/* スイッチの入力受付 */	
	while(1)
	{
		wait_ms(CHATTERING_WAIT*3);		// チャタリング防止の待ち時間
		motor_power_off();			// ステッピングモーターを脱力
		buzzer_off();				// ブザーの発振を停止させる

		while( !(switch_state_left & switch_state_center & switch_state_right) )
		{
			// スイッチが離されるまで待つ
			switch_state_left   = get_switch_state(MODE_SW_RED);
			switch_state_center = get_switch_state(MODE_SW_YELLOW);
			switch_state_right  = get_switch_state(MODE_SW_BLUE);
		}		

		wait_ms(CHATTERING_WAIT);		// チャタリング防止の待ち時間

		display_led(MODE_LED_PATTERN_1);	// 車体前方のLEDを表示する

		while( (switch_state_left & switch_state_center & switch_state_right) )
		{
			// いずれかのスイッチが押されるまで待つ
			switch_state_left   = get_switch_state(MODE_SW_RED);
			switch_state_center = get_switch_state(MODE_SW_YELLOW);
			switch_state_right  = get_switch_state(MODE_SW_BLUE);
		}
		
		sound_buzzer_enter();			// 決定スイッチが押されたときの音を鳴らす
		execute_program();			// プログラムを実行する
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
void sound_buzzer_enter(void)
{
	set_buzzer_freq(DEC_FREQ);		// 音(周波数)を変更する　（ピ）
	buzzer_on();				// ブザーを発振させる
	wait_ms(80);				// 適当な待ち時間
	
	set_buzzer_freq(INC_FREQ);		// 音(周波数)を変更する　（ロッ）
	wait_ms(80);				// 適当な待ち時間
	buzzer_off();				// ブザーの発振を停止させる
	
	return;
}

/*==============================================================================*/
/* プログラム実行								*/
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void execute_program(void)
{
	/* ステッピングモーターを励磁 */
	motor_power_on();
	
	/* 定期処理実行 */
	task_routine();
	
	/* ステッピングモーターを脱力 */
	motor_power_off();
	
	return;
}
