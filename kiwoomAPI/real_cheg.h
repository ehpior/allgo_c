/*
	종목배치
*/
#ifndef __real_cheg__
#define __real_cheg__

#pragma pack(1)

//101
typedef struct real_cheg{

	char code[6];		// 종목코드[6]
	char time[6];   	// 0. 체결시간[6]
	int price;   		// 1. 현재가
	int change_price;   // 2. 전일대비
	int increase_rate; 	// 3. 등락율
	int sell_1;      	// 4. 최우선 매도호가
	int buy_1;      	// 5. 최우선 매수호가
	int volume;      	// 6. 거래량
	int cul_volume;   	// 7. 누적거래량
	int cul_amount;   	// 8. 누적거래대금
	int open;      		// 9. 시가
	int high;      		// 10. 고가
	int low;      		// 11. 저가
	char plus_minus;   	// 12. 전일대비기호[1]
	int a1;      		// 13. 전일거래량대비
	int a2;      		// 14. 거래대금증감
	int a3;      		// 15. 전일거래량대비(비율)
	int turn_over;   	// 16. 거래회전율
	int a4;      		// 17. 거래비용
	int volume_power;   // 18. 체결강도
	int capitalization; // 19. 시가총액(억)
	int market;      	// 20. 장구분
	int a5;      		// 21. KO접근도
	int high_time;   	// 22. 상한가발생시간
	int low_time;      	// 23. 하한가발생기간
	
} real_cheg;

#pragma pack()

#endif
