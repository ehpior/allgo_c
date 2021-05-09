/*
	종목배치
*/
#ifndef __real_cheg__
#define __real_cheg__

#pragma pack(1)

//106
typedef struct real_cheg{

	int index;			// index
	char code[6];		// 종목코드[6]
	char time[6];   	// 0. 체결시간[6]
	float price;   		// 1. 현재가
	float change_price;   // 2. 전일대비
	float increase_rate; 	// 3. 등락율
	float sell_1;      	// 4. 최우선 매도호가
	float buy_1;      	// 5. 최우선 매수호가
	float volume;      	// 6. 거래량
	float cul_volume;   	// 7. 누적거래량
	float cul_amount;   	// 8. 누적거래대금
	float open;      		// 9. 시가
	float high;      		// 10. 고가
	float low;      		// 11. 저가
	float plus_minus;   	// 12. 전일대비기호[1]
	float a1;      		// 13. 전일거래량대비
	float a2;      		// 14. 거래대금증감
	float a3;      		// 15. 전일거래량대비(비율)
	float turn_over;   	// 16. 거래회전율
	float a4;      		// 17. 거래비용
	float volume_power;   // 18. 체결강도
	float capitalization; // 19. 시가총액(억)
	float market;      	// 20. 장구분
	float a5;      		// 21. KO접근도
	float high_time;   	// 22. 상한가발생시간
	float low_time;      	// 23. 하한가발생기간
	
} real_cheg;

typedef struct real_cheg_data{
	int data_cnt;
	real_cheg data[5000];
} real_cheg_data;

#pragma pack()

#endif
