--��1��
-- BEGIN Transaction ֮�������
-- COMMIT OR ROLLBACK ��β
-- ��Ȼ����һֱ����û������

--��2��
-- ����Բ�ѯ���ûӰ��
-- ����ֻ�����ݿ����ɾ��Ӱ��

BEGIN TRANSACTION
	CREATE TABLE Student_nan
	(   Sno     bigint,
		Sname varchar(256),
		Sdept   varchar(256)
	);
	INSERT 
	into Student_nan(Sno,Sname,Sdept)
	select s.Sno, s.Sname ,s.Sdept 
	from Student s
	WHERE s.Ssex  = '��'
COMMIT;
	
ROLLBACK ;