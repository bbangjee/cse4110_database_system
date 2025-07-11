# CSE4110 Database System

서강대학교 CSE4110 데이터베이스 시스템 수업 프로젝트

## 📚 프로젝트 개요

편의점 체인 관리를 위한 데이터베이스 시스템 설계 및 구현

### 🎯 주요 목표
- 편의점 운영에 필요한 데이터베이스 설계
- 효율적인 재고 관리 및 판매 분석
- 고객 로열티 프로그램 관리
- 실제 운영 가능한 시스템 구현

## 📁 프로젝트 구조

```
cse4110_database_system/
├── prj01/                    # Project 1: E-R 다이어그램 설계
│   └── 20190808_방지혁.pdf   # ERD 설계 보고서
|   └── 20190808_방지혁.png   # ER Diagram
├── prj02/                    # Project 2: 데이터베이스 구현
│   ├── docs/                 # 설계 문서
│   ├── database/             # SQL 스크립트
│   ├── src/                  # C++ 소스코드
│   └── README.md             # 구현 가이드
├── notes/                    # 필기 노트 폴더
│   └── ch02_공부.pdf         # ch02 공부
│   └── ch03_공부.pdf         # ch03 공부
│   └── ch06_공부.pdf         # ch06 공부
│   └── ch07_공부.pdf         # ch07 공부
└── README.md                 # 이 파일
```

## 🗂 프로젝트 상세

### 📊 Project 1: 개념적 데이터베이스 설계
- **기간**: 2025년 4월
- **내용**: E-R 다이어그램 설계 및 요구사항 분석
- **결과물**: 
  - 편의점 관리 시스템 ERD
  - 엔티티 및 관계 설명
  - 샘플 쿼리 커버리지 분석

**주요 엔티티**:
- Customer (고객)
- Store (매장)
- Product (상품)
- Vendor (공급업체)
- Sales_Transaction (판매거래)
- Inventory (재고)

### 💻 Project 2: 물리적 데이터베이스 구현
- **기간**: 2025년 6월
- **내용**: MySQL 데이터베이스 구현 및 C++ 애플리케이션 개발
- **기술스택**: 
  - MySQL 8.0+
  - C++ with MySQL Connector C
  - MinGW 컴파일러

**주요 기능**:
- 재고 관리 및 알림
- 판매 분석 및 통계
- 고객 로열티 관리
- 공급업체 관리

## 🔍 주요 쿼리 기능

1. **재고 관리**: 특정 제품의 매장별 재고량 조회
2. **판매 분석**: 매장별 최고 판매 상품 분석
3. **매출 통계**: 분기별 매장 매출 순위
4. **공급업체 분석**: 벤더별 제품 공급 현황
5. **재주문 알림**: 재주문 임계값 이하 상품 조회
6. **고객 분석**: 로열티 고객 구매 패턴 분석
7. **매장 비교**: 프랜차이즈 vs 직영점 상품 다양성

## 🛠 시스템 요구사항

- **OS**: Windows 10+
- **Database**: MySQL 8.0+
- **Compiler**: MinGW (GCC)
- **Library**: MySQL Connector C 6.1

## 📈 학습 성과

- 실무 중심의 데이터베이스 설계 경험
- 정규화 및 최적화 기법 적용
- C++과 MySQL 연동 프로그래밍
- 대용량 데이터 처리 및 쿼리 최적화

---

**서강대학교 컴퓨터공학과**  
**CSE4110 Database Systems - 2025 Spring**
