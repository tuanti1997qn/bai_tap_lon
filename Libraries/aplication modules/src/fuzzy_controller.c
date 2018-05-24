#include "fuzzy_controller.h"

/* variable */
float parameter_in[VARIABLE_IN][GIA_TRI_BIEN_NGON_NGU][TRAMP_PA_RA]; // vi bat dau tu 0 => tim cach viet hay hon

float parameter_out[VARIABLE_OUT];

float value_in[VARIABLE_IN][GIA_TRI_BIEN_NGON_NGU];

float value_out[VARIABLE_OUT];

/* rule viet theo kieu so bcd voi 4 bit cuoi la cua ngo ra */
int32_t rule[FUZZY_RULE]; // format rule: BCD with the lowest nibble is out 

/* define static function */ 
static float s_f_fuzzy_LinearInterpolation(float f_Left, float f_CenterLeft , float f_CenterRight, float f_right, float f_Value );
static float s_f_fuzzy_SolveFuzzy( void );
static void s_v_fuzzy_CalMuyInValue( float* f_InValue );
static void s_v_fuzzy_CalMuyOutValue( void );/* chua test cai ham nay, chan qua co thang tuan tuong lai nao thich thi sua. hoac co van de roi sua :V */

/*extern function*/
float f_fuzzy_FuzzyProcess( float* f_Value )
{
    s_v_fuzzy_CalMuyInValue( f_Value );
    s_v_fuzzy_CalMuyOutValue();
    return s_f_fuzzy_SolveFuzzy();
}

void v_fuzzy_SetRule( int16_t position , int32_t new_rule )
{
    rule[position] = new_rule;
}

int32_t i32_fuzzy_GetRule( int16_t position )
{
    return rule[position];
}

void v_fuzzy_SetParameterOut( int16_t position, float new_para )
{
    parameter_out[position] = new_para;
}

float f_fuzzy_GetParameterOut( int16_t position )   
{
    parameter_out[position] = new_para;
}

void v_fuzzy_SetParameterIn( int16_t kind_input, int16_t bien_ngon_ngu, int16_t tramp_para, float value )
{
    parameter_in[kind_input][bien_ngon_ngu][tramp_para] = value;
}

float f_fuzzy_GetParameterOut( int16_t kind_input, int16_t bien_ngon_ngu, int16_t tramp_para )
{   
    return parameter_in[kind_input][bien_ngon_ngu][tramp_para];
}
//dang xay dung giai thuat dang hoang dung luu do giai thuat dang hoang






/* static function */
/* Interpolation trapezium */
static float s_f_fuzzy_LinearInterpolation(float f_Left, float f_CenterLeft , float f_CenterRight, float f_right, float f_Value ) // ngau chua noi suy tuyen tinh
{
    float dx,k,temp ;
    if( ( f_Value >= f_CenterLeft ) && ( f_Value <= f_CenterRight ) ) // f_CenterLeft <= f_Value <= f_CenterRight
    {
        return 1;
    }
    else if( ( f_Value > f_Left ) && ( f_Value < f_CenterLeft ) )  // f_Left <= f_Value <= f_CenterRight
    {
        dx = f_Value - f_Left;// chu may ma quen cach noi suy tuyen tinh thi hoc lai nam nhat nha
        k = 1 / (f_CenterLeft - f_Left);
        return ( k *dx );
    }
    else if( ( f_Value > f_CenterRight ) && ( f_Value < f_right ) ) // f_CenterRight <= f_Value <= f_right
    {
        dx = f_right - f_Value;// chu may ma quen cach noi suy tuyen tinh thi hoc lai nam nhat nha
        k = 1 / (f_right - f_CenterRight);
        return ( k *dx );// f_Value > f_right
    }
    else if( f_Value <= f_Left ) // f_Value<f_Left
    {
        return 0;
    }
    else if( f_Value >= f_right )
    {
        return 0;
    }
}

/* weighted average solution */
static float s_f_fuzzy_SolveFuzzy( void ) //dat ten nghe chuoi qua => sua sau
{
    int16_t i16_count;
    float f_numerator = 0, f_denominator = 0;
    for( i16_count = VARIABLE_OUT-1; i16_count >= 0; i16_count-- )
    {
        f_numerator +=  value_out[i16_count] + parameter_out[i16_count];
        f_denominator += parameter_out[i16_count];
    }
    return f_numerator/f_denominator;
}

/* calculate muy input value*/
static void s_v_fuzzy_CalMuyInValue( float* f_InValue )
{
    /* chuong trinh hien chua biet lam the nao cho truong hop tong quat. hien dang viet cho 4 bien vao */
    int16_t i16_cnt_Input, i16_cnt_BienNgonNgu;
    for( i16_cnt_Input = 0; i16_cnt_Input <= VARIABLE_IN-1; i16_cnt_Input++ )
    {
        for( i16_cnt_BienNgonNgu = 0; i16_cnt_BienNgonNgu <= GIA_TRI_BIEN_NGON_NGU-1; i16_cnt_BienNgonNgu++ )
        {
            value_in[i16_cnt_Input][i16_cnt_BienNgonNgu] = f_fuzzy_LinearInterpolation( parameter_in[i16_cnt_Input][i16_cnt_BienNgonNgu][0], parameter_in[i16_cnt_Input][i16_cnt_BienNgonNgu][1],
                                                                                        parameter_in[i16_cnt_Input][i16_cnt_BienNgonNgu][2], parameter_in[i16_cnt_Input][i16_cnt_BienNgonNgu][3],
                                                                                        f_InValue[i16_cnt_Input] );// code hoi chuoi. co gan doc nha tuan cua thang sau. dai khai la cai nay tinh ra cai muy cua tung bien ngon ngu. mang f_InValue se chua cac bien khac nhau x, dx,phi,dphi
        }
    }
}

/* calculate muy output value */
/* trong rule co chua luat la 1 so BCD tu do phan ra duoc luat vd 1234, 1 la gia tri ngon ngu dau tien cua x
    2 la gi tri ngon ngu thu 2 cua dx,...*/
/* cong BSUM*/
static void s_v_fuzzy_CalMuyOutValue( void )
{
    int16_t i16_cnt_Output i16_cnt_Rule, i16_cnt_NumberInput, temp;
    /* clear all output buffer */
    for( i16_cnt_Output = 0; i16_cnt_Output <= VARIABLE_OUT-1; i16_cnt_Output++ )
    {
            value_out[ i16_cnt_Output ] = 0;// vi de nhan nen la bang 1
    }
    for( i16_cnt_Rule = 0; i16_cnt_Rule <= FUZZY_RULE-1; i16_cnt_Rule++ )
    {
        /* vong for nay de nhan het muy cua in vao trong 1 bien tam roi sau do cong vao mang*/
        temp = 1;
        for( i16_cnt_NumberInput = 0; i16_cnt_NumberInput <= VARIABLE_IN-1; i16_cnt_NumberInput++ )
        {
            /* nhan them vao so rule theo so suat */
            temp *= value_in[i16_cnt_NumberInput][( rule[i16_cnt_Rule] >> 4*( VARIABLE_IN - i16_cnt_NumberInput ) ) & 0x0F ];
        }
        value_out[ rule[i16_cnt_Rule] & 0x0F ] += temp;
        /* cong BSUM nen neu vuot 1 se bang 1*/
        if( value_out[ rule[i16_cnt_Rule] & 0x0F ] >= 1)
        {
            value_out[ rule[i16_cnt_Rule] & 0x0F ] = 1;
        }
    }
}

// chu y khi giai mo phai chu y den tong hop(dung MAX hay BSUM)





// viet them 1 ham nhap rule hoac la gan rule o day luon