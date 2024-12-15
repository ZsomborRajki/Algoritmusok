#include <iostream>
#include <vector>
#include <string>
using namespace std;

class DeBruijnSequence
{
private:
    // Mentett élek
    vector<bool> visited;
    string result;
    int n;
    int totalPossibilities;

    void generateSequence(int current)
    {
        // lehetséges élek végigjárása
        for (int i = 0; i < 2; i++)
        {
            // Kiszámoljuk a következő csúcsot
            // A << 1 balra shifteli a bitjeit
            // A & (totalPossibilities - 1) azért kell, hogy a bitenkénti és művelettel
            // a számokat 0 és totalPossibilities - 1 között tartsuk
            /*
            n = 2
            current | i | current<<1 | (totalPossibilities-1) | result
               0    | 0 |     0     |           1           |    0
               0    | 1 |     0     |           1           |    1
               1    | 0 |     2     |           1           |    0
               1    | 1 |     2     |           1           |    1
            */
            int next = ((current << 1) & (totalPossibilities - 1)) | i;

            // Ha még nem jártunk itt, akkor meglátogatjuk
            // current * 2 + i azért kell, mert a következő csúcsot a current csúcsból
            if (!visited[current * 2 + i])
            {
                visited[current * 2 + i] = true;
                // Rekurzív hívás a következő csúcsra Depth-first search módszerrel
                generateSequence(next);
                // eredményhez hozzáadjuk a számot
                result += char('0' + i);
            }
        }
    }

public:
    DeBruijnSequence(int sequenceLength) : n(sequenceLength)
    {
        // A lehetséges élek száma
        totalPossibilities = 1 << (n - 1);
        // A lehetséges élek száma * 2, mert minden élhez két irány van
        visited.resize(totalPossibilities * 2, false);
        result = "";
    }

    string generate()
    {

        // Speciális esetek kezelése
        if (n == 1)
        {
            return "10";
        }

        // Depth-first search keresés indítása 0 kezdőpontból
        generateSequence(0);

        // A végén hozzáadjuk az utolsó n - 1 számot
        for (int i = 0; i < n - 1; i++)
        {
            result += '0';
        }

        return result;
    }
};

int main()
{
    int n;
    cin >> n;

    DeBruijnSequence generator(n);
    string result = generator.generate();

    cout << result << endl;
    return 0;
}