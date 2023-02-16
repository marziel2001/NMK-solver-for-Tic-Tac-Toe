#include <iostream>
#define DLUGOSC_KOMENDY 40
using namespace std;

enum Gracz
{
    pierwszy = 1,
    drugi = 2
};
typedef struct Gra
{
    char** TICTACTOE;
    int x, y, k, aktywnyGracz, ucinanie;
} Gra;

void StworzPlansze(Gra& gra)
{
    gra.TICTACTOE = new char* [gra.x];

    for (int i = 0; i < gra.x; i++)
    {
        gra.TICTACTOE[i] = new char[gra.y];
    }

    for (int i = 0; i < gra.x; i++)
    {
        for (int j = 0; j < gra.y; j++)
        {
            gra.TICTACTOE[i][j] = '0';
        }
    }
}
void UsunPlansze(Gra& gra)
{
    for (int i = 0; i < gra.x; i++)
    {
        delete gra.TICTACTOE[i];
    }
    delete gra.TICTACTOE;
}
void WypiszPlansze(Gra const& gra)
{
    for (int j = 0; j < gra.y; j++)
    {
        for (int i = 0; i < gra.x; i++)
        {
            printf("%c ", gra.TICTACTOE[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
bool CzyWygral(Gra& gra, int gracz)
{
    int seria = 0;
    char znaczek = '1';
    if (gracz == drugi) znaczek = '2';

    //sprawdzanie ciagu poziomo
    for (int i = 0; i < gra.y; i++)
    {
        for (int j = 0; j < gra.x; j++)
        {
            if (gra.TICTACTOE[j][i] == znaczek) seria++;
            else seria = 0;

            if (seria >= gra.k) return true;
        }
        seria = 0;
    }
    //sprawdzanie ciagu pionowo
    for (int j = 0; j < gra.x; j++)
    {
        for (int i = 0; i < gra.y; i++)
        {
            if (gra.TICTACTOE[j][i] == znaczek) seria++;
            else seria = 0;

            if (seria >= gra.k) return true;
        }
        seria = 0;
    }

    //sprawdzanie na skos "\"
    //gorny trojkat
    for (int j = 0; j <= gra.x - gra.k; j++)
    {
        for (int p = 0; p < gra.y && (j + p) < gra.x; p++)
        {
            if (gra.TICTACTOE[j + p][p] == znaczek) seria++;
            else seria = 0;

            if (seria >= gra.k) return true;
        } seria = 0;
    }
    //dolny trojkat
    for (int i = 0; i <= gra.y - gra.k; i++)
    {
        for (int p = 0; p < gra.x && (i + p) < gra.y; p++)
        {
            if (gra.TICTACTOE[p][i + p] == znaczek) seria++;
            else seria = 0;

            if (seria >= gra.k) return true;
        } seria = 0;
    }

    //sprawdzanie na skos "/"
    //gorny trojkat
    for (int j = 0; j <= gra.x - gra.k; j++)
    {
        for (int p = 0; p < gra.y && (j + p) < gra.x; p++)
        {
            if (gra.TICTACTOE[(gra.x - 1) - (j + p)][p] == znaczek) seria++;
            else seria = 0;

            if (seria >= gra.k) return true;
        } seria = 0;
    }
    //dolny trojkat
    for (int i = 0; i <= gra.y - gra.k; i++)
    {
        for (int p = 0; p < gra.x && (i + p) < gra.y; p++)
        {
            if (gra.TICTACTOE[(gra.x - 1) - p][i + p] == znaczek) seria++;
            else seria = 0;

            if (seria >= gra.k) return true;
        } seria = 0;
    }
    return false;
}
int PusteMiejsca(Gra& gra)
{
    int miejsca = 0;
    for (int i = 0; i < gra.x; i++)
    {
        for (int j = 0; j < gra.y; j++)
        {
            if (gra.TICTACTOE[i][j] == '0') miejsca++;
        }
    }
    return miejsca;
}
bool CzyKoniec(Gra& gra) // sprawdzamy czy plansza nie jest juz wygrana / pelna
{
    if (CzyWygral(gra, 1) == false && CzyWygral(gra, 2) == false)
    {
        if (PusteMiejsca(gra) == 0) return true; // remis
        else return false;
    }
    else return true;
}
void GenerujKolejneRuchy(Gra& gra)
{
    if (CzyKoniec(gra) == false)
    {
        if (gra.ucinanie == 0)
        {
            printf("%d\n", PusteMiejsca(gra));
        }
        for (int i = 0; i < gra.y; i++) {
            for (int j = 0; j < gra.x; j++) {
                if (gra.TICTACTOE[j][i] == '0')
                {
                    if (gra.aktywnyGracz == pierwszy) gra.TICTACTOE[j][i] = '1';
                    else gra.TICTACTOE[j][i] = '2';
                    if (gra.ucinanie == 0) WypiszPlansze(gra);
                    if (gra.ucinanie == 1)
                    {
                        if (CzyKoniec(gra)) {
                            printf("1\n");
                            WypiszPlansze(gra);
                            return;
                        }
                    }
                    gra.TICTACTOE[j][i] = '0';
                }
            }
        }
        if (gra.ucinanie == 1) {
            gra.ucinanie = 0;
            GenerujKolejneRuchy(gra);
        }
    }
    else printf("0\n");
}
void WczytajPlansze(Gra& gra)
{
    for (int i = 0; i < gra.y; i++)
    {
        for (int j = 0; j < gra.x; j++)
        {
            cin >> gra.TICTACTOE[j][i];
        }
    }
}
int NaIleSposobowWygrana(Gra& gra, int gracz)
{
    int licznik = 0;

    for (int i = 0; i < gra.y; i++) {
        for (int j = 0; j < gra.x; j++) {
            if (gra.TICTACTOE[j][i] == '0')
            {
                if (gracz == 1)
                {
                    gra.TICTACTOE[j][i] = '1';
                    if (CzyWygral(gra, 1)) {
                        licznik++;
                    }
                }
                else
                {
                    gra.TICTACTOE[j][i] = '2';
                    if (CzyWygral(gra, 2)) {
                        licznik++;
                    }
                }

                gra.TICTACTOE[j][i] = '0';
                if (licznik == 2) return licznik;
            }
        }
    }
    return licznik;
}
int Minimax(Gra& gra, int gracz)
{
    if (CzyWygral(gra, 1)) return 1;
    if (CzyWygral(gra, 2)) return -1;
    if ((PusteMiejsca(gra) == 0)) return 0;

    if (gracz == 1)
    {
        if (NaIleSposobowWygrana(gra, 2) >= 2)
        {
            if (NaIleSposobowWygrana(gra, 1) == 0)
            {
                return -1;
            }
        }
        int najlepszyWynik = -1000;

        for (int i = 0; i < gra.y; i++) {
            for (int j = 0; j < gra.x; j++) {
                if (gra.TICTACTOE[j][i] == '0')
                {
                    gra.TICTACTOE[j][i] = '1';

                    int tmpWynik = Minimax(gra, 2);

                    if (tmpWynik == 1)
                    {
                        gra.TICTACTOE[j][i] = '0';
                        return 1;
                    } // optymalizacja nr 1 - wynik == 1 oznacza wygrana i obcinamy dalsze sprawdzanie
                    if (tmpWynik > najlepszyWynik) najlepszyWynik = tmpWynik;

                    if (PusteMiejsca(gra) == 0)
                    { // koniec rekurencji gdy plansza pelna
                        gra.TICTACTOE[j][i] = '0';
                        return najlepszyWynik;
                    }
                    gra.TICTACTOE[j][i] = '0';
                }
            }
        }
        return najlepszyWynik;
    }

    else
    {
        if (NaIleSposobowWygrana(gra, 1) >= 2)
        {
            if (NaIleSposobowWygrana(gra, 2) == 0)
            {
                return 1;
            }
        }

        int najlepszyWynik = 1000;

        for (int i = 0; i < gra.y; i++) {
            for (int j = 0; j < gra.x; j++) {
                if (gra.TICTACTOE[j][i] == '0')
                {
                    gra.TICTACTOE[j][i] = '2';

                    int tmpWynik = Minimax(gra, 1);

                    if (tmpWynik == -1)
                    {
                        gra.TICTACTOE[j][i] = '0';
                        return -1;
                    }

                    if (tmpWynik < najlepszyWynik) najlepszyWynik = tmpWynik;

                    if (PusteMiejsca(gra) == 0) {
                        gra.TICTACTOE[j][i] = '0';
                        return najlepszyWynik;
                    }
                    // cofniecie ruchu
                    gra.TICTACTOE[j][i] = '0';
                }
            }
        }
        return najlepszyWynik;
    }
}

int main()
{
    char komenda[DLUGOSC_KOMENDY] = {};
    Gra ttt;
    ttt.aktywnyGracz = pierwszy;

    while (cin.good() && (strcmp(komenda, "q") != 0))
    {
        // przyklad: GEN_ALL_POS_MOV 4 4 3 1 
        // 1 2 0 1
        // 0 1 0 2
        // 0 2 0 1
        // 0 0 2 0

        //GEN_ALL_POS_MOV 4 4 3 1 1 2 0 1 0 1 0 2 0 2 0 1 0 0 2 0
        //SOLVE_GAME_STATE 4 4 3 1 1 2 0 1 0 1 0 2 0 2 0 1 0 0 2 0

        cin >> komenda;
        cin >> ttt.y >> ttt.x;
        cin >> ttt.k;
        cin >> ttt.aktywnyGracz;

        StworzPlansze(ttt);
        WczytajPlansze(ttt);

        if (strcmp(komenda, "GEN_ALL_POS_MOV") == 0)
        {
            ttt.ucinanie = 0;
            GenerujKolejneRuchy(ttt);
        }
        else if (strcmp(komenda, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0)
        {
            ttt.ucinanie = 1;
            GenerujKolejneRuchy(ttt);
        }
        else if (strcmp(komenda, "SOLVE_GAME_STATE") == 0)
        {
            int wynik = Minimax(ttt, ttt.aktywnyGracz);
            if (wynik == 1) printf("FIRST_PLAYER_WINS\n");
            else if (wynik == -1) printf("SECOND_PLAYER_WINS\n");
            else printf("BOTH_PLAYERS_TIE\n");
        }
        UsunPlansze(ttt);
    }
    return 0;
}