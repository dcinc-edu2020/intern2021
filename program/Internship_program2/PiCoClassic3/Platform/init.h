/*==============================================================================*/
/* Init Header File								*/
/*==============================================================================*/
#ifndef _INIT_H
#define _INIT_H

/*------------------------------------------------------------------------------*/
/* Function Prototype								*/
/*------------------------------------------------------------------------------*/
void init_all(void);		// 全体初期化
void init_clock(void);		// CPUの動作周波数を設定
void init_io(void);		// IOポート初期化
void init_cmt(void);		// CMT初期化
void init_mtu(void);		// MTU設定
void init_adc(void);		// AD初期化

#endif