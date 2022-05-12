--CREATE View CompStud AS
--		(SELECT * FROM Student
--		WHERE D# in (SELECT D# from Dept
--									WHERE Dname='�����'));
									
--��1��������Ϣϵѧ������ͼ
CREATE view IS_Student
as 
select Sno,Sname,Sage
FROM Student
WHERE Sdept = 'IS';

--��2��������Ϣϵѧ������ͼ��
-- ��Ҫ������޸ĺͲ������ʱ����Ҫ��֤����ͼֻ��
-- ��Ϣϵ��ѧ��
CREATE view IS_Student 
as
select Sno,Sname,Sage
from Student
WHERE Sdept = 'IS'
WITH CHECK OPTIONS;
-- ����ͼ���в���ʱ���Զ����� WHERE Sdept = 'IS'

--��3��������Ϣϵѡ����1�ſγ̵�ѧ������ͼ������ѧ�ţ��������ɼ���
CREATE view IS_S1(Sno,Sname,Grade)
as 
Select s.Sno,s.Sname,s2.Grade
from Student s,SC s2
WHERE s.Sno = s2.Sno 
				AND Sdept = 'IS' 
				and s2.Cno ='1';
				
--��4��������Ϣϵѡ����1�ſγ�
-- �ҳɼ���90�����ϵ�ѧ������ͼ
-- IS_S2 ������ IS_S1 ��ͼ��
CREATE view IS_S2
AS
SELECT Sno,Sname,Grade
from IS_S1 
WHERE Grade >= 90;

-- ��5���������е���ͼ
-- ����һ����ӳѧ��������ݵ���ͼ
CREATE view BT_S(Sno,Sname,Sbirth)
as 
SELECT s.Sno,s.Sname,2014-s.Sage 
from Student s ;

-- ��6��������ͼ
-- ��ѧ����ѧ�ż�ƽ���ɼ�����Ϊһ����ͼ
CREATE view S_G(Sno,Gavg)
as 
SELECT Sno,AVG(Grade)
from SC
group by Sno;

--��7����ͼ���һһ��Ӧʱ����ṹ�ı䣬��ͼ�ͻ�ʧЧ
-- ��������Ů������ͼ
CREATE view F_Student(F_sno,name,sex,age,dept)
as 
select *
from Student
WHERE Ssex = 'Ů';

--��8��ɾ����ͼ
DROP view IS1_Student ;

-- ��9��ɾ��Ƕ����ͼʱ��Ҫʹ�ü���ɾ��
-- ע�����ϴ������
DROP view IS_S1 CASCADE;
-- ��ֱ��ɾ��IS_S1, ����������IS_S2 ʧЧ
DROP view IS_S1;

--  ��ѯ��ͼ
--  ��ͼ����(����ѯ��ͼת��Ϊ�Ա�Ĳ�ѯ)
-- ��10����ѯѡ����1�ſγ̵���Ϣϵ��ѧ��
SELECT IS_Student.Sno ,Sname
from IS_Student,SC
WHERE IS_Student.Sno = SC.Sno AND
				SC.Cno ='1';
			
--��11�������ͼ����ֱ��ת��ʱ
-- ��ѯƽ���ɼ���90�ϵ�ѧ��ѧ�ź�ƽ���ɼ�
SELECT Sno,AVG(Grade)
from SC
group by Sno 
HAVING AVG(Grade) >= 90; 
			
--��12�� ������ͼ
-- ����Ϣϵѧ����ͼ IS_Student�в���һ���µ�ѧ����¼��
-- ����ѧ��Ϊ'201215129'��'����',����'20'
-- IS δ������
INSERT 
into IS_Student 
values ('201215129','����',20);
-- ��ͼδ���£����Ǳ����

--��13��ɾ����Ϣϵѧ����ͼIS_Student��ѧ��Ϊ '201215129'�ļ�¼
DELETE 
FROM IS_Student 
WHERE Sno = '201215129';

--��14�����ɸ�����ͼ
-- ������ͼ���ɸ���
-- ����ͼ������ȥ�޸���ԭ���ĸ���ɼ�
UPDATE S_G 
set Gavg =90
WHERE Sno ='201215121';
			
-- ��15�����뷨���ͽ����
INSERT 
INTO IS_Student 
VALUES('201215278','����',21);
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			


