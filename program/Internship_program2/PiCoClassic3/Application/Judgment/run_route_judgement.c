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
unsigned int run_route[MAZESIZE_X * MAZESIZE_Y];	// ���s�o�H�L�^�p�z�� �ő�F6�~6

/*------------------------------------------------------------------------------*/
/* Function prototype								*/
/*------------------------------------------------------------------------------*/
static void init_run_route(void);					// ���s�o�H��񏉊���
static int judgement_next_run_mode(int next_direction, int my_dir);	// ���s���[�h����
static int get_next_direction(int my_pos_x, int my_pos_y, int my_dir);	// �i�s�����擾
static int get_priority(int my_dir, int next_dir);			// �s��D��x�Z�o

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* �ŒZ���s				                                        */
/* 										*/
/* �����}�b�v�̏����������Ɍ������đ��s����					*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-		       					*/
/*			-							*/
/*  Return   :         	-							*/
/*==============================================================================*/
void create_run_route(void)
{
	int next_direction;		// ���ɐi�ނׂ�����
	
	/* �����ʒu�̐ݒ� */
	int my_pos_x = 0;		// �������W(0,1) �c�v���O�����N�����ɕK��1�}�X�k�֐i�ނ���
	int my_pos_y = 1;		// �������W(0,1)
	int my_direction  = NORTH;	// �����̌����͕K���k����
	
	int route_count = 0;		// ���s�o�H�J�E���g�ϐ�
	
	/* ���s�o�H���̏����� */
	init_run_route();
	
	/* �S�[���ʒu�ɓ��B����܂ŕ����}�b�v�ɏ]���đ��s�o�H���쐬���� */
	while( (my_pos_x != GOAL_X) || (my_pos_y != GOAL_Y) )
	{	
		/* ���ɐi�ނׂ��������擾���� */
		next_direction = get_next_direction(my_pos_x, my_pos_y, my_direction);
		
		/* ���݂̎��Ԍ����Ǝ��ɐi�ނׂ��������瑖�s�o�H��ݒ� */
		run_route[route_count] = judgement_next_run_mode(next_direction, my_direction);
		my_direction = next_direction;
		route_count++;
		
		/* ���W�X�V */
		switch(my_direction)
		{
			case NORTH:
				my_pos_y++;		// �k�֐i�񂾎���Y���W�𑝂₷
				break;
			case EAST:
				my_pos_x++;		// ���֐i�񂾎���X���W�����炷
				break;		
			case WEST:
				my_pos_x--;		// ���֐i�񂾎���X���W�𑝂₷
				break;	
			case SOUTH:
				my_pos_y--;		// ��֐i�񂾎���Y���W�𑝂₷
				break;
			default:
				break;			
		}
	}
	
	/* �S�[���̐ݒ� */
	run_route[route_count] = Stop;
	
	return;
}

/*==============================================================================*/
/* �i�s�����擾				                                        */
/* 										*/
/* �����}�b�v�ɏ]���Ď��Ɍ������������擾����					*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		my_pos_x	���Ԉʒu��X���W				*/
/*			my_pos_y	���Ԉʒu��Y���W				*/
/*			my_direction	���Ԃ̌��݌����Ă������		*/
/*  Return   :         	next_direction	���Ɍ���������				*/
/*==============================================================================*/
static int get_next_direction(int my_pos_x, int my_pos_y, int my_dir)
{
	int next_direction;	// �i�s����
	int priority 	 = 0;	// �i�s�����̗D��x
	int tmp_priority = 0;	// �i�s�����̗D��x(�ꎞ�I�Ɋi�[�p)

	unsigned int min_step;				// �ŏ������X�e�b�v
	min_step = step_map[my_pos_x][my_pos_y];	// ���݈ʒu�̕����X�e�b�v���ŏ������X�e�b�v�ɐݒ�
	
	
	// ���݈ʒu��������}�b�v����ԒႢ�����Ɍ�����
	if(my_pos_y < MAZESIZE_Y-1)				// �k�F�͈̓`�F�b�N
	{
		if( wall_info[my_pos_x][my_pos_y].north == NO_WALL )
		{
			tmp_priority = get_priority(my_dir, NORTH);		// ���Ԃ̌����Ă����������D��x���Z�o
			if((step_map[my_pos_x][my_pos_y + 1] < min_step))	// �k��1�}�X�i�񂾏ꍇ�̕����}�b�v�����������
			{
				min_step = step_map[my_pos_x][my_pos_y + 1];	// �ЂƂ܂��k���ŏ��X�e�b�v�Ƃ���
				next_direction  = NORTH;			// ������ۑ�
				priority	= tmp_priority;			// �D��x��ۑ�
			}
			else if((step_map[my_pos_x][my_pos_y + 1] == min_step))	// �����������ꍇ�͗D��x���画�f����
			{
				if(priority < tmp_priority)		// �D��x��]��
				{
					next_direction  = NORTH;	// �������X�V
					priority = tmp_priority;	// �D��x��ۑ�
				}				
			}
		}
	}
	
	if(my_pos_x < MAZESIZE_X-1)				// ���F�͈̓`�F�b�N
	{
		if( wall_info[my_pos_x][my_pos_y].east == NO_WALL )
		{
			tmp_priority = get_priority(my_dir, EAST);		// ���Ԃ̌����Ă����������D��x���Z�o
			if((step_map[my_pos_x + 1][my_pos_y] < min_step))	// ����1�}�X�i�񂾏ꍇ�̕����}�b�v�����������
			{
				min_step = step_map[my_pos_x + 1][my_pos_y];	// �ЂƂ܂������ŏ��X�e�b�v�Ƃ���
				next_direction  = EAST;				// ������ۑ�
				priority	= tmp_priority;			// �D��x��ۑ�
			}
			else if((step_map[my_pos_x + 1][my_pos_y] == min_step))	// �����������ꍇ�͗D��x���画�f����
			{
				if(priority < tmp_priority)		// �D��x��]��
				{
					next_direction  = EAST;		// �������X�V
					priority = tmp_priority;	// �D��x��ۑ�
				}				
			}
		}
	}
	
	if(my_pos_x > 0)	// // ���F�͈̓`�F�b�N
	{
		if( wall_info[my_pos_x][my_pos_y].west == NO_WALL )
		{
			tmp_priority = get_priority(my_dir, WEST);		// ���Ԃ̌����Ă����������D��x���Z�o
			if((step_map[my_pos_x - 1][my_pos_y] < min_step))	// ����1�}�X�i�񂾏ꍇ�̕����}�b�v�����������
			{
				min_step = step_map[my_pos_x - 1][my_pos_y];	// �ЂƂ܂������ŏ��X�e�b�v�Ƃ���
				next_direction  = WEST;				// ������ۑ�
				priority	= tmp_priority;			// �D��x��ۑ�
			}
			else if((step_map[my_pos_x - 1][my_pos_y] == min_step))	// �����������ꍇ�͗D��x���画�f����
			{
				if(priority < tmp_priority)		// �D��x��]��
				{
					next_direction  = WEST;		// �������X�V
					priority = tmp_priority;	// �D��x��ۑ�
				}				
			}
		}
	}
	
	if(my_pos_y > 0)	// // ��F�͈̓`�F�b�N
	{
		if( wall_info[my_pos_x][my_pos_y].south == NO_WALL )
		{
			tmp_priority = get_priority(my_dir, SOUTH);		// ���Ԃ̌����Ă����������D��x���Z�o
			if((step_map[my_pos_x][my_pos_y - 1] < min_step))	// ����1�}�X�i�񂾏ꍇ�̕����}�b�v�����������
			{
				min_step = step_map[my_pos_x][my_pos_y - 1];	// �ЂƂ܂������ŏ��X�e�b�v�Ƃ���
				next_direction  = SOUTH;			// ������ۑ�
				priority	= tmp_priority;			// �D��x��ۑ�
			}
			else if((step_map[my_pos_x][my_pos_y - 1] == min_step))	// �����������ꍇ�͗D��x���画�f����
			{
				if(priority < tmp_priority)		// �D��x��]��
				{
					next_direction  = SOUTH;	// �������X�V
					priority = tmp_priority;	// �D��x��ۑ�
				}				
			}
		}
	}
	
	/* ���Ԃ̕����ƍs��������������ŏI�I�ȕ�����ݒ� */
	//next_direction = (4 + next_direction - my_dir) % 4;
	
	return next_direction;
}


/*==============================================================================*/
/* �s��D��x�Z�o			                                        */
/* 										*/
/* ���WX,Y�ƁA���Ԃ������Ă�����pdir����D��x���Z�o����			*/
/*   �E���Ԃ̌����ƍs��������������A�O(2)��(1)��(0)�Ƃ��ėD��x��t������	*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		my_dir		���݌����Ă�����p		       	*/
/*			next_dir	�s���������p				*/
/*  Return   :         	get_priority	�D��x(0�`2)				*/
/*==============================================================================*/
static int get_priority(int my_dir, int next_dir)
{	
	int priority = 0;	// �D��x���L�^����ϐ�

	/* �D��x�Z�o */
	if(my_dir == next_dir)					// �s���������������݂̐i�s�����Ɠ����ꍇ
	{
		priority = 3;	// �O
	}
	else if( ((4 + my_dir - next_dir) % 4) == SOUTH)	// �s���������������݂̐i�s�����Ƌt�̏ꍇ
	{
		priority = 0;	// ��
	}
	else if( ((4 + my_dir - next_dir) % 4) == EAST)		// �s���������������̏ꍇ
	{
		priority = 2;	// �E
	}
	else if( ((4 + my_dir - next_dir) % 4) == WEST)		// �s���������������̏ꍇ
	{
		priority = 1;	// ��
	}

	return priority;
}

/*==============================================================================*/
/* ���s�o�H��񏉊���				                                */
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
/* ���s���[�h����			                                        */
/* 										*/
/* ���݂̎��Ԃ̌����Ǝ��ɍs���ׂ��������瑖�s���[�h�𔻒肷��			*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		next_direction	���Ɍ���������				*/
/*			my_dir		���Ԃ̌��݌����Ă������		*/
/*  Return   :         	next_run_mode	���s���[�h				*/
/*==============================================================================*/
static int judgement_next_run_mode(int next_direction, int my_dir)
{
	int next_run_mode;
	
	next_run_mode = ((4 + next_direction - my_dir) % 4);
	
	return next_run_mode;
}