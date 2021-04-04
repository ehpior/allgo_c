/*
	�����ġ
*/
#ifndef __real_cheg__
#define __real_cheg__

#pragma pack(1)

//106
typedef struct real_cheg{

	int index;			// index
	char code[6];		// �����ڵ�[6]
	char time[6];   	// 0. ü��ð�[6]
	float price;   		// 1. ���簡
	float change_price;   // 2. ���ϴ��
	float increase_rate; 	// 3. �����
	float sell_1;      	// 4. �ֿ켱 �ŵ�ȣ��
	float buy_1;      	// 5. �ֿ켱 �ż�ȣ��
	float volume;      	// 6. �ŷ���
	float cul_volume;   	// 7. �����ŷ���
	float cul_amount;   	// 8. �����ŷ����
	float open;      		// 9. �ð�
	float high;      		// 10. ��
	float low;      		// 11. ����
	float plus_minus;   	// 12. ���ϴ���ȣ[1]
	float a1;      		// 13. ���ϰŷ������
	float a2;      		// 14. �ŷ��������
	float a3;      		// 15. ���ϰŷ������(����)
	float turn_over;   	// 16. �ŷ�ȸ����
	float a4;      		// 17. �ŷ����
	float volume_power;   // 18. ü�ᰭ��
	float capitalization; // 19. �ð��Ѿ�(��)
	float market;      	// 20. �屸��
	float a5;      		// 21. KO���ٵ�
	float high_time;   	// 22. ���Ѱ��߻��ð�
	float low_time;      	// 23. ���Ѱ��߻��Ⱓ
	
} real_cheg;

typedef struct real_cheg_data{
	int data_cnt;
	real_cheg data[3000];
} real_cheg_data;

#pragma pack()

#endif
