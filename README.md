# Games101 作业环境一键部署 (Windows)
基于 Visual Studio 2026、CMake(安装vs2026时把CMake选上)和vcpkg。<br>
一、安装vcpkg，并配置环境变量。<br>
  （1）安装vcpkg<br>
  ```
  git clone https://github.com/Microsoft/vcpkg.git
  cd vcpkg
  bootstrap-vcpkg.bat
  ```
  <img width="800" height="600" alt="9861b19b-f592-4870-a72d-4e8f5d717bfe" src="https://github.com/user-attachments/assets/776eb502-b0ae-48a2-b98d-915c5da6ce7e" /><br>
（2）配置环境变量<br>
  <img width="584" height="262" alt="df1e58f9-e02c-4a66-98f4-0272b13eda16" src="https://github.com/user-attachments/assets/6b69e05a-e7d8-46c2-a58a-353f5872497f" /><br>


二、拉取仓库代码，使用vs2026打开Games101文件夹<br>
（1）拉取代码<br>
<img width="800" height="600" alt="d151edb1-c2da-4859-a057-755a8986ae32" src="https://github.com/user-attachments/assets/179e1069-7d9b-46ea-bee9-f0655af36486" /><br>
（2）使用vs2026打开Games101文件夹，vs2026需要把cmake安装了<br>
<img width="890" height="575" alt="5e0881ca-d48b-4065-a227-16850b73660e" src="https://github.com/user-attachments/assets/b1cb96b8-b307-4958-be5c-a897bb887315" /><br>
（3）等待分析，时间很长<br>
可以随意切换文件夹视图或者Cmake目标视图<br>
<img width="351" height="480" alt="08cd7b21-f4de-435a-b0c5-a97ff27372bf" src="https://github.com/user-attachments/assets/747a3476-42f4-42f7-982d-4dd3e3ffb3e1" /><br>
<img width="355" height="150" alt="b2ce8f1c-5217-404e-8b02-af917fa9b1d4" src="https://github.com/user-attachments/assets/1cc4060b-16ad-4dae-88ec-8cefc378a6ba" /><br>

三、运行对应课时的实验<br>
（1）把自己要写的实验设为启动项<br>
<img width="354" height="641" alt="b2648111-fadd-4b57-9289-7cd7b8885450" src="https://github.com/user-attachments/assets/779e1ccc-942f-4be5-92a1-9d8317e1b0ad" /><br>
（2）在调试->调试和AssignmentX的设置 这里配置运行时的参数<br>
<img width="488" height="466" alt="3b05a538-7818-404c-bbb6-cd081d21d0b0" src="https://github.com/user-attachments/assets/d99376ee-428b-429e-bccc-b6c87058d9a1" /><br>
<img width="800" height="600" alt="0bf47bf3-615a-4f13-94a8-dd551fd62e74" src="https://github.com/user-attachments/assets/d959b31a-4c68-4bd3-a677-df06bbf14880" /><br>
输出在 Games101\out\build\x64-Debug\Assignment1 文件夹里。<br>
写作业7的时候记得把这换成release，速度快很多<br>
<img width="715" height="266" alt="3dc3bb9e-c3d1-48d9-8fd3-e915bf244e95" src="https://github.com/user-attachments/assets/4b9083b4-58fa-4a90-a44e-3afb29d3e753" /><br>
输出也会改为Games101\out\build\x64-Release\Assignment7<br>


