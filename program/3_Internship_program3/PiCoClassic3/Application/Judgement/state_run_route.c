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
eRunInfoType route_run_info;		// �ŒZ�o�H���s�w�����

/*------------------------------------------------------------------------------*/
/* Static Variable								*/
/*------------------------------------------------------------------------------*/
static int my_pos_x;		// �ԑ̍��Wx
static int my_pos_y;		// �ԑ̍��Wy
static eDirectionType my_direction;	// �ԑ̂̌���

/*------------------------------------------------------------------------------*/
/* Function prototype								*/
/*------------------------------------------------------------------------------*/
static eRunInfoType judgement_next_run_info(eDirectionType my_dir, eDirectionType next_dir);	// ���s�w����񔻒�
static eDirectionType get_next_direction(int my_pos_x, int my_pos_y, eDirectionType my_dir);	// �i�s�����擾
static int get_priority(eDirectionType my_dir, eDirectionType next_dir);			// �s��D��x�Z�o

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* �o�H���s������								*/
/* ---------------------------------------------------------------------------- */
/*  ����:		-							*/
/*  �o��:		-							*/
/*==============================================================================*/
void init_run_route(void)
{
	route_run_info = Stop;

	// �����ʒu�F(0,0) �k����
	my_pos_x = 0;
	my_pos_y = 0;
	my_direction = North;

	return;
}

/*==============================================================================*/
/* �ŒZ�o�H���s									*/
/* 										*/
/* �����}�b�v�̏����������Ɍ������đ��s����					*/
/* ---------------------------------------------------------------------------- */
/*  ����:		wall_info		�}�b�v�Ǐ��			*/
/*			step_map		�����}�b�v			*/
/*  �o��:		route_run_info		�ŒZ�o�H���s�w�����		*/
/*==============================================================================*/
void run_route()
{
	int switch_state_left;		// ���X�C�b�`(��)�̏��
	eDirectionType next_direction;	// ���ɐi�ނׂ�����

	if( (my_pos_x == 0) && (my_pos_y == 0) )
	{
		// �{�^���������ꂽ��1���ڂ�i��

		// ���{�^�����������܂Œ�~
		route_run_info = Stop;
		switch_state_left   = get_switch_state(MODE_SW_RED);
		if( switch_state_left == SW_ON )
		{
			// 1���ڂ͕K�����1���i�ށi���̃}�X�Ƃ̋��ڂ܂Ői�ނ̂Ŕ����j
			route_run_info = Half;
			my_pos_x = 0;
			my_pos_y = 1;
			my_direction = North;
		}
	}
	else if( (my_pos_x != GOAL_X) || (my_pos_y != GOAL_Y) )
	{
		// �S�[���ʒu�ɓ��B����܂Ń}�b�v�Ǐ��A�����}�b�v�ɏ]���đ��s����

		// �}�b�v�Ǐ��A�����}�b�v�����Ɏ��ɐi�ނׂ����������肷��
		next_direction = get_next_direction(my_pos_x, my_pos_y, my_direction);

		// ���݂̎��Ԍ����Ǝ��ɐi�ނׂ��������瑖�s�w����ݒ�
		route_run_info = judgement_next_run_info(my_direction, next_direction);

		// �ԑ̏��X�V
		my_direction = next_direction;
		switch(my_direction)
		{
			case North:
				my_pos_y++;		// �k�֐i�񂾎���Y���W�𑝂₷
				break;
			case East:
				my_pos_x++;		// ���֐i�񂾎���X���W�����炷
				break;
			case West:
				my_pos_x--;		// ���֐i�񂾎���X���W�𑝂₷
				break;
			case South:
				my_pos_y--;		// ��֐i�񂾎���Y���W�𑝂₷
				break;
			default:
				break;
		}
	}else{
		// �S�[���������~����
		route_run_info = Stop;
	}

	return;
}

/*==============================================================================*/
/* �i�s�����擾									*/
/* 										*/
/* �����}�b�v�ɏ]���Ď��Ɍ������������擾����					*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		my_pos_x	���Ԉʒu��X���W				*/
/*			my_pos_y	���Ԉʒu��Y���W				*/
/*			my_direction	���Ԃ̌��݌����Ă������		*/
/*  Return   :		next_direction	���Ɍ���������				*/
/*==============================================================================*/
static eDirectionType get_next_direction(int my_pos_x, int my_pos_y, eDirectionType my_dir)
{
	eDirectionType next_direction;	// �i�s����
	int priority 	 = 0;	// �i�s�����̗D��x
	int tmp_priority = 0;	// �i�s�����̗D��x(�ꎞ�I�Ɋi�[�p)

	unsigned int min_step;				// �ŏ������X�e�b�v
	min_step = step_map[my_pos_x][my_pos_y];	// ���݈ʒu�̕����X�e�b�v���ŏ������X�e�b�v�ɐݒ�

	// ���݈ʒu��������}�b�v����ԒႢ�����Ɍ�����
	if(my_pos_y < MAZESIZE_Y-1)				// �k�F�͈̓`�F�b�N
	{
		if( wall_info[my_pos_x][my_pos_y].north == NO_WALL )
		{
			tmp_priority = get_priority(my_dir, North);		// ���Ԃ̌����Ă����������D��x���Z�o
			if((step_map[my_pos_x][my_pos_y + 1] < min_step))	// �k��1�}�X�i�񂾏ꍇ�̕����}�b�v�����������
			{
				min_step = step_map[my_pos_x][my_pos_y + 1];	// �ЂƂ܂��k���ŏ��X�e�b�v�Ƃ���
				next_direction  = North;			// ������ۑ�
				priority	= tmp_priority;			// �D��x��ۑ�
			}
			else if((step_map[my_pos_x][my_pos_y + 1] == min_step))	// �����������ꍇ�͗D��x���画�f����
			{
				if(priority < tmp_priority)		// �D��x��]��
				{
					next_direction  = North;	// �������X�V
					priority = tmp_priority;	// �D��x��ۑ�
				}
			}
		}
	}

	if(my_pos_x < MAZESIZE_X-1)				// ���F�͈̓`�F�b�N
	{
		if( wall_info[my_pos_x][my_pos_y].east == NO_WALL )
		{
			tmp_priority = get_priority(my_dir, East);		// ���Ԃ̌����Ă����������D��x���Z�o
			if((step_map[my_pos_x + 1][my_pos_y] < min_step))	// ����1�}�X�i�񂾏ꍇ�̕����}�b�v�����������
			{
				min_step = step_map[my_pos_x + 1][my_pos_y];	// �ЂƂ܂������ŏ��X�e�b�v�Ƃ���
				next_direction  = East;				// ������ۑ�
				priority	= tmp_priority;			// �D��x��ۑ�
			}
			else if((step_map[my_pos_x + 1][my_pos_y] == min_step))	// �����������ꍇ�͗D��x���画�f����
			{
				if(priority < tmp_priority)		// �D��x��]��
				{
					next_direction  = East;		// �������X�V
					priority = tmp_priority;	// �D��x��ۑ�
				}
			}
		}
	}

	if(my_pos_x > 0)	// // ���F�͈̓`�F�b�N
	{
		if( wall_info[my_pos_x][my_pos_y].west == NO_WALL )
		{
			tmp_priority = get_priority(my_dir, West);		// ���Ԃ̌����Ă����������D��x���Z�o
			if((step_map[my_pos_x - 1][my_pos_y] < min_step))	// ����1�}�X�i�񂾏ꍇ�̕����}�b�v�����������
			{
				min_step = step_map[my_pos_x - 1][my_pos_y];	// �ЂƂ܂������ŏ��X�e�b�v�Ƃ���
				next_direction  = West;				// ������ۑ�
				priority	= tmp_priority;			// �D��x��ۑ�
			}
			else if((step_map[my_pos_x - 1][my_pos_y] == min_step))	// �����������ꍇ�͗D��x���画�f����
			{
				if(priority < tmp_priority)		// �D��x��]��
				{
					next_direction  = West;		// �������X�V
					priority = tmp_priority;	// �D��x��ۑ�
				}
			}
		}
	}

	if(my_pos_y > 0)	// // ��F�͈̓`�F�b�N
	{
		if( wall_info[my_pos_x][my_pos_y].south == NO_WALL )
		{
			tmp_priority = get_priority(my_dir, South);		// ���Ԃ̌����Ă����������D��x���Z�o
			if((step_map[my_pos_x][my_pos_y - 1] < min_step))	// ����1�}�X�i�񂾏ꍇ�̕����}�b�v�����������
			{
				min_step = step_map[my_pos_x][my_pos_y - 1];	// �ЂƂ܂������ŏ��X�e�b�v�Ƃ���
				next_direction  = South;			// ������ۑ�
				priority	= tmp_priority;			// �D��x��ۑ�
			}
			else if((step_map[my_pos_x][my_pos_y - 1] == min_step))	// �����������ꍇ�͗D��x���画�f����
			{
				if(priority < tmp_priority)		// �D��x��]��
				{
					next_direction  = South;	// �������X�V
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
/* �s��D��x�Z�o								*/
/* 										*/
/* ���݌����Ă�����p�ƁA�s���������p����D��x���Z�o����			*/
/* �D��x�͍������ɁA���i(3)�A�E��(2)�A����(1)�AU�^�[��(0)�Ƃ���		*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		my_dir		���݌����Ă�����p			*/
/*			next_dir	�s���������p				*/
/*  Return   :		priority	�D��x(0�`3)				*/
/*==============================================================================*/
static int get_priority(eDirectionType my_dir, eDirectionType next_dir)
{
	int priority = 0;	// �D��x���L�^����ϐ�

	/* �D��x�Z�o */
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
/* ���s�w����񔻒�								*/
/* 										*/
/* ���݂̎��Ԃ̌����Ǝ��ɍs���ׂ��������瑖�s�w�����𔻒肷��			*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		next_direction	���Ɍ���������				*/
/*			my_dir		���Ԃ̌��݌����Ă������		*/
/*  Return   :		next_run_info	���s�w�����				*/
/*==============================================================================*/
static eRunInfoType judgement_next_run_info(eDirectionType my_dir, eDirectionType next_dir)
{
	eRunInfoType next_run_info;

	next_run_info = (eRunInfoType)((4 + next_dir - my_dir) % 4);

	return next_run_info;
}