/*
	�����ġ
*/
#ifndef __real_program__
#define __real_program__

#pragma pack(1)

//69
typedef struct real_program{

	char code[6];		// �����ڵ�[6]
	char time[6];   	// 0. ü��ð�[6]
	int price;   		// 1. ���簡
	char plus_minus;   	// 2. ���ϴ���ȣ[1]
	int change_price;   // 3. ���ϴ��
	int increase_rate;  // 4. �����
	int cul_volume;   	// 5. �����ŷ���
	int sell_volume;   	// 6. �ŵ�����
	int sell_amount;   	// 7. �ŵ��ݾ�
	int buy_volume;   	// 8. �ż�����
	int buy_amount;   	// 9. �ż��ݾ�
	int net_buy_volume; // 10. ���ż�����
	int net_buy_amount; // 11. ���ż��ݾ�
	int a1;   			// 12. ���ż��ݾ�����
	int a2;   			// 13. ����ۿ����ܿ��ð�
	int market;   		// 14. ������
	int ticker;   		// 15. �����ں�ticker
	
} real_program;

#pragma pack()

#endif
