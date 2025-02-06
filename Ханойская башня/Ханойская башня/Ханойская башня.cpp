#include <iostream>
using namespace std;
void solve_disks(int N, int from, int to) {
    int other_disk;
    if (from == 1)
        if (to == 2)
            other_disk = 3;
        else
            other_disk = 2;
    else
        if (from == 2)
            if (to == 3)
                other_disk = 1;
            else
                other_disk = 3;
        else
            if (to == 1)
                other_disk = 2;
            else
                other_disk = 1;
    if (N > 1) solve_disks(N - 1, from, other_disk);
    cout << "Перенос диска размера " << N << " c штыря " << from << " на штырь " << to << endl;
    if (N > 1) solve_disks(N - 1, other_disk, to);

}
int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Алгоритм переноса пирамидки c 4 дисками: " << endl;
    solve_disks(4, 1, 2);
    return 0;
}
