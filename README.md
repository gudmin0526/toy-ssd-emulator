**SSD Emulator**

SSD HW 에뮬레이션과 이를 제어/테스트하는 Shell을 병렬로 개발한다.

---

**1. Branch Strategy**

**Main Branches**

```
main    : 최종 통합 브랜치
ssd     : SSD 에뮬레이션 통합 브랜치
shell   : 테스트/제어 Shell 통합 브랜치
```

**Feature Branches**

```
ssd-f/<feature>
shell-f/<feature>
```

예시:

- `ssd-f/nand-write`
- `shell-f/io-generator`

---

**2. Development Flow**

1. 기능 개발은 반드시 feature 브랜치에서 시작
- `ssd-f/<feature>`
- `shell-f/<feature>`
1. Feature 브랜치는 해당 SW 브랜치로 PR
- `ssd-f/* → ssd-main`
- `shell-f/* → shell-main`
1. 작업 종료 시점에 ssd, shell을 main으로 통합 main 브랜치에 직접 push는 금지

---

**3. Coding Convention**

- 변수 / 함수 이름: `snake_case`
- 중괄호 스타일: K&R

```
if (cond) {
    ...
}
```

- 들여쓰기: 한 가지 방식만 사용 (예: space 4칸)
- 복잡한 로직에는 한 줄 설명 주석 추가

---

**4. Commit Guideline**

- 확실한 변화 하나당 커밋 1개
- 커밋 전 최소 확인:
    - 컴파일 또는 실행 가능 여부 확인
- 커밋 메시지 형식은 자유 (단, 어떤 변화인지 알 수 있게 작성)

---

**5. Roles**

**SSD H/W**

- 김형민
- 김재동
- 김태곤

**Test Shell**

- 김민교
- 장혜나