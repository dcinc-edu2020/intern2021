/*==============================================================================*/
/* Switch Driver Header File							*/
/*==============================================================================*/
#ifndef _SWITCH_DRIVER_H
#define _SWITCH_DRIVER_H

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* ���[�h�I���X�C�b�`��� */
#define MODE_SW_RED	(0)			// ���X�C�b�`	(��)
#define MODE_SW_YELLOW	(1)			// �����X�C�b�`	(��)
#define MODE_SW_BLUE	(2)			// �E�X�C�b�`	(��)

/* ���[�h�I���X�C�b�`��� */
#define SW_LEFT		(PORT3.PIDR.BIT.B1)	// ���X�C�b�`	(��)
#define SW_CENTER	(PORTC.PIDR.BIT.B3)	// �����X�C�b�`	(��)
#define SW_RIGHT	(PORTC.PIDR.BIT.B2)	// �E�X�C�b�`	(��)

/* �X�C�b�`��� */
#define SW_OFF		(1)			// �X�C�b�`��OFF�̎��Ɏ��l
#define SW_ON		(0)			// �X�C�b�`��ON�̎��Ɏ��l

/* �X�C�b�`����p��` */
#define CHATTERING_WAIT	(50)			// �`���^�����O���p�҂�����

/*------------------------------------------------------------------------------*/
/* Function Prototype								*/
/*------------------------------------------------------------------------------*/
int get_switch_state(int switch_kind);		// �X�C�b�`��Ԏ擾

#endif