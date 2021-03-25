/*
	종목배치
*/
#ifndef __real_cheg__
#define __real_cheg__

#pragma pack(1)

//200
typedef struct real_cheg{

	int index;			// index
	char code[6];		// 종목코드[6]
	char time[6];   	// 0. 체결시간[6]
	double price;   		// 1. 현재가
	double change_price;   // 2. 전일대비
	double increase_rate; 	// 3. 등락율
	double sell_1;      	// 4. 최우선 매도호가
	double buy_1;      	// 5. 최우선 매수호가
	double volume;      	// 6. 거래량
	double cul_volume;   	// 7. 누적거래량
	double cul_amount;   	// 8. 누적거래대금
	double open;      		// 9. 시가
	double high;      		// 10. 고가
	double low;      		// 11. 저가
	double plus_minus;   	// 12. 전일대비기호[1]
	double a1;      		// 13. 전일거래량대비
	double a2;      		// 14. 거래대금증감
	double a3;      		// 15. 전일거래량대비(비율)
	double turn_over;   	// 16. 거래회전율
	double a4;      		// 17. 거래비용
	double volume_power;   // 18. 체결강도
	double capitalization; // 19. 시가총액(억)
	double market;      	// 20. 장구분
	double a5;      		// 21. KO접근도
	double high_time;   	// 22. 상한가발생시간
	double low_time;      	// 23. 하한가발생기간
	
} real_cheg;

typedef struct real_cheg_data{
	int data_cnt;
	real_cheg data[3000];
} real_cheg_data;

#pragma pack()

#endif
