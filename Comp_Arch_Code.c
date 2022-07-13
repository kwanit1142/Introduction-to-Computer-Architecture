#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

float Random_Number(float lower_num,float high_num)
{
    srand(time(0));
    int random_n = rand();
    float random_num = random_n % (int)(high_num-lower_num+1.0);
    return random_num*(pow(-1,rand()));
}

int sign_bit(float num)
{
    if (num>=0.0)
    {
        int a=0;
        return a;
    }
    else
    {
        int b=1;
        return b;
    }
}

int Bit_to_Number(int arr[], int mantissa_size, int system_size)
{
    int num=0,output,factor;
    if (arr[0]==0)
    {
        factor=1;
    }
    else
    {
        factor=-1;
    }
    for (int count=0,trace=system_size-1;trace>=system_size-mantissa_size;trace--,count++)
    {
        num = num + arr[trace]*pow(2,count);
        if (trace==system_size-mantissa_size)
        {
            output=num;
        }
    }
    output = output*factor;
    return output;
}

void Assignment(int size_system, int bias, float mi,float ni)
{
    float add = mi+ni;
    int R_m[size_system],R_n[size_system],R_o[size_system];
    int c=0,c_out,c_out_2,c_out_3;
    R_m[0]=sign_bit(mi);
    R_n[0]=sign_bit(ni);
    int m=(int)abs(mi), n=(int)abs(ni);
    int exponent_size = (int)(log(bias)/log(2));
    int mantissa_size = size_system - exponent_size - 2;
    printf("\nSign-bit-size = 1\n");
    printf("Exponent-bits-size = %d\n",exponent_size+1);
    printf("Mantissa-bits-size = %d\n",mantissa_size);
    while (m!=1)
    {
        R_m[size_system-c-1] = m%2;
        m = m/2;
        m=(int)m;
        c= c+1;
        if (m==1)
        {
            c_out=c;
            break;
        }
    }
    R_m[size_system-c_out-1] = 1;
    for (int i=size_system-c_out-2;i>=size_system-mantissa_size;i--)
    {
        R_m[i]=0;
    }
    c=0;
    while (n!=1)
    {
        R_n[size_system-c-1] = n%2;
        n = n/2;
        n=(int)n;
        c= c+1;
        if (n==1)
        {
            c_out_2=c;
            break;
        }
    }
    R_n[size_system-c_out_2-1] = 1;
    for (int i=size_system-c_out_2-2;i>=size_system-mantissa_size;i--)
    {
        R_n[i]=0;
    }
    c=0;
    while (c_out!=1)
    {
        R_m[exponent_size-c+1] = c_out%2;
        c_out = c_out/2;
        c_out = (int)c_out;
        c= c+1;
        if (c_out==1)
        {
            c_out=c;
            break;
        }
    }
    R_m[exponent_size-c_out+1] = 1;
    for (int ii=exponent_size-c_out;ii>=1;ii--)
    {
        R_m[ii]=0;
    }
    c=0;
    while (c_out_2!=1)
    {
        R_n[exponent_size-c+1] = c_out_2%2;
        c_out_2 = c_out_2/2;
        c_out_2 = (int)c_out_2;
        c= c+1;
        if (c_out_2==1)
        {
            c_out_2=c;
            break;
        }
    }
    R_n[exponent_size-c_out_2+1] = 1;
    for (int ii=exponent_size-c_out_2;ii>=1;ii--)
    {
        R_n[ii]=0;
    }
    c=0;
    int m_retrieve = Bit_to_Number(R_m,mantissa_size,size_system);
    int n_retrieve = Bit_to_Number(R_n,mantissa_size,size_system);
    int result = m_retrieve + n_retrieve;
    printf("\n m+n = %d\n",result);
    if ((float)result != add)
    {
        printf("\n Config_Warning:- Precision Error Encountered\n");
    }
    R_o[0]=sign_bit((float)result);
    int o=(int)abs(result);
    while (o!=1)
    {
        R_o[size_system-c-1] = o%2;
        o = o/2;
        o=(int)o;
        c= c+1;
        if (o==1)
        {
            c_out_3=c;
            break;
        }
    }
    R_o[size_system-c_out_3-1] = 1;
    for (int i=size_system-c_out_3-2;i>=size_system-mantissa_size;i--)
    {
        R_o[i]=0;
    }
    c=0;
    while (c_out_3!=1)
    {
        R_o[exponent_size-c+1] = c_out_3%2;
        c_out_3 = c_out_3/2;
        c_out_3 = (int)c_out_3;
        c= c+1;
        if (c_out_3==1)
        {
            c_out_3=c;
            break;
        }
    }
    R_o[exponent_size-c_out_3+1] = 1;
    for (int ii=exponent_size-c_out_3;ii>=1;ii--)
    {
        R_o[ii]=0;
    }
    printf("\n Bit-Representation of m = ");
    for (int dis=0;dis<size_system;dis++)
    {
        if ((dis==1) || (dis==exponent_size+2))
        {
            printf("|--|");
        }
        printf("%d",R_m[dis]);
    }
    printf("\n");
    printf("\n Bit-Representation of n = ");
    for (int dis=0;dis<size_system;dis++)
    {
        if ((dis==1) || (dis==exponent_size+2))
        {
            printf("|--|");
        }
        printf("%d",R_n[dis]);
    }
    printf("\n");
    printf("\n Bit-Representation of m+n = ");
    for (int dis=0;dis<size_system;dis++)
    {
        if ((dis==1) || (dis==exponent_size+2))
        {
            printf("|--|");
        }
        printf("%d",R_o[dis]);
    }
}

void main()
{
    int roll_num,s,b,test;
    float m,random,n;
    printf("Enter the last 3 digits of roll number\n");
    scanf("%d",&roll_num);
    roll_num %= 1000;
    if (roll_num>=70)
    {
        m = roll_num*2.2;
        s=24;
        b=roll_num;
    }
    else if (roll_num<10)
    {
        m = roll_num*13.3;
        s=20;
        b = roll_num*13;
    }
    else if ((roll_num>=10) && (roll_num<30))
    {
        m = roll_num*7.4;
        s=22;
    }
    else
    {
        m = roll_num*3.5;
        s=26;
        if (roll_num>=50)
        {
            b=roll_num;
        }
        else
        {
            b=roll_num*3;
        }
    }
    n = Random_Number(m,255);
    printf("m = %f\n",m);
    printf("n = %f\n",n);
    printf("bias = %d\n",b);
    printf("bit-system-size = %d\n",s);
    Assignment(s,b,m,n);
}