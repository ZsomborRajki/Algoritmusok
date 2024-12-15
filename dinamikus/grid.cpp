#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MOD = 1e9 + 7;

int countPaths(vector<string> &grid)
{
    int n = grid.size();
    // dp[i][j] útvonalak tárolása a (0,0) és (i,j) pontok között
    vector<vector<long long>> dp(n, vector<long long>(n, 0));

    // Initialize first cell ha az nem csapda
    dp[0][0] = (grid[0][0] == '.' ? 1 : 0);

    // Első sor inicializálása
    for (int j = 1; j < n; j++)
    {
        if (grid[0][j] == '.')
        {
            dp[0][j] = dp[0][j - 1];
        }
    }

    // Első oszlop inicializálása
    for (int i = 1; i < n; i++)
    {
        if (grid[i][0] == '.')
        {
            dp[i][0] = dp[i - 1][0];
        }
    }

    // Többi cella kiszámítása
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            // Ha nem csapda
            if (grid[i][j] == '.')
            {
                // Add paths from above and left
                dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % MOD;
            }
        }
    }

    return dp[n - 1][n - 1];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<string> grid(n);
    for (int i = 0; i < n; i++)
    {
        cin >> grid[i];
    }

    cout << countPaths(grid) << "\n";

    return 0;
}
