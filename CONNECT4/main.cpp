#include <iostream>
using namespace std;
int a[7][8], calculator=79, jucator=88, zero=95, n=6, m=7, h[100], winScore=1000000000;


void afisareTabla(){
    cout<<endl<<endl;
    for(int i=n;i>=1;i--)
    {
        for(int j=1;j<=m;j++) cout<<char(a[i][j])<<"  ";
        cout<<endl;
    }
    cout<<"-------------------"<<endl;
    for(int j=1;j<=m;j++) cout<<j<<"  ";
    cout<<endl<<endl;
}

void alegereJucator(){
    afisareTabla();

    int coloana=0;
    while(coloana < 1 || coloana > 7 || h[coloana] == 6)
        cout<<"Alege o coloana: ", cin>>coloana;
    a[++h[coloana]][coloana] = jucator;
}

int countOriz(int st, int dr, int linie, int piesa){
    int k=0;
    for(int i=st;i<=dr;i++)
        if(a[linie][i] == piesa) k++;
    return k;
}

int countVert(int jos, int sus, int coloana, int piesa){
    int k=0;
    for(int i=jos;i>=sus;i--)
        if(a[i][coloana] == piesa) k++;
    return k;
}

int countDiag1(int jos, int sus, int coloana, int piesa){
    int k=0;
    for(int i=jos;i>=sus;i--)
        if(a[i][coloana++] == piesa) k++;
    return k;
}

int countDiag2(int jos, int sus, int coloana, int piesa){
    int k=0;
    for(int i=sus;i<=jos;i++)
        if(a[i][coloana++] == piesa) k++;
    return k;
}

bool tablaPlina(){
    for(int i=1;i<=m;i++)
        if(h[i]!=n) return 0;
    return 1;
}

bool win(int piesa)
{
    //orizontale
    for(int i=n;i>=1;i--)
        for(int j=1;j<=m-3;j++)
            if (countOriz(j, j + 3, i, piesa) == 4) return 1;

    //verticale
    for(int j=1;j<=m;j++)
        for(int i=n;i>=4;i--)
            if(countVert(i, i-3, j, piesa)==4) return 1;

    //diagonala1
    for(int j=1;j<=m-3;j++)
        for(int i=n;i>=4;i--)
            if(countDiag1(i, i-3, j, piesa)==4) return 1;

    //diagonala2
    for(int j=1;j<=m-3;j++)
        for(int i=n;i>=4;i--)
            if(countDiag2(i, i-3, j, piesa)==4) return 1;

    return 0;
}

long long scorTabla(int piesa){
    long long scor = 0;

    int oponent;
    if(piesa==jucator) oponent=calculator;
    else oponent=jucator;

    if(win(piesa)) return winScore;
    if(win(oponent)) return -winScore;
    if(tablaPlina()) return 0;

    //orizontale
    for(int i=n;i>=1;i--)
        for(int j=1;j<=m-3;j++)
            if (countOriz(j, j + 3, i, piesa) == 3 && countOriz(j, j + 3, i, zero) == 1) scor += 100;
            else if (countOriz(j, j + 3, i, piesa) == 2 && countOriz(j, j + 3, i, zero) == 2) scor += 40;
            else if(countOriz(j, j + 3, i, oponent) == 3 && countOriz(j, j + 3, i, zero) == 1) scor -= 80;


    //verticale
    for(int j=1;j<=m;j++)
        for(int i=n;i>=4;i--)
            if (countVert(i, i - 3, j, piesa) == 3 && countVert(i, i - 3, j, zero) == 1) scor += 100;
            else if (countVert(i, i - 3, j, piesa) == 2 && countVert(i, i - 3, j, zero) == 2) scor += 40;
            else if (countVert(i, i - 3, j, oponent) == 3 && countVert(i, i - 3, j, zero) == 1) scor -= 80;

    //diagonala1
    for(int j=1;j<=m-3;j++)
        for(int i=n;i>=4;i--)
            if (countDiag1(i, i-3, j, piesa)==3 && countDiag1(i, i-3, j, zero)==1) scor += 100;
            else if (countDiag1(i, i-3, j, piesa)==2 && countDiag1(i, i-3, j, zero)==2) scor += 40;
            else if(countDiag1(i, i-3, j, oponent)==3 && countDiag1(i, i-3, j, zero)==1) scor -= 80;

    //diagonala2
    for(int j=1;j<=m-3;j++)
        for(int i=n;i>=4;i--)
            if (countDiag2(i, i-3, j, piesa)==3 && countDiag2(i, i-3, j, zero)==1) scor += 100;
            else if (countDiag2(i, i-3, j, piesa)==2 && countDiag2(i, i-3, j, zero)==2) scor += 40;
            else if (countDiag2(i, i-3, j, oponent)==3 && countDiag2(i, i-3, j, zero)==1) scor -= 80;


    return scor;
}


long long minimax(int depth, long long alpha, long long beta, int piesa){
    long long scor;
    if(piesa == jucator) scor = scorTabla(calculator);
    else scor = -scorTabla(jucator);

    if(depth==0 || tablaPlina() || scor==winScore || scor==-winScore)
        return scor;

    if(piesa==calculator){
        long long maxVal = -1000000000, val;
        for(int i=1;i<=m;i++)
            if(h[i] != n){
                a[++h[i]][i] = calculator;
                val = minimax(depth-1, alpha, beta, jucator);
                a[h[i]--][i] = zero;
                maxVal = max(maxVal, val);
                alpha = max(alpha, val);
                if(beta <= alpha) break;
            }
        return maxVal;
    }

    if(piesa == jucator){
        long long minVal = 1000000000, val;
        for(int i=1;i<=m;i++)
            if(h[i] != n){
                a[++h[i]][i] = jucator;
                val = minimax(depth-1, alpha, beta, calculator);
                a[h[i]--][i] = zero;
                minVal = min(minVal, val);
                beta = min(beta, val);
                if(beta <= alpha) break;
            }
        return minVal;
    }

}


int bestMove(){
    long long  maxim=-1000000000, val;
    int best;
    for(int i=1;i<=m;i++)
    {
        if(h[i]!=n)
        {
            a[++h[i]][i] = calculator;
            val=minimax(7, -1000000000, 1000000000, jucator); // 7 e minim
            if(val>=maxim) maxim=val, best=i;
            a[h[i]--][i] = zero;
        }
    }
    return best;
}

void alegereCalculator(){
    int coloana = bestMove();
    a[++h[coloana]][coloana] = calculator;
}


int main(){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) a[i][j]=zero;

    int turn = jucator;
    int celalalt = calculator;

    while(!win(celalalt) && !tablaPlina())
    {
        celalalt = turn;
        if(turn==jucator)
            alegereJucator(), turn=calculator;
        else{
            alegereCalculator(), turn=jucator;
        }
    }

    if(win(celalalt)) {
        if (celalalt == calculator) afisareTabla(), cout << "Ai pierdut! :)";
        else cout << "Ai castigat! :(";
    }
    else cout<<"Remiza.";

}