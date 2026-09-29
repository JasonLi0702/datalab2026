/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ((~(~x & ~y)) & (~(x & y)));
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!((x>>31)^(y>>31)))
        return !((!x)^(!y));
    else return 0;
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int b16=(!!(v>>16))<<4;
    v=v>>b16;
    int b8=(!!(v>>8))<<3;
    v=v>>b8;
    int b4=(!!(v>>4))<<2;
    v=v>>b4;
    int b2=(!!(v>>2))<<1;
    v=v>>b2;
    int b1=(!!(v>>1));

    return (b16|b8|b4|b2|b1);
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int n3 = n<<3;//n*8
    int m3 = m<<3;
    int n_mark=(0xFF << n3);
    int m_mark=(0xFF << m3);
    int body=~(n_mark|m_mark);
    int body_num=(x & body);//7
    int n_num=(((x & n_mark) >> n3)<<m3)&m_mark;
    int m_num=(((x & m_mark) >> m3)<<n3)&n_mark;   
    return body_num|(n_num|m_num);//17
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned int answer=0;
    int i=0;
    for(i=0;!!(i-32);i=i+1){
        answer=answer+(((v>>i)&1)<<(31-i));
    }
        return answer;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mask=0x80000000;
    x=x>>n;
    mask=~(mask>>(n+1+~(1)));
    int ans_NnotZero=x&mask;
    int signal=!!n;
    return (((~(signal))+1)&ans_NnotZero)|((~((~(signal))+1))&x);
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    x=~x;
    int s=x>>31;
    int b16=(!!(x>>16))<<4;
    x=x>>b16;
    int b8=(!!(x>>8))<<3;
    x=x>>b8;
    int b4=(!!(x>>4))<<2;
    x=x>>b4;
    int b2=(!!(x>>2))<<1;
    x=x>>b2;
    int b1=(!!(x>>1));
    x=x>>b1;
    int b0=x;
    return ((~s)&(33+(~(b16+b8+b4+b2+b1+b0))))|0;

}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
  unsigned v, keep, lost, half, sign;
    int mask=0x007FFFFF,shift=0;//保留23位待存入小數部分
    if(x==0)
        return 0;
    sign=x&0x80000000u;
    v=x;
    if(sign)
        v=~v+1;
    int locate=0;
    while ((v>>locate)>1)
        locate=locate+1;
    if(locate>23){
        shift=locate-23;
        keep=v>>shift;
        lost=v-(keep<<shift);
        half=1u<<(shift-1);
        if((lost+(keep&1))>half)
            keep=keep+1;

        locate=locate+(keep>>24);
    }
    else{
        keep=v<<(23-locate);
    }
    return sign|((127+locate)<<23)|(keep&mask);
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000u,exp = uf & 0x7F800000u,frac = uf & 0x007FFFFFu;
    unsigned new_exp = exp >> 23;
    if(new_exp == 0xFFu)
        return uf;
    if(new_exp == 0){
        if(frac == 0)
            return uf;
        frac=frac<<1;//frac*2 if唔會爆就直接re,else變做-125唔要咗第廿四個
        if(frac & 0x00800000u){     
            new_exp = 1;
            frac = frac & 0x007FFFFFu;
            return sign | (new_exp << 23) | frac;
        }
        return sign | (new_exp << 23) | frac;
    }
    else{
        new_exp = new_exp + 1;
        if(new_exp == 0xFFu)
            return sign | 0x7F800000u;
        return sign | (new_exp << 23) | frac;
    }
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int exp=((uf2>>20)&0x7FF);
    if((exp-1023)>=31)
        return 0x80000000;
    if((exp-1023)<0)
        return 0;
    int frac=((uf2&0xFFFFF)<<10)|((uf1&0xFFC00000)>>22)|0x40000000;
    int num=frac>>(30-(exp-1023));
    if(uf2>=0x80000000u)
        return -num;
    return num;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if(x>127)
        return 0x7F800000;
    else if(x<-126)
        if(x<-149)
            return 0;
        else
            return 1<<(149+x);
    else
        return (x+127)<<23;
}
