--��1���󲻼���γ̳������ŵ�ͬѧ��ѧ�ţ�����
 SELECT s1.Sno,s2.Sname
From SC s1 
join Student s2
on s1.Sno = s2.Sno 
WHERE S1.Grade < 60
GROUP by s2.Sname,s1 .Sno 
HAVING COUNT(*) > 2; 
-- ����
-- ��ѯ���кͷ������ ��Ҫһ��������

--��2�� ��ѯ��10�����ϲ�����Ŀγ̺�
SELECT Cno
from SC s 
WHERE s.Grade < 60
GROUP by Cno 
HAVING COUNT(*) > 10;

-- ��3����ѯѡ�����������Ͽγ̵�ѧ��ѧ��
SELECT Sno
FROM SC s 
group by Sno 
HAVING COUNT(Cno) > 3; 

-- ��4����ѯƽ���ɼ����ڵ���90�ֵ�ѧ��ѧ�ź�ƽ���ɼ�
SELECT Sno,AVG(Grade)
from SC s 
group by Sno 
HAVING Avg(s.Grade) >= 90;