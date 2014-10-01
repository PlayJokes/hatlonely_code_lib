import smtplib
from email.mime.text import MIMEText

mailto_list = ['hatlonely@foxmail.com']
mail_host = 'smtp.163.com'
mail_user = 'love_sweety'
mail_postfix = '163.com'
mail_passwd = 'xxxxxxxx'

def send_mail(to_list, sub, content):
    me = mail_user + '<' + mail_user + '@' + mail_postfix + '>'
    msg = MIMEText(content, _subtype='plain', _charset='gb2312')
    msg['Subject'] = sub
    msg['From'] = me
    msg['To'] = ';'.join(to_list)
    try:
        server = smtplib.SMTP()
        server.connect(mail_host)
        server.login(mail_user, mail_passwd)
        server.sendmail(me, to_list, msg.as_string())
        server.close()
        return True
    except Exception, e:
        print e
        return False

def main():
    if send_mail(mailto_list, 'hello', 'hello world!'):
        print 'send success'
    else:
        print 'send fail'
    
if __name__ == '__main__':
    main()
