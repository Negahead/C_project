#include <stdio.h>
#include <stdlib.h>

#define MONTH 12
#define MAXAUTH 31
#define MAXTITLE 41

struct book {
    char author[MAXAUTH];
    char title[MAXTITLE];
    double price;
};

/*
 * A global variable is variable that can be accessed through out the program and changes made
 * to global variable persist.
 */
int global_variable = 10;

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

    /*
     * there is no default value for any pointer,it contains a garbage value,
     * and there is no default value for anything within a struct(unless it is created statically)
     * and there is no way to providing one.
     */
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


    struct book library = {
            "Baron Schwartz",
            "High Performance MySQL",
            16.95
    };


    /*
     * the difference is that char* line = "hello world" will place "hello world" in the read-only parts of the memory,
     * and the compiler allocates a static anonymous array to hold the string literal,and making line a pointer
     * to that makes any writing operation on this memory illegal,
     * while doing char s[] = "hello world"; puts the literal string in read-only memory and copies the string to newly
     * allocated memory on the stack,thus making s[0] = 'j' legal.
     */
    char* line = "just another perl hacker"; // static const char __secret_anonymous_array[] = "just another perl hacker";
    printf("character at the first place is %c\n",*line); // j
    printf("character at the second place is %c\n",*(line+1)); // u
    char line_array[] = "just another perl hacker";
    printf("line array is %s\n",line_array);
    printf("line is %s\n",line);

    printf("sizeof(struct book) is %td\n", sizeof(library)); // 80
    printf("book title is %c\n",*(library.title+1));
    printf("book author is %s\n",library.author);
    printf("book price is %f\n",library.price);

    struct book library1;
    struct book* library_pt;
    printf("library1 default memory address is %p\n",&library); // varies in every execution
    if(library1.title == NULL) {
        printf("null\n");
    } else {
        printf("not null\n");
    }
    printf("book");

    /*
     * malloc() and calloc() both create a contiguous block of memory
     * the only difference between malloc() and calloc() is that,malloc() allocates A SINGLE BLOCK OF MEMORY
     * whereas calloc() allocates multiple blocks memory each of the same size and set all bytes to zero.
     * the malloc function allocates space for an object whose size is specified by size and whose value is indeterminate,
     * however,the operating system often initialize this memory space to 0,you can use rather calloc() to
     * be sure that every bits are set to 0
     */
    struct book* struct_ptr = (struct book* ) malloc(3 * sizeof(struct book));
    struct book* struct_ptr2 = (struct book* )calloc(3, sizeof(struct book));
    printf("default price is %d\n",*struct_ptr->title); // 0
    printf("default price is %d\n",*struct_ptr2->title); // 0

    struct book_list {
        struct book item;
        struct book_list* next;
    };

    printf("sizeof(struct book) is %td\n", sizeof(struct book)); // 80
    printf("sizeof(struct book_list) is %td\n", sizeof(struct book_list)); // 88
    printf("sizeof(int*) is %td\n", sizeof(int*)); // 8

    change_global_variable();
    printf("global variable is %d\n",global_variable); // 100

}

void interchange(int* x,int* y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
/*
 * In C,functions are global by default,The "static" key word before a function makes it static,
 * unlike global function in C,access to static functions is restricted to the file where they are
 * declared.
 *
 *
 *
 * Static variables have a property of preserving their value even after they are out of their scope!
 * they remains in memory while the program is running.
 * Static variables are allocated memory in (initialized)data segment,not stack segment.
 * Static variables like global variables are initialized as 0 if not initialized explicitly.
 * Static variables can only be initialized using constant literals.
 */
static void static_function(){
    printf("static function");
}

void change_global_variable() {
    global_variable = 100;
}