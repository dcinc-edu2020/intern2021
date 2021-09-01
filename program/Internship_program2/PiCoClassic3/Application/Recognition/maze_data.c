/*==============================================================================*/
/* Maze Data C File								*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "maze_data.h"

/*------------------------------------------------------------------------------*/
/* Global Variable								*/
/*------------------------------------------------------------------------------*/
const int 	goal_x = GOAL_X;			// ゴール座標：X
const int 	goal_y = GOAL_Y;			// ゴール座標：Y
const st_wall	wall_info[MAZESIZE_X][MAZESIZE_Y] =	// 迷路の壁情報を格納する構造体配列
{
	{
		/* X = 0 */
		{NO_WALL, WALL	 , WALL	  , WALL},	// (0,0)　┗━┛
		{NO_WALL, WALL	 , NO_WALL, WALL},	// (0,1)　┃　┃
		{NO_WALL, WALL	 , NO_WALL, WALL},	// (0,2)　┃　┃
		{NO_WALL, WALL	 , NO_WALL, WALL},	// (0,3)　┃　┃
		{NO_WALL, NO_WALL, NO_WALL, WALL},	// (0,4)　┃
		{WALL	, NO_WALL, NO_WALL, WALL},	// (0,5)　┏━
	},
	{
		/* X = 1 */
		{NO_WALL, NO_WALL, WALL	  , WALL},	// (1,0)　┗━
		{NO_WALL, WALL	 , NO_WALL, WALL},	// (1,1)　┃　┃
		{WALL,	  WALL	 , NO_WALL, WALL},	// (1,2)　┃　┃
		{NO_WALL, NO_WALL, WALL, WALL},		// (1,3)　┃　┃
		{WALL, NO_WALL	 , NO_WALL, NO_WALL},	// (1,4)　┏━
		{WALL, NO_WALL   , WALL   , NO_WALL},	// (1,5)　		
	},
	{
		/* X = 2 */
		{WALL, NO_WALL, WALL,NO_WALL},		// (2,0)
		{WALL, WALL, WALL,WALL},		// (2,1)
		{NO_WALL, NO_WALL, WALL,WALL},		// (2,2)
		{WALL, WALL, NO_WALL,NO_WALL},		// (2,3)
		{WALL, NO_WALL, WALL,NO_WALL},		// (2,4)
		{WALL, NO_WALL, WALL,NO_WALL},		// (2,5)		
	},
	{
		{WALL, NO_WALL, WALL,NO_WALL},		// (3,0)
		{NO_WALL, NO_WALL, WALL,WALL},		// (3,1)
		{WALL, WALL, NO_WALL,NO_WALL},		// (3,2)
		{WALL, NO_WALL, WALL,WALL},		// (3,3)
		{WALL, NO_WALL, WALL,NO_WALL},		// (3,4)
		{WALL, NO_WALL, WALL,NO_WALL},		// (3,5)		
	},
	{
		{WALL, NO_WALL, WALL,NO_WALL},		// (4,0)
		{WALL, NO_WALL, WALL,NO_WALL},		// (4,1)
		{WALL, NO_WALL, WALL,WALL},		// (4,2)
		{WALL, NO_WALL, WALL,NO_WALL},		// (4,3)
		{WALL, WALL, WALL,NO_WALL},		// (4,4)
		{WALL, NO_WALL, WALL,NO_WALL},		// (4,5)		
	},
	{
		{NO_WALL, WALL, WALL,NO_WALL},		// (5,0)
		{NO_WALL, WALL, NO_WALL,NO_WALL},	// (5,1)
		{NO_WALL, WALL, NO_WALL,NO_WALL},	// (5,2)
		{NO_WALL, WALL, NO_WALL,NO_WALL},	// (5,3)
		{NO_WALL, WALL, NO_WALL,WALL},		// (5,4)
		{WALL, WALL, NO_WALL,NO_WALL}		// (5,5)		
	},
};