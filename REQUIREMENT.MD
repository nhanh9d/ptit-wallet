# Đề bài tập lớn: Hệ thống quản lý ví điểm thưởng

Gửi cả lớp,

Tôi gửi bản mô tả bài tập lớn dưới đây. Các em tìm đọc thêm các tài liệu để hiểu rõ đề bài của dự án. Chúng ta sẽ tiến hành phân tích từng mục để có bản yêu cầu và thiết kế khả thi nhất cho đồ án. Sau đó, chúng ta sẽ chia thành các nhóm 3-4 người để cài đặt dự án.

Có điều gì thắc mắc, các em có thể email hỏi tôi hoặc đến buổi học sẽ cùng trao đổi.

**Thời hạn nộp:** hạn cuối nộp bài tập lớn …/…/2025. (Tôi sẽ kiểm tra lịch thi với Trường để chọn ngày nộp bài tập lớn và thông báo cụ thể cho lớp)

Chúc mọi người tìm được hứng thú khi thực hiện bài tập lớn này.

Cảm ơn cả lớp!

---

## Yêu cầu chung

- Viết chương trình bằng **C++** (dĩ nhiên, vì đây là bài tập môn Ngôn ngữ C++)
- Giao diện **văn bản**, thao tác kiểu nhập dòng lệnh.
- Tạo một tài khoản kho chứa mã nguồn (source code repo) trên [GitHub](https://github.com) hoặc [Bitbucket](https://bitbucket.org)
- Tạo kho chứa mã nguồn cho dự án này
- Chia sẻ kho chứa cho các thành viên trong nhóm để cùng làm. Các thành viên đều phải tham gia vào các phần việc trong dự án.
- Khi nộp bài, chia sẻ truy cập kho chứa cho GV với vai trò đọc để GV có thể theo dõi quá trình thực hiện và chấm điểm.

---

## Tiêu chí chấm điểm

### (A) Chương trình có đủ chức năng, chạy đúng như mô tả (**50%**)

### (B) Tài liệu dự án (**15%**)
Trong `README.md` của kho chứa mã nguồn cho dự án cần có:
- Giới thiệu dự án
- Giới thiệu thành viên tham gia dự án, kèm công việc được giao (xem thêm trong mục C)
- Bản phân tích, đặc tả chức năng đầy đủ
- Mô tả cách tải chương trình, dịch chương trình, các tập tin, các thư viện kèm theo (nếu có)
- Mô tả cách chạy chương trình, kèm các thao tác thực hiện
- Nếu có tham khảo tài liệu thì cần ghi rõ nguồn tài liệu đã tham khảo

#### Mã nguồn:
- Mã nguồn có chú thích, giải thích hoạt động rõ ràng; mô tả input/output, thủ tục xử lý.

### (C) Quản lý nhân lực dự án (**15%**)
- Trong danh mục các lần nộp bài, nộp tập tin mã nguồn (commits) phải thể hiện công việc và đóng góp của các thành viên của dự án (xem B)

### (D) Báo cáo (**20%**)
- Khi nộp phải có mặt cả nhóm và chạy demo chương trình để chấm điểm.
- Nhóm trả lời các câu hỏi của GV về chương trình, dự án.

### (E) Trừ điểm
- Nếu thành viên không có đủ minh chứng tham gia thực hiện dự án, gồm:
    - Không có thông tin nộp bài, không tham gia xây dựng chương trình/báo cáo (xem C)
    - Thành viên không trả lời được câu hỏi theo phân công trách nhiệm/công việc, cũng như câu hỏi liên quan đến tổng thể dự án (xem D)
    - Điểm bài tập lớn của thành viên này là **1**; đồng thời, điểm mục (C) và (D) của các thành viên khác trong nhóm bị trừ **50%** so với số điểm cho thực tế.
- Trường hợp thành viên có đủ minh chứng nộp bài và tham gia thực hiện nhưng không tham gia buổi báo cáo thì được chấm theo các thang điểm (A, B, C), trừ thang điểm Báo cáo (D) là **0**.
- Nếu nội dung thực hiện (mã nguồn, báo cáo) bị phát hiện là **sao chép** từ nhóm khác thì điểm bài tập lớn của các nhóm tham gia chia sẻ, sao chép là **0**.

---

# Đề tài: Hệ thống đăng nhập và đăng ký tài khoản, quản lý ví điểm thưởng

Dự án Hệ thống đăng nhập và đăng ký chủ yếu liên quan đến quá trình đăng ký người dùng. Thông tin xác thực người dùng như tên người dùng và mật khẩu được yêu cầu từ người dùng. Nếu người dùng đăng ký thành công thì với thông tin xác thực được cung cấp, một bản ghi (có thể là tập tin) của người dùng cụ thể sẽ được tạo trong cơ sở dữ liệu (CSDL).

**Ví điểm thưởng** là cơ chế quản lý các lượng (đơn vị: điểm) được dùng để quy đổi ra hàng hóa (còn gọi là hoạt động mua - bán). Giữa các ví có giao dịch chuyển điểm.

## A. Các chức năng

1. **Tạo mới tài khoản khi đăng ký:**
    - Người dùng nhập dữ liệu để tạo tài khoản.
    - Có thể có nhân viên nhập liệu (người quản lý) để tạo tài khoản hộ người dùng, với điều kiện người dùng cung cấp đầy đủ thông tin cá nhân theo yêu cầu tạo tài khoản.
    - Hãy phân tích và đề xuất một cấu trúc dữ liệu (lớp) quản lý thông tin tài khoản người dùng.

2. **Lưu trữ dữ liệu:**
    - Lưu lại dữ liệu tài khoản người dùng xuống tập tin.
    - Hãy đề xuất việc lưu trữ dữ liệu người dùng dưới dạng tập tin riêng cho từng người dùng hay một tập tin cho tất cả người dùng? Nêu lý do lựa chọn giải pháp.
    - Với mật khẩu, hãy tìm hiểu cách lưu mật khẩu của người dùng vào CSDL. Gợi ý: dùng hàm băm (hash function).
    - Mọi lưu trữ phải có bản sao lưu (backup). Hãy tìm hiểu quy trình sao lưu - phục hồi dữ liệu. Đề xuất giải pháp sao lưu cho dữ liệu người dùng.

3. **Quản lý đăng nhập**
    - **3.1 Sinh mật khẩu tự động:**
        - Sinh một mật khẩu tự động kèm theo thông tin đăng nhập của người dùng trong trường hợp người dùng không cung cấp mật khẩu.
        - Trường hợp này thường được sử dụng khi nhân viên quản lý mở tài khoản mới và người dùng không thể trực tiếp nhập mật khẩu cho mình.
    - **3.2 Thay đổi mật khẩu:**
        - Một người dùng có thể tự thay đổi mật khẩu đăng nhập của mình.
        - Hãy tìm hiểu quy trình xử lý thay đổi mật khẩu.
        - Với trường hợp mật khẩu tự sinh, hệ thống phải kiểm tra mật khẩu là tự sinh và yêu cầu người dùng thay đổi ngay mật khẩu mới trong lần đăng nhập đầu tiên của mình.
    - **3.3 OTP - One Time Password:**
        - Bảo mật hai lớp để xác thực giao dịch.
        - OTP được sử dụng trong đồ án này để xác thực các hoạt động thay đổi thông tin quan trọng của người dùng.
        - Hãy tìm hiểu về OTP và đề xuất giải pháp sử dụng OTP cho đồ án (phần B). Xem nguồn tham khảo [1] và [2] và tìm thêm các tài liệu khác về OTP.
    - **3.4 Đăng nhập:**
        - Khi người dùng đăng nhập bằng tài khoản của mình, chương trình phải tìm kiếm trong dữ liệu đã lưu trữ và xác định liệu thông tin đăng nhập đó có tồn tại và hợp lệ không. Nếu hợp lệ, cho phép người dùng vào hệ thống và sử dụng các chức năng tương ứng.

## B. Phân chia người dùng và chức năng

### Nhóm người dùng gồm:

- **a/ Người dùng thông thường** chỉ được phép truy xuất thông tin cá nhân của mình.
    - Được phép điều chỉnh tên, mật khẩu v.v. Hãy căn cứ vào quản lý thông tin tài khoản trên để đưa ra yêu cầu cho phép điều chỉnh, thay đổi trường dữ liệu cụ thể và viết các chức năng cập nhật tương ứng.
    - Khi điều chỉnh xong, hệ thống gửi một mã OTP đến chủ tài khoản cùng thông báo các nội dung sẽ thay đổi để chủ tài khoản xác nhận thao tác cập nhật.
    - Nếu mã OTP do chủ tài khoản nhập vào hợp lệ, hệ thống tiến hành cập nhật thông tin của người dùng.

- **b/ Người dùng quản lý:** Ngoài chức năng quản lý thông tin cá nhân, người quản lý có thể:
    - b.1 Theo dõi danh sách nhóm
    - b.2 Tạo thêm tài khoản mới
    - b.3 Điều chỉnh thông tin của tài khoản khi có yêu cầu từ chủ tài khoản (làm hộ). Khi điều chỉnh xong, hệ thống gửi một mã OTP đến chủ tài khoản cùng thông báo các nội dung sẽ thay đổi để chủ tài khoản xác nhận thao tác cập nhật.
    - Nếu mã OTP do chủ tài khoản nhập vào hợp lệ, hệ thống tiến hành cập nhật thông tin của người dùng.
    - **Chú ý:** Không được phép thay đổi tên tài khoản đăng nhập.

## C. Quản lý hoạt động ví

- Mỗi người dùng có một bộ dữ liệu về số điểm (**ví - wallet**) và dữ liệu các giao dịch trao đổi, chuyển điểm từ một ví sang một ví khác.
- Một ví có mã số định danh duy nhất phân biệt với tất cả các ví còn lại.
- **Ví tổng:** nguồn duy nhất sinh ra tổng số điểm sẽ lưu chuyển trong toàn bộ hệ thống.
- **Giao dịch chuyển d điểm từ ví A sang ví B** sẽ gồm các thao tác thành phần sau:

    1. Tìm, mở ví A. Đây là ví chủ của giao dịch, là ví của chủ tài khoản muốn thực hiện chuyển điểm đi.
    2. Tìm, mở ví B. Đây là ví đích của giao dịch. Nếu mã ví B tồn tại, tiếp tục đến 3_Giao dịch
    3. Giao dịch: Hai tác vụ dưới đây là không tách rời (atomic). Bất kỳ có một bất thường (exception) nào xảy ra trong một tác vụ đều dẫn đến hủy toàn bộ giao dịch, phục hồi lại trạng thái số dư của hai ví A và B trước 3_
        - 3.1 `if (A.balance >= d)`
            - `A.balance = A.balance - d`
        - else
            - "low balance. Cannot proceed.”. Đến 4_
        - 3.2 `B.balance = B.balance + d`
    4. Kết thúc

- Hãy đề xuất cách sử dụng OTP để xác nhận thực hiện giao dịch chuyển điểm giữa các ví.
- Hệ thống ghi nhận lại giao dịch này trong lịch sử giao dịch (**transaction log**)
- **Báo cáo:** hệ thống cho phép người dùng theo dõi số dư, lịch sử giao dịch (và trạng thái thực hiện giao dịch)

---

## Nguồn tham khảo
- [1] CPP_OTP, https://github.com/patzol768/cpp-otp, truy cập lần cuối ngày 04/10/2024
- [2] COTP, https://github.com/tilkinsc/COTP, truy cập lần cuối ngày 04/10/2024
- [3] ACID, https://200lab.io/blog/acid-la-gi/, truy cập lần cuối ngày 04/10/2024