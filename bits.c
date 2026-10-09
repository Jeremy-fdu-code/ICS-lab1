/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
/* 用德摩根定律表示“至少一个为 1 且不能同时为 1”，只使用 ~ 和 &。 */
    return ~(~x & ~y) & ~(x & y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  /* 算术右移得到符号掩码：负数保留补码取负结果，非负数清零。 */
    return (~x + 1) & (x >> 31);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
 /* 提取源字节，清除目标字节，再把源字节放入目标位置。 */
    int s = src << 3;
    int d = dst << 3;
    int byte = (x >> s) & 255;
    return (x & ~(255 << d)) | (byte << d);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
 /* 算术右移后用低 32-n 位掩码清除符号扩展，兼容 n=0 和 n=31。 */
    int mask = ~(((1 << 31) >> n) << 1);
    return (x >> n) & mask;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
 /* 构造每字节低四位掩码，将高、低半字节分别移到对方的位置。 */
    int m = 15 | (15 << 8);
    m = m | (m << 16);
    return ((x & m) << 4) | ((x >> 4) & m);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  /* 先填上最低的零位，再隔离剩余最低零位；零位不足两个时得到 0。 */
    int y = x | (x + 1);
    return ~y & (y + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
 /* 分层异或把所有位的奇偶性折叠到最低位，再生成补充的奇校验位。 */
    x = x ^ (x >> 16);
    x = x ^ (x >> 8);
    x = x ^ (x >> 4);
    x = x ^ (x >> 2);
    x = x ^ (x >> 1);
    return !(x & 1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  /* 位移量对 32 取模，合并逻辑右移部分与绕回高位的部分，避免移位 32。 */
    int k = n & 31;
    int left = (~k + 1) & 31;
    int mask = ~(((1 << 31) >> k) << 1);
    return ((x >> k) & mask) | (x << left);
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  /* 加半步减一再按商的奇偶调整，最后清低 n 位，使半程选择偶数商。 */
    int q = x >> n;
    int half = 1 << (n + ~0);
    int bias = half + ~0 + (q & 1);
    return ((x + bias) >> n) << n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  /* 用按位恒等式安全求中点下界，半整数且 x>y 时加一，使结果靠近 x。 */
    int sx = x >> 31;
    int sy = y >> 31;
    int d = x ^ y;
    int base = (x & y) + (d >> 1);
    /* 异号直接比较符号；同号采用 y-x 的符号，屏蔽异号差值的溢出影响。 */
    int greater = (~sx & sy) |
                  (~(sx ^ sy) & ((y + (~x + 1)) >> 31));
    return base + ((d & 1) & greater);
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  /* 安全比较 x 与两个端点；比较结果不同或等于端点时，属于闭区间。 */
    int sx = x >> 31;
    int sa = a >> 31;
    int sb = b >> 31;
    int da = sx ^ sa;
    int db = sx ^ sb;
    int ltA = (da & sx) |
              (~da & ((x + (~a + 1)) >> 31));
    int ltB = (db & sx) |
              (~db & ((x + (~b + 1)) >> 31));
    return ((ltA ^ ltB) & 1) | !(x ^ a) | !(x ^ b);
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
   /* 分阶段计算 2x、4x、5x，检测符号翻转；溢出时按原符号选择饱和值。 */
    int twice = x + x;
    int four = twice + twice;
    int five = four + x;
    int overflow = ((x ^ twice) | (twice ^ four) |
                    (four ^ five)) >> 31;
    int limit = (1 << 31) ^ ~(x >> 31);
    return (overflow & limit) | (~overflow & five);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
   /* 分离每个数的低两位与高位，安全求精确和除以 4 后向下取整的 h。 */
    int r = (x & 3) + (y & 3) + (z & 3);
    int h = (x >> 2) + (y >> 2) + (z >> 2) + (r >> 2);
    /* 原和合法等价于 h 能用 30 位有符号数表示，即最高三位均为符号位。 */
    int sign = h >> 31;
    int overflow = !!((h >> 29) ^ sign);
    return (~overflow + 1) & (1 | sign);
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  /* 拆分编码，精确计算有效数三倍，再归一化并执行一次最近偶数舍入。 */
    unsigned sign, exp, frac, t, q, rem, half;
    int shift;

    sign = uf & 0x80000000u;
    exp = (uf >> 23) & 0xffu;
    frac = uf & 0x7fffffu;
    shift = 1;

    /* NaN 和无穷保留原始位模式。 */
    if (exp == 0xffu)
        return uf;

    t = frac;
    /* 仅规格化数补上隐藏的最高位 1。 */
    if (exp)
        t = t | 0x800000u;
    t = t * 3u;

    /* 有效数过大时多右移一位并增加阶码，保持总倍率为 3/2。 */
    if (exp && t >= 0x2000000u) {
        shift = 2;
        exp = exp + 1u;
    }

    q = t >> shift;
    rem = t & ((1u << shift) - 1u);
    half = 1u << (shift - 1);
    /* 超过半程进位，恰好半程仅在保留部分为奇数时进位。 */
    if (rem > half || (rem == half && (q & 1u)))
        q = q + 1u;

    /* 非规格化数的结果可自然跨到规格化编码，零的符号也得到保留。 */
    if (!exp)
        return sign | q;

    /* 处理舍入产生的有效数进位，以及超出有限浮点范围的结果。 */
    if (q >= 0x1000000u) {
        q = q >> 1;
        exp = exp + 1u;
    }

    if (exp >= 0xffu)
        return sign | 0x7f800000u;

    return sign | (exp << 23) | (q & 0x7fffffu);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
 /* 按阶码区分整数、近零值和含小数值，再清除小数位并做最近偶数舍入。 */
    unsigned sign, exp, frac, mag, mask, rem, half, whole;
    int shift;

    sign = uf & 0x80000000u;
    exp = (uf >> 23) & 0xffu;
    frac = uf & 0x7fffffu;

    /* 特殊值原样返回；实际指数至少 23 的有限数已无小数位。 */
    if (exp == 0xffu)
        return uf;
    if (exp >= 150u)
        return uf;
    /* 绝对值小于 0.5 时返回带输入符号的零。 */
    if (exp < 126u)
        return sign;

    /* 恰好 0.5 舍到偶数零，其余绝对值在 (0.5,1) 内的数舍到 1。 */
    if (exp == 126u) {
        if (frac == 0)
            return sign;
        return sign | 0x3f800000u;
    }

    /* 此时低 shift 位代表小数；保留丢弃部分用于半程及奇偶判断。 */
    shift = 150u - exp;
    mag = uf & 0x7fffffffu;
    mask = (1u << shift) - 1u;
    rem = mag & mask;
    whole = mag & ~mask;
    half = 1u << (shift - 1);

    /* 在浮点编码上进位，自然处理跨阶码的结果。 */
    if (rem > half || (rem == half && ((mag >> shift) & 1u)))
        whole = whole + (1u << shift);

    return sign | whole;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
 /* 取得无符号绝对值，找到最高位，再构造或舍入到 24 位有效数。 */
    unsigned sign, mag, tmp, exp, mant, mask, rem, half;
    int p, shift;

    if (x == 0)
        return 0;

    sign = 0;
    mag = x;
    /* 在 unsigned 中取负，保证 INT_MIN 的绝对值也可表示。 */
    if (x < 0) {
        sign = 0x80000000u;
        mag = ~mag + 1u;
    }

    /* p 是最高的 1 的位置，实际指数为 p，存储阶码为 p+127。 */
    tmp = mag;
    p = 0;
    while (tmp >> 1) {
        tmp = tmp >> 1;
        p = p + 1;
    }

    exp = p + 127;
    if (p <= 23) {
        /* 有效位不超过 24 位时，左移补零即可精确表示。 */
        mant = mag << (23 - p);
    } else {
        /* 保留最高 24 位，利用低位余数执行最近偶数舍入。 */
        shift = p - 23;
        mant = mag >> shift;
        mask = (1u << shift) - 1u;
        rem = mag & mask;
        half = 1u << (shift - 1);

        if (rem > half || (rem == half && (mant & 1u)))
            mant = mant + 1u;

        /* 舍入可能产生第 25 位，此时重新归一化并增加阶码。 */
        if (mant == 0x1000000u) {
            mant = mant >> 1;
            exp = exp + 1u;
        }
    }

    return sign | (exp << 23) | (mant & 0x7fffffu);
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  /* 分层合并 2 位、4 位和字节计数，最后累计四个字节中的 1 的数量。 */
    int m1 = 0x55 | (0x55 << 8);
    int m2 = 0x33 | (0x33 << 8);
    int m4 = 0x0f | (0x0f << 8);
    m1 = m1 | (m1 << 16);
    m2 = m2 | (m2 << 16);
    m4 = m4 | (m4 << 16);

    x = (x & m1) + ((x >> 1) & m1);
    x = (x & m2) + ((x >> 2) & m2);
    x = (x + (x >> 4)) & m4;
    x = x + (x >> 8);
    x = x + (x >> 16);
    return x & 0x3f;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
 /* 依次交换相邻的 16、8、4、2、1 位组，复用掩码将操作数控制在 34。 */
    int m = 255 | (255 << 8);
    x = (x << 16) | ((x >> 16) & m);

    m = m ^ (m << 8);
    x = ((x >> 8) & m) | ((x & m) << 8);

    m = m ^ (m << 4);
    x = ((x >> 4) & m) | ((x & m) << 4);

    m = m ^ (m << 2);
    x = ((x >> 2) & m) | ((x & m) << 2);

    m = m ^ (m << 1);
    x = ((x >> 1) & m) | ((x & m) << 1);
    return x;
}
