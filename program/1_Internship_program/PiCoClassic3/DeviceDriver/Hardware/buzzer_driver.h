/*==============================================================================*/
/* Buzzer Driver Header File							*/
/*==============================================================================*/
#ifndef BUZZER_DRIVER_H
#define BUZZER_DRIVER_H

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* ブザー */
#define BUZZER		(PORTB.PODR.BIT.B3)	// ブザー

/* システム設定周波数 */
#define INC_FREQ	(2000)			// モードが増加した時に鳴らす音の周波数
#define DEC_FREQ	(1000)			// モードが減少した時に鳴らす音の周波数

/* 音階の周波数 */
#define BZ_FREQ_REST    (0)			// 休符
#define BZ_FREQ_LA0     (440)			// ラ（A）の周波数
#define BZ_FREQ_SI0     (494)			// シ（B）の周波数
#define BZ_FREQ_DO      (523)			// ド（C）の周波数
#define BZ_FREQ_RE      (587)			// レ（D）の周波数
#define BZ_FREQ_MI      (659)			// ミ（E）の周波数
#define BZ_FREQ_FA      (698)			// ファ（F）の周波数
#define BZ_FREQ_SO      (784)			// ソ（G）の周波数
#define BZ_FREQ_LA      (880)			// ラ（A）の周波数
#define BZ_FREQ_SI      (988)			// シ（B）の周波数
#define BZ_FREQ_DO2     (1047)			// ド（C）の周波数
#define BZ_FREQ_RE2     (1174)			// レ（D）の周波数
#define BZ_FREQ_MI2     (1318)			// ミ（E）の周波数
#define BZ_FREQ_FA2     (1396)			// ファ（F）の周波数
#define BZ_FREQ_SO2     (1568)			// ソ（G）の周波数
#define BZ_FREQ_LA2     (1760)			// ラ（A）の周波数
#define BZ_FREQ_SI2     (1976)			// シ（B）の周波数
#define BZ_FREQ_DO3     (2094)			// ド（C）の周波数

/*------------------------------------------------------------------------------*/
/* Function Prototype								*/
/*------------------------------------------------------------------------------*/
void set_buzzer_freq(unsigned short frequency);		// ブザー周波数設定
void buzzer_on(void);					// ブザー発振開始
void buzzer_off(void);					// ブザー発振停止

#endif