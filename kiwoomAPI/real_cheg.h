/*
	�����ġ
*/
#ifndef __real_cheg__
#define __real_cheg__

#pragma pack(1)

//101
typedef struct real_cheg{

	char code[6];		// �����ڵ�[6]
	char time[6];   	// 0. ü��ð�[6]
	int price;   		// 1. ���簡
	int change_price;   // 2. ���ϴ��
	int increase_rate; 	// 3. �����
	int sell_1;      	// 4. �ֿ켱 �ŵ�ȣ��
	int buy_1;      	// 5. �ֿ켱 �ż�ȣ��
	int volume;      	// 6. �ŷ���
	int cul_volume;   	// 7. �����ŷ���
	int cul_amount;   	// 8. �����ŷ����
	int open;      		// 9. �ð�
	int high;      		// 10. ��
	int low;      		// 11. ����
	char plus_minus;   	// 12. ���ϴ���ȣ[1]
	int a1;      		// 13. ���ϰŷ������
	int a2;      		// 14. �ŷ��������
	int a3;      		// 15. ���ϰŷ������(����)
	int turn_over;   	// 16. �ŷ�ȸ����
	int a4;      		// 17. �ŷ����
	int volume_power;   // 18. ü�ᰭ��
	int capitalization; // 19. �ð��Ѿ�(��)
	int market;      	// 20. �屸��
	int a5;      		// 21. KO���ٵ�
	int high_time;   	// 22. ���Ѱ��߻��ð�
	int low_time;      	// 23. ���Ѱ��߻��Ⱓ
	
} real_cheg;

#pragma pack()

#endif
