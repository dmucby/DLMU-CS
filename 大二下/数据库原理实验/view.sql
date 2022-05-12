--CREATE View CompStud AS
--		(SELECT * FROM Student
--		WHERE D# in (SELECT D# from Dept
--									WHERE Dname='计算机'));
									
--（1）建立信息系学生的视图
CREATE view IS_Student
as 
select Sno,Sname,Sage
FROM Student
WHERE Sdept = 'IS';

--（2）建立信息系学生的视图，
-- 并要求进行修改和插入操作时仍需要保证该视图只有
-- 信息系的学生
CREATE view IS_Student 
as
select Sno,Sname,Sage
from Student
WHERE Sdept = 'IS'
WITH CHECK OPTIONS;
-- 对视图进行操作时会自动加入 WHERE Sdept = 'IS'

--（3）建立信息系选修了1号课程的学生的视图（包括学号，姓名，成绩）
CREATE view IS_S1(Sno,Sname,Grade)
as 
Select s.Sno,s.Sname,s2.Grade
from Student s,SC s2
WHERE s.Sno = s2.Sno 
				AND Sdept = 'IS' 
				and s2.Cno ='1';
				
--（4）建立信息系选修了1号课程
-- 且成绩在90分以上的学生的视图
-- IS_S2 建立在 IS_S1 视图上
CREATE view IS_S2
AS
SELECT Sno,Sname,Grade
from IS_S1 
WHERE Grade >= 90;

-- （5）带虚拟列的视图
-- 定义一个反映学生出生年份的视图
CREATE view BT_S(Sno,Sname,Sbirth)
as 
SELECT s.Sno,s.Sname,2014-s.Sage 
from Student s ;

-- （6）分组视图
-- 将学生的学号及平均成绩定义为一个视图
CREATE view S_G(Sno,Gavg)
as 
SELECT Sno,AVG(Grade)
from SC
group by Sno;

--（7）视图与表一一对应时，表结构改变，视图就会失效
-- 建立所有女生的视图
CREATE view F_Student(F_sno,name,sex,age,dept)
as 
select *
from Student
WHERE Ssex = '女';

--（8）删除视图
DROP view IS1_Student ;

-- （9）删除嵌套视图时需要使用级联删除
-- 注意书上代码错误
DROP view IS_S1 CASCADE;
-- 可直接删除IS_S1, 但是依赖于IS_S2 失效
DROP view IS_S1;

--  查询视图
--  视图消解(将查询视图转换为对表的查询)
-- （10）查询选修了1号课程的信息系的学生
SELECT IS_Student.Sno ,Sname
from IS_Student,SC
WHERE IS_Student.Sno = SC.Sno AND
				SC.Cno ='1';
			
--（11）表和视图不能直接转换时
-- 查询平均成绩在90上的学生学号和平均成绩
SELECT Sno,AVG(Grade)
from SC
group by Sno 
HAVING AVG(Grade) >= 90; 
			
--（12） 更新视图
-- 向信息系学生视图 IS_Student中插入一个新的学生记录，
-- 其中学号为'201215129'，'赵新',年龄'20'
-- IS 未被插入
INSERT 
into IS_Student 
values ('201215129','赵新',20);
-- 视图未更新，但是表更新

--（13）删除信息系学生视图IS_Student中学号为 '201215129'的记录
DELETE 
FROM IS_Student 
WHERE Sno = '201215129';

--（14）不可更新视图
-- 派生视图不可更新
-- 该视图不可能去修改其原来的各项成绩
UPDATE S_G 
set Gavg =90
WHERE Sno ='201215121';
			
-- （15）插入法外狂徒张三
INSERT 
INTO IS_Student 
VALUES('201215278','张三',21);
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			


