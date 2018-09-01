#include <stdio.h>

int main()
{
    int a[10] = {4, 2, 11, 4, 15, 7, 9, 12, 3, 6};
    int i, sum;

    for (i = 0; i < 10; i++) {
        printf("a[%d] = %3d\n", i, a[i]);   /* 配列内容の表示 */
    }
    printf("\n");
    
    sum = 0;
    for (i = 0; i < 10; i++) {
        sum += a[i];                        /* 総和の計算 */
    }
    printf("sum= %3d\n", sum);

    return 0;
}
