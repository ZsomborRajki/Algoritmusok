#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Cell
{
    int row, col, height;
    Cell(int r, int c, int h) : row(r), col(c), height(h) {}
};

struct CompareCell
{
    bool operator()(const Cell &a, const Cell &b)
    {
        return a.height > b.height;
    }
};

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int calculateWaterVolume(vector<vector<int>> &heights)
{
    int n = heights.size();
    int m = heights[0].size();

    vector<vector<bool>> visited(n, vector<bool>(m, false));

    priority_queue<Cell, vector<Cell>, CompareCell> pq;

    for (int i = 0; i < n; i++)
    {
        pq.push(Cell(i, 0, heights[i][0]));
        pq.push(Cell(i, m - 1, heights[i][m - 1]));
        visited[i][0] = visited[i][m - 1] = true;
    }
    for (int j = 1; j < m - 1; j++)
    {
        pq.push(Cell(0, j, heights[0][j]));
        pq.push(Cell(n - 1, j, heights[n - 1][j]));
        visited[0][j] = visited[n - 1][j] = true;
    }

    int totalWater = 0;

    while (!pq.empty())
    {
        Cell current = pq.top();
        pq.pop();

        for (int i = 0; i < 4; i++)
        {
            int newRow = current.row + dx[i];
            int newCol = current.col + dy[i];

            if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < m && !visited[newRow][newCol])
            {
                visited[newRow][newCol] = true;

                int waterHeight = max(current.height - heights[newRow][newCol], 0);
                totalWater += waterHeight;

                pq.push(Cell(newRow, newCol, max(current.height, heights[newRow][newCol])));
            }
        }
    }

    return totalWater;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> heights(n, vector<int>(m));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> heights[i][j];
            }
        }

        cout << calculateWaterVolume(heights) << endl;

        if (t > 0)
            cout << endl;
    }

    return 0;
}
