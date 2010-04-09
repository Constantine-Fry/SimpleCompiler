/* 
 * File:   lexems.h
 * Author: Dred
 *
 * Created on 9 Апрель 2010 г., 1:01
 */

//Лексемы
enum {
//	RIGHT_ASSIGN=10,
//	LEFT_ASSIGN,
//	ADD_ASSIGN,
//	SUB_ASSIGN,
//	MUL_ASSIGN,
//	DIV_ASSIGN,
//	MOD_ASSIGN,
//	AND_ASSIGN,
//	XOR_ASSIGN,
//	OR_ASSIGN,
//	RIGHT_OP,
//	LEFT_OP,
	INC_OP = 10,//++
	DEC_OP,//--
	AND_OP,//&
	OR_OP,//||
	LE_OP,//
	GE_OP,//>=
	EQ_OP,//==
	NE_OP,//<=
	MUL_OP,//*
	SUB_OP,//-
	DIV_OP,// /
	ADD_OP,//+
	MOV_OP,//=
	IDENTIFIER,
	KEYWORD
};

//Ключевые слова
char *gKeywords[] = { "break", "case", "char", "do", "else", "for",
	"goto", "if", "int16", "int32", "switch", "while", 0
};

//Типы символов 
#define BLANK 1
#define NEWLINE 2      
#define LETTER 4
#define DIGIT 8
#define OTHER 16
#define ETX 3 //конец текста

//Мапа соответсвий символов и их типов
static int gCharMap[256] = { 
	/* 000 nul */ 0,
	/* 001 soh */ 0,
	/* 002 stx */ 0,
	/* 003 etx */ ETX,
	/* 004 eot */ 0,
	/* 005 enq */ 0,
	/* 006 ack */ 0,
	/* 007 bel */ 0,
	/* 010 bs  */ 0,
	/* 011 ht  */ BLANK,
	/* 012 nl  */ NEWLINE,
	/* 013 vt  */ BLANK,
	/* 014 ff  */ BLANK,
	/* 015 cr  */ 0,
	/* 016 so  */ 0,
	/* 017 si  */ 0,
	/* 020 dle */ 0,
	/* 021 dc1 */ 0,
	/* 022 dc2 */ 0,
	/* 023 dc3 */ 0,
	/* 024 dc4 */ 0,
	/* 025 nak */ 0,
	/* 026 syn */ 0,
	/* 027 etb */ 0,
	/* 030 can */ 0,
	/* 031 em  */ 0,
	/* 032 sub */ 0,
	/* 033 esc */ 0,
	/* 034 fs  */ 0,
	/* 035 gs  */ 0,
	/* 036 rs  */ 0,
	/* 037 us  */ 0,
	/* 040 sp  */ BLANK,
	/* 041 !   */ OTHER,
	/* 042 "   */ OTHER,
	/* 043 #   */ OTHER,
	/* 044 $   */ 0,
	/* 045 %   */ OTHER,
	/* 046 &   */ OTHER,
	/* 047 '   */ OTHER,
	/* 050 (   */ OTHER,
	/* 051 )   */ OTHER,
	/* 052 *   */ OTHER,
	/* 053 +   */ OTHER,
	/* 054 ,   */ OTHER,
	/* 055 -   */ OTHER,
	/* 056 .   */ OTHER,
	/* 057 /   */ OTHER,
	/* 060 0   */ DIGIT,
	/* 061 1   */ DIGIT,
	/* 062 2   */ DIGIT,
	/* 063 3   */ DIGIT,
	/* 064 4   */ DIGIT,
	/* 065 5   */ DIGIT,
	/* 066 6   */ DIGIT,
	/* 067 7   */ DIGIT,
	/* 070 8   */ DIGIT,
	/* 071 9   */ DIGIT,
	/* 072 :   */ OTHER,
	/* 073 ;   */ OTHER,
	/* 074 <   */ OTHER,
	/* 075 =   */ OTHER,
	/* 076 >   */ OTHER,
	/* 077 ?   */ OTHER,
	/* 100 @   */ 0,
	/* 101 A   */ LETTER,
	/* 102 B   */ LETTER,
	/* 103 C   */ LETTER,
	/* 104 D   */ LETTER,
	/* 105 E   */ LETTER,
	/* 106 F   */ LETTER,
	/* 107 G   */ LETTER,
	/* 110 H   */ LETTER,
	/* 111 I   */ LETTER,
	/* 112 J   */ LETTER,
	/* 113 K   */ LETTER,
	/* 114 L   */ LETTER,
	/* 115 M   */ LETTER,
	/* 116 N   */ LETTER,
	/* 117 O   */ LETTER,
	/* 120 P   */ LETTER,
	/* 121 Q   */ LETTER,
	/* 122 R   */ LETTER,
	/* 123 S   */ LETTER,
	/* 124 T   */ LETTER,
	/* 125 U   */ LETTER,
	/* 126 V   */ LETTER,
	/* 127 W   */ LETTER,
	/* 130 X   */ LETTER,
	/* 131 Y   */ LETTER,
	/* 132 Z   */ LETTER,
	/* 133 [   */ OTHER,
	/* 134 \   */ OTHER,
	/* 135 ]   */ OTHER,
	/* 136 ^   */ OTHER,
	/* 137 _   */ LETTER,
	/* 140 `   */ 0,
	/* 141 a   */ LETTER,
	/* 142 b   */ LETTER,
	/* 143 c   */ LETTER,
	/* 144 d   */ LETTER,
	/* 145 e   */ LETTER,
	/* 146 f   */ LETTER,
	/* 147 g   */ LETTER,
	/* 150 h   */ LETTER,
	/* 151 i   */ LETTER,
	/* 152 j   */ LETTER,
	/* 153 k   */ LETTER,
	/* 154 l   */ LETTER,
	/* 155 m   */ LETTER,
	/* 156 n   */ LETTER,
	/* 157 o   */ LETTER,
	/* 160 p   */ LETTER,
	/* 161 q   */ LETTER,
	/* 162 r   */ LETTER,
	/* 163 s   */ LETTER,
	/* 164 t   */ LETTER,
	/* 165 u   */ LETTER,
	/* 166 v   */ LETTER,
	/* 167 w   */ LETTER,
	/* 170 x   */ LETTER,
	/* 171 y   */ LETTER,
	/* 172 z   */ LETTER,
	/* 173 {   */ OTHER,
	/* 174 |   */ OTHER,
	/* 175 }   */ OTHER,
	/* 176 ~   */ OTHER, 
};

