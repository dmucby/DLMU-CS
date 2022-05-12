/*
（1） 查询所有学生的详细信息

（2） 查询1班的学生学号及姓名(某些列)

（3） 查询‘刘晨’的出生年（列表达式）

（4） 查询姓‘刘’的学生的详细情况

（5） 查询选修了1号课的学生姓名、性别、成绩

（10） 查询2班至少选修一门其先行课为1号课的学生的详细情况

（12） 查询1班2号课成绩最低的学生

（14） *查询至少选了1班2号同学所选课的所有同学(EXISTS\相关子查询)

（15） *查询不选1号课的学生(EXISTS)

（16） 查询1班平均分在85分以上的同学详细情况及各科成绩(GROUP)

（17） 查询选了1号课且选了2号课的学生的学号

（18） 查询选了1号课但不选2号课的学生的学号

（19） 查询选2号课的学生的名字及相应2号课成绩，按成绩排序(ORDER BY 连接)
*/


SELECT Student.*,SC.*
from Student,SC 
WHERE Student.Sno = SC.Sno;

SELECT Student.Sno,Sname
from Student,SC
WHERE SC.Sno = Student.Sno AND  
			SC.Sno ='2' AND grade > 90;

-- 查询先修课程
SELECT c1.cno, c2.Cpno
from Course c1,Course c2
WHERE c1.Cpno = c2.Cno;

-- 查询每个学生的学号、姓名、选秀的课程及成绩
SELECT S.Sno,S.sname,C.cname,grade
from Student s ,SC ,Course c 
WHERE s.Sno  = SC.sno and C.cno = SC.Cno 

--（6） 查询没有先行课的课程的课号和课名(NULL的使用)
SELECT c.cno,c.cname
from Course c 
WHERE c.Cpno IS  NULL ; -- 注意不是 = 而是 IS NULL

-- （7） 查询2班的所有女生的情况(AND OR)
-- （8） 查询学分为2到4之间的课程(Between and)
SELECT *
from Course c 
WHERE c.Ccredit BETWEEN 2 and 4;

-- （9） 查询选修1或2号课的学生的详细情况
--  有疑问
SELECT distinct s.*
from  Student s 
join SC s2 
on s.Sno = s2.Sno 
WHERE s2.cno = 1 or s2.cno = 2; 

SELECT distinct s.*
from  Student s ,SC s2 
WHERE s.Sno = s2.Sno AND 
				s2.cno = 1 or s2.cno = 2; 


-- （11） 查询2号科成绩最高的学生
SELECT distinct s.*
from  Student s 
join SC s2 
on s.Sno = s2.Sno 
WHERE  s2.grade =
( SELECT max(grade)
from SC
WHERE SC.Cno=2);

-- （13） 查询选修2号课且成绩不是最低的同学(ANY)



-- （20）查询至少选修了学生201215122选秀的全部课程的学生学号
SELECT DISTINCT Sno
FROM SC SCX
WHERE not EXISTS 
			(SELECT *
			FROM  SC SCY
			WHERE SCY.Sno = '201215122' and 
			NOT EXISTS 
			(		SELECT  * 
					FROM SC SCZ
					WHERE SCX.Sno = SCZ.Sno 
					AND SCY.Cno = SCZ.Cno 
			) 
			);

-- (21) 查询选修了全部课程的学生姓名
SELECT Sname
from Student s 
WHERE NOT EXISTS 
		(SELECT *
		FROM Course c 
		WHERE not EXISTS 
				(SELECT *
				FROM SC s2 
				WHERE s2.Sno = s.Sno 
				AND s2.Cno=c.Cno
				)
		);

	







