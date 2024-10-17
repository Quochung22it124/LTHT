```bash
sudo apt-get update
sudo apt-get install msmtp msmtp-mta
```

```
defaults
auth           on
tls            on
tls_trust_file /etc/ssl/certs/ca-certificates.crt
logfile        ~/.msmtp.log
account        gmail
host           smtp.gmail.com
port           587
from           your_email@gmail.com
user           your_email@gmail.com
password       your_password
account default : gmail
```


```
chmod 600 ~/.msmtprc
```
```
gcc send_mail.c -o send_mail
```
```
crontab -e

*/5 * * * * /home/hieunguyen/Personal/LTHT/send_mail
```
