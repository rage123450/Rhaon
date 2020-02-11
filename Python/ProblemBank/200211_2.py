# 021
lang = "python"
print(lang[0] + ' ' + lang[2])

# 022
license_plate = "24가 2210"
#print(license_plate[4:9])
#print(license_plate[-4:])
print(license_plate[4:])

# 023
string = "홀짝홀짝홀짝"
#print(string[0] + string[2] + string[4])
print(string[0::2])     # 인덱스 시작:0, 인덱스 증감폭:2
print(string[1::2])     # 인덱스 시작:1, 인덱스 증감폭:2

# 024
string = "PYTHON"
print(string[::-1])

# 025
phone_number = "010-1111-2222"
print(phone_number.replace('-',' ',2))

# 026
print(phone_number.replace('-','',2))

# 027
url = "http://sharebook.kr"
#print(url[17:19])
print(url[-2::])

# 028
lang = 'python'
# 기존에 생성한 문자열은 변경 할 수 없습니다.
#lang[0] = 'P'
print(lang)

# 029
string = 'abcdfe2a354a32a'
print(string.replace('a','A',1))

# 030
string = 'abcd'
string.replace('b', 'B')
print(string)