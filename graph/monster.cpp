#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct Point
{
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

struct State
{
    Point pos;
    string path;
    State(Point p, string path) : pos(p), path(path) {}
};

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};
const char dir[] = {'U', 'R', 'D', 'L'};

void compute_monster_distances(vector<vector<int>> &monster_dist, const vector<string> &grid, const vector<Point> &monsters)
{
    int n = grid.size();
    int m = grid[0].size();
    queue<Point> q;

    //  Maximum távolság minden mezőre
    monster_dist.assign(n, vector<int>(m, 1e9));

    // Minden szörny kezdőpozíciója
    for (const Point &monster : monsters)
    {
        monster_dist[monster.x][monster.y] = 0;
        q.push(monster);
    }

    // BFS a szörnyökkel
    while (!q.empty())
    {
        Point curr = q.front();
        q.pop();

        // szomszédok bejárása
        for (int d = 0; d < 4; d++)
        {
            int nx = curr.x + dx[d];
            int ny = curr.y + dy[d];

            // ha a szomszéd benne van a pályán és még nem jártunk ott
            if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                grid[nx][ny] != '#' &&
                monster_dist[nx][ny] > monster_dist[curr.x][curr.y] + 1)
            {
                monster_dist[nx][ny] = monster_dist[curr.x][curr.y] + 1;
                q.push(Point(nx, ny));
            }
        }
    }
}

bool solve_labyrinth(vector<string> &grid, int n, int m)
{
    Point start;
    vector<Point> monsters;

    // kezdő pozíció és szörnyek pozícióinak megtalálása
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 'A')
            {
                start = Point(i, j);
                grid[i][j] = '.';
            }
            else if (grid[i][j] == 'M')
            {
                monsters.push_back(Point(i, j));
            }
        }
    }

    vector<vector<int>> monster_dist;
    compute_monster_distances(monster_dist, grid, monsters);

    if (monster_dist[start.x][start.y] <= 0)
    {
        cout << "NO\n";
        return false;
    }

    // BFS válltozók
    queue<State> q;
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    // alapértelmezett értékek
    q.push(State(start, ""));
    visited[start.x][start.y] = true;

    while (!q.empty())
    {
        State curr = q.front();
        q.pop();

        // Már elértünk a célhoz, rögtön kilépünk
        if (curr.pos.x == 0 || curr.pos.x == n - 1 ||
            curr.pos.y == 0 || curr.pos.y == m - 1)
        {
            cout << "YES\n"
                 << curr.path.length() << "\n"
                 << curr.path << "\n";
            return true;
        }

        // szomszédok bejárása
        for (int d = 0; d < 4; d++)
        {
            int nx = curr.pos.x + dx[d];
            int ny = curr.pos.y + dy[d];

            // ha a szomszéd benne van a pályán és még nem jártunk ott
            if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                grid[nx][ny] != '#' && !visited[nx][ny])
            {

                // ha a szörnyök nem érnek el oda hamarabb
                if (curr.path.length() + 1 < monster_dist[nx][ny])
                {
                    visited[nx][ny] = true;
                    q.push(State(Point(nx, ny), curr.path + dir[d]));
                }
            }
        }
    }

    cout << "NO\n";
    return false;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    for (int i = 0; i < n; i++)
    {
        cin >> grid[i];
    }

    solve_labyrinth(grid, n, m);
    return 0;
}
