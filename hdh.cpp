#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Tientrinh {
    int id;    // Tên tiến trình
    int tgden; // Thời gian đến
    int tgxl;  // Thời gian xử lý
    int tght;  // Thời gian hoàn thành
    int tgxv;  // Thời gian xoay vòng
    int tgph;  // Thời gian phản hồi
};

void LaplichCPU(queue<Tientrinh>& processes, int sltt) {
    int tghientai = 0;
    int tongtgcho = 0;
    int totaltgxv = 0;
    int totaltgph = 0;
    int tongtgchay = 0; // Tổng thời gian chạy của tất cả các tiến trình

    while (!processes.empty()) {
        Tientrinh tthientai = processes.front();
        processes.pop();
        cout << "Quá trình chạy của tiến trình " << tthientai.id << " từ " << tghientai << " đến " << tghientai + tthientai.tgxl << endl;
        int waitingTime = tghientai - tthientai.tgden;
        tongtgcho += waitingTime;
        tghientai += tthientai.tgxl;
        tthientai.tgxv = tghientai - tthientai.tgden;
        totaltgxv += tthientai.tgxv;
        tthientai.tgph = tghientai - tthientai.tgden - tthientai.tgxl;
        totaltgph += tthientai.tgph;
        tongtgchay += tthientai.tgxl;
    }

    double tgchotb = (tongtgcho * 1.0) / sltt;
    double averagetgxv = (totaltgxv * 1.0) / sltt;
    double averagetgph = (totaltgph * 1.0) / sltt;
    double cpus = ((tongtgchay * 1.0) / tghientai) * 100; // Tỷ lệ sử dụng CPU

    cout << "Thời gian chờ trung bình: " << tgchotb << endl;
    cout << "Thời gian xoay vòng trung bình: " << averagetgxv << endl;
    cout << "Thời gian phản hồi trung bình: " << averagetgph << endl;
    cout << "Hiệu suất CPU: " << cpus << "%" << endl;
}

int main() {
    queue<Tientrinh> tientrinh;
    int n; // Số lượng tiến trình
    cin >> n;
    for (int i = 0; i < n; i++) {
        Tientrinh t;
        t.id = i + 1; // Tăng id tự động
        cin >> t.tgden >> t.tgxl;
        tientrinh.push(t);
    }

    vector<Tientrinh> sxtientrinh;
    while (!tientrinh.empty()) {
        sxtientrinh.push_back(tientrinh.front());
        tientrinh.pop();
    }

    // Sắp xếp theo thời gian đến và thời gian xử lý tiến trình
    sort(sxtientrinh.begin(), sxtientrinh.end(), [](const Tientrinh& p1, const Tientrinh& p2) {
        if (p1.tgxl != p2.tgxl) {
            return p1.tgxl < p2.tgxl;
        } else {
            return p1.tgden < p2.tgden;
        }
    });

    Tientrinh tmp;
    int vt = 0;
    int ID = -1;
    int tg = 9999;
    for (int i = 0; i < sxtientrinh.size(); i++) {
        if (sxtientrinh[i].tgden < tg) {
            ID = sxtientrinh[i].id;
            tg = sxtientrinh[i].tgden;
            tmp = sxtientrinh[i];
            vt = i;
        }
    }

    // Xóa đi tiến trình chạy đầu tiên trong mảng vector
    sxtientrinh.erase(sxtientrinh.begin() + vt);

    // Đẩy tiến trình đầu tiên vào hàng đợi để chạy
    tientrinh.push(tmp);

    for (const auto& tt : sxtientrinh) {
        tientrinh.push(tt);
    }

    LaplichCPU(tientrinh, tientrinh.size());

    return 0;
}