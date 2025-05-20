# Hệ thống quản lý ví điểm thưởng

## Prerequisite
- **macOS (Apple Silicon/M1/M2/M3 tested)** hoặc Linux
- **Windows** (xem hướng dẫn riêng bên dưới)
- **g++ >= 7** (C++17)
- **make**
- **OpenSSL dev** (Mac: `brew install openssl@3`, Windows: cài OpenSSL và thiết lập biến môi trường)
- **curl** (để tải thư viện QR code nếu cần)

### Prerequisite cho Windows
- **MinGW-w64** (g++ >= 7, tải tại https://www.mingw-w64.org/)
- **make** (có thể cài qua MSYS2 hoặc MinGW)
- **OpenSSL cho Windows** (tải tại https://slproweb.com/products/Win32OpenSSL.html hoặc dùng MSYS2: `pacman -S mingw-w64-x86_64-openssl`)
- **Thêm đường dẫn include/lib của OpenSSL vào lệnh build:**
  - Ví dụ: `-IC:/OpenSSL-Win64/include -LC:/OpenSSL-Win64/lib`
- **curl** (tùy chọn, có thể tải tại https://curl.se/windows/)

## Build & Run
### 1. Build và chạy bằng Makefile (Linux/macOS/Windows có make)
```bash
make run
```
- File thực thi sẽ nằm ở `build/wallet_app` (hoặc `build/wallet_app.exe` trên Windows)

### 2. Build và chạy bằng script tự động (Linux/macOS)
```bash
./build_and_run.sh
```
- Script sẽ log từng bước build và chạy app.

### 3. Build thủ công (nếu cần)
#### Trên macOS:
```bash
cd src
# Build
 g++ -std=c++17 -I/opt/homebrew/opt/openssl@3/include -L/opt/homebrew/opt/openssl@3/lib \
   -o wallet_app main.cpp user.cpp manager.cpp wallet.cpp transaction.cpp utils.cpp data_manager.cpp otp.cpp qrcodegen.cpp -lssl -lcrypto
# Chạy
 ./wallet_app
```
#### Trên Windows (MinGW):
```bash
cd src
# Build
 g++ -std=c++17 -IC:/OpenSSL-Win64/include -LC:/OpenSSL-Win64/lib \
   -o wallet_app.exe main.cpp user.cpp manager.cpp wallet.cpp transaction.cpp utils.cpp data_manager.cpp otp.cpp qrcodegen.cpp -lssl -lcrypto
# Chạy
 wallet_app.exe
```

## Chức năng chính
- Đăng ký, đăng nhập tài khoản (hash mật khẩu, sinh mật khẩu tự động, chuẩn TOTP)
- Quản lý ví điểm thưởng, chuyển điểm giữa các ví, ví tổng
- Quản lý giao dịch, lịch sử, trạng thái
- OTP xác thực các thao tác quan trọng (chuẩn Google Authenticator)
- Phân quyền user/manager
- Backup/phục hồi dữ liệu
- Báo cáo: xem số dư, lịch sử giao dịch, tổng hợp
- Hiển thị QR code OTP trực tiếp trên terminal

## Thành viên & Phân công
| Họ tên      | Công việc chính                                  |
|------------|--------------------------------------------------|
| **Thanh**      | Phát triển chức năng quản lý (manager), backup, báo cáo |
| **Quang**      | Phát triển chức năng người dùng (user), OTP, giao dịch  |
| **Nhật Anh**   | Phân tích yêu cầu, tạo boilerplate, build script, main entry, tích hợp hệ thống |

## Tham khảo
- [CPP_OTP](https://github.com/patzol768/cpp-otp)
- [COTP](https://github.com/tilkinsc/COTP)
- [ACID](https://200lab.io/blog/acid-la-gi/)
- [QR-Code-generator](https://github.com/nayuki/QR-Code-generator)

## Luồng thao tác
- Đăng ký: nhập thông tin, hệ thống kiểm tra trùng username, hash mật khẩu hoặc sinh mật khẩu tự động nếu không nhập.
- Đăng nhập: nhập username, password, kiểm tra hash, phân quyền user/manager.
- User: xem/sửa thông tin cá nhân, đổi mật khẩu, chuyển điểm, xác thực OTP khi thao tác quan trọng, xem số dư, lịch sử giao dịch.
- Manager: tạo tài khoản mới, xem danh sách user, điều chỉnh thông tin hộ user (có OTP), xem báo cáo tổng hợp, nạp điểm từ ví tổng, backup/restore.
- Giao dịch: chuyển điểm giữa các ví, kiểm tra số dư, ghi log giao dịch, trạng thái.
- Backup/Restore: tạo bản sao lưu dữ liệu, phục hồi khi cần.

## File dữ liệu
- `users.txt`: lưu thông tin user, manager
- `transactions.txt`: lưu lịch sử giao dịch
- `backup/`: thư mục chứa bản sao lưu

## Phân tích & Đặc tả chức năng
- **Lưu trữ dữ liệu:**
  - Tất cả user, manager lưu chung 1 file `users.txt` để dễ quản lý, backup, tránh trùng lặp.
  - Giao dịch lưu ở `transactions.txt`. Backup tự động vào thư mục `backup/`.
- **Bảo mật:**
  - Mật khẩu được hash trước khi lưu (không lưu plain text).
  - OTP chuẩn TOTP, xác thực 2 lớp khi đổi thông tin quan trọng.
- **Luồng chính:**
  - Đăng ký/đăng nhập, phân quyền user/manager.
  - User thao tác với ví cá nhân, manager thao tác với toàn hệ thống.
  - Giao dịch chuyển điểm kiểm tra số dư, xác thực OTP, ghi log.
  - Backup/restore dữ liệu, báo cáo tổng hợp.
- **Lý do chọn thiết kế:**
  - Lưu file chung giúp dễ backup, dễ kiểm soát, phù hợp bài tập lớn nhóm nhỏ.
  - Hash password, OTP giúp tăng bảo mật, sát thực tế.

## Quy tắc commit & minh chứng đóng góp
- Mỗi thành viên khi hoàn thành chức năng phải commit với message rõ ràng, ví dụ:
  - `[manager] Thanh: Thêm chức năng backup/restore`
  - `[user] Quang: Hoàn thiện xác thực OTP khi đổi mật khẩu`
  - `[core] Nhật Anh: Tạo Makefile, build script, tích hợp QR code`
- Mỗi commit nên gắn tên người thực hiện để GV dễ kiểm tra đóng góp.
- Khi nộp bài, đảm bảo lịch sử commit thể hiện rõ quá trình làm việc của từng thành viên.

## Lưu ý chấm điểm & báo cáo
- Khi demo, mỗi thành viên cần nắm rõ phần mình làm và tổng thể hệ thống.
- Nếu thành viên không có commit hoặc không trả lời được phần mình làm sẽ bị trừ điểm nặng theo quy định.
- Không sao chép mã nguồn giữa các nhóm.

---

## HƯỚNG DẪN SỬ DỤNG CHI TIẾT

### 1. Đăng ký tài khoản mới
- Chọn `2. Đăng ký` ở menu chính.
- Nhập username, họ tên, email, vai trò (user/manager), mật khẩu (hoặc để trống để sinh tự động).
- Lưu ý: username không được trùng.
- Sau khi đăng ký, hệ thống sẽ in ra mật khẩu (nếu sinh tự động) và secret key OTP (dưới dạng QR code).

### 2. Đăng nhập
- Chọn `1. Đăng nhập` ở menu chính.
- Nhập username, password.
- Nếu đúng, sẽ vào menu user hoặc manager.

### 3. Scan mã QR OTP
- Sau khi đăng ký hoặc trong menu user, chọn `8. Xem mã QR OTP để scan`.
- Dùng app Google Authenticator/Microsoft Authenticator scan trực tiếp QR trên terminal.
- Nếu không scan được, copy link bên dưới QR vào web https://www.qr-code-generator.com/ để tạo QR.

### 4. Đổi mật khẩu/Xác thực OTP
- Khi đổi mật khẩu, cập nhật thông tin, chuyển điểm... hệ thống sẽ yêu cầu nhập mã OTP.
- Mở app Google Authenticator, nhập đúng 6 số OTP hiện tại.
- Nếu sai OTP, kiểm tra lại secret key trên app có trùng với QR vừa scan không, và đồng bộ thời gian hệ thống.

### 5. Chuyển điểm
- Chọn `4. Chuyển điểm` trong menu user.
- Nhập username người nhận, số điểm, xác thực OTP.
- Nếu thành công, số dư hai ví sẽ thay đổi, log giao dịch được ghi lại.

### 6. Nạp điểm từ ví tổng (chỉ manager)
- Đăng nhập bằng tài khoản manager.
- Chọn `10. Nạp điểm cho user từ ví tổng`.
- Nhập username user cần nạp, số điểm.
- Số dư ví tổng sẽ giảm, ví user tăng.

### 7. Backup/Restore dữ liệu (chỉ manager)
- Chọn `8. Backup dữ liệu` để tạo bản sao lưu.
- Chọn `9. Phục hồi dữ liệu` để phục hồi từ bản backup mới nhất.

### 8. Báo cáo tổng hợp (chỉ manager)
- Chọn `6. Xem báo cáo tổng hợp` để xem tổng số user, manager, giao dịch, tổng điểm, số dư ví tổng.

### 9. Xem lịch sử giao dịch
- Chọn `6. Xem lịch sử giao dịch` trong menu user để xem toàn bộ giao dịch liên quan đến ví của mình.

---

**Mọi thắc mắc hoặc lỗi phát sinh, vui lòng liên hệ nhóm phát triển hoặc xem lại README này!** 