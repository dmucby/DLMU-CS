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

-- ��ѯѡ���˿γ̵�ѧ��������
SELECT COUNT(DISTINCT Sno)
from SC;

SELECT AVG(Grade)
from SC
WHERE Cno = '1';

-- ������γ̺ż���Ӧ��ѡ������
SELECT Cno,COUNT(Sno)
from SC s Group by Cno;

-- ��ѯѡ�����������Ͽγ̵�ѧ��ѧ��
SELECT  Sno  FROM SC
Group by Sno;

SELECT Sno
from SC 
group by Sno
HAVING COUNT(*) > 3; 

-- ��ѯƽ���ɼ����ڵ���90�ֵ�ѧ��ѧ�ź�ƽ���ɼ�
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