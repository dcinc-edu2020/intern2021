/*==============================================================================*/
/* State Run Route C File							*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "DeviceDriver/Hardware/switch_driver.h"
#include "Application/Judgement/maze_setting.h"
#include "Application/Judgement/state_draw_map.h"
#include "Application/Judgement/state_calc_map.h"
#include "Application/Judgement/state_run_route.h"
#include "Application/Judgement/run_info_judgement.h"

/*------------------------------------------------------------------------------*/
/* Global Variable								*/
/*------------------------------------------------------------------------------*/
eRunInfoType route_run_info;		// 最短経路走行指示情報

/*------------------------------------------------------------------------------*/
/* Static Variable								*/
/*------------------------------------------------------------------------------*/
static int my_pos_x;		// 車体座標x
static int my_pos_y;		// 車体座標y
static eDirectionType my_direction;	// 車体の向き

/*------------------------------------------------------------------------------*/
/* Function prototype								*/
/*------------------------------------------------------------------------------*/
static eRunInfoType judgement_next_run_info(eDirectionType my_dir, eDirectionType next_dir);	// 走行指示情報判定
static eDirectionType get_next_direction(int my_pos_x, int my_pos_y, eDirectionType my_dir);	// 進行方向取得
static int get_priority(eDirectionType my_dir, eDirectionType next_dir);			// 行先優先度算出

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* 経路走行初期化								*/
/* ---------------------------------------------------------------------------- */
/*  入力:		-							*/
/*  出力:		-							*/
/*==============================================================================*/
void init_run_route(void)
{
	route_run_info = Stop;

	// 初期位置：(0,0) 北向き
	my_pos_x = 0;
	my_pos_y = 0;
	my_direction = North;

	return;
}

/*==============================================================================*/
/* 最短経路走行									*/
/* 										*/
/* 歩数マップの小さい方向に向かって走行する					*/
/* ---------------------------------------------------------------------------- */
/*  入力:		wall_info		マップ壁情報			*/
/*			step_map		歩数マップ			*/
/*  出力:		route_run_info		最短経路走行指示情報		*/
/*==============================================================================*/
void run_route()
{
	int switch_state_left;		// 左スイッチ(赤)の状態
	eDirectionType next_direction;	// 次に進むべき方向

	if( (my_pos_x == 0) && (my_pos_y == 0) )
	{
		// ボタンが押されたら1歩目を進む

		// 左ボタンが押されるまで停止
		route_run_info = Stop;
		switch_state_left   = get_switch_state(MODE_SW_RED);
		if( switch_state_left == SW_ON )
		{
			// 1歩目は必ず上に1区画進む（次のマスとの境目まで進むので半区画）
			route_run_info = Half;
			my_pos_x = 0;
			my_pos_y = 1;
			my_direction = North;
		}
	}
	else if( (my_pos_x != GOAL_X) || (my_pos_y != GOAL_Y) )
	{
		// ゴール位置に到達するまでマップ壁情報、歩数マップに従って走行する

		// マップ壁情報、歩数マップを元に次に進むべき方向を決定する
		next_direction = get_next_direction(my_pos_x, my_pos_y, my_direction);

		// 現在の自車向きと次に進むべき方向から走行指示を設定
		route_run_info = judgement_next_run_info(my_direction, next_direction);

		// 車体情報更新
		my_direction = next_direction;
		switch(my_direction)
		{
			case North:
				my_pos_y++;		// 北へ進んだ時はY座標を増やす
				break;
			case East:
				my_pos_x++;		// 西へ進んだ時はX座標を減らす
				break;
			case West:
				my_pos_x--;		// 東へ進んだ時はX座標を増やす
				break;
			case South:
				my_pos_y--;		// 南へ進んだ時はY座標を増やす
				break;
			default:
				break;
		}
	}else{
		// ゴールしたら停止する
		route_run_info = Stop;
	}

	return;
}

/*==============================================================================*/
/* 進行方向取得									*/
/* 										*/
/* 歩数マップに従って次に向かう方向を取得する					*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		my_pos_x	自車位置のX座標				*/
/*			my_pos_y	自車位置のY座標				*/
/*			my_direction	自車の現在向いている方向		*/
/*  Return   :		next_direction	次に向かう方向				*/
/*==============================================================================*/
static eDirectionType get_next_direction(int my_pos_x, int my_pos_y, eDirectionType my_dir)
{
	eDirectionType next_direction;	// 進行方向
	int priority 	 = 0;	// 進行方向の優先度
	int tmp_priority = 0;	// 進行方向の優先度(一時的に格納用)

	unsigned int min_step;				// 最小歩数ステップ
	min_step = step_map[my_pos_x][my_pos_y];	// 現在位置の歩数ステップを最小歩数ステップに設定

	// 現在位置から歩数マップが一番低い方向に向かう
	if(my_pos_y < MAZESIZE_Y-1)				// 北：範囲チェック
	{
		if( wall_info[my_pos_x][my_pos_y].north == NO_WALL )
		{
			tmp_priority = get_priority(my_dir, North);		// 自車の向いている方向から優先度を算出
			if((step_map[my_pos_x][my_pos_y + 1] < min_step))	// 北に1マス進んだ場合の歩数マップが小さければ
			{
				min_step = step_map[my_pos_x][my_pos_y + 1];	// ひとまず北を最小ステップとする
				next_direction  = North;			// 方向を保存
				priority	= tmp_priority;			// 優先度を保存
			}
			else if((step_map[my_pos_x][my_pos_y + 1] == min_step))	// 歩数が同じ場合は優先度から判断する
			{
				if(priority < tmp_priority)		// 優先度を評価
				{
					next_direction  = North;	// 方向を更新
					priority = tmp_priority;	// 優先度を保存
				}
			}
		}
	}

	if(my_pos_x < MAZESIZE_X-1)				// 東：範囲チェック
	{
		if( wall_info[my_pos_x][my_pos_y].east == NO_WALL )
		{
			tmp_priority = get_priority(my_dir, East);		// 自車の向いている方向から優先度を算出
			if((step_map[my_pos_x + 1][my_pos_y] < min_step))	// 東に1マス進んだ場合の歩数マップが小さければ
			{
				min_step = step_map[my_pos_x + 1][my_pos_y];	// ひとまず東を最小ステップとする
				next_direction  = East;				// 方向を保存
				priority	= tmp_priority;			// 優先度を保存
			}
			else if((step_map[my_pos_x + 1][my_pos_y] == min_step))	// 歩数が同じ場合は優先度から判断する
			{
				if(priority < tmp_priority)		// 優先度を評価
				{
					next_direction  = East;		// 方向を更新
					priority = tmp_priority;	// 優先度を保存
				}
			}
		}
	}

	if(my_pos_x > 0)	// // 西：範囲チェック
	{
		if( wall_info[my_pos_x][my_pos_y].west == NO_WALL )
		{
			tmp_priority = get_priority(my_dir, West);		// 自車の向いている方向から優先度を算出
			if((step_map[my_pos_x - 1][my_pos_y] < min_step))	// 東に1マス進んだ場合の歩数マップが小さければ
			{
				min_step = step_map[my_pos_x - 1][my_pos_y];	// ひとまず東を最小ステップとする
				next_direction  = West;				// 方向を保存
				priority	= tmp_priority;			// 優先度を保存
			}
			else if((step_map[my_pos_x - 1][my_pos_y] == min_step))	// 歩数が同じ場合は優先度から判断する
			{
				if(priority < tmp_priority)		// 優先度を評価
				{
					next_direction  = West;		// 方向を更新
					priority = tmp_priority;	// 優先度を保存
				}
			}
		}
	}

	if(my_pos_y > 0)	// // 南：範囲チェック
	{
		if( wall_info[my_pos_x][my_pos_y].south == NO_WALL )
		{
			tmp_priority = get_priority(my_dir, South);		// 自車の向いている方向から優先度を算出
			if((step_map[my_pos_x][my_pos_y - 1] < min_step))	// 東に1マス進んだ場合の歩数マップが小さければ
			{
				min_step = step_map[my_pos_x][my_pos_y - 1];	// ひとまず東を最小ステップとする
				next_direction  = South;			// 方向を保存
				priority	= tmp_priority;			// 優先度を保存
			}
			else if((step_map[my_pos_x][my_pos_y - 1] == min_step))	// 歩数が同じ場合は優先度から判断する
			{
				if(priority < tmp_priority)		// 優先度を評価
				{
					next_direction  = South;	// 方向を更新
					priority = tmp_priority;	// 優先度を保存
				}
			}
		}
	}

	/* 自車の方向と行きたい方向から最終的な方向を設定 */
	//next_direction = (4 + next_direction - my_dir) % 4;

	return next_direction;
}


/*==============================================================================*/
/* 行先優先度算出								*/
/* 										*/
/* 現在向いている方角と、行きたい方角から優先度を算出する			*/
/* 優先度は高い順に、直進(3)、右折(2)、左折(1)、Uターン(0)とする		*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		my_dir		現在向いている方角			*/
/*			next_dir	行きたい方角				*/
/*  Return   :		priority	優先度(0～3)				*/
/*==============================================================================*/
static int get_priority(eDirectionType my_dir, eDirectionType next_dir)
{
	int priority = 0;	// 優先度を記録する変数

	/* 優先度算出 */
	switch(judgement_next_run_info(my_dir, next_dir))
	{
		case Forward:
			priority = 3;
			break;
		case TurnRight:
			priority = 2;
			break;
		case TurnLeft:
			priority = 1;
			break;
		case Reverse:
			priority = 0;
			break;
		default:
			break;
	}

	return priority;
}

/*==============================================================================*/
/* 走行指示情報判定								*/
/* 										*/
/* 現在の自車の向きと次に行くべき方向から走行指示情報を判定する			*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		next_direction	次に向かう方向				*/
/*			my_dir		自車の現在向いている方向		*/
/*  Return   :		next_run_info	走行指示情報				*/
/*==============================================================================*/
static eRunInfoType judgement_next_run_info(eDirectionType my_dir, eDirectionType next_dir)
{
	eRunInfoType next_run_info;

	next_run_info = (eRunInfoType)((4 + next_dir - my_dir) % 4);

	return next_run_info;
}