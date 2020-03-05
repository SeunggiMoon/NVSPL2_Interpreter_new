<img src="https://blogfiles.pstatic.net/MjAyMDAzMDVfMTUg/MDAxNTgzMzk1MDM0ODIx.T5Mor8GQZVeT-Njj4rhsrKhANNRN1V4S8yXk6zw6UQQg.I0zmy6cp95au_9STrCCi2H8F6vkzsAxT7A9ZihmKo1kg.PNG.moon44432/nvspl2logo2.png?type=w1" alt="NVSPL2 Logo"></img><br/>

# NVSPL2 프로젝트

## 찾아보기
[1. NVSPL2 언어](#language)   
[2. NVSPL2 인터프리터](#interpreter)   
└ [2-3. 사용법](#usage)   
[3. 기타 서드 파티 인터프리터, 컴파일러 및 개발 환경](#third-party)   
[4. 도움을 주신 분들](#contributors)   

<a name="language"/>

## 1. NVSPL2 언어

### 1-1. 개요
적은 명령어로도 프로그래밍을 할 수 있게 만들어진 스크립트 언어이자, 난해한 프로그래밍 언어의 일종입니다.   
현재 표준 v1, v2(NVSPL2-15)를 거쳐 표준 v3(NVSPL2-20)까지 제정되어 있습니다.   
아래의 설명은 표준 v3을 따릅니다.   

### 1-2. 특징
* 간단한 숫자, 문자 출력부터, 구구단 또는 더 복잡한 프로그램까지도 작성할 수 있습니다.   
* 난해한 프로그래밍 언어의 특성 상, 프로그램을 작성하는 데에는 정신력이 많이 필요합니다.
* 모든 명령어들이 하나의 문자로 이루어져 있으며, 대소문자를 구분하지 않습니다.   
* 공백, 개행 등 명령어가 아닌 문자는 실행에 영향을 주지 않습니다. 따라서 어떠한 스타일로도 코드를 작성할 수 있습니다.

### 1-3. 저장 공간
내부적으로 1024개의 실수로 이루어진 배열을 사용합니다.   
옮길 수 있는 인덱스가 존재하며, 인덱스의 기본값은 `0`입니다.   
인덱스의 최솟값은 `0`, 최댓값은 `1023`입니다.   

### 1-4. 명령어
>아래의 설명은 대문자 기준으로 작성되었지만, 소문자 명령어도 사용이 가능합니다.   
#### 1-4-1. F
배열 인덱스를 `1` 증가시킵니다.
#### 1-4-2. B
배열 인덱스를 `1` 감소시킵니다.
#### 1-4-3. +
배열 인덱스가 가리키는 요소의 값을 `1` 증가시킵니다.
#### 1-4-4. -
배열 인덱스가 가리키는 요소의 값을 `1` 감소시킵니다.
#### 1-4-5. ,
배열 인덱스가 가리키는 요소의 값을 임의의 실수만큼 증가 또는 감소시킵니다.   
예를 들어, `,1` 또는 `,1.0`은 요소의 값을 `1` 증가시킵니다.   
`,-1` 또는 `,-1.0`은 요소의 값을 `1` 감소시킵니다.   
이 때, 마이너스 부호가 명령어로서 다시 인식되지는 않습니다.   
#### 1-4-6. I
배열 인덱스가 가리키는 요소 값의 정수부를 출력합니다.
#### 1-4-7. C
배열 인덱스가 가리키는 요소 값의 정수부를 ASCII 문자로 출력합니다.
#### 1-4-8. R
배열 인덱스가 가리키는 요소 값을 소숫점이 있는 실수 형태로 출력합니다.
#### 1-4-9. S
1칸의 공백 (` `)을 출력합니다.
#### 1-4-10. E
개행합니다. (`\n` 출력과 동일한 기능)
#### 1-4-11. O (알파벳)
배열 인덱스가 가리키는 요소 값을 `0`으로 설정합니다.
#### 1-4-12. :
루프의 시작 지점을 나타냅니다.
#### 1-4-13. ;
배열 인덱스가 가리키는 요소 값이 0이 아니면, 짝이 맞는 `:`로 돌아갑니다.
#### 1-4-14. Q
프로그램을 종료합니다.
#### 1-4-15. &#35;
`#`부터 그 줄 끝까지를 모두 주석으로 처리하게 합니다.

### 1-5. 예제
#### 1-5-1. Hello World!
`,72CO,101CO,108CO,108CO,111COS,119CO,111CO,114CO,108CO,100CO,33CQ`   
`Hello World!`를 출력하는 프로그램입니다.

#### 1-5-2. 1~10 출력하기
`F,10:B+ISF-; Q`   
`1 2 3 4 5 6 7 8 9 10 `을 출력하는 프로그램입니다.

#### 1-5-3. 곱하기 구현하기
```
,5
:
F,3
B-
;
FI
Q
```   
3을 더하는 작업을 5번 수행하여 3 * 5를 계산합니다.   
`15`를 출력합니다.

#### 1-5-4. 구구단 출력하기
```
# variables
# 0 1 2 3 4 5 6 7 8
# x i y j X Y a b c
 
# x = 2, i = 8
# for x=2 to 9, i=8 to 0
,2F,8:
 
 # y = 2, j = 8
 # for x=2 to 9, j=8 to 0
 F,1F,9:
 
  BBB             # point to x
  :-FFFF+F+BBBBB; # x ->+ X, Y
  FFFFF           # point to Y
  :-BBBBB+FFFFF;  # Y ->+ x
 
  BBB                 # point to y
  :-FFF+F+F+F+BBBBBB; # y ->+ Y, a, b, c
  FFFFFF              # point to c
  :-BBBBBB+FFFFFF;    # c ->+ y
 
  # while ( --X != 0 )
  BBBB-
  :
   FF                 # point to a
   :-F+B;             # a ->+ b
 
   B                  # point to Y
   :-F+FF+BBB;        # Y ->+ a, c
   FFF                # point to c
   :-BBB+FFF;         # c ->+ Y
 
  # end while
  BBBB-;
 
  # now b = x * y
 
  BBBB IS FFFFF IS FF IE  # output x, y, b
  OB OB OB OB             # clear X, Y, a, b
 
 # end for
 B+F-;B
 OB
 
# end for
B+F-;
 
# quit
Q
```   
구구단을 출력합니다.   
`2 1 2` 부터 `9 9 81`까지 출력합니다.

<a name="interpreter"/>

## 2. NVSPL2 인터프리터

### 2-1. 개요
Naissoft가 직접 개발하는 공식 인터프리터입니다.   
표준 v3을 완전히 지원하며, 가볍고 사용하기 쉽습니다.

### 2-2. 구조 및 작동 과정
1. __전처리 및 중간 코드 생성__ : 원본 소스 파일을 불러와 공백, 개행, 주석을 제거합니다. 중간 코드를 담는 명령어 배열을 생성하고, 남은 명령어와 숫자들을 명령어 배열에 삽입합니다. 숫자도 문자로 변환되어 삽입됩니다.   
2. __코드 실행__ : 명령어 배열의 인덱스를 옮겨 가며 명령어를 하나씩 실행합니다.   
숫자를 입력받을 때에는 명령어 배열의 일부를 새로운 문자열로 만든 후 그곳에서 숫자를 추출합니다.   
2-1. __다중 반복문 처리__ : 내부적으로 depth를 표현하는 두 개의 변수(`depth`, `cdepth`)를 사용합니다.   
`depth`는 실행해야 하는 반복문의 깊이를 나타냅니다.   
`cdepth` Current depth를 의미하며, 명령어 배열의 인덱스가 위치한 곳의 반복문 깊이를 나타냅니다.   

<a name="usage"/>

### 2-3. 사용법

#### 2-3-1. 소스 코드 작성하기
어떠한 텍스트 에디터로도 NVSPL2 코드를 작성할 수 있습니다.    
코드를 작성했다면 `*.nvs` 파일로 저장하세요.   

#### 2-3-2. 작성한 코드 실행하기
>NVSPL2 인터프리터는 기본적으로 `nvspl2.exe`라는 이름으로 제공됩니다. 아래의 설명은 이를 기준으로 작성되었습니다.   

NVSPL2 인터프리터가 위치한 디렉토리에서 명령 프롬프트를 열고   
`nvspl2 <소스 파일 디렉토리>\<소스 파일명>.nvs` 를 입력하세요.   

##### 2-3-2-1. 인터프리터 실행 시 에러
1. 필요한 정보를 모두 입력하지 않았을 시   
`usage : nvspl2 <filename> <options...>` 가 출력됩니다.   
2. 소스 파일명을 잘못 입력했을 경우   
`error : wrong filename` 가 출력됩니다.
   
정상적으로 실행되면, 코드를 모두 실행한 후   
`Execution finished with return value n (x.xxxs)` 와 같이 반환 값과 코드 실행 시간이 표시됩니다.   

##### 2-3-2-2. 인터프리터의 반환 값
에러의 유무 및 종류에 따라 반환 값이 달라집니다.   
1. `0` : 프로그램이 정상적으로 종료되었습니다.   
2. `1` : 명령어가 성공적으로 실행되었습니다. _(인터프리터 내부적으로 사용되는 반환 값으로, 출력되지 않습니다.)_   
3. `-1` : 배열 인덱스가 최댓값을 초과했습니다.   
4. `-2` : 배열 인덱스가 0보다 작습니다.   

#### 2-3-3. 인터프리터 옵션
>현재 구현 중인 기능입니다. 빠른 시일 내에 완료할 예정입니다.

`nvspl2 test.nvs -l -p` 와 같이 여러 개의 옵션을 순서에 상관없이 소스 파일명 뒤에 표시할 수 있습니다.   

<a name="third-party"/>

## 3. 기타 서드 파티 인터프리터, 컴파일러 및 개발 환경

<a name="contributors"/>

## 4. 도움을 주신 분들
