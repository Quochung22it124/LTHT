#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void send_email(const char *recipient, const char *subject, const char *body) {
    // Mở một pipe để gửi email
    FILE *mail_pipe = popen("/usr/bin/msmtp --read-envelope-from --read-recipients", "w");
    if (mail_pipe == NULL) {
        perror("Failed to open pipe for sending mail");
        return;
    }

    // Thêm thông tin địa chỉ "From" để tránh lỗi
    fprintf(mail_pipe, "From: hieund.22it@vku.udn.vn\n");
    fprintf(mail_pipe, "To: %s\n", recipient);
    fprintf(mail_pipe, "Subject: %s\n", subject);
    fprintf(mail_pipe, "\n%s\n", body);

    // Đóng pipe và kiểm tra lỗi
    if (pclose(mail_pipe) == -1) {
        perror("Failed to close pipe");
    }
}

void log_email(const char *recipient, const char *subject, const char *body) {
    FILE *log_file = fopen("/home/hieunguyen/Personal/LTHT/output.txt", "a");
    if (log_file == NULL) {
        perror("Failed to open log file");
        return;
    }

    time_t current_time = time(NULL);
    char *time_str = ctime(&current_time);
    // Ghi log
    fprintf(log_file, "Time: %s", time_str);
    fprintf(log_file, "To: %s\n", recipient);
    fprintf(log_file, "Subject: %s\n", subject);
    fprintf(log_file, "Body: %s\n\n", body);
    fclose(log_file);
}

int main() {
    const char *recipient = "nguyenthuhue.vku@gmail.com";
    const char *subject = "Test Email Notification by HieuNguyen";
    const char *body = "HieuNguyen test cronjob";

    send_email(recipient, subject, body);
    log_email(recipient, subject, body);
    return 0;
}
