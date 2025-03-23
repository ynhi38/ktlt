#include <iostream>
using namespace std;
/*
    Hàm tính x_n sử dụng đệ quy
    Công thức: x_n = n * (x_0 + x_1 + ... + x_(n-1))
    Nếu n = 0 hoặc n = 1 thì x_n = 1 (điều kiện dừng)
*/
int tinhXnDeQuy(int n) {
    if (n == 0 || n == 1) return 1; // Điều kiện cơ sở
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += n * tinhXnDeQuy(i); // Gọi đệ quy tính các giá trị nhỏ hơn
    }
    return sum;
}
/*
    Hàm tính x_n không dùng đệ quy (dùng vòng lặp)
    Sử dụng mảng để lưu giá trị đã tính trước
*/
int tinhXnKhongDeQuy(int n) {
    int x[100]; // Mảng lưu trữ kết quả đã tính
    x[0] = x[1] = 1; // Giá trị cơ sở
    for (int i = 2; i <= n; i++) {
        x[i] = 0;
        for (int j = 0; j < i; j++) {
            x[i] += i * x[j]; // Áp dụng công thức tính x_n
        }
    }
    return x[n]; // Trả về kết quả x_n
}
int main() {
    /*
        Họ tên: Nguyễn Thị Yến Nhi
        MSSV: 3124411202
        Lớp: DCT124C7
    */
    int n;
    cout << "Nhap n: ";
    cin >> n;
    // Gọi hàm tính x_n bằng đệ quy
    cout << "Gia tri x_" << n << " (de quy) = " << tinhXnDeQuy(n) << endl;
    // Gọi hàm tính x_n không dùng đệ quy
    cout << "Gia tri x_" << n << " (khong de quy) = " << tinhXnKhongDeQuy(n) << endl;
    return 0;
}
