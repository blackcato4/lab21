#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    // กรณีที่ไม่มีการใส่ตัวเลขตามหลัง (มีแค่ชื่อโปรแกรม)
    if (argc <= 1) {
        cout << "Please input numbers to find average." << endl;
        return 0;
    }

    double sum = 0.0;
    int count = argc - 1;

    // นำค่าอาร์กิวเมนต์ที่รับมาทั้งหมดมาบวกกัน
    for (int i = 1; i < argc; ++i) {
        sum += atof(argv[i]); // แปลง String เป็น Double
    }

    // คำนวณค่าเฉลี่ย
    double average = sum / count;

    // แสดงผลลัพธ์
    cout << "---------------------------------" << endl;
    cout << "Average of " << count << " numbers = " << average << endl;
    cout << "---------------------------------" << endl;

    return 0;
}
