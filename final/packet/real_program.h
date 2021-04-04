/*
	종목배치
*/
#ifndef __real_program__
#define __real_program__

#pragma pack(1)

//76
typedef struct real_program{

	int index;		
	char code[6];		// 종목코드[6]
	char time[6];   	// 0. 체결시간[6]
	float price;   		// 1. 현재가
	float plus_minus;   	// 2. 전일대비기호[1]
	float change_price;   // 3. 전일대비
	float increase_rate;  // 4. 등락율
	float cul_volume;   	// 5. 누적거래량
	float sell_volume;   	// 6. 매도수량
	float sell_amount;   	// 7. 매도금액
	float buy_volume;   	// 8. 매수수량
	float buy_amount;   	// 9. 매수금액
	float net_buy_volume; // 10. 순매수수량
	float net_buy_amount; // 11. 순매수금액
	float a1;   			// 12. 순매수금액증감
	float a2;   			// 13. 장시작예상잔여시간
	float market;   		// 14. 장운영구분
	float ticker;   		// 15. 투자자별ticker
	
} real_program;

typedef struct real_program_data{
	int data_cnt;
	real_program data[3000];
} real_program_data;

#pragma pack()

#endif
