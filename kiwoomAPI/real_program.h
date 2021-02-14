/*
	종목배치
*/
#ifndef __real_program__
#define __real_program__

#pragma pack(1)

//69
typedef struct real_program{

	char code[6];		// 종목코드[6]
	char time[6];   	// 0. 체결시간[6]
	int price;   		// 1. 현재가
	char plus_minus;   	// 2. 전일대비기호[1]
	int change_price;   // 3. 전일대비
	int increase_rate;  // 4. 등락율
	int cul_volume;   	// 5. 누적거래량
	int sell_volume;   	// 6. 매도수량
	int sell_amount;   	// 7. 매도금액
	int buy_volume;   	// 8. 매수수량
	int buy_amount;   	// 9. 매수금액
	int net_buy_volume; // 10. 순매수수량
	int net_buy_amount; // 11. 순매수금액
	int a1;   			// 12. 순매수금액증감
	int a2;   			// 13. 장시작예상잔여시간
	int market;   		// 14. 장운영구분
	int ticker;   		// 15. 투자자별ticker
	
} real_program;

#pragma pack()

#endif
