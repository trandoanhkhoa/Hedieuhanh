#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
struct Tientrinh {
    int id;   // Tên tiến trình
    int tgden;// Thời gian đến
    int tgxl; //Thời gian xử lý
    int tght; //Thời gian hoàn thành
    int tgxv; //Thời gian xoay vòng
    int tgph; //Thời gian phản hồi
    int priority; 
};
void LaplichCPU(queue<Tientrinh>& processes, int sltt) {
    int tghientai = 0;
    int tongtgcho = 0;
    int totaltgxv = 0;
    int totaltgph = 0;
    while (!processes.empty()) {
        Tientrinh tthientai = processes.front();
        processes.pop();
        cout << "Qúa trình chạy của tiến trình " << tthientai.id << " từ " << tghientai << " đến " << tghientai + tthientai.tgxl << endl;
        int waitingTime = tghientai - tthientai.tgden;
        tongtgcho += waitingTime;
        tghientai += tthientai.tgxl;
        tthientai.tgxv = tghientai - tthientai.tgden;
        totaltgxv += tthientai.tgxv;
        tthientai.tgph = tghientai - tthientai.tgden - tthientai.tgxl;
        totaltgph += tthientai.tgph;
    }
    double tgchotb = (tongtgcho*1.0)/sltt;
    double averagetgxv = (totaltgxv*1.0)/sltt;
    double averagetgph = (totaltgph*1.0)/sltt;
    cout << "Thời gian chờ trung bình: " << tgchotb << endl;
    cout << "Thời gian xoay vòng trung bình: " << averagetgxv << endl;
    cout << "Thời gian phản hồi trung bình: " << averagetgph << endl;
}
 
int main() {
    queue<Tientrinh> tientrinh;
    tientrinh.push({1, 2, 7, 0, 0}); 
    tientrinh.push({2, 4, 1, 0, 0}); 
    tientrinh.push({3, 2, 4, 0, 0}); 
    tientrinh.push({4, 0, 4, 0, 0}); 
    //Đẩy tất cả các tiến trình vào một mảng vector
    vector<Tientrinh> sxtientrinh;
    while (!tientrinh.empty()) {
        sxtientrinh.push_back(tientrinh.front());
        tientrinh.pop();
    }
    //Sắp xếp theo thời gian đến và thời gian xử lý tiến trình
    sort(sxtientrinh.begin(), sxtientrinh.end(), [](const Tientrinh& p1, const Tientrinh& p2) {
        if (p1.tgden != p2.tgden) {
            return p1.tgden < p2.tgden;
        } else {
            return p1.tgxl < p2.tgxl;
        }
    });
    for (const auto& tt : sxtientrinh) {
            tientrinh.push(tt);
    }
    LaplichCPU(tientrinh, tientrinh.size());
    return 0;
} 
