/*
	�����ġ
*/
#ifndef __real_program__
#define __real_program__

#pragma pack(1)

//106
typedef struct real_program{

	int index;		
	char code[6];		// �����ڵ�[6]
	char time[6];   	// 0. ü��ð�[6]
	double price;   		// 1. ���簡
	double plus_minus;   	// 2. ���ϴ���ȣ[1]
	double change_price;   // 3. ���ϴ��
	double increase_rate;  // 4. �����
	double cul_volume;   	// 5. �����ŷ���
	double sell_volume;   	// 6. �ŵ�����
	double sell_amount;   	// 7. �ŵ��ݾ�
	double buy_volume;   	// 8. �ż�����
	double buy_amount;   	// 9. �ż��ݾ�
	double net_buy_volume; // 10. ���ż�����
	double net_buy_amount; // 11. ���ż��ݾ�
	double a1;   			// 12. ���ż��ݾ�����
	double a2;   			// 13. ����ۿ����ܿ��ð�
	double market;   		// 14. ������
	double ticker;   		// 15. �����ں�ticker
	
} real_program;

typedef struct real_program_data{
	int data_cnt;
	real_program data[3000];
} real_program_data;

#pragma pack()

#endif
