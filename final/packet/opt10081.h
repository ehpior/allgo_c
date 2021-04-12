
#ifndef __opt10081__
#define __opt10081__

typedef struct opt10081{

	char code[6];	// 0.종목코드8
	int price;		// 1.현재가4
	int volume;		// 2.거래량4
	int amount;		// 3.거래대금4
	char date[8];	// 4.일자8
	int open;		// 5.시가4
	int high;		// 6.고가4
	int low;		// 7.저가4
	int a1;			// 8.수정주가구분
	int a2;			// 9.수정비율
	int a3;			// 10.대업종구분
	int a4;			// 11.소업종구분
	int a5;			// 12.종목정보
	int a6;			// 13.수정주가이벤트
	int a7;			// 14.전일종가
	
} opt10081;

#endif
