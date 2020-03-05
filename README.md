<img src="https://blogfiles.pstatic.net/MjAyMDAzMDVfMTUg/MDAxNTgzMzk1MDM0ODIx.T5Mor8GQZVeT-Njj4rhsrKhANNRN1V4S8yXk6zw6UQQg.I0zmy6cp95au_9STrCCi2H8F6vkzsAxT7A9ZihmKo1kg.PNG.moon44432/nvspl2logo2.png?type=w1" alt="NVSPL2 Logo"></img><br/>

# NVSPL2 프로젝트
## 1. NVSPL2 언어
### 1-1. 개요
적은 명령어로도 프로그래밍을 할 수 있게 만들어진 스크립트 언어이자, 난해한 프로그래밍 언어의 일종입니다.   
현재 표준 v1, v2(NVSPL2-15)를 거쳐 표준 v3(NVSPL2-20)까지 제정되어 있습니다.   
아래의 설명은 표준 v3을 따릅니다.   
### 1-2. 특징
* 간단한 숫자, 문자 출력부터, 구구단 또는 더 복잡한 프로그램까지도 작성할 수 있습니다.   
* 모든 명령어들이 하나의 문자로 이루어져 있으며, 대소문자를 구분하지 않습니다.   
* 공백, 개행은 실행에 영향을 주지 않습니다. 따라서 어떠한 스타일로도 코드를 작성할 수 있습니다.
### 1-3. 저장 공간
내부적으로 1024개의 실수로 이루어진 배열을 사용합니다.   
옮길 수 있는 인덱스가 존재하며, 인덱스의 기본값은 `0`입니다.   
인덱스의 최솟값은 `0`, 최댓값은 `1023`입니다.   
### 1-4. 명령어
#### 1-4-1. F
배열 인덱스를 1 증가시킵니다.
#### 1-4-2. B
배열 인덱스를 1 감소시킵니다.
