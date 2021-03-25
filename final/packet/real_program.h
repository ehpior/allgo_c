/*
	종목배치
*/
#ifndef __real_program__
#define __real_program__

#pragma pack(1)

//106
typedef struct real_program{

	int index;		
	char code[6];		// 종목코드[6]
	char time[6];   	// 0. 체결시간[6]
	double price;   		// 1. 현재가
	double plus_minus;   	// 2. 전일대비기호[1]
	double change_price;   // 3. 전일대비
	double increase_rate;  // 4. 등락율
	double cul_volume;   	// 5. 누적거래량
	double sell_volume;   	// 6. 매도수량
	double sell_amount;   	// 7. 매도금액
	double buy_volume;   	// 8. 매수수량
	double buy_amount;   	// 9. 매수금액
	double net_buy_volume; // 10. 순매수수량
	double net_buy_amount; // 11. 순매수금액
	double a1;   			// 12. 순매수금액증감
	double a2;   			// 13. 장시작예상잔여시간
	double market;   		// 14. 장운영구분
	double ticker;   		// 15. 투자자별ticker
	
} real_program;

typedef struct real_program_data{
	int data_cnt;
	real_program data[3000];
} real_program_data;

#pragma pack()

#endif
