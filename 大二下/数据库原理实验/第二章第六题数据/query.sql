--(1)�ҳ����й�Ӧ�̵����������ڳ��С�
SELECT S.SNAME ,S.CITY 
FROM S;

--(2)�ҳ�������������ơ���ɫ��������
SELECT P.PNAME ,P.COLOR ,P.WEIGHT 
FROM P;

--(3)�ҳ�ʹ�ù�Ӧ��S1����Ӧ����Ĺ��̺��롣
SELECT SPJ.JNO
FROM SPJ 
WHERE SPJ.SNO = 'S1';

--(4)�ҳ�������ĿJ2ʹ�õĸ�����������Ƽ���������
SELECT DISTINCT  P.PNAME ,SPJ.QTY 
FROM SPJ,P
WHERE SPJ.JNO = 'J2' 
AND P.PNO = SPJ.PNO;

SELECT DISTINCT P.PNAME ,SPJ.QTY 
FROM SPJ
JOIN P
ON P.PNO = SPJ.PNO 
WHERE SPJ.JNO = 'J2';

--(5)�ҳ��Ϻ����̹�Ӧ������������롣
SELECT DISTINCT  SPJ.PNO 
FROM S 
JOIN SPJ
ON SPJ.SNO = S.SNO 
WHERE S.CITY ='�Ϻ�';

--(6)�ҳ�ʹ���Ϻ���������Ĺ������ơ�
SELECT J.JNAME
FROM J 
WHERE J.JNO IN (
		SELECT DISTINCT  SPJ.JNO 
		FROM S 
		JOIN SPJ
		ON SPJ.SNO = S.SNO 
		WHERE S.CITY ='�Ϻ�'
);


--(7)�ҳ�û��ʹ������������Ĺ��̺��롣
SELECT J.JNAME,j.JNO 
FROM J 
WHERE J.JNO not IN (
		SELECT DISTINCT  SPJ.JNO 
		FROM S 
		JOIN SPJ
		ON SPJ.SNO = S.SNO 
		WHERE S.CITY ='���'
);


--(8)��ȫ����ɫ�������ɫ�ĳ���ɫ��
UPDATE P
SET P.COLOR = '��'
WHERE P.COLOR  = '��';

--(9)��S5����J4�����P6��Ϊ��S3��Ӧ��
UPDATE SPJ 
SET SPJ.SNO = 'S3'
WHERE SPJ.SNO = 'S5'
AND SPJ.JNO = 'J4'
AND PNO = 'P4';

--(10)�ӹ�Ӧ�̹�ϵ��ɾ����Ӧ�̺���S2�ļ�¼�����ӹ�Ӧ�����ϵ��ɾ����Ӧ�ļ�¼��
DELETE 
FROM S  -- ע�����FROM
WHERE S.SNO = 'S2';

DELETE 
FROM SPJ 
WHERE SPJ.SNO ='S2';

--(11)�뽫(S2��J6��P4��200)���빩Ӧ�����ϵ��
INSERT 
INTO SPJ
VALUES 
('S2','J6','P4',200);

SELECT SPJ.SNO
FROM SPJ 
WHERE SPJ.SNO ='S2'
AND SPJ.JNO = 'J6';





