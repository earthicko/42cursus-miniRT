- `builder` 디렉토리에 `build_.*c` 파일 생성
  - `is_*` 이름을 가진 패턴 매칭 함수 구현
  - `build_*` 이름을 가진 빌더 함수 구현
- `parser_internal.h`에 정보 추가
  - `N_IDENTIFIER_*` 개수 수정
  - `IDENTIFIER_*` 정의 추가
- `builder_internal.h`에 정보 추가
  - `is_*` 패턴매칭함수 프로토타입 추가
  - `build_*` 빌더 프로토타입 추가
- `managers*.c`에 정보 추가
  - `tokenname_manager`에 `IDENTIFIER_*` 추가
  - `*_patternmatcher_manager`에 함수의 포인터 추가
  - `*_builder_manager`에 함수의 포인터 추가
  - `parser_internal.h`에 선언된 순서와 일치해야 함
- `Makefile`에 필요한 파일 추가
