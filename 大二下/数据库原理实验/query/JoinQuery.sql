/*
��1�� ��ѯ����ѧ������ϸ��Ϣ

��2�� ��ѯ1���ѧ��ѧ�ż�����(ĳЩ��)

��3�� ��ѯ���������ĳ����꣨�б��ʽ��

��4�� ��ѯ�ա�������ѧ������ϸ���

��5�� ��ѯѡ����1�ſε�ѧ���������Ա𡢳ɼ�

��10�� ��ѯ2������ѡ��һ�������п�Ϊ1�ſε�ѧ������ϸ���

��12�� ��ѯ1��2�ſγɼ���͵�ѧ��

��14�� *��ѯ����ѡ��1��2��ͬѧ��ѡ�ε�����ͬѧ(EXISTS\����Ӳ�ѯ)

��15�� *��ѯ��ѡ1�ſε�ѧ��(EXISTS)

��16�� ��ѯ1��ƽ������85�����ϵ�ͬѧ��ϸ��������Ƴɼ�(GROUP)

��17�� ��ѯѡ��1�ſ���ѡ��2�ſε�ѧ����ѧ��

��18�� ��ѯѡ��1�ſε���ѡ2�ſε�ѧ����ѧ��

��19�� ��ѯѡ2�ſε�ѧ�������ּ���Ӧ2�ſγɼ������ɼ�����(ORDER BY ����)
*/


SELECT Student.*,SC.*
from Student,SC 
WHERE Student.Sno = SC.Sno;

SELECT Student.Sno,Sname
from Student,SC
WHERE SC.Sno = Student.Sno AND  
			SC.Sno ='2' AND grade > 90;

-- ��ѯ���޿γ�
SELECT c1.cno, c2.Cpno
from Course c1,Course c2
WHERE c1.Cpno = c2.Cno;

-- ��ѯÿ��ѧ����ѧ�š�������ѡ��Ŀγ̼��ɼ�
SELECT S.Sno,S.sname,C.cname,grade
from Student s ,SC ,Course c 
WHERE s.Sno  = SC.sno and C.cno = SC.Cno 

--��6�� ��ѯû�����пεĿγ̵ĿκźͿ���(NULL��ʹ��)
SELECT c.cno,c.cname
from Course c 
WHERE c.Cpno IS  NULL ; -- ע�ⲻ�� = ���� IS NULL

-- ��7�� ��ѯ2�������Ů�������(AND OR)
-- ��8�� ��ѯѧ��Ϊ2��4֮��Ŀγ�(Between and)
SELECT *
from Course c 
WHERE c.Ccredit BETWEEN 2 and 4;

-- ��9�� ��ѯѡ��1��2�ſε�ѧ������ϸ���
--  ������
SELECT distinct s.*
from  Student s 
join SC s2 
on s.Sno = s2.Sno 
WHERE s2.cno = 1 or s2.cno = 2; 

SELECT distinct s.*
from  Student s ,SC s2 
WHERE s.Sno = s2.Sno AND 
				s2.cno = 1 or s2.cno = 2; 


-- ��11�� ��ѯ2�ſƳɼ���ߵ�ѧ��
SELECT distinct s.*
from  Student s 
join SC s2 
on s.Sno = s2.Sno 
WHERE  s2.grade =
( SELECT max(grade)
from SC
WHERE SC.Cno=2);

-- ��13�� ��ѯѡ��2�ſ��ҳɼ�������͵�ͬѧ(ANY)



-- ��20����ѯ����ѡ����ѧ��201215122ѡ���ȫ���γ̵�ѧ��ѧ��
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

-- (21) ��ѯѡ����ȫ���γ̵�ѧ������
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

	







