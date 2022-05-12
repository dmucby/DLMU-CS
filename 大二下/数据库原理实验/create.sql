create table Student
(
    Sno   bigint       not null,
    Sname varchar(256) not null,
    Ssex  varchar(10)      null ,
    Sage  int          null ,
    Sdept varchar(256) null ,
    primary key(Sno),
);

INSERT INTO university.dbo.Student
(Sno, Sname, Ssex, Sage, Sdept)
VALUES(201215121, N'����', N'��', 20, N'CS');
INSERT INTO university.dbo.Student
(Sno, Sname, Ssex, Sage, Sdept)
VALUES(201215122, N'����', N'Ů', 19, N'CS');
INSERT INTO university.dbo.Student
(Sno, Sname, Ssex, Sage, Sdept)
VALUES(201215123, N'����', N'Ů', 18, N'MA');
INSERT INTO university.dbo.Student
(Sno, Sname, Ssex, Sage, Sdept)
VALUES(201215125, N'����', N'��', 19, N'IS');

create table Course
(
    Cno     bigint       not null,
    Cname  varchar(256) null,
    Cpno    bigint       null,
    Ccredit int          null,
    primary key (Cno)
);

INSERT INTO university.dbo.Course
(Cno, Cname, Cpno, Ccredit)
VALUES(1, N'���ݿ�', 5, 4);
INSERT INTO university.dbo.Course
(Cno, Cname, Cpno, Ccredit)
VALUES(2, N'��ѧ', NULL, 2);
INSERT INTO university.dbo.Course
(Cno, Cname, Cpno, Ccredit)
VALUES(3, N'��Ϣϵͳ', 1, 4);
INSERT INTO university.dbo.Course
(Cno, Cname, Cpno, Ccredit)
VALUES(4, N'����ϵͳ', 6, 3);
INSERT INTO university.dbo.Course
(Cno, Cname, Cpno, Ccredit)
VALUES(5, N'���ݽṹ', 7, 4);
INSERT INTO university.dbo.Course
(Cno, Cname, Cpno, Ccredit)
VALUES(6, N'���ݴ���', NULL, 2);
INSERT INTO university.dbo.Course
(Cno, Cname, Cpno, Ccredit)
VALUES(7, N'PASCAL����', 6, 4);

create table SC
(
    Sno   bigint        not null,
    Cno  bigint        not null,
    Grade decimal(5, 3) null
    primary key (Sno,Cno),
    foreign key (Sno) references Student,
   	foreign key (Cno) references Course);

INSERT INTO university.dbo.SC
(Sno, Cno, Grade)
VALUES(201215121, 1, 92.0);
INSERT INTO university.dbo.SC
(Sno, Cno, Grade)
VALUES(201215121, 2, 85.0);
INSERT INTO university.dbo.SC
(Sno, Cno, Grade)
VALUES(201215121, 3, 88.0);
INSERT INTO university.dbo.SC
(Sno, Cno, Grade)
VALUES(201215122, 2, 90.0);
INSERT INTO university.dbo.SC
(Sno, Cno, Grade)
VALUES(201215122, 3, 80.0);
