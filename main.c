#include <stdio.h>

#define MONTH 12
#define MAXAUTH 31
#define MAXTITLE 41

struct book {
    char author[MAXAUTH];
    char title[MAXTITLE];
    double price;
};

int main() {
    int month[MONTH] = {31,28,31,30,31,30,31,30,31,31,30,31};
    for(int i = 0; i < MONTH ; i++) {
        printf("month %d has %d days,memory position is %p\n",i+1,*(month+i),month+i);
    }

    // you cant modify const_int_pt itself like const_int_pt++
    // but the object pointed to by const_int_pt shall not be modified
    const int* const_int_pt = month; // const_int_pt is a read only pointer,so it's illegal: *const_int_pt = 454;
    printf("value in const_int_pt is %d\n",*const_int_pt);
    const_int_pt++; // you can't change the value that const_int_pt point to,but this is legal.
    printf("value in const_int_pt is %d\n",*const_int_pt);


    int* const ptr = &month[1];
    *ptr = 29; // OK
    // ptr = &month[3]; Wrong

    int age[] = {12,43,56,67,78,34,23,324};
    for(int index=0; index < sizeof(age) / sizeof(age[0]); index++) {
        printf("index %d has value %d\n",index,age[index]);
    }
    /*
     * sizeof(type) or sizeof(expression) return the size in bytes.w
     */
    printf("sizeof(int) is %td\n",sizeof(int));
    printf("sizeof(short) is %td\n",sizeof(short));
    printf("sizeof(char) is %td\n",sizeof(char));
    printf("sizeof(long) is %td\n",sizeof(long));
    printf("sizeof(double) is %td\n",sizeof(double));
    printf("sizeof(float) is %td\n",sizeof(float));

    int i = 343.56456;
    printf("i is %d\n",i); // 343
    int j = 2334;
    int* pt = &j;
    double d = 2334.44567878; // 2334.44567878 is interpreted as a double by default;
    double* pd = &d;
    pt = pd;
    printf("value is pointer pt is now %f\n",*pt); // 0.000000
    float f = 3434.4456745f; // f suffix simply tells the compiler which is float and which is double.
    float* pf =&f;
    printf("double value of d is %f\n",d);
    printf("float value of f is %f\n",f);

    int x = 10;
    int y = 100;
    interchange(&x,&y);
    printf("x is now %d,y ios now %d\n",x,y);


    int array2[][2] = {
            {1,2},
            {3,4},
            {5,6},
            {7,8}
    };
    printf("sizeof(array2) is %td\n",sizeof(array2));
    printf("sizeof(array2[0]) is %td\n",sizeof(array2[0]));
    printf("memory location of array2 is %p\n",array2);
    printf("value in array2 is %d\n",**array2);
    printf("memory location of array2+1 is %p\n",array2+1); // 8 bytes difference
    printf("value in array2+1 is %d\n",**(array2+1));
    printf("%d\n",*(*(array2+1)+1));


    struct book library;

    printf("sizeof(struct book) is %td\n", sizeof(library)); // 80

}

void interchange(int* x,int* y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}