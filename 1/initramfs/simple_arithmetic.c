int main() {
    unsigned long long a = 0;
    int i = 0;
    while(1){
        i++;
        a += rand() % 100;
        if (i == 100)
            a = i = 0;
        }
    return 0;
}