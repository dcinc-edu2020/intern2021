/*==============================================================================*/
/* Run Route Judgement C File							*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "maze_data.h"
#include "step_map_judgement.h"
#include "tire_control.h"
#include "run_route_judgement.h"

/*------------------------------------------------------------------------------*/
/* Global Variable								*/
/*------------------------------------------------------------------------------*/
unsigned int run_route[MAZESIZE_X * MAZESIZE_Y];	// 走行経路記録用配列 最大：6×6

/*------------------------------------------------------------------------------*/
/* Function prototype								*/
/*------------------------------------------------------------------------------*/
static void init_run_route(void);					// 走行経路情報初期化
static int judgement_next_run_mode(int next_direction, int my_dir);	// 走行モード判定
static int get_next_direction(int my_pos_x, int my_pos_y, int my_dir);	// 進行方向取得
static int get_priority(int my_dir, int next_dir);			// 行先優先度算出

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* 最短走行				                                        */
/* 										*/
/* 歩数マップの小さい方向に向かって走行する					*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-		       					*/
/*			-							*/
/*  Return   :         	-							*/
/*==============================================================================*/
void create_run_route(void)
{
	int next_direction;		// 次に進むべき方向
	
	/* 初期位置の設定 */
	int my_pos_x = 0;		// 初期座標(0,1) …プログラム起動時に必ず1マス北へ進むため
	int my_pos_y = 1;		// 初期座標(0,1)
	int my_direction  = NORTH;	// 初期の向きは必ず北向き
	
	int route_count = 0;		// 走行経路カウント変数
	
	/* 走行経路情報の初期化 */
	init_run_route();
	
	/* ゴール位置に到達するまで歩数マップに従って走行経路を作成する */
	while( (my_pos_x != GOAL_X) || (my_pos_y != GOAL_Y) )
	{	
		/* 次に進むべき方向を取得する */
		next_direction = get_next_direction(my_pos_x, my_pos_y, my_direction);
		
		/* 現在の自車向きと次に進むべき方向から走行経路を設定 */
		run_route[route_count] = judgement_next_run_mode(next_direction, my_direction);
		my_direction = next_direction;
		route_count++;
		
		/* 座標更新 */
		switch(my_direction)
		{
			case NORTH:
				my_pos_y++;		// 北へ進んだ時はY座標を増やす
				break;
			case EAST:
				my_pos_x++;		// 西へ進んだ時はX座標を減らす
				break;		
			case WEST:
				my_pos_x--;		// 東へ進んだ時はX座標を増やす
				break;	
			case SOUTH:
				my_pos_y--;		// 南へ進んだ時はY座標を増やす
				break;
			default:
				break;			
		}
	}
	
	/* ゴールの設定 */
	run_route[route_count] = Stop;
	
	return;
}

/*==============================================================================*/
/* 進行方向取得				                                        */
/* 										*/
/* 歩数マップに従って次に向かう方向を取得する					*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		my_pos_x	自車位置のX座標				*/
/*			my_pos_y	自車位置のY座標				*/
/*			my_direction	自車の現在向いている方向		*/
/*  Return   :         	next_direction	次に向かう方向				*/
/*==============================================================================*/
static int get_next_direction(int my_pos_x, int my_pos_y, int my_dir)
{
	int next_direction;	// 進行方向
	int priority 	 = 0;	// 進行方向の優先度
	int tmp_priority = 0;	// 進行方向の優先度(一時的に格納用)

	unsigned int min_step;				// 最小歩数ステップ
	min_step = step_map[my_pos_x][my_pos_y];	// 現在位置の歩数ステップを最小歩数ステップに設定
	
	
	// 現在位置から歩数マップが一番低い方向に向かう
	if(my_pos_y < MAZESIZE_Y-1)				// 北：範囲チェック
	{
		if( wall_info[my_pos_x][my_pos_y].north == NO_WALL )
		{
			tmp_priority = get_priority(my_dir, NORTH);		// 自車の向いている方向から優先度を算出
			if((step_map[my_pos_x][my_pos_y + 1] < min_step))	// 北に1マス進んだ場合の歩数マップが小さければ
			{
				min_step = step_map[my_pos_x][my_pos_y + 1];	// ひとまず北を最小ステップとする
				next_direction  = NORTH;			// 方向を保存
				priority	= tmp_priority;			// 優先度を保存
			}
			else if((step_map[my_pos_x][my_pos_y + 1] == min_step))	// 歩数が同じ場合は優先度から判断する
			{
				if(priority < tmp_priority)		// 優先度を評価
				{
					next_direction  = NORTH;	// 方向を更新
					priority = tmp_priority;	// 優先度を保存
				}				
			}
		}
	}
	
	if(my_pos_x < MAZESIZE_X-1)				// 東：範囲チェック
	{
		if( wall_info[my_pos_x][my_pos_y].east == NO_WALL )
		{
			tmp_priority = get_priority(my_dir, EAST);		// 自車の向いている方向から優先度を算出
			if((step_map[my_pos_x + 1][my_pos_y] < min_step))	// 東に1マス進んだ場合の歩数マップが小さければ
			{
				min_step = step_map[my_pos_x + 1][my_pos_y];	// ひとまず東を最小ステップとする
				next_direction  = EAST;				// 方向を保存
				priority	= tmp_priority;			// 優先度を保存
			}
			else if((step_map[my_pos_x + 1][my_pos_y] == min_step))	// 歩数が同じ場合は優先度から判断する
			{
				if(priority < tmp_priority)		// 優先度を評価
				{
					next_direction  = EAST;		// 方向を更新
					priority = tmp_priority;	// 優先度を保存
				}				
			}
		}
	}
	
	if(my_pos_x > 0)	// // 西：範囲チェック
	{
		if( wall_info[my_pos_x][my_pos_y].west == NO_WALL )
		{
			tmp_priority = get_priority(my_dir, WEST);		// 自車の向いている方向から優先度を算出
			if((step_map[my_pos_x - 1][my_pos_y] < min_step))	// 東に1マス進んだ場合の歩数マップが小さければ
			{
				min_step = step_map[my_pos_x - 1][my_pos_y];	// ひとまず東を最小ステップとする
				next_direction  = WEST;				// 方向を保存
				priority	= tmp_priority;			// 優先度を保存
			}
			else if((step_map[my_pos_x - 1][my_pos_y] == min_step))	// 歩数が同じ場合は優先度から判断する
			{
				if(priority < tmp_priority)		// 優先度を評価
				{
					next_direction  = WEST;		// 方向を更新
					priority = tmp_priority;	// 優先度を保存
				}				
			}
		}
	}
	
	if(my_pos_y > 0)	// // 南：範囲チェック
	{
		if( wall_info[my_pos_x][my_pos_y].south == NO_WALL )
		{
			tmp_priority = get_priority(my_dir, SOUTH);		// 自車の向いている方向から優先度を算出
			if((step_map[my_pos_x][my_pos_y - 1] < min_step))	// 東に1マス進んだ場合の歩数マップが小さければ
			{
				min_step = step_map[my_pos_x][my_pos_y - 1];	// ひとまず東を最小ステップとする
				next_direction  = SOUTH;			// 方向を保存
				priority	= tmp_priority;			// 優先度を保存
			}
			else if((step_map[my_pos_x][my_pos_y - 1] == min_step))	// 歩数が同じ場合は優先度から判断する
			{
				if(priority < tmp_priority)		// 優先度を評価
				{
					next_direction  = SOUTH;	// 方向を更新
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
/* 行先優先度算出			                                        */
/* 										*/
/* 座標X,Yと、自車が向いている方角dirから優先度を算出する			*/
/*   ・自車の向きと行きたい方向から、前(2)横(1)後(0)として優先度を付加する	*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		my_dir		現在向いている方角		       	*/
/*			next_dir	行きたい方角				*/
/*  Return   :         	get_priority	優先度(0～2)				*/
/*==============================================================================*/
static int get_priority(int my_dir, int next_dir)
{	
	int priority = 0;	// 優先度を記録する変数

	/* 優先度算出 */
	if(my_dir == next_dir)					// 行きたい方向が現在の進行方向と同じ場合
	{
		priority = 3;	// 前
	}
	else if( ((4 + my_dir - next_dir) % 4) == SOUTH)	// 行きたい方向が現在の進行方向と逆の場合
	{
		priority = 0;	// 後
	}
	else if( ((4 + my_dir - next_dir) % 4) == EAST)		// 行きたい方向が東の場合
	{
		priority = 2;	// 右
	}
	else if( ((4 + my_dir - next_dir) % 4) == WEST)		// 行きたい方向が西の場合
	{
		priority = 1;	// 左
	}

	return priority;
}

/*==============================================================================*/
/* 走行経路情報初期化				                                */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-		       					*/
/*			-							*/
/*  Return   :         	-							*/
/*==============================================================================*/
static void init_run_route(void)
{
	int route_cnt;
		
	for(route_cnt = 0; route_cnt < (MAZESIZE_X * MAZESIZE_Y); route_cnt++)
	{
		run_route[route_cnt] = INVALID_VALUE;
	}
	
	return;
}

/*==============================================================================*/
/* 走行モード判定			                                        */
/* 										*/
/* 現在の自車の向きと次に行くべき方向から走行モードを判定する			*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		next_direction	次に向かう方向				*/
/*			my_dir		自車の現在向いている方向		*/
/*  Return   :         	next_run_mode	走行モード				*/
/*==============================================================================*/
static int judgement_next_run_mode(int next_direction, int my_dir)
{
	int next_run_mode;
	
	next_run_mode = ((4 + next_direction - my_dir) % 4);
	
	return next_run_mode;
}