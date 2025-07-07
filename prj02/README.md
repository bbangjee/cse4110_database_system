# 편의점 데이터베이스 관리 시스템

C++과 MySQL을 이용한 편의점 체인 데이터베이스 관리 애플리케이션

## 📋 프로젝트 정보

- **개발자**: 20190808 방지혁
- **개발 기간**: 2025년 6월
- **과목**: CSE4110 Database Systems

## 🛠 개발 환경

- **OS**: Windows
- **컴파일러**: MinGW (g++)
- **데이터베이스**: MySQL 8.0+
- **연결 라이브러리**: MySQL Connector C 6.1

## 📚 사용 라이브러리

```cpp
#include <iostream>  // 표준 입출력
#include <string>    // 문자열 처리
#include <cstdio>    // C 스타일 입출력
#include <mysql.h>   // MySQL 연결
```

> ⚠️ **주의**: 기존 사이버캠퍼스 파일의 헤더 형태와 다름

## 🔧 컴파일 방법

```bash
g++ main.cpp -o main.exe -I"C:/Program Files/MySQL/MySQL Connector C 6.1/include" -L"C:/Program Files/MySQL/MySQL Connector C 6.1/lib" -lmysql
```

### 컴파일 옵션 설명
- `-I`: MySQL 헤더 파일 경로 지정
- `-L`: MySQL 라이브러리 경로 지정
- `-lmysql`: MySQL 라이브러리 링크

## 📁 파일 구조

```
prj02/
├── docs/
│   ├── logical_schema.png
│   ├── physical_schema.png
│   └── project_report.pdf
├── database/
│   ├── schema.sql
│   └── sample_data.sql
└── src/
    ├── main.cpp
    ├── libmysql.dll
    └── README.txt
README.md
```

## 🚀 실행 방법

1. **MySQL 서버 실행**
2. **데이터베이스 초기화**
   ```sql
   -- schema.sql 실행
   -- sample_data.sql 실행
   ```
3. **컴파일**
4. **프로그램 실행**
   ```bash
   ./main.exe  # libmysql.dll 필요
   ```

## 🔧 주요 문제 해결사항

### 1. SSL 연결 문제 해결

MySQL Connector C 6.1에서 SSL 연결 오류 발생으로 다음 코드 추가:

```cpp
mysql_ssl_mode sslmode = SSL_MODE_DISABLED;
if (mysql_options(conn, MYSQL_OPT_SSL_MODE, &sslmode))
{
    std::cerr << "mysql_options() failed: " << mysql_error(conn) << "\n";
    mysql_close(conn);
    return 1;
}
```

### 2. 인증 플러그인 문제 해결

**문제**: MySQL 8.0의 기본 인증 방식(`caching_sha2_password`)이 MySQL Connector C 6.1에서 지원되지 않음

**오류 메시지**:
```
Connection failure: Authentication plugin 'caching_sha2_password' cannot be loaded
```

**해결 방법**:
```sql
ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY '1234';
FLUSH PRIVILEGES;
```

### 3. 런타임 라이브러리 의존성

실행 시 `libmysql.dll`이 **필수**로 필요하므로 소스 파일과 같은 폴더에 배치

## ⚠️ 중요 사항

- MySQL Connector C 6.1과 MySQL 8.0 간의 호환성 문제로 인해 특별한 설정이 필요
- `libmysql.dll` 파일이 실행 파일과 같은 디렉토리에 있어야 함
- 인증 방식을 `mysql_native_password`로 변경해야 정상 작동

---

**CSE4110 Database Systems - Project 2**