/*
	�����ġ
*/
#ifndef __real_cheg__
#define __real_cheg__

#pragma pack(1)

//200
typedef struct real_cheg{

	int index;			// index
	char code[6];		// �����ڵ�[6]
	char time[6];   	// 0. ü��ð�[6]
	double price;   		// 1. ���簡
	double change_price;   // 2. ���ϴ��
	double increase_rate; 	// 3. �����
	double sell_1;      	// 4. �ֿ켱 �ŵ�ȣ��
	double buy_1;      	// 5. �ֿ켱 �ż�ȣ��
	double volume;      	// 6. �ŷ���
	double cul_volume;   	// 7. �����ŷ���
	double cul_amount;   	// 8. �����ŷ����
	double open;      		// 9. �ð�
	double high;      		// 10. ��
	double low;      		// 11. ����
	double plus_minus;   	// 12. ���ϴ���ȣ[1]
	double a1;      		// 13. ���ϰŷ������
	double a2;      		// 14. �ŷ��������
	double a3;      		// 15. ���ϰŷ������(����)
	double turn_over;   	// 16. �ŷ�ȸ����
	double a4;      		// 17. �ŷ����
	double volume_power;   // 18. ü�ᰭ��
	double capitalization; // 19. �ð��Ѿ�(��)
	double market;      	// 20. �屸��
	double a5;      		// 21. KO���ٵ�
	double high_time;   	// 22. ���Ѱ��߻��ð�
	double low_time;      	// 23. ���Ѱ��߻��Ⱓ
	
} real_cheg;

typedef struct real_cheg_data{
	int data_cnt;
	real_cheg data[3000];
} real_cheg_data;

#pragma pack()

#endif
