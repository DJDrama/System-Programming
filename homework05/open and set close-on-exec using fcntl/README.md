## :camera_flash: Screenshots

[FD_CLOEXEC 없이 실행한 결과]
<img src="screenshot_no_fcntl.png" width="1024">
  
1. FD_CLOEXEC 없이 실행한 결과, ./exec_file을 통해 exec_file을 실행하였을 때. 
2. ps aux | grep exec_file 을 통해 현재 돌고 있는 프로세스 중 'exec_file'을 찾는다.
3. ll /proc/{pid}/fd 를 터미널에서 입력하면 fd '3'을 상속받은 것을 확인할 수 있다.


[FD_CLOEXEC 이용하여 실행한 결과]
<img src="screenshot_using_fcntl.png" width="1024">
  
1. FD_CLOEXEC 없이 실행한 결과, ./exec_file을 통해 exec_file을 실행하였을 때. 
2. ps aux | grep exec_file 을 통해 현재 돌고 있는 프로세스 중 'exec_file'을 찾는다.
3. ll /proc/{pid}/fd 를 터미널에서 입력하면 fd '3'이 없다.
