#include <iostream>
#include <cstring>
using namespace std;
#define MAX 1000 // Định nghĩa độ dài tối đa của chuỗi
  //  Hàm kiểm tra xem một ký tự có phải là nguyên âm hay không.
void isVowel(char c, bool &result) {
    char vowels[] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
    result = false;  // Mặc định không phải nguyên âm
    for (char v : vowels) {
        if (c == v) {
            result = true;
            return;
        }
    }
}
int main() {
    /*
        Thông tin sinh viên:
        Họ tên: Nguyễn Thị Yến Nhi
        MSSV: 3124411202
        Lớp: DCT124C7
    */
    char str[MAX]; // Mảng lưu chuỗi nhập vào
    cout << "Nhập chuỗi: ";
    cin.getline(str, MAX); // Nhập chuỗi có khoảng trắng
  // Đếm số nguyên âm và phụ âm
    int vowelCount = 0, consonantCount = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) { // Nếu là chữ cái
            bool check;
            isVowel(str[i], check);
            if (check) vowelCount++;
            else consonantCount++;
        }
    }
// Tách từ và đếm số từ
    char words[MAX][MAX]; // Mảng lưu các từ
    int wordCount = 0, charCount[MAX] = {0}; // Số từ, số ký tự của từng từ
    int i = 0, j = 0;

    while (str[i] != '\0') {
        if (str[i] != ' ') { // Nếu không phải khoảng trắng, thêm vào từ
            words[wordCount][j++] = str[i];
        } else if (j > 0) { // Khi gặp khoảng trắng, kết thúc từ
            words[wordCount][j] = '\0'; // Kết thúc từ bằng ký tự NULL
            charCount[wordCount] = j;   // Lưu số ký tự của từ đó
            wordCount++;
            j = 0;
        }
        i++;
    }
    if (j > 0) { // Thêm từ cuối cùng nếu có
        words[wordCount][j] = '\0';
        charCount[wordCount] = j;
        wordCount++;
    }
    //Đếm số lần xuất hiện của mỗi từ
    int wordFrequency[MAX] = {0};
    for (int i = 0; i < wordCount; i++) {
        if (wordFrequency[i] == -1) continue; // Bỏ qua từ đã đếm
        wordFrequency[i] = 1;
        for (int j = i + 1; j < wordCount; j++) {
            if (strcmp(words[i], words[j]) == 0) { // Nếu từ giống nhau
                wordFrequency[i]++;
                wordFrequency[j] = -1; // Đánh dấu từ đã đếm
            }
        }
    }
    //Nhập ký tự cần xóa
    char ch;
    cout << "Nhập ký tự cần xóa: ";
    cin >> ch;
    // Xóa tất cả các vị trí chứa ký tự ch trong chuỗi
    char newStr[MAX];
    int k = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ch) { // Nếu không phải ký tự cần xóa, thêm vào chuỗi mới
            newStr[k++] = str[i];
        }
    }
    newStr[k] = '\0'; // Kết thúc chuỗi mới
    // Xuất kết quả
    cout << "Số nguyên âm: " << vowelCount << endl;
    cout << "Số phụ âm: " << consonantCount << endl;
    cout << "Số từ trong chuỗi: " << wordCount << endl;
    cout << "Số ký tự trong từng từ:\n";
    for (int i = 0; i < wordCount; i++) {
        cout << words[i] << ": " << charCount[i] << " ký tự\n";
    }
    cout << "Số lần xuất hiện của từng từ:\n";
    for (int i = 0; i < wordCount; i++) {
        if (wordFrequency[i] != -1)
            cout << words[i] << ": " << wordFrequency[i] << " lần\n";
    }
    cout << "Chuỗi sau khi xóa ký tự '" << ch << "': " << newStr << endl;

    return 0;
}
