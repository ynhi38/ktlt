#include <iostream> // Thư viện nhập xuất dữ liệu
#include <fstream>  // Thư viện làm việc với file
#include <climits>  // Thư viện chứa giá trị INT_MIN
using namespace std;

// Hàm đọc dữ liệu từ file test.txt
void readFile(const char *filename, int **&A, int &m, int &n) {
    ifstream file(filename); // Mở file để đọc
    if (!file) { // Kiểm tra nếu không mở được file
        cerr << "Lỗi: Không thể mở file\n"; // In lỗi
        exit(1); // Thoát chương trình
    }
    file >> m >> n; // Đọc số dòng và số cột
    A = new int *[m]; // Cấp phát bộ nhớ cho mảng 2 chiều
    for (int i = 0; i < m; i++) {
        A[i] = new int[n]; // Cấp phát từng hàng
        for (int j = 0; j < n; j++) {
            file >> A[i][j]; // Đọc từng phần tử vào mảng
        }
    }
    file.close(); // Đóng file sau khi đọc xong
}

// Hàm tìm số lớn nhất và lớn nhì trong mảng
void findMaxNumbers(int **A, int m, int n, int &max1, int &max2) {
    max1 = max2 = INT_MIN; // Khởi tạo max1 và max2 với giá trị nhỏ nhất có thể
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] > max1) { // Nếu phần tử lớn hơn max1
                max2 = max1; // Cập nhật max2
                max1 = A[i][j]; // Cập nhật max1
            } else if (A[i][j] > max2 && A[i][j] != max1) { // Nếu phần tử lớn hơn max2 nhưng khác max1
                max2 = A[i][j]; // Cập nhật max2
            }
        }
    }
}

// Hàm tính tổng các phần tử trên mỗi cột
void sumColumns(int **A, int m, int n, int *&sumArr) {
    sumArr = new int[n]{}; // Cấp phát động cho mảng sumArr và khởi tạo các phần tử bằng 0
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            sumArr[j] += A[i][j]; // Cộng dồn giá trị từng cột
        }
    }
}

// Hàm tạo mảng C từ mảng A
void createArrayC(int **A, int **&C, int m, int n) {
    C = new int *[m]; // Cấp phát động cho mảng C
    for (int i = 0; i < m; i++) {
        int minVal = A[i][0]; // Giả sử phần tử đầu tiên của hàng là nhỏ nhất
        for (int j = 1; j < n; j++) {
            if (A[i][j] < minVal) { // Nếu tìm thấy giá trị nhỏ hơn
                minVal = A[i][j]; // Cập nhật minVal
            }
        }
        C[i] = new int[n]; // Cấp phát hàng thứ i của C
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] * minVal; // Nhân phần tử với giá trị nhỏ nhất của hàng đó
        }
    }
}

// Hàm ghi kết quả ra file output.txt
void writeFile(const char *filename, int max1, int max2, int *sumArr, int n, int **C, int m) {
    ofstream file(filename); // Mở file để ghi
    if (!file) { // Kiểm tra nếu không mở được file
        cerr << "Lỗi: Không thể mở file để ghi!\n"; // In lỗi
        exit(1); // Thoát chương trình
    }
    file << "Số lớn nhất: " << max1 << "\n"; // Ghi số lớn nhất
    file << "Số lớn nhì: " << max2 << "\n"; // Ghi số lớn nhì
    file << "Tổng mỗi cột: ";
    for (int j = 0; j < n; j++) {
        file << sumArr[j] << " "; // Ghi tổng từng cột
    }
    file << "\nMảng C:\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            file << C[i][j] << " "; // Ghi từng phần tử của mảng C
        }
        file << "\n";
    }
    file.close(); // Đóng file sau khi ghi xong
}

// Hàm giải phóng bộ nhớ của mảng động
void freeMemory(int **A, int m) {
    for (int i = 0; i < m; i++) {
        delete[] A[i]; // Giải phóng từng hàng
    }
    delete[] A; // Giải phóng con trỏ mảng
}

// Hàm main
int main() {
    /*
        Họ và tên: Nguyễn Thị Tến Nhi
        MSSV: 3124411202
        Lớp: DCT124C7
    */
    int **A, **C, m, n; // Khai báo mảng động A, C và các biến m, n để lưu kích thước mảng
    int max1, max2; // Khai báo biến lưu số lớn nhất và lớn nhì
    int *sumArr; // Con trỏ mảng lưu tổng từng cột
    readFile("test.txt", A, m, n); // Đọc dữ liệu từ file
    findMaxNumbers(A, m, n, max1, max2); // Tìm số lớn nhất và lớn nhì
    sumColumns(A, m, n, sumArr); // Tính tổng từng cột
    createArrayC(A, C, m, n); // Tạo mảng C theo quy tắc bài toán
    writeFile("output.txt", max1, max2, sumArr, n, C, m); // Ghi kết quả ra file
    freeMemory(A, m); // Giải phóng bộ nhớ mảng A
    freeMemory(C, m); // Giải phóng bộ nhớ mảng C
    delete[] sumArr; // Giải phóng mảng tổng sumArr
    cout << "Chương trình hoàn thành, kiểm tra file output.txt\n"; // Thông báo hoàn thành
    return 0;
}
