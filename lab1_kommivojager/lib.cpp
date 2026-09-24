#include <cstddef>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define UI unsigned int

//создания массива длины n случаных чисел от lf до rt
void randMs(int* ms, int n, int lf, int rt) {
    srand(time(0));
    for (int i = 0; i < n; i++)
        ms[i] = rand() % (rt - lf + 1) + lf;
}
//вывод массива
void printMs(int* ms, int n) {
    int* ptr;
    for (ptr = ms; ptr < ms + n; ptr++)
        printf("%d ", *ptr);
    printf("\n");
}
//ввод массива 
void scanMs(int* ms, int n) {
    int* ptr;
    for (ptr = ms; ptr < ms + n; ptr++)
        scanf("%d", ptr);
}

//возвращает макс эл-нт из 2ух
int max(int a, int b) {
    
    int x = (a > b) ? a : b;
    return x;
}

//возвращает мин эл-нт из 2ух
int min(int a, int b) {
    return ( a < b ) ? a : b;
}

//макс эл-нт массива
int maxMs(int* ms, int n) {
    int mx = -100000;
    for (int i = 0; i < n; i++)
        if (ms[i] > mx)
            mx = ms[i];
    return mx;
}
//мин эл-нт массива
int minMs(int* ms, int n) {
    int mn = 100000;
    for (int i = 0; i < n; i++)
        if (ms[i] < mn)
            mn = ms[i];
    return mn;
}
//гномья сортировка
void gnomeSort(int* ms, int n) {
    int i = 0;
    while (i < n) {
        if (i == 0 || ms[i] >= ms[i - 1])
            i++;
        else {
            int a = ms[i]; ms[i] = ms[i - 1]; ms[i - 1] = a;
            i--;
        }
    }
}
//гномья в обратную сторону
void gnomeSortRev(int* ms, int n) {
    int i = n;
    while (i > 0) {
        if (i == n || ms[i] <= ms[i - 1])
            i--;
        else {
            int a = ms[i]; ms[i] = ms[i - 1]; ms[i - 1] = a;
            i++;
        }
    }
}
//проверка числа на простое(1да, -1нет)
int prost(int n) {
    for (int i = 2;i < n / 2;++i)
        if (n % 2 == 0)
            return -1;
    return 1;
}
//меняем 2 значение двух целочисленных переменных местами
void maswap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
//сдвиг влево эл-та на pos позиции
void ShiftLeft(int* a, int n, int pos) {
    for (int i = pos; i < n - 1; i++)
        a[i] = a[i + 1];
}
//сдвиг влево k эл-тов начиная с l позиции
void ShiftLeft_k(int* a, int n, int l, int k) {
    for (int i = l; i < n - k; i++)
        a[i] = a[i + k];
}
//вставляем эл-нт на 0ую поз 
void Vstavka(int* a, int n, int k) {
    int i;
    for (i = n - 1;a[i] > k && i >= 0; i--)
        a[i + 1] = a[i];
    a[i + 1] = k;
}
//поиск числа k. Возвращаем индекс
int mafind(int* a, int n, int k) {
    for (int i = 0;i < n;++i) {
        if (a[i] == k)
            return i;
    }
    return -1;
}
//ввод матрицы m на n
void scanMatr(int matr[][100], int m, int n) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &matr[i][j]);
}
//вывод матрицы
void printMatr(int matr[][100], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", matr[i][j]);
        printf("\n");
    }
}
//случайная матрица(аналогично randms)
void randMatr(int matr[][100], int m, int n, int lf, int rt) {
    srand(time(0));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            matr[i][j] = rand() % (rt - lf + 1) + lf;
}
//мин число в матрице. Выводим коор-ты этого числа
void minMatr(int matr[][100], int m, int n, int* i_min, int* j_min) {
    int i, j;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            if (matr[i][j] < matr[*i_min][*j_min]) {
                *i_min = i;
                *j_min = j;
            }
}

//макс число в матрице. Выводим коор-ты этого числа
void maxMatr(int matr[][100], int m, int n, int* i_max, int* j_max) {
    int i, j;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            if (matr[i][j] > matr[*i_max][*j_max]) {
                *i_max = i;
                *j_max = j;
            }
}
//ввод динамической матрицы
void scanMatrD(int** matr, int m, int n){
    for (int i = 0; i < m; i++) 
        for (int j = 0; j < n; j++) 
            scanf("%d", &matr[i][j]);
}
//вывод динамической матрицы
void printMatrD(int** matr, int m, int n){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++)
            printf("%d ", matr[i][j]);
        printf("\n");
    }
}
//удаляет столбец k у матрицы m n
int DelCol(int** matr, int m, int n, int k) {
    int i;
    for (i = 0; i < m; i++)
        ShiftLeft(matr[i], n, k);
    return n - 1;
}
//удаляет строку k у статической матрицы m n
int DelStrS(int** matr, int m, int n, int k) {
    int i, j;
    for (i = k; i < m-1; i++)
        for (j = 0; j < n; j++)
            matr[i][j] = matr[i + 1][j];
    return --m;
}
//удаляет строку k у динамической матрицы m n
int DelStrD(int** matr, int m, int n, int k) {
    int i;
    delete[] matr[k]; 
    for (i = k; i < m - 1; i++)
        matr[i] = matr[i + 1];
    return --m; 
} 
//создает случайну динамическую матрицу m n с диапозоном случайных числел от lf до rt
void randMatrD(int** matr, int m, int n, int lf, int rt) {
    srand(time(0));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            matr[i][j] = rand() % (rt - lf + 1) + lf;
}
//проверка символа на цифру
bool number(char ch) {
    if (ch >= '0' && ch <= '9')
        return true;
    return false;
}
//проверка символа на заглавную букву
bool Letter(char ch) {
    if (ch >= 'A' && ch <= 'Z')
        return true;
    return false;
}
//проверка символа на строчную букву
bool letter(char ch){
    if (ch >= 'a' && ch <= 'z')
        return true;
    return false;
}
//возвращает индекс найденного пробела начиная с i-ой позиции
int findSpace(char s[], int i){
    for (; s[i] != '\0' && s[i] != ' '; i++) ;
    return i; 
}
//возвращает индекс найденного НЕ пробела начиная с i-ой позиции
int space(char s[], int i){
    for (; s[i] && s[i] == ' '; i++);
    
    return i;
}

//возвращает индекс найденной заяптой
int comma(char s[], int i) {
    for (; s[i] && s[i] == ','; i++);
    return i;
}
int Definebit(unsigned int value, int k){
    unsigned int mask = 1;
    mask = mask << k; // mask <<=k
    if ((value & mask) == 0)
        return 0;
    else 
        return 1; 
    }
void outputBV(unsigned int x, int n){
    unsigned int mask=1; int i;
    mask <<= n-1;
    for(i=0; i < n; i++, mask >>= 1)
        if (x&mask)
            printf("1");
        else
            printf("0"); // putchar('0');
    // printf("%d", (x&mask) ? 1 : 0 ) ;
}
unsigned int setUp1(unsigned int x, int k){
    unsigned int mask=1;
    mask <<= k;
    x|=mask;
    return x;
}   
unsigned int input1BV (char s[], int n){
    unsigned int x=0; int i;
    for(i=0; i<n; i++)
        if (s[i]=='1')
            x=setUp1(x,n-1-i);
    return x; 
}
UI input2BV (char s[], int n){
    UI x=0; int i;
    for(i=0; i<n; i++){
        x<<=1;
        if (s[i]=='1')
            x|=1;
    }
    return x; 
}
void inputBM (UI *bm, int m, int n){
    char s[33];
    for (int i=0; i<m; i++){
        fgets(s, 33, stdin); 
        bm[i]=input2BV(s, n);
    }
}
void outputBM (UI *bm, int m, int n){ 
    for (int i=0; i<m; i++){
        outputBV(bm[i], n);
        puts(" ");
    }
}
int weightСolumn(UI *bm, int m, int k){ 
    int w=0, i;
    UI mask=1<<k;
    for(i=0; i<m; i++)
        if (bm[i]&mask)
            w++;
    return w;
}
void createRandFile(const char *name, int n, int lf, int rt){
    FILE *f;
    int x;
    f=fopen(name, "w");
    if(f==NULL) {
        perror ("ошибка в CreateFile"); 
        exit(-1);
    }
    srand(time(0));
    for(int i=0; i<n; i++){
        x=rand()%(rt - lf + 1) + lf;
        fprintf(f, "%d ", x);
    }
    fclose(f);
}
void printFile(const char *name){
    FILE *f; int x;
    f=fopen(name, "r");
    if(f==NULL){
        perror("ошибка открытия файла в PrintFile");
        exit(1);
    }
    fscanf(f, "%d", &x);
    while(!feof(f)){
        printf("%d ", x); 
        fscanf(f, "%d", &x);
    }
    fclose(f);
}
int fibonacci(int n){
    if (n == 1 || n == 2)
        return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}
int Ifibonacci(int n){
    int a=1, b=1, fib=0;
    for (int i=0;i<n;++i){
        fib=a+b;
        a=b; b=fib;
    }
    return fib;
}
void sliyanie(const char *name, const char *name1, const char *name2){
    FILE *f1, *f2, *f;
    f1=fopen(name1, "r");
    f2=fopen(name2, "r");
    f=fopen(name, "w");
    int x, y, fl1=0, fl2=0;
    if (f1 != NULL && fscanf(f1, "%d", &x) == 1) 
        fl1 = 1;
    if (f2 != NULL && fscanf(f2, "%d", &y) == 1) 
        fl2 = 1;
    while (fl1 && fl2){
        if (x<y){
            fprintf(f, "%d ", x);
            fl1 = fscanf(f1, "%d", &x) == 1;
        }
        else{
            fprintf(f, "%d ", y);
            fl2 = fscanf(f2, "%d", &y) == 1;
        }
    }
    
    while(fl1){
        fprintf(f, "%d ", x);
        fl1 = fscanf(f1, "%d", &x) == 1;
    }
    while(fl2){
        fprintf(f, "%d ", y);
        fl2 = fscanf(f2, "%d", &y) == 1;
    }
    
    fcloseall();
}
void sliyanieFeof(const char *name, const char *name1, const char *name2){
    FILE *f1, *f2, *f;
    f1=fopen(name1, "r");
    f2=fopen(name2, "r");
    f=fopen(name, "w");
    if (f1==NULL || f2==NULL || f==NULL){
        printf("OPEN ERORR");
        exit(-1);
    }
    int x, y;
    fscanf(f1, "%d", &x); 
    fscanf(f2, "%d", &y);
    while (!feof(f1) && !feof(f2)){
        if (x<y){
            fprintf(f, "%d ", x);
            fscanf(f1, "%d", &x);
        }
        else{
            fprintf(f, "%d ", y);
            fscanf(f2, "%d", &y);
        }
    }
    
    while(!feof(f1)){
        fprintf(f, "%d ", x);
        fscanf(f1, "%d", &x);
    }
    while(!feof(f2)){
        fprintf(f, "%d ", y);
        fscanf(f2, "%d", &y);
    }
    
    fcloseall();
}
int linSearch(int* a, int n, int k){
    int i=0;
    while (i<n)
    if(a[i]==k)
        return i;
    else
        ++i;
    return -1;
}
int linSearchBarier(int* a, int n, int k){
    a[n]=k; int i=0;
    while (a[i]!=k)
        ++i;
    if(i==n)
        return -1;
    else
        return i;
}
int binSearch(int  a[], int n, int k){
    int l = 0, r = n - 1; 
    while (l<=r) {
        int m=l+(r-l)/2;
        if (a[m]==k)
            return m;
        if (k>a[m])
            l=m+1;
        if (k<a[m])
            r=m-1;
    }
    return -1;
}
void randMsVosrast(int* ms, int n, int mn, int mx) {
    srand(time(0));
    ms[0]=rand()%10;
    for (int i = 1; i < n; i++){
        int k=mn+rand()%(mx-mn+1);
        ms[i]=ms[i-1]+k;
    }
}
int boyerMour(int n, int m, char* s, char* p){
    int tab[256];
    int k, j;
    for(int i=0;i<256; ++i)
        tab[i]=m;
    for(int i=0;i<m-i; ++i)
        tab[p[i]]=m-1-i;

    int i = m - 1;
    while (i<n) {
        k=i; j=m-1;
        while (j>=0 && s[k]==p[j]) {
                --k; --j;
        }
        if (j<0)
            return k+1;
        else
            i+=tab[s[i]];
    }
    return -1;
}
int boyerMourBased(int n, int m, char* s, char* p){
    int tab[256];
    int k, j, tmp=0;
    for(int i=0;i<256; ++i)
        tab[i]=m;
    for(int i=0;i<m-i; ++i)
        tab[p[i]]=m-1-i;

    int i = m - 1;
    while (i<n) {
        k=i; j=m-1; tmp=0;
        while (j>=0) {
            if (s[k]==p[j]){
                --k;--j;++tmp;
            }
            else
                break;
        }
        if (j<0)
            return k+1;
        else
            i+=(tab[s[k]]-tmp);
    }
    return -1;
}
void BubbleSort(int *a, int n){
    int flag=1;
    for (int k=n-1; k>0 && flag; --k){
        for (int i=0, flag=0; i<k;++i){
            if (a[i]>a[i+1]){
                maswap(&a[i], &a[i+1]);
                flag=1;
            }
        }
    }
}
void updBubbleSort(int *a, int n){
    int r=0, rt=n-1;

    while (r != rt){
        r = rt;
        int i = 0;
        while (i < r){
            if (a[i] > a[i+1]){
                maswap(&a[i], &a[i+1]);
                rt = i;
            }
            i += 1;
        }
    }
}
void shakerSortUpd(int *a, int n){
    int l=0, r=n-1, place=n;
    while (l<r){
        for(int i=l; i<r;++i)
            if(a[i]>a[i+1]){
                maswap(&a[i], &a[i+1]); 
                place=i;
            }
        r=place;
        for(int i=r;i>l;--i)
            if (a[i]<a[i-1]){
                maswap(&a[i], &a[i-1]);
                place=i;
            }
        l=place;
    }
}
void shakerSort(int *a, int n){
    int l=0, r=n-1;
    while (l<r){
        for(int i=l; i<r;++i)
            if(a[i]>a[i+1])
                maswap(&a[i], &a[i+1]);
        --r;
        for(int i=r;i>l;--i)
            if (a[i]<a[i-1]){
                maswap(&a[i], &a[i-1]);
            }
        ++l;
    }
}
void vstavkaBinSearchSort(int * a, int n){
    for (int i=1;i<n;i++)
        if (a[i]<a[i-1]){
            int x=a[i], l=0, r=i-1;
            while (l<r){
                int m=(l+r)/2;
                if (x<a[m])
                    r=m;
                else
                    l=m+1;
            }
            for (int j=i-1;j>=l;j--)
                a[j+1]=a[j];
            a[l]=x;
    }
}
int sum(int a, int b, int c){
    return(a+b+c);
}