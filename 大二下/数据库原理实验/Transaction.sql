--（1）
-- BEGIN Transaction 之后必须以
-- COMMIT OR ROLLBACK 结尾
-- 不然事务一直开启没背结束

--（2）
-- 事务对查询语句没影响
-- 事务只对数据库的增删改影响

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
	WHERE s.Ssex  = '男'
COMMIT;
	
ROLLBACK ;