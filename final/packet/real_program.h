/*
	�����ġ
*/
#ifndef __real_program__
#define __real_program__

#pragma pack(1)

//76
typedef struct real_program{

	int index;		
	char code[6];		// �����ڵ�[6]
	char time[6];   	// 0. ü��ð�[6]
	float price;   		// 1. ���簡
	float plus_minus;   	// 2. ���ϴ���ȣ[1]
	float change_price;   // 3. ���ϴ��
	float increase_rate;  // 4. �����
	float cul_volume;   	// 5. �����ŷ���
	float sell_volume;   	// 6. �ŵ�����
	float sell_amount;   	// 7. �ŵ��ݾ�
	float buy_volume;   	// 8. �ż�����
	float buy_amount;   	// 9. �ż��ݾ�
	float net_buy_volume; // 10. ���ż�����
	float net_buy_amount; // 11. ���ż��ݾ�
	float a1;   			// 12. ���ż��ݾ�����
	float a2;   			// 13. ����ۿ����ܿ��ð�
	float market;   		// 14. ������
	float ticker;   		// 15. �����ں�ticker
	
} real_program;

typedef struct real_program_data{
	int data_cnt;
	real_program data[3000];
} real_program_data;

#pragma pack()

#endif
