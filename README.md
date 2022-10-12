# Calendar_TeamProject
A05팀 전공 기초 프로젝트

작업 목록
1. Calendar Class  
  1.1 달력 윤년 계산 - 완료  
  1.2 달력 요일 및 위치 계산 - 완료  
  1.3 달력 출력 - 완료/ 당직인원 기능이 추가되면 변경이 필요함  
  1.4 당직 인원 ID 출력 - 작업 필요  
  1.5 당직 스케쥴 파일 IO - 작업 필요  

2. NominalList Class  
  2.1 명부 출력 - 완료  
  2.2 명부 신규 인원 삽입 - 완료  
  2.3 명부 탐색 - 완료  
  2.4 명부 인원 삭제 - 완료  
  2.5 명부 저장 파일 IO (삽입, 삭제, 프로그램 완전종료시 자동 저장, 종료시 저장는 메뉴에서 FileOutput함수 실행해주세요.)   
      2.5.1 저장파일 양식  
         202209 (작업중인 달이 있으면 해당 달,  없으면 -1로 저장 )  
         시작달 이름 ID  
         시작달 이름 ID  
      
      2.5.2 비정상 파일 거르기 조건
        1. 시작달 (-1 혹은 길이가 6이 아님)  
        2. 인원 시작달(길이가 6이 아님)  
        3. 이름, 아이디 안거름(좋은 방안이 생각나시면 알려주세용)  
        ->비정상 파일일시 함수가 false를 리턴하고 종료됩니다. 메뉴 처음 실행시 FileInput한번 실행해주세요.  
        
    2.6 명부 정렬 - 시작달 기준 오름차순(선임부터) 순서대로 정렬됩니다.  
    
    사용 IDE : 비주얼 스튜디오 2019 버전 16.11
