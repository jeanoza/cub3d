#include <stdio.h>
#include <stdlib.h>

typedef struct s_test {
    int buf[30][30];
} t_test;


void func1(t_test *test){
    test->buf[0][0] = 42;
    test->buf[0][1] = 42 *2;
    test->buf[0][3] = 42 *3;
}

void func2(t_test *test) {
    printf("%d\n", test->buf[0][0]);
    printf("%d\n", test->buf[0][1]);
    printf("%d\n", test->buf[0][2]);
    printf("%d\n", test->buf[0][3]);
}

int main(void)
{
    t_test test;

    func1(&test);
    func2(&test);
    
}