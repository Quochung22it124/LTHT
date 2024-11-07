#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void send_email(const char *recipient, const char *subject, const char *body) {
    FILE *mail_pipe = popen("/usr/bin/msmtp --read-envelope-from --read-recipients", "w");
    if (mail_pipe == NULL) {
        perror("Failed to open pipe for sending mail");
        return;
    }

    fprintf(mail_pipe, "From: hungfanchelsea@gmail.com\n");
    fprintf(mail_pipe, "To: %s\n", recipient);
    fprintf(mail_pipe, "Subject: %s\n", subject);
    fprintf(mail_pipe, "\n%s\n", body);

    if (pclose(mail_pipe) == -1) {
        perror("Failed to close pipe");
    }
}

void log_email(const char *recipient, const char *subject, const char *body) {
    FILE *log_file = fopen("/home/tranquochung090204/Downloads/demo/LTHT/output.txt", "a");
    if (log_file == NULL) {
        perror("Failed to open log file");
        return;
    }

    time_t current_time = time(NULL);
    char *time_str = ctime(&current_time);
    fprintf(log_file, "Time: %s", time_str);
    fprintf(log_file, "To: %s\n", recipient);
    fprintf(log_file, "Subject: %s\n", subject);
    fprintf(log_file, "Body: %s\n\n", body);
    fclose(log_file);
}

int main() {
    FILE *input_file = fopen("/home/tranquochung090204/Downloads/demo/LTHT/input.txt", "r");
    if (input_file == NULL) {
        perror("Failed to open input file");
        return 1;
    }

    char recipient[100], subject[100], body[500];
    char line[600];
    int has_email = 0, has_subject = 0, has_content = 0;

    while (fgets(line, sizeof(line), input_file)) {
        if (strncmp(line, "email:", 6) == 0) {
            sscanf(line + 6, "%s", recipient);
            has_email = 1;
        } else if (strncmp(line, "subject:", 8) == 0) {
            sscanf(line + 8, "%[^\n]", subject);
            has_subject = 1;
        } else if (strncmp(line, "content:", 8) == 0) {
            sscanf(line + 8, "%[^\n]", body);
            has_content = 1;
        }

        // Kiểm tra nếu đã có đủ thông tin để gửi email
        if (has_email && has_subject && has_content) {
            send_email(recipient, subject, body);
            log_email(recipient, subject, body);

            // Reset các biến để đọc thông tin email tiếp theo
            has_email = has_subject = has_content = 0;
        }
    }

    fclose(input_file);
    return 0;
}

