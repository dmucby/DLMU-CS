SELECT * FROM Student; 

SELECT * FROM  Student
WHERE Sage  >= 19;

SELECT *
from SC 
WHERE Cno = '3'
ORDER BY Grade ASC;

SELECT * 
FROM SC;

SELECT * 
FROM Student 
order by Sdept ASC,Sage desc;

SELECT COUNT(*)
from Student;

-- 查询选修了课程的学生的人数
SELECT COUNT(DISTINCT Sno)
from SC;

SELECT AVG(Grade)
from SC
WHERE Cno = '1';

-- 求各个课程号及相应的选课人数
SELECT Cno,COUNT(Sno)
from SC s Group by Cno;

-- 查询选修了三门以上课程的学生学号
SELECT  Sno  FROM SC
Group by Sno;

SELECT Sno
from SC 
group by Sno
HAVING COUNT(*) > 3; 

-- 查询平均成绩大于等于90分的学生学号和平均成绩
SELECT Sno,AVG(Grade)
from SC 
GROUP BY Sno 
HAVING AVG(Grade) >= 90; 

SELECT AVG(Grade)
from SC ;

SELECT *
from SC ;

SELECT Cno,
COUNT(*) as course_count 
from SC 
Group By Cno 
HAVING COUNT(*) >= 2; 