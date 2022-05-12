--（1）授予表 对Student的SELECT、UPDATE、INSERT权限
grant SELECT,UPDATE,INSERT
on Student   -- 书上语句错误 不用+Table
to R1;
--with GRANT option;

--（2）创建用户R1
CREATE role R1;

