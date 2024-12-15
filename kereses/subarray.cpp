#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;

    // maradék mentése mapban
    unordered_map<long long, long long> remainder_count;
    remainder_count[0] = 1; // 0 kezdünk

    long long current_sum = 0;
    long long result = 0;

    // minden szám olvasása
    for (int i = 0; i < n; i++)
    {
        long long num;
        cin >> num;

        // frissítsük az összeget és figyeljünk a negatív számokra
        current_sum = (current_sum + num % n + n) % n;

        // ha láttuk a maradékot, hozzáadjuk és elmentjük
        result += remainder_count[current_sum];

        // maradék növelése
        remainder_count[current_sum]++;
    }

    cout << result << "\n";

    return 0;
}