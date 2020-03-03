int syracuse(int n) {
    int cpt;
    if(n % 2 == 0) {
        n /= 2;
    } else {
        n = 3*n+1;
    }
    if(n != 1) {
        cpt += 1;
        syracuse(n);
    } else {
        return cpt;
    }
}

int main() {
    int n;
    print('Entrez un nombre: ');
    scanf('%d', &n);
    print(syracuse(n));
}