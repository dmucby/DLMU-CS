--��1����ѧ��002�ſγ̵�ͬѧ��ѧ��003�ſγ̵�ͬѧѧ��
SELECT s.Sno,s2.Sname 
from SC s 
join Student s2 ON s.Sno  = s2.Sno 
WHERE s.Cno = '2'
UNION 
SELECT s.Sno,s2.Sname 
from SC s 
join Student s2 ON s.Sno  = s2.Sno 
WHERE s.Cno ='3';

--��д
SELECT DISTINCT s.Sno,  s2.Sname
from SC s,Student s2,SC s3 
WHERE s.Cno ='2' AND s3.Cno ='3'
AND s.Sno  = s2.Sno ;