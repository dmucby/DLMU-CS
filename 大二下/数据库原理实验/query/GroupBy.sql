--（1）求不及格课程超过两门的同学的学号，姓名
 SELECT s1.Sno,s2.Sname
From SC s1 
join Student s2
on s1.Sno = s2.Sno 
WHERE S1.Grade < 60
GROUP by s2.Sname,s1 .Sno 
HAVING COUNT(*) > 2; 
-- 疑问
-- 查询的列和分组的列 需要一样？？？

--（2） 查询有10人以上不及格的课程号
SELECT Cno
from SC s 
WHERE s.Grade < 60
GROUP by Cno 
HAVING COUNT(*) > 10;

-- （3）查询选修了三门以上课程的学生学号
SELECT Sno
FROM SC s 
group by Sno 
HAVING COUNT(Cno) > 3; 

-- （4）查询平均成绩大于等于90分的学生学号和平均成绩
SELECT Sno,AVG(Grade)
from SC s 
group by Sno 
HAVING Avg(s.Grade) >= 90;