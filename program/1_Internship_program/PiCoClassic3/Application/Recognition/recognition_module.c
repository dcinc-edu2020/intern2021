/*==============================================================================*/
/* Recognition Module C File							*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "Application/Recognition/distance_recognition.h"
#include "Application/Recognition/recognition_module.h"

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* 認知コンポーネントグループの初期化						*/
/* ---------------------------------------------------------------------------- */
/*  入力:		-							*/
/*  出力:		-							*/
/*==============================================================================*/
void init_recognition(void)
{
	return;
}

/*==============================================================================*/
/* 認知										*/
/*										*/
/* ---------------------------------------------------------------------------- */
/*  入力:		-							*/
/*  出力:		-							*/
/*==============================================================================*/
void recognition(void)
{
	/* 物標距離計測 */
	distance_recognition();

	return;
}