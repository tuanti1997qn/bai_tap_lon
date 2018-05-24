#ifndef __FUZZY_CONTROLLER_H_
#define __FUZZY_CONTROLLER_H_

#include "main.h"

/* use sugeno fuzzy */
#define VARIABLE_IN 4
#define GIA_TRI_BIEN_NGON_NGU 5 // KIEM TEN CHO NGAU SAU
#define TRAMP_PA_RA 4 // dung hinh thang nen dua 4 so vao

#define VARIABLE_OUT 7 // so gia tri cua ngo ra theo luat sugeno

#define FUZZY_RULE ( const int16_t )pow(GIA_TRI_BIEN_NGON_NGU,VARIABLE_IN)


float f_fuzzy_FuzzyProcess( float* f_Value );

/* co the tu set luat hoac vao file fuzzy_cotroller sua cho nhanh(khong khuyen khich lam) */
/* rule duoc viet duoi dang so bcd bat dau la 0(vi du NB se la 0) kieu nhu cua matlab ay co ma bat dau = 0 chu khong phai la 1 ) voi 4 bit cuoi la la cho ngo ra. chi ho tro toi da 9 bien ngon ngu.  */
void v_fuzzy_SetRule( int16_t position , int32_t new_rule );
void v_fuzzy_SetParameterOut( int16_t position, float new_para );
float f_fuzzy_GetParameterOut( int16_t position )   ;
void v_fuzzy_SetParameterIn( int16_t kind_input, int16_t bien_ngon_ngu, int16_t tramp_para, float value );
float f_fuzzy_GetParameterOut( int16_t kind_input, int16_t bien_ngon_ngu, int16_t tramp_para );


/* tai but: co 1 bang sao o D:\Project\code block\test  dung cho code block de test truoc khi cho vao do that tranh gay hau qua nghiem trong */
#endif